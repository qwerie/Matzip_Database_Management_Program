// CSelectTab3.cpp: 구현 파일
//

#include "pch.h"
#include "Matzip.h"
#include "CSelectTab3.h"
#include "afxdialogex.h"
#include "MatzipDlg.h"


// CSelectTab3 대화 상자

IMPLEMENT_DYNAMIC(CSelectTab3, CDialogEx)

CSelectTab3::CSelectTab3(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SELECT_TAB3, pParent)
{

}

CSelectTab3::~CSelectTab3()
{
}

void CSelectTab3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, select3_list);
}


BEGIN_MESSAGE_MAP(CSelectTab3, CDialogEx)
	ON_BN_CLICKED(IDC_SELECT3_QUERY_BTN, &CSelectTab3::OnBnClickedSelect3QueryBtn)
END_MESSAGE_MAP()


// CSelectTab3 메시지 처리기


void CSelectTab3::OnBnClickedSelect3QueryBtn()
{
	select3_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	select3_list.DeleteAllItems();

	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[201];

	SQLSMALLINT colCount = -1;
	SQLCHAR data[50][31];
	SQLINTEGER nulldata[50];

	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 201, "SELECT U.USERID, S.RESTNAME, R.STAR, R.CONTENT "
			"FROM USERS U, REVIEW R, RESTAURANT S "
			"WHERE U.USERID = R.USERID AND R.RESTID = S.RESTNO AND U.USERID <> '%s' "
			"ORDER BY U.USERID DESC;",userid);

		SQLExecDirect(hStmt, query, SQL_NTS);
		SQLNumResultCols(hStmt, &colCount);
		for (int i = 0; i < colCount; ++i) {
			SQLBindCol(hStmt, i + 1, SQL_C_CHAR, data[i], sizeof(data[i]), (SQLLEN*)&nulldata[i]);
		}

		int row_item;
		//int row = 0;
		while (SQLFetch(hStmt) != SQL_NO_DATA)
		{
			//row_item = result_list.InsertItem(row, (char*)data[0]);
			row_item = select3_list.InsertItem(0, (char*)data[0]);
			for (int i = 1; i < colCount; ++i) {
				select3_list.SetItemText(row_item, i, (char*)data[i]);
			}
			//row++;
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


BOOL CSelectTab3::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (!db_connect())
	{
		AfxMessageBox("서버 접속에 실패하여 종료합니다.");
		CDialogEx::OnCancel();
	}
	//SELECT U.USERID, S.RESTNAME, R.STAR, R.CONTENT 
	select3_list.InsertColumn(0, "User ID", LVCFMT_CENTER, 100);
	select3_list.InsertColumn(1, "음식점 이름", LVCFMT_CENTER, 100);
	select3_list.InsertColumn(2, "별점", LVCFMT_CENTER, 80);
	select3_list.InsertColumn(3, "Content", LVCFMT_CENTER, 350);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
