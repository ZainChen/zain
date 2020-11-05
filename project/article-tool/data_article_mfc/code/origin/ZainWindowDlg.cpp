
// ZainWindowDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ZainWindow.h"
#include "ZainWindowDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//全局数据控制变量
//CZainWindowDlg zwdg;

// CZainWindowDlg 对话框


CZainWindowDlg::CZainWindowDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ZainWindow, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(ZainIco);
}

void CZainWindowDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, ListData, m_ListData);
    DDX_Control(pDX, EditOutLook, m_OutLook);
    DDX_Control(pDX, TreeData, m_TreeData);
}

BEGIN_MESSAGE_MAP(CZainWindowDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_WM_CTLCOLOR()
    ON_BN_CLICKED(BtnOutLookClear, &CZainWindowDlg::OnBnClickedBtnoutlookclear)
    ON_BN_CLICKED(BtnOutLookSave, &CZainWindowDlg::OnBnClickedBtnoutlooksave)
    ON_WM_SIZE()
    ON_BN_CLICKED(BtnFullScreen, &CZainWindowDlg::OnBnClickedBtnfullscreen)
    ON_BN_CLICKED(BtnEscFullScreen, &CZainWindowDlg::OnBnClickedBtnescfullscreen)
END_MESSAGE_MAP()


// CZainWindowDlg 消息处理程序

BOOL CZainWindowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

    //SkinH_Attach();  //SkinSharp皮肤设置
    SkinH_AttachEx("./SkinSharp/skin1.she", NULL);

    InitTreeStyle();  //初始化数据树样式
    InitListStyle();  //初始化列表样式
    InitEditOutLookStyle();  //初始化输出框样式
    

    


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CZainWindowDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

    //======================数据初始化函数======================
    if(!bInit) {
        InitConfigDataAll();  //初始化所有配置数据
        InitTreeData();  //初始化数据树数据
        ShowListData("./");  //初始化数据表数据




        bInit = true;
    }
    
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CZainWindowDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//动态改变控件大小
void CZainWindowDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialogEx::OnSize(nType, cx, cy);

    // TODO: 在此处添加消息处理程序代码
    CWnd* pWndEol = GetDlgItem(EditOutLook);
    if(pWndEol->GetSafeHwnd()) {
        pWndEol->MoveWindow(0, cy-130, cx, 130);
    }
    CWnd* pWndLd = GetDlgItem(ListData);
    if(pWndLd->GetSafeHwnd()) {
        pWndLd->MoveWindow(260, 20, cx-260, cy-150);
    }
    CWnd* pWndTd = GetDlgItem(TreeData);
    if(pWndTd->GetSafeHwnd()) {
        pWndTd->MoveWindow(0, 20, 260, cy-180);
    }
    CWnd* pWndBfs = GetDlgItem(BtnFullScreen);
    if(pWndBfs->GetSafeHwnd()) {
        pWndBfs->MoveWindow(cx-60, 0, 30, 20);
    }
    CWnd* pWndBefs = GetDlgItem(BtnEscFullScreen);
    if(pWndBefs->GetSafeHwnd()) {
        pWndBefs->MoveWindow(cx-30, 0, 30, 20);
    }
    CWnd* pWndBolc = GetDlgItem(BtnOutLookClear);
    if(pWndBolc->GetSafeHwnd()) {
        pWndBolc->MoveWindow(0, cy-160, 130, 30);
    }
    CWnd* pWndBols = GetDlgItem(BtnOutLookSave);
    if(pWndBols->GetSafeHwnd()) {
        pWndBols->MoveWindow(130, cy-160, 130, 30);
    }

    
        
}

void CZainWindowDlg::OnBnClickedBtnfullscreen()
{
    // TODO: 在此添加控件通知处理程序代码
    RECT sizerect;
    BOOL bfullscreen = TRUE;
    Gofullscreen(m_hWnd, bfullscreen, sizerect);
}

void CZainWindowDlg::OnBnClickedBtnescfullscreen()
{
    // TODO: 在此添加控件通知处理程序代码
    RECT sizerect;
    sizerect.top = 150;
    sizerect.bottom = 850;
    sizerect.left = 450;
    sizerect.right = 1450;
    BOOL bfullscreen = FALSE;
    Gofullscreen(m_hWnd, bfullscreen, sizerect);
}

void CZainWindowDlg::OnBnClickedBtnoutlookclear()
{
    // TODO: 在此添加控件通知处理程序代码
    m_OutLook.SetWindowText("");
}


void CZainWindowDlg::OnBnClickedBtnoutlooksave()
{
    // TODO: 在此添加控件通知处理程序代码
    CString strOutLook;
    m_OutLook.GetWindowText(strOutLook);
    m_OutLook.SetWindowText("");
    string writeFilePath = "./data/";
    if(_access(writeFilePath.c_str(), 0) == -1)
        CreatePath(writeFilePath);  //创建文件夹(支持含子文件的文件夹)
    string writeFilePathName = "./data/ZainRecord.txt";
    EditOutLookAddText("已保存到记录文件!储存目录:"+ writeFilePathName +"\n");
    UnicodeToUTF8StringWriteToFile(writeFilePathName, CStringtoString(strOutLook), "tail");  //添加到记录文件
}







