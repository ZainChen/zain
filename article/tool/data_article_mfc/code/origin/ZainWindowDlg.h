
// ZainWindowDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#include"../zain/data_struct_save.h"
#include"../zain/TreeData.h"


// CZainWindowDlg 对话框
class CZainWindowDlg : public CDialogEx
{
// 构造
public:
	CZainWindowDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = ZainWindow };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

//界面消息相应函数
public:
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnBnClickedBtnfullscreen();
    afx_msg void OnBnClickedBtnescfullscreen();
    afx_msg void OnBnClickedBtnoutlookclear();
    afx_msg void OnBnClickedBtnoutlooksave();

//变量
public:
    CFont m_FontListData;  //数据表字体样式
    CFont m_FontOutLook;  //输出框字体样式
    CEdit m_OutLook;  //输出框
    CTreeData m_TreeData;  // 数据树
    CListCtrl m_ListData;  //数据表

    string m_StrConfigFileName = "config.zain";  //配置文件名

    bool bInit = false;  //是否初始化完成

    ZY_DATA m_Data;  //储存所有数据库内容


//功能函数
public:
    //控件样式初始化
    bool InitEditOutLookStyle();  //初始化输出框样式
    bool InitTreeStyle();  //初始化数据树样式
    bool InitListStyle();  //初始化数据表样式
    

    //数据初始化
    bool InitConfigDataAll();  //初始化所有配置数据(根据配置文件初始化)
    bool InitTreeData();  //初始化数据树数据
    
    

    //通用功能函数
    bool GetConfigDataDFS(ZY_DATA & zdData, string strDataPath);  //根据数据库配置文件获取指定路径下所有数据
    bool ShowListData(string strDataPath);  //将指定路径下的配置文件或所有文件名显示到列表中
    bool ShowConfigListData(string strDataPath);  //将指定路径下的配置文件显示到列表中
    bool ShowPathListData(string strDataPath);  //将指定路径下所有文件名显示到列表中
    bool InitTreeDataDFS(HTREEITEM hItem, CTreeCtrl& m_TreeData, ZY_DATA zdData);  //指定节点下所有子节点初始化指定数据

    


    //zain工具函数
    void Respond(); //在循环前加上此函数防止窗口无响应
    bool EditOutLookAddText(string str);  //输出框尾加文本内容函数
    void ExpandAllNode(HTREEITEM hItem, CTreeCtrl& m_treeShow);  //展开Tree控件指定节点下所有节点
    void Gofullscreen(HWND hwnd, BOOL bfullscreen, RECT &sizerect);  //自定义屏幕缩放函数
    
    
    
};
