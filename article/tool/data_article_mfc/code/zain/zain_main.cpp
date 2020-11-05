#include"stdafx.h"
#include"../origin/ZainWindowDlg.h"

/*
==============================================================
控件样式初始化
==============================================================
*/
//初始化输出框样式
bool CZainWindowDlg::InitEditOutLookStyle() {
    //设置输出框件字体
    m_FontOutLook.CreatePointFont(100, UTF8StringToUnicodeString("微软雅黑").c_str());
    m_OutLook.SetFont(&m_FontOutLook);


    return true;
}

//初始化数据树样式
bool CZainWindowDlg::InitTreeStyle() {
    //m_TreeData.ModifyStyle(NULL, TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT);  //设置树形控件样式


    return true;
}

//初始化数据表样式
bool CZainWindowDlg::InitListStyle() {
    //设置列表控件字体
    m_FontListData.CreatePointFont(100, UTF8StringToUnicodeString("微软雅黑").c_str());
    m_ListData.SetFont(&m_FontListData);
    
    //设置列表控件样式
    DWORD dwListDataStyle = m_ListData.GetExtendedStyle();  //获取m_ListData样式
    dwListDataStyle |= LVS_EX_FULLROWSELECT;  //整行选中
    dwListDataStyle |= LVS_EX_GRIDLINES;  //添加网格线
    m_ListData.SetExtendedStyle(dwListDataStyle);  //样式添加到m_ListData中

    return true;
}







/*
==============================================================
数据初始化
==============================================================
*/
/*
初始化所有配置数据(根据配置文件初始化)
参数:
    无
返回值:
    bool : true|false(成功|失败)
例子:
    无
*/
bool CZainWindowDlg::InitConfigDataAll() {
    EditOutLookAddText("正在初始化所有配置数据...\n");
    if(_access(UTF8StringToUnicodeString("./"+m_StrConfigFileName).c_str(), 0) == -1) {  //第一个配置文件不存在,异常
        EditOutLookAddText("配置文件为空:./"+m_StrConfigFileName+"\n");
        return false;
    }
    bool bIcd = GetConfigDataDFS(m_Data, "./");  //初始化数据库配置
    if(!bIcd) {
        EditOutLookAddText("初始化数据库配置失败！\n");
        return false;
    }
    EditOutLookAddText("所有配置数据初始化完成.\n");
    return true;
}

//初始化数据树数据
bool CZainWindowDlg::InitTreeData() {
    HTREEITEM hRoot;
	vector<HTREEITEM> vecHroot;
    vecHroot.push_back(hRoot);
	for(int i = 0; i < m_Data.vecZdcf.size(); i++) {
        hRoot =  m_TreeData.InsertItem(m_Data.vecZdcf[i].strName.c_str(), TVI_ROOT);  //根结点
        vecHroot.push_back(hRoot);
        
        InitTreeDataDFS(hRoot, m_TreeData, m_Data.mapIdToDB[m_Data.vecZdcf[i].iId].vecVecStrDT[0]);  //指定节点下所有子节点初始化指定数据
        
        //InitTreeDataDFS(hRoot, m_TreeData, m_Data.mapIdToDB[m_Data.vecZdcf[i].iId].vecVecStrDT[0]);  //指定节点下所有子节点初始化指定数据

        ExpandAllNode(vecHroot[i+1], m_TreeData);  //展开Tree控件指定节点下所有节点
	}
    return true;
}

//将指定路径下的配置文件或所有文件名显示到列表中
bool CZainWindowDlg::ShowListData(string strDataPath) {

    bool bCon = ShowConfigListData(strDataPath);  //配置文件显示是否成功(记录)
    if(!bCon) {  //没有配置文件，为叶子节点，显示所有文件内容
        ShowPathListData(strDataPath);
    }
    
    return true;
}

//将指定路径下的配置文件显示到列表中
bool CZainWindowDlg::ShowConfigListData(string strDataPath) {

    //清空m_ListData
    while( m_ListData.DeleteColumn(0) );  //删除所有列
    m_ListData.DeleteAllItems();  //删除所有行

    strDataPath = UTF8StringToUnicodeString(strDataPath);
    if(strDataPath[strDataPath.size()-1] != '/') {
        strDataPath += "/";
    }
    vector<string> vecStrCon = FileReadUTF8ToUnicodeString(strDataPath+m_StrConfigFileName);
    if(vecStrCon.size() != 0) {  //有配置文件，非叶子节点，显示配置文件内容
        int iLine = 0;
        for(long long i = 0; i < vecStrCon.size(); i++) {
            vector<string> vecStrLines = SplitStringChar(vecStrCon[i], '\t');  //按指定字符拆分指定string字符串到容器中
            if(vecStrLines.size() == 0) {
                continue;
            } else {
                if(i == 0) {
                    iLine = vecStrLines.size();
                    m_ListData.InsertColumn(0, UTF8StringToUnicodeString("行号").c_str(), LVCFMT_LEFT, 40);  //设置每列的属性,InsertColumn(第几列，属性名，属性名的格式，列宽)
                    for(int j = 0; j < iLine; j++) {
                        vector<string> vecStrlineCon = SplitStringChar(vecStrLines[j], '|');  //按指定字符拆分指定string字符串到容器中
                        if(vecStrlineCon.size() != 3) {
                            MessageBoxUTF8String("配置文件标题格式异常!");
                            return false;
                        } else {
                            m_ListData.InsertColumn(j+1, vecStrlineCon[0].c_str(), StringToInt(vecStrlineCon[1]), StringToInt(ReplaceALLNoRepeat(vecStrlineCon[2], "\r", "")));  //设置每列的属性,InsertColumn(第几列，属性名，属性名的格式，列宽)
                        }
                    }
                } else {
                    if(vecStrLines.size() != iLine) {
                        MessageBoxUTF8String("配置文件列数不一致！");
                        return false;
                    }
                    m_ListData.InsertItem(i-1, IntToString(i).c_str());  //InsertItem(n, str)第n行第0列插入str,n从0开始
                    for(int j = 0; j < iLine; j++) {
                        m_ListData.SetItemText(i-1, j+1, vecStrLines[j].c_str());  //SetItemText(n, line, str)第n行第line列插入str,用SetItemText插入第0列元素无效
                    }
                }
            }

        }
    } else {  //有配置文件，为叶子节点，显示所有文件内容
        return false;
    }


    //设置每列的属性,InsertColumn(第几列，属性名，属性名的格式，列宽)
    //m_ListData.InsertColumn(0, "NO", LVCFMT_LEFT, 30);
    //m_ListData.InsertColumn(1, "NAME", LVCFMT_LEFT, 100);
    //m_ListData.InsertColumn(2, "PATH", LVCFMT_LEFT, 250);

    //插入数据
    //for(int i = 0; i < 100; i++) {
    //    string strNo = StringtoCString(IntToString(i));
    //    m_ListData.InsertItem(i, strNo.c_str());  //InsertItem(n, str)第n行第0列插入str,n从0开始
    //    m_ListData.SetItemText(i, 1, ("zain"+strNo).c_str());  //SetItemText(n, line, str)第n行第line列插入str,用SetItemText插入第0列元素无效
    //    m_ListData.SetItemText(i, 2, ("./志银/zain"+strNo).c_str());
    //}

    return true;
}

//将指定路径下所有文件名显示到列表中
bool CZainWindowDlg::ShowPathListData(string strDataPath) {
    //清空m_ListData
    while(m_ListData.DeleteColumn(0));  //删除所有列
    m_ListData.DeleteAllItems();  //删除所有行

    m_ListData.InsertColumn(0, UTF8StringToUnicodeString("行号").c_str(), LVCFMT_LEFT, 40);  //设置每列的属性,InsertColumn(第几列，属性名，属性名的格式，列宽)
    m_ListData.InsertColumn(1, UTF8StringToUnicodeString("文件").c_str(), LVCFMT_LEFT, 300);
    m_ListData.InsertColumn(2, UTF8StringToUnicodeString("大小").c_str(), LVCFMT_LEFT, 100);

    vector<string> files;
    getFiles(UTF8StringToUnicodeString(strDataPath), files);
    for(long long i = 0; i < files.size(); i++) {
        string strDp = ReplaceALLNoRepeat(files[i], "\\", "|");  //字符串替换(只替换一遍)
        vector<string> vecStr = SplitStringChar(strDp, '|');  //按指定字符拆分指定string字符串到容器中
        string strFilePath;
        int k = vecStr.size();
        for(int j = 1; j < k; j++) {
            strFilePath += vecStr[j];
            if(j < k-1)
                strFilePath += "/";
        }
        struct _stat info;
        _stat(files[i].c_str(), &info);
        string strFileSize = IntToString(info.st_size)+" -Byte";

        m_ListData.InsertItem(i, IntToString(i+1).c_str());  //InsertItem(n, str)第n行第0列插入str,n从0开始
        m_ListData.SetItemText(i, 1, strFilePath.c_str());  //SetItemText(n, line, str)第n行第line列插入str,用SetItemText插入第0列元素无效
        m_ListData.SetItemText(i, 2, strFileSize.c_str());  //SetItemText(n, line, str)第n行第line列插入str,用SetItemText插入第0列元素无效

        //EditOutLookAddText(strFilePath+"\n");
    }
    return true;
}


/*
根据数据库配置文件获取指定文件夹下所有数据
参数:
    ZY_DATA & zdData : 获取到的所有数据
    string strDataPath : 指定文件夹路径
返回值:
    bool : true|false(成功|失败)
例子:
    无
*/
bool CZainWindowDlg::GetConfigDataDFS(ZY_DATA & zdData, string strDataPath) {
    //EditOutLookAddText("正在初始化数据...\n");

    if(strDataPath[strDataPath.size()-1] != '/') {
        strDataPath += "/";
    }
    string strFileNamePath = strDataPath+m_StrConfigFileName;  //配置文件路径及文件名
    if(_access(UTF8StringToUnicodeString(strDataPath).c_str(), 0) == -1) {  //文件夹不存在,异常
        EditOutLookAddText("数据文件夹不存在:" + strDataPath + "\n");
        return false;
    }
    if(_access(UTF8StringToUnicodeString(strFileNamePath).c_str(), 0) == -1) {  //配置文件不存在为正常(表示数据根部文件)
        //EditOutLookAddText("文件不存在:"+strFileNamePath+"\n");
        return true;
    }

    vector<string> vecStrDBCon = FileReadToString(UTF8StringToUnicodeString(strFileNamePath));
    int iDBNum = vecStrDBCon.size();  //数据库数量
    if(iDBNum <= 1) {
        EditOutLookAddText("数据库为空:"+strFileNamePath+"\n");
        return false;
    }
    //初始化所有数据库标题属性
    vector<string> vecStrTitle = SplitStringChar(vecStrDBCon[0], '\t');
    int iTitleLineNum = vecStrTitle.size();  //标题属性数量(列数)
    if(iTitleLineNum < 3) {
        EditOutLookAddText("配置文件标题属性数量异常(最少3列):"+strFileNamePath+"\n");
        return false;
    }
    for(int i = 0; i < iTitleLineNum; i++) {
        vector<string> vecStrTs = SplitStringChar(vecStrTitle[i], '|');
        int iTitle = vecStrTs.size();
        if(iTitle != 3) {
            EditOutLookAddText("配置文件标题格式异常:"+strFileNamePath+"\n");
            return false;
        }
        ZY_DATA_TITLE_VALUE lTitle;
        lTitle.strValue = UTF8StringToUnicodeString(vecStrTs[0]);
        lTitle.iAlign = StringToInt(vecStrTs[1]);
        lTitle.iWidth = StringToInt(vecStrTs[2]);
        zdData.vecStrTitleData.push_back(lTitle);
    }
    //初始化所有数据库内容
    for(int i = 1; i < iDBNum; i++) {
        vector<string> vecStrCon = SplitStringChar(vecStrDBCon[i], '\t');
        int iConLineNum = vecStrCon.size();  //内容属性数量(列数)
        if(iConLineNum != iTitleLineNum) {
            EditOutLookAddText("配置文件内容与标题属性数量不一致:["+strFileNamePath+"]->["+vecStrDBCon[i]+"]\n");
            return false;
        }
        //储存固定属性
        ZY_DATA_CON_FIX lZdcf;
        string strPath = strDataPath+vecStrCon[1]+"/";  //此路径作为参数,解决路径字符编码问题
        lZdcf.iId = StringToInt(vecStrCon[0]);
        lZdcf.strName = UTF8StringToUnicodeString(vecStrCon[1]);
        lZdcf.strPath = UTF8StringToUnicodeString(strDataPath)+lZdcf.strName+"/";
        string strPn = UTF8StringToUnicodeString(strDataPath)+lZdcf.strName;
        if(lZdcf.strPath != UTF8StringToUnicodeString(vecStrCon[2]) && strPn != UTF8StringToUnicodeString(vecStrCon[2])) {
            EditOutLookAddText("配置文件路径属性异常:["+strFileNamePath+"]->["+vecStrDBCon[i]+"]->["+vecStrCon[2]+"]\n");
            return false;
        }
        zdData.vecZdcf.push_back(lZdcf);
        //储存完整数据
        bool bRepeat = false;  //记录固定属性值是否重复
        if(zdData.mapIdToDB[lZdcf.iId].zdcf.strName != "") {
            EditOutLookAddText("配置文件Id值重复:["+strFileNamePath+"]->["+vecStrDBCon[i]+"]->["+IntToString(lZdcf.iId)+"]\n");
            bRepeat = true;
        }
        if(zdData.mapNameToDB[lZdcf.strName].zdcf.strName != "") {
            EditOutLookAddText("配置文件Id值重复:["+strFileNamePath+"]->["+vecStrDBCon[i]+"]->["+lZdcf.strName+"]\n");
            bRepeat = true;
        }
        if(bRepeat) {
            return false;
        }
        zdData.mapIdToDB[lZdcf.iId].zdcf = lZdcf;
        for(int j = 3; j < iConLineNum; j++) {
            zdData.mapIdToDB[lZdcf.iId].vecStrCon.push_back(UTF8StringToUnicodeString(vecStrCon[j]));
        }

        ZY_DATA lzData;
        bool bIcd = GetConfigDataDFS(lzData, strPath);  //根据数据库配置文件获取指定文件夹下所有数据
        zdData.mapIdToDB[lZdcf.iId].vecVecStrDT.push_back(lzData);

        zdData.mapNameToDB[lZdcf.strName] = zdData.mapIdToDB[lZdcf.iId];
        zdData.mapPathToDB[lZdcf.strPath] = zdData.mapIdToDB[lZdcf.iId];

        if(!bIcd) {
            EditOutLookAddText("初始化数据库配置失败:"+strPath+"\n");
            return false;
        }

    }

    //EditOutLookAddText("初始化数据完成.\n");
    return true;
}

/*
指定节点下所有子节点初始化指定数据
参数:
    HTREEITEM hItem : 带添加子节点的tree
    CTreeCtrl& m_treeShow : 数据树对象
    ZY_DATA zdData : 待添加的数据
返回值:
    bool : true|false(成功|失败)
例子:
    无
*/
bool CZainWindowDlg::InitTreeDataDFS(HTREEITEM hItem, CTreeCtrl& m_TreeData, ZY_DATA zdData) {
    if(zdData.vecZdcf.size() > 0) {
        for(int i = 0; i < zdData.vecZdcf.size(); i++) {
            HTREEITEM hNode = m_TreeData.InsertItem(zdData.vecZdcf[i].strName.c_str(), hItem);  //根结点

            InitTreeDataDFS(hNode, m_TreeData, zdData.mapIdToDB[zdData.vecZdcf[i].iId].vecVecStrDT[0]);  //指定节点下所有子节点初始化指定数据

            ExpandAllNode(hNode, m_TreeData);  //展开Tree控件指定节点下所有节点
        }
    }
    return true;
}






//--------------zain工具函数--------------
//在循环前加上此函数防止窗口无响应
void CZainWindowDlg::Respond() {
    MSG msg;
    while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

//输出框尾加文本内容函数
bool CZainWindowDlg::EditOutLookAddText(string str) {
    Respond(); //在循环前加上此函数防止窗口无响应
    str = GetSystemWindowTime()+str;  //获取系统时间(精确到秒级),需要用到windows.h头文件
    CString strOutLook;
    m_OutLook.GetWindowText(strOutLook);
    if(strOutLook.GetLength() > 25000) {  //显示字符长度超过25000Byte后清空(尾加存入日志文件后清空)
        m_OutLook.SetWindowTextA("");
        EditOutLookAddText(GetSystemWindowTime() + "显示字符长度超过25000Byte，已保存到记录文件!储存目录:./ZainRecord.txt\n");
        string writeFilePathName = "./data/ZainRecord.txt";
        if(_access(writeFilePathName.c_str(), 0) == -1)
            CreatePath(writeFilePathName);  //创建文件夹(支持含子文件的文件夹)
        StringWriteToFile(writeFilePathName, CStringtoString(strOutLook), "tail");  //添加到记录文件
    }
    int nLength = m_OutLook.SendMessage(WM_GETTEXTLENGTH);
    m_OutLook.SetSel(nLength, nLength);
    m_OutLook.ReplaceSel(StringtoCString(UTF8StringToUnicodeString(str)));
    //m_OutLook.ReplaceSel(StringtoCString(str));
    return true;
}

//展开Tree控件指定节点下所有节点
void CZainWindowDlg::ExpandAllNode(HTREEITEM hItem, CTreeCtrl& m_treeShow) {
    HTREEITEM hChild = m_treeShow.GetChildItem(hItem); //获得第一个子节点
    while(hChild) {
        m_treeShow.Expand(hItem, TVE_EXPAND); //展开当前节点
        ExpandAllNode(hChild, m_treeShow); //递归展开第一个子节点下所有节点
        hChild = m_treeShow.GetNextSiblingItem(hChild); //获得第二个子节点
    }
}

//自定义屏幕缩放函数
void CZainWindowDlg::Gofullscreen(HWND hwnd, BOOL bfullscreen, RECT &sizerect)
{
    int cx, cy;
    HDC DC = ::GetDC(0);
    cx = GetDeviceCaps(DC, HORZRES)+GetSystemMetrics(SM_CXBORDER)+1;
    cy = GetDeviceCaps(DC, VERTRES)+GetSystemMetrics(SM_CYBORDER)+1;
    ::ReleaseDC(0, DC);
    if(bfullscreen)
    {
        ::GetWindowRect(hwnd, &sizerect);
        SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE)&(~WS_CAPTION|WS_BORDER));
        ::SetWindowPos(hwnd, HWND_TOPMOST, -GetSystemMetrics(SM_CXBORDER)-1, GetSystemMetrics(SM_CYBORDER)-1, cx+1, cy+1, SWP_NOZORDER);
    } else
    {
        //::GetWindowRect(hwnd, &sizerect);
        SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE)|(WS_CAPTION|WS_BORDER));
        ::SetWindowPos(hwnd, HWND_NOTOPMOST, sizerect.left, sizerect.top, sizerect.right-sizerect.left, sizerect.bottom-sizerect.top, SWP_SHOWWINDOW);
    }
}
