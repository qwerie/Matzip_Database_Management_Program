// UpdateDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Matzip.h"
#include "UpdateDlg.h"
#include "afxdialogex.h"


// UpdateDlg 대화 상자

IMPLEMENT_DYNAMIC(UpdateDlg, CDialogEx)

UpdateDlg::UpdateDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UPDATE_DLG, pParent)
{

}

UpdateDlg::~UpdateDlg()
{
}

void UpdateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_UPDATE_MAIN_TAB, m_update_tabs);
}


BEGIN_MESSAGE_MAP(UpdateDlg, CDialogEx)

	ON_NOTIFY(TCN_SELCHANGE, IDC_UPDATE_MAIN_TAB, &UpdateDlg::OnTcnSelchangeUpdateMainTab)
END_MESSAGE_MAP()


// UpdateDlg 메시지 처리기


BOOL UpdateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CRect rect;
	m_update_tabs.GetWindowRect(rect);
	m_update_tabs.InsertItem(0, "Scenario #1");  // tab 이름
	m_update_tabs.InsertItem(1, "Scenario #2");
	m_update_tabs.InsertItem(2, "Scenario #3");
	m_update_tabs.InsertItem(3, "Scenario #4");
	m_update_tabs.SetCurSel(0);
	
	tab1 = new CUpdateTab1;
	tab1->Create(IDD_UPDATE_TAB1, &m_update_tabs);
	tab1->MoveWindow(0, 20, rect.Width(), rect.Height());
	tab1->ShowWindow(SW_SHOW);

	tab2 = new CUpdateTab2;
	tab2->Create(IDD_UPDATE_TAB2, &m_update_tabs);
	tab2->MoveWindow(0, 20, rect.Width(), rect.Height());
	tab2->ShowWindow(SW_HIDE);

	tab3 = new CUpdateTab3;
	tab3->Create(IDD_UPDATE_TAB3, &m_update_tabs);
	tab3->MoveWindow(0, 20, rect.Width(), rect.Height());
	tab3->ShowWindow(SW_HIDE);

	tab4 = new CUpdateTab4;
	tab4->Create(IDD_UPDATE_TAB4, &m_update_tabs);
	tab4->MoveWindow(0, 20, rect.Width(), rect.Height());
	tab4->ShowWindow(SW_HIDE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void UpdateDlg::OnTcnSelchangeUpdateMainTab(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (IDC_UPDATE_MAIN_TAB == pNMHDR->idFrom) {
		int select = m_update_tabs.GetCurSel();
		switch (select) {
		case 0:
			tab1->ShowWindow(SW_SHOW);
			tab2->ShowWindow(SW_HIDE);
			tab3->ShowWindow(SW_HIDE);
			tab4->ShowWindow(SW_HIDE);
			break;
		case 1:
			tab1->ShowWindow(SW_HIDE);
			tab2->ShowWindow(SW_SHOW);
			tab3->ShowWindow(SW_HIDE);
			tab4->ShowWindow(SW_HIDE);
			break;
		case 2:
			tab1->ShowWindow(SW_HIDE);
			tab2->ShowWindow(SW_HIDE);
			tab3->ShowWindow(SW_SHOW);
			tab4->ShowWindow(SW_HIDE);
			break;
		case 3:
			tab1->ShowWindow(SW_HIDE);
			tab2->ShowWindow(SW_HIDE);
			tab3->ShowWindow(SW_HIDE);
			tab4->ShowWindow(SW_SHOW);
			break;
			*pResult = 0;
		}
	}
}
