#pragma once
#include "CUpdateTab1.h"
#include "CUpdateTab2.h"
#include "CUpdateTab3.h"
#include "CUpdateTab4.h"

// UpdateDlg 대화 상자

class UpdateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(UpdateDlg)
private:
	CUpdateTab1* tab1;
	CUpdateTab2* tab2;
	CUpdateTab3* tab3;
	CUpdateTab4* tab4;
public:
	UpdateDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~UpdateDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UPDATE_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CTabCtrl m_update_tabs;
	afx_msg void OnTcnSelchangeUpdateMainTab(NMHDR* pNMHDR, LRESULT* pResult);
};
