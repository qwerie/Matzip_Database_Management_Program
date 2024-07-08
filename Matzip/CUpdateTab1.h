#pragma once


// CUpdateTab1 대화 상자

class CUpdateTab1 : public CDialogEx
{
	DECLARE_DYNAMIC(CUpdateTab1)
private:
	char id[31], pw[21], name[21], birth[21], sex[5];
	CString cStr;

public:
	CUpdateTab1(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CUpdateTab1();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UPDATE_TAB1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	
	virtual BOOL OnInitDialog();
//	COleDateTime m_birth;
	CDateTimeCtrl m_birth_ctrl;
	int m_update_radio;
	afx_msg void OnBnClickedUpdateBtn();
};
