#pragma once


// CSelectTab4 대화 상자

class CSelectTab4 : public CDialogEx
{
	DECLARE_DYNAMIC(CSelectTab4)
private:
	char id[256];
	char pw[256];
	CString str;
public:
	CSelectTab4(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSelectTab4();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SELECT_TAB4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLoginBtn();
};
