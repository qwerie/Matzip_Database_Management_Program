#pragma once


// CInsertTab1 대화 상자

class CInsertTab1 : public CDialogEx
{
	DECLARE_DYNAMIC(CInsertTab1)

public:
	CInsertTab1(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CInsertTab1();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INSERT_TAB1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRegisterBtn();
	virtual BOOL OnInitDialog();
	int radio1;
	CDateTimeCtrl m_birth;
};
