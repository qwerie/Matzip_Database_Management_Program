#pragma once
#include "CInsertTab1.h"
#include "CInsertTab2.h"
#include "CInsertTab3.h"
#include "CInsertTab4.h"

// InsertDlg 대화 상자

class InsertDlg : public CDialogEx
{
	DECLARE_DYNAMIC(InsertDlg)
private:
	CInsertTab1* tab1;
	CInsertTab2* tab2;
	CInsertTab3* tab3;
	CInsertTab4* tab4;
public:
	InsertDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~InsertDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INSERT_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_insert_tabs;
	afx_msg void OnSelchangeInsertMainTab(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
};
