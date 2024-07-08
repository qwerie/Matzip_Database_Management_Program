#pragma once
#include "CSelectTab1.h"
#include "CSelectTab2.h"
#include "CSelectTab3.h"
#include "CSelectTab4.h"
#include "CSelectTab5.h"
#include "CSelectTab6.h"

// SelectDlg 대화 상자

class SelectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SelectDlg)

private:
	CSelectTab1* tab1;
	CSelectTab2* tab2;
	CSelectTab3* tab3;
	CSelectTab4* tab4;
	CSelectTab5* tab5;
	CSelectTab6* tab6;
public:
	SelectDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SelectDlg();
	void show_window(int select);

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SELECT_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_select_tabs;
	afx_msg void OnSelchangeSelectMainTab(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
};
