// InsertDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Matzip.h"
#include "InsertDlg.h"
#include "afxdialogex.h"

// InsertDlg 대화 상자

IMPLEMENT_DYNAMIC(InsertDlg, CDialogEx)

InsertDlg::InsertDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INSERT_DLG, pParent)
{

}

InsertDlg::~InsertDlg()
{
}

void InsertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INSERT_MAIN_TAB, m_insert_tabs);
}


BEGIN_MESSAGE_MAP(InsertDlg, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_INSERT_MAIN_TAB, &InsertDlg::OnSelchangeInsertMainTab)
END_MESSAGE_MAP()


// InsertDlg 메시지 처리기


BOOL InsertDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CRect rect;
	m_insert_tabs.GetWindowRect(rect);
	m_insert_tabs.InsertItem(0, "Scenario #1");  // tab 이름
	m_insert_tabs.InsertItem(1, "Scenario #2");
	m_insert_tabs.InsertItem(2, "Scenario #3");  // tab 이름
	m_insert_tabs.InsertItem(3, "Scenario #4");
	m_insert_tabs.SetCurSel(0);

	tab1 = new CInsertTab1;
	tab1->Create(IDD_INSERT_TAB1, &m_insert_tabs);
	tab1->MoveWindow(0, 20, rect.Width(), rect.Height());
	tab1->ShowWindow(SW_SHOW);

	tab2 = new CInsertTab2;
	tab2->Create(IDD_INSERT_TAB2, &m_insert_tabs);
	tab2->MoveWindow(0, 20, rect.Width(), rect.Height());
	tab2->ShowWindow(SW_HIDE);

	tab3 = new CInsertTab3;
	tab3->Create(IDD_INSERT_TAB3, &m_insert_tabs);
	tab3->MoveWindow(0, 20, rect.Width(), rect.Height());
	tab3->ShowWindow(SW_HIDE);
	
	tab4 = new CInsertTab4;
	tab4->Create(IDD_INSERT_TAB4, &m_insert_tabs);
	tab4->MoveWindow(0, 20, rect.Width(), rect.Height());
	tab4->ShowWindow(SW_HIDE);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void InsertDlg::OnSelchangeInsertMainTab(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (IDC_INSERT_MAIN_TAB == pNMHDR->idFrom) {
		int select = m_insert_tabs.GetCurSel();
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
		}
		*pResult = 0;
	}
}

