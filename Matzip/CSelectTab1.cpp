// CSelectTab1.cpp: 구현 파일
//

#include "pch.h"
#include "Matzip.h"
#include "CSelectTab1.h"
#include "afxdialogex.h"
#include "MatzipDlg.h"


// CSelectTab1 대화 상자

IMPLEMENT_DYNAMIC(CSelectTab1, CDialogEx)


CSelectTab1::CSelectTab1(CWnd* pParent /*=nullptr*/)
: CDialogEx(IDD_SELECT_TAB1, pParent)
{

}

CSelectTab1::~CSelectTab1()
{
}

void CSelectTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SELECT1_LIST, select1_list);
}


BEGIN_MESSAGE_MAP(CSelectTab1, CDialogEx)
	ON_BN_CLICKED(IDC_SELECT1_QUERY_BTN, &CSelectTab1::OnBnClickedSelect1QueryBtn)
END_MESSAGE_MAP()


// CSelectTab1 메시지 처리기


BOOL CSelectTab1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (!db_connect())
	{
		AfxMessageBox("서버 접속에 실패하여 종료합니다.");
		CDialogEx::OnCancel();
	}

	select1_list.InsertColumn(0, "음식점 이름", LVCFMT_CENTER, 100);
	select1_list.InsertColumn(1, "User ID", LVCFMT_CENTER, 100);
	select1_list.InsertColumn(2, "별점", LVCFMT_CENTER, 80);
	select1_list.InsertColumn(3, "Content", LVCFMT_CENTER, 350);
	

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CSelectTab1::OnBnClickedSelect1QueryBtn()
{
	select1_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	select1_list.DeleteAllItems();

	CString str;
	GetDlgItemText(IDC_RESTNAME_EDIT, str);
	char* st = LPSTR(LPCTSTR(str));

	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[201];

	SQLSMALLINT colCount = -1;
	SQLCHAR data[50][31];
	SQLINTEGER nulldata[50];

	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 201,"SELECT S.RESTNAME, USERID, STAR, CONTENT "
			"FROM REVIEW R, RESTAURANT S "
			"WHERE R.RESTID = S.RESTNO AND S.RESTNAME = '%s';",st);   

		SQLExecDirect(hStmt, query, SQL_NTS);
		SQLNumResultCols(hStmt, &colCount);
		for (int i = 0; i < colCount; ++i) {
			SQLBindCol(hStmt, i + 1, SQL_C_CHAR, data[i], sizeof(data[i]), (SQLLEN*)&nulldata[i]);
		}

		int row_item;
		while (SQLFetch(hStmt) != SQL_NO_DATA)
		{
			row_item = select1_list.InsertItem(0, (char*)data[0]);
			for (int i = 1; i < colCount; ++i) {
				select1_list.SetItemText(row_item, i, (char*)data[i]);
			}
		}

		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
	else {
		AfxMessageBox("오류가 발생했습니다.");
		db_disconnect();
		CDialogEx::OnCancel();
	}
}
