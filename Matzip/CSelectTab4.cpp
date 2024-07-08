// CSelectTab4.cpp: 구현 파일
//

#include "pch.h"
#include "Matzip.h"
#include "CSelectTab4.h"
#include "afxdialogex.h"
#include "LoginDlg.h"
#include "MatzipDlg.h"

LoginDlg login;

// CSelectTab4 대화 상자

IMPLEMENT_DYNAMIC(CSelectTab4, CDialogEx)

CSelectTab4::CSelectTab4(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SELECT_TAB4, pParent)
{

}

CSelectTab4::~CSelectTab4()
{
}

void CSelectTab4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSelectTab4, CDialogEx)
	ON_BN_CLICKED(IDC_LOGIN_BTN, &CSelectTab4::OnBnClickedLoginBtn)
END_MESSAGE_MAP()


// CSelectTab4 메시지 처리기


void CSelectTab4::OnBnClickedLoginBtn()
{
	GetDlgItemText(IDC_ID_EDIT, str);
	strcpy_s(id, CStringA(str).GetString());
	GetDlgItemText(IDC_PW_EDIT, str);
	strcpy_s(pw, CStringA(str).GetString());

	login.set_id(id); login.set_pw(pw);
	if (!login.try_login())
		AfxMessageBox("아이디 또는 비밀번호가 틀렸습니다.");
	else {
		str.Format("%s님, 어서오세요!", userid);
		AfxMessageBox(str);
	}
}
