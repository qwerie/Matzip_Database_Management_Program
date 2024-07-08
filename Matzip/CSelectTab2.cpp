// CSelectTab2.cpp: 구현 파일
//

#include "pch.h"
#include "Matzip.h"
#include "CSelectTab2.h"
#include "afxdialogex.h"
#include "MatzipDlg.h"


// CSelectTab2 대화 상자

IMPLEMENT_DYNAMIC(CSelectTab2, CDialogEx)

CSelectTab2::CSelectTab2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SELECT_TAB2, pParent)
{

}

CSelectTab2::~CSelectTab2()
{
}

void CSelectTab2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, select2_list);
}


BEGIN_MESSAGE_MAP(CSelectTab2, CDialogEx)
	ON_BN_CLICKED(IDC_SELECT2_QUERY_BTN, &CSelectTab2::OnBnClickedSelect2QueryBtn)
END_MESSAGE_MAP()


// CSelectTab2 메시지 처리기


void CSelectTab2::OnBnClickedSelect2QueryBtn()
{
	select2_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	select2_list.DeleteAllItems();

	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[201];

	SQLSMALLINT colCount = -1;
	SQLCHAR data[50][31];
	SQLINTEGER nulldata[50];

	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 201, "SELECT S.RESTNAME, AVG(R.STAR) AS AVGSTAR "
			"FROM RESTAURANT S, REVIEW R "
			"WHERE S.RESTNO = R.RESTID "
			"GROUP BY RESTNAME "
			"ORDER BY AVGSTAR DESC;");

		SQLExecDirect(hStmt, query, SQL_NTS);
		SQLNumResultCols(hStmt, &colCount);
		for (int i = 0; i < colCount; ++i) {
			SQLBindCol(hStmt, i + 1, SQL_C_CHAR, data[i], sizeof(data[i]), (SQLLEN*)&nulldata[i]);
		}

		int row_item;
		while (SQLFetch(hStmt) != SQL_NO_DATA)
		{
			row_item = select2_list.InsertItem(0, (char*)data[0]);
			for (int i = 1; i < colCount; ++i) {
				select2_list.SetItemText(row_item, i, (char*)data[i]);
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


BOOL CSelectTab2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (!db_connect())
	{
		AfxMessageBox("서버 접속에 실패하여 종료합니다.");
		CDialogEx::OnCancel();
	}
	//S.RESTNAME, AVG(R.STAR) AS AVGSTAR
	select2_list.InsertColumn(0, "음식점 이름", LVCFMT_CENTER, 200);
	select2_list.InsertColumn(1, "평균 별점", LVCFMT_CENTER, 200);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
