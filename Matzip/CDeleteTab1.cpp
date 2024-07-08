// CDeleteTab1.cpp: 구현 파일
//

#include "pch.h"
#include "Matzip.h"
#include "CDeleteTab1.h"
#include "afxdialogex.h"
#include "MatzipDlg.h"


// CDeleteTab1 대화 상자

IMPLEMENT_DYNAMIC(CDeleteTab1, CDialogEx)

CDeleteTab1::CDeleteTab1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DELETE_TAB1, pParent)
{

}

CDeleteTab1::~CDeleteTab1()
{
}

void CDeleteTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDeleteTab1, CDialogEx)
	ON_BN_CLICKED(IDC_DELETE_USER_BTN, &CDeleteTab1::OnBnClickedDeleteUserBtn)
END_MESSAGE_MAP()


// CDeleteTab1 메시지 처리기


BOOL CDeleteTab1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (!db_connect())
	{
		AfxMessageBox("서버 접속에 실패하여 종료합니다.");
		CDialogEx::OnCancel();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDeleteTab1::OnBnClickedDeleteUserBtn()
{
	CString str;
	GetDlgItemText(IDC_ID_EDIT, str);
	char id[256];
	strcpy_s(id, CStringA(str).GetString());
	//DELETE FROM USERS
//	WHERE USERID = 'UJ' AND PASSWORD = '1234';
	GetDlgItemText(IDC_password_EDIT, str);
	char pw[256];
	strcpy_s(pw, CStringA(str).GetString());

	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[101];
	SQLRETURN retCode;

	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 101, "DELETE FROM USERS	WHERE USERID = '%s' AND PASSWORD = '%s';", id, pw);

		retCode = SQLExecDirect(hStmt, query, SQL_NTS);
		if (retCode == SQL_ERROR || retCode == SQL_NO_DATA_FOUND)
		{
			AfxMessageBox("Query execution error!");
			CDialogEx::OnCancel();
		}
		else
			AfxMessageBox("정상적으로 반영되었습니다.");

		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
	else {
		AfxMessageBox("오류가 발생했습니다.");
		db_disconnect();
		CDialogEx::OnCancel();
	}
}
