// TreeData.cpp : 实现文件
//

#include "stdafx.h"
#include "../origin/ZainWindow.h"
#include"../origin/ZainWindowDlg.h"
#include "TreeData.h"


// CTreeData

IMPLEMENT_DYNAMIC(CTreeData, CTreeCtrl)

CTreeData::CTreeData()
{

}

CTreeData::~CTreeData()
{
}


BEGIN_MESSAGE_MAP(CTreeData, CTreeCtrl)
    ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CTreeData::OnTvnSelchanged)
END_MESSAGE_MAP()



// CTreeData 消息处理程序



//左键单击树节点
void CTreeData::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

    // TODO: 在此添加控件通知处理程序代码
    CZainWindowDlg* zwdg = (CZainWindowDlg*)AfxGetApp()->GetMainWnd(); //获得主程序句柄
    HTREEITEM hTn = zwdg->m_TreeData.GetSelectedItem();
    vector<string> vecStrNodeName;
    while(hTn) {
        string strTreeValue = CStringtoString(GetItemText(hTn));
        vecStrNodeName.push_back(strTreeValue);
        hTn = GetParentItem(hTn);
    }
    string strPath = "./";
    for(int i = vecStrNodeName.size()-1; i >= 0; i--) {
        strPath += vecStrNodeName[i]+"/";
    }
    string strUtf8 = UnicodeStringToUTF8String(strPath);
    //zwdg->EditOutLookAddText(strUtf8+"\n");
    zwdg->ShowListData(strUtf8);

    *pResult = 0;
}
