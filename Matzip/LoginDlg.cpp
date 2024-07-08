// LoginDlg.cpp: 구현 파일
//
#include "pch.h"
#include "Matzip.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "afx.h"
#include "InsertDlg.h"
#include "MatzipDlg.h"

char userid[256];
char userpw[256];
// LoginDlg 대화 상자

IMPLEMENT_DYNAMIC(LoginDlg, CDialogEx)

LoginDlg::LoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGIN_DLG, pParent)
{

}

LoginDlg::~LoginDlg()
{
}

void LoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(LoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_REGISTER_BUTTON, &LoginDlg::OnBnClickedRegisterButton)
	ON_BN_CLICKED(IDC_LOGIN_BTN, &LoginDlg::OnBnClickedLoginBtn)
	ON_BN_CLICKED(IDC_ADMIN_BTN, &LoginDlg::OnBnClickedAdminBtn)
END_MESSAGE_MAP()


// LoginDlg 메시지 처리기

void LoginDlg::OnBnClickedRegisterButton()
{
	InsertDlg register1;
	register1.DoModal();
}

void LoginDlg::OnBnClickedLoginBtn()
{
	GetDlgItemText(IDC_ID_EDIT, str);
	strcpy_s(id, CStringA(str).GetString());
	GetDlgItemText(IDC_PW_EDIT, str);
	strcpy_s(pw, CStringA(str).GetString());

	if (!try_login())
		AfxMessageBox("아이디 또는 비밀번호가 틀렸습니다.");
	else {
		str.Format("%s님, 어서오세요!", userid);
		AfxMessageBox(str);
		db_disconnect();
		CDialogEx::OnOK();
	}
}

BOOL LoginDlg::try_login() {
	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[101];

	SQLCHAR temp_pw[31];
	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
	{


		sprintf_s((char*)query, 101, "SELECT USERID FROM USERS WHERE USERID='%s' AND PASSWORD='%s'", id, pw);

		SQLExecDirect(hStmt, query, SQL_NTS);

		SQLBindCol(hStmt, 1, SQL_C_CHAR, temp_pw, sizeof(temp_pw), NULL);

		if (SQLFetch(hStmt) != SQL_NO_DATA) {
			strcpy_s(userid, id);
			strcpy_s(userpw, pw); 
			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
			return true;
		}
		else {
			return false;
		}

		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
	else {
		AfxMessageBox("오류가 발생했습니다.");

		return false;
	}
}

void LoginDlg::OnBnClickedAdminBtn()
{
	strcpy_s(userid, "Yujin1");
	strcpy_s(userpw, "1234");
	CDialogEx::OnOK();
}
