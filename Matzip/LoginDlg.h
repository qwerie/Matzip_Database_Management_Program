#pragma once


// LoginDlg 대화 상자

class LoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(LoginDlg)
private:
	char id[256];
	char pw[256];
	CString str;

public:
	LoginDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~LoginDlg();
	void set_id(char* str) {
		strcpy_s(id, str);
	}
	void set_pw(char* str) {
		strcpy_s(pw, str);
	}

	/*CString get_id() {
		return id;
	}
	CString get_pw() {
		return pw;
	}*/
	BOOL LoginDlg::try_login();


// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRegisterButton();
	afx_msg void OnBnClickedLoginBtn();
	afx_msg void OnBnClickedAdminBtn();
};
