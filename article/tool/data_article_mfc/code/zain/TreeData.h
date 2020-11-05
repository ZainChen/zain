#pragma once

// CTreeData

class CTreeData : public CTreeCtrl
{
	DECLARE_DYNAMIC(CTreeData)

public:
	CTreeData();
	virtual ~CTreeData();

protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
};


