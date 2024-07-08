// CSelectTab6.cpp: 구현 파일
//

#include "pch.h"
#include "Matzip.h"
#include "CSelectTab6.h"
#include "afxdialogex.h"
#include "MatzipDlg.h"

// CSelectTab6 대화 상자

IMPLEMENT_DYNAMIC(CSelectTab6, CDialogEx)

CSelectTab6::CSelectTab6(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SELECT_TAB6, pParent)
{

}

CSelectTab6::~CSelectTab6()
{
}

void CSelectTab6::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SELECT6_LIST, Select6_list);
	DDX_Control(pDX, SELECT6_TEXT, Select6_text);
}


BEGIN_MESSAGE_MAP(CSelectTab6, CDialogEx)
END_MESSAGE_MAP()


// CSelectTab6 메시지 처리기


BOOL CSelectTab6::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	Select6_list.InsertColumn(0, "User ID", LVCFMT_CENTER, 70);
	Select6_list.InsertColumn(1, "즐겨찾기날짜", LVCFMT_CENTER, 120);
	Select6_list.InsertColumn(2, "식당 이름", LVCFMT_CENTER, 150);
	Select6_list.InsertColumn(3, "가격대", LVCFMT_CENTER, 70);
	Select6_list.InsertColumn(4, "영업시작", LVCFMT_CENTER, 80);
	Select6_list.InsertColumn(5, "영업종료", LVCFMT_CENTER, 80);
	Select6_list.InsertColumn(6, "유형", LVCFMT_CENTER, 60);
	Select6_list.InsertColumn(7, "전화번호", LVCFMT_CENTER, 150);
	Select6_list.InsertColumn(8, "위치", LVCFMT_CENTER, 250);
	

	str.Format("%s님의 즐겨찾기 목록", userid);
	Select6_text.SetWindowText(str);
	

	if (!db_connect())
	{
		AfxMessageBox("서버 접속에 실패하여 종료합니다.");
		return false;
	}
	Select6_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	Select6_list.DeleteAllItems();

	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[301];

	SQLSMALLINT colCount = -1;
	SQLCHAR data[50][31];
	SQLINTEGER nulldata[50];

	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
	{
			sprintf_s((char*)query, 301, "SELECT USERID, FAVDATE, S.RESTNAME, PRICE, STARTTIME, ENDTIME, T.RESTTYPE, PHONE, LOC "
				"FROM FAVORITE, RESTAURANT AS S, RESTTYPE T "
				"WHERE FAVORITE.RESTID = S.RESTNO AND S.RESTTYPENO = T.RESTTYPENO AND USERID = '%s' ORDER BY FAVDATE DESC; ", userid);

		SQLExecDirect(hStmt, query, SQL_NTS);
		SQLNumResultCols(hStmt, &colCount);
		for (int i = 0; i < colCount; ++i) {
			SQLBindCol(hStmt, i + 1, SQL_C_CHAR, data[i], sizeof(data[i]), (SQLLEN*)&nulldata[i]);
		}

		int row_item;
		while (SQLFetch(hStmt) != SQL_NO_DATA)
		{
			row_item = Select6_list.InsertItem(0, (char*)data[0]);
			for (int i = 1; i < colCount; ++i) {
				Select6_list.SetItemText(row_item, i, (char*)data[i]);
			}
		}

		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
	else {
		AfxMessageBox("오류가 발생했습니다.");
		db_disconnect();
		return false;
	}
	

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
