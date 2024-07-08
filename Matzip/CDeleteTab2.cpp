// CDeleteTab2.cpp: 구현 파일
//

#include "pch.h"
#include "Matzip.h"
#include "CDeleteTab2.h"
#include "afxdialogex.h"
#include "MatzipDlg.h"


// CDeleteTab2 대화 상자

IMPLEMENT_DYNAMIC(CDeleteTab2, CDialogEx)

CDeleteTab2::CDeleteTab2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DELETE_TAB2, pParent)
{

}

CDeleteTab2::~CDeleteTab2()
{
}

void CDeleteTab2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DELETE2_LIST, Delete2_list);
}


BEGIN_MESSAGE_MAP(CDeleteTab2, CDialogEx)
	
	ON_BN_CLICKED(IDC_BUTTON1, &CDeleteTab2::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDeleteTab2 메시지 처리기

BOOL CDeleteTab2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	Delete2_list.InsertColumn(0, "User ID", LVCFMT_CENTER, 70);
	Delete2_list.InsertColumn(1, "식당 ID", LVCFMT_CENTER, 70);
	Delete2_list.InsertColumn(2, "Review ID", LVCFMT_CENTER, 85);
	Delete2_list.InsertColumn(3, "음식점 이름", LVCFMT_CENTER, 150);
	Delete2_list.InsertColumn(4, "별점", LVCFMT_CENTER, 50);
	Delete2_list.InsertColumn(5, "Content", LVCFMT_CENTER, 240);
	
	if (!Update_listControl()) {
		AfxMessageBox("데이터를 불러오는 과정에서 오류가 발생했습니다.");
		CDialogEx::OnCancel();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDeleteTab2::OnBnClickedButton1()
{
	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[201];

	SQLSMALLINT colCount = -1;
	SQLRETURN retCode;

	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
	{
		CString str;
		char restid[256], reviewid[256];
		GetDlgItemText(IDC_DELETE_RESTID_EDIT, str);
		strcpy_s(restid, CStringA(str).GetString());
		GetDlgItemText(IDC_DELETE_REVIEWID_EDIT, str);
		strcpy_s(reviewid, CStringA(str).GetString());
		sprintf_s((char*)query, 201, "DELETE FROM REVIEW "
			"WHERE USERID = '%s' AND RESTID = %s AND REVIEWID = %s;", userid, restid, reviewid);
		
		retCode = SQLExecDirect(hStmt, query, SQL_NTS);
		if (retCode == SQL_ERROR || retCode == SQL_NO_DATA_FOUND)
		{
			AfxMessageBox("Query execution error!");
			CDialogEx::OnCancel();
		}
		else {
			AfxMessageBox("정상적으로 반영되었습니다.");
			if (!Update_listControl()) {
				AfxMessageBox("데이터를 불러오는 과정에서 오류가 발생했습니다.");
				CDialogEx::OnCancel();
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

BOOL CDeleteTab2::Update_listControl() {
	if (!db_connect())
	{
		AfxMessageBox("서버 접속에 실패하여 종료합니다.");
		return false;
	}
	Delete2_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	Delete2_list.DeleteAllItems();

	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[201];

	SQLSMALLINT colCount = -1;
	SQLCHAR data[50][31];
	SQLINTEGER nulldata[50];

	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 201, "SELECT USERID, RESTID, REVIEWID, S.RESTNAME, STAR, CONTENT "
			"FROM REVIEW R, RESTAURANT S "
			"WHERE R.RESTID = S.RESTNO AND USERID = '%s';",userid);
		//DELETE FROM REVIEW
		//WHERE USERID = 'Yujin4' AND RESTID = 15 AND REVIEWID = 3;
		SQLExecDirect(hStmt, query, SQL_NTS);
		SQLNumResultCols(hStmt, &colCount);
		for (int i = 0; i < colCount; ++i) {
			SQLBindCol(hStmt, i + 1, SQL_C_CHAR, data[i], sizeof(data[i]), (SQLLEN*)&nulldata[i]);
		}

		int row_item;
		while (SQLFetch(hStmt) != SQL_NO_DATA)
		{
			row_item = Delete2_list.InsertItem(0, (char*)data[0]);
			for (int i = 1; i < colCount; ++i) {
				Delete2_list.SetItemText(row_item, i, (char*)data[i]);
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

	return true;
}

