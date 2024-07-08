#pragma once
#include "CDeleteTab1.h"
#include "CDeleteTab2.h"
#include "CDeleteTab3.h"
#include "CDeleteTab4.h"

// DeleteDlg 대화 상자

class DeleteDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DeleteDlg)
private:
	CDeleteTab1* tab1;
	CDeleteTab2* tab2;
	CDeleteTab3* tab3;
	CDeleteTab4* tab4;
public:
	DeleteDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DeleteDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DELETE_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	CTabCtrl m_delete_tabs;
};
