// SelectDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Matzip.h"
#include "SelectDlg.h"
#include "afxdialogex.h"


// SelectDlg 대화 상자

IMPLEMENT_DYNAMIC(SelectDlg, CDialogEx)

SelectDlg::SelectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SELECT_DLG, pParent)
{

}

SelectDlg::~SelectDlg()
{
}

void SelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SELECT_MAIN_TAB, m_select_tabs);
}


BEGIN_MESSAGE_MAP(SelectDlg, CDialogEx)
	
	ON_NOTIFY(TCN_SELCHANGE, IDC_SELECT_MAIN_TAB, &SelectDlg::OnSelchangeSelectMainTab)
END_MESSAGE_MAP()


// SelectDlg 메시지 처리기


void SelectDlg::OnSelchangeSelectMainTab(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (IDC_SELECT_MAIN_TAB == pNMHDR->idFrom) {
		int select = m_select_tabs.GetCurSel();
		show_window(select);
		
	}
	*pResult = 0;
}

void SelectDlg::show_window(int select) {
	switch (select) {
	case 0:
		tab1->ShowWindow(SW_SHOW);
		tab2->ShowWindow(SW_HIDE);
		tab3->ShowWindow(SW_HIDE);
		tab4->ShowWindow(SW_HIDE);
		tab5->ShowWindow(SW_HIDE);
		tab6->ShowWindow(SW_HIDE);
		break;
	case 1:
		tab1->ShowWindow(SW_HIDE);
		tab2->ShowWindow(SW_SHOW);
		tab3->ShowWindow(SW_HIDE);
		tab4->ShowWindow(SW_HIDE);
		tab5->ShowWindow(SW_HIDE);
		tab6->ShowWindow(SW_HIDE);
		break;
	case 2:
		tab1->ShowWindow(SW_HIDE);
		tab2->ShowWindow(SW_HIDE);
		tab3->ShowWindow(SW_SHOW);
		tab4->ShowWindow(SW_HIDE);
		tab5->ShowWindow(SW_HIDE);
		tab6->ShowWindow(SW_HIDE);
		break;
	case 3:
		tab1->ShowWindow(SW_HIDE);
		tab2->ShowWindow(SW_HIDE);
		tab3->ShowWindow(SW_HIDE);
		tab4->ShowWindow(SW_SHOW);
		tab5->ShowWindow(SW_HIDE);
		tab6->ShowWindow(SW_HIDE);
		break;
	case 4:
		tab1->ShowWindow(SW_HIDE);
		tab2->ShowWindow(SW_HIDE);
		tab3->ShowWindow(SW_HIDE);
		tab4->ShowWindow(SW_HIDE);
		tab5->ShowWindow(SW_SHOW);
		tab6->ShowWindow(SW_HIDE);
		break;
	case 5:
		tab1->ShowWindow(SW_HIDE);
		tab2->ShowWindow(SW_HIDE);
		tab3->ShowWindow(SW_HIDE);
		tab4->ShowWindow(SW_HIDE);
		tab5->ShowWindow(SW_HIDE);
		tab6->ShowWindow(SW_SHOW);
		break;
	}
}


BOOL SelectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CRect rect;
	m_select_tabs.GetWindowRect(rect);
	m_select_tabs.InsertItem(0, "Scenario #1");  // tab 이름
	m_select_tabs.InsertItem(1, "Scenario #2");
	m_select_tabs.InsertItem(2, "Scenario #3");
	m_select_tabs.InsertItem(3, "Scenario #4");
	m_select_tabs.InsertItem(4, "Scenario #5");
	m_select_tabs.InsertItem(5, "Scenario #6");
	m_select_tabs.SetCurSel(0);

	tab1 = new CSelectTab1;
	tab1->Create(IDD_SELECT_TAB1, &m_select_tabs);
	tab1->MoveWindow(0, 20, rect.Width(), rect.Height());
	tab1->ShowWindow(SW_SHOW);

	tab2 = new CSelectTab2;
	tab2->Create(IDD_SELECT_TAB2, &m_select_tabs);
	tab2->MoveWindow(0, 20, rect.Width(), rect.Height());
	tab2->ShowWindow(SW_HIDE);

	tab3 = new CSelectTab3;
	tab3->Create(IDD_SELECT_TAB3, &m_select_tabs);
	tab3->MoveWindow(0, 20, rect.Width(), rect.Height());
	tab3->ShowWindow(SW_HIDE);

	tab4 = new CSelectTab4;
	tab4->Create(IDD_SELECT_TAB4, &m_select_tabs);
	tab4->MoveWindow(0, 20, rect.Width(), rect.Height());
	tab4->ShowWindow(SW_HIDE);

	tab5 = new CSelectTab5;
	tab5->Create(IDD_SELECT_TAB5, &m_select_tabs);
	tab5->MoveWindow(0, 20, rect.Width(), rect.Height());
	tab5->ShowWindow(SW_HIDE);

	tab6 = new CSelectTab6;
	tab6->Create(IDD_SELECT_TAB6, &m_select_tabs);
	tab6->MoveWindow(0, 20, rect.Width(), rect.Height());
	tab6->ShowWindow(SW_HIDE);


	//초기화면
	//show_window(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
