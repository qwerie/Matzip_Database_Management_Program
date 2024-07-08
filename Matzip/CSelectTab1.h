#pragma once

// CSelectTab1 대화 상자

class CSelectTab1 : public CDialogEx
{
	DECLARE_DYNAMIC(CSelectTab1)

public:
	CSelectTab1(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSelectTab1();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SELECT_TAB1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl select1_list;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSelect1QueryBtn();
};
