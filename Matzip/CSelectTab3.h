#pragma once


// CSelectTab3 대화 상자

class CSelectTab3 : public CDialogEx
{
	DECLARE_DYNAMIC(CSelectTab3)

public:
	CSelectTab3(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSelectTab3();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SELECT_TAB3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl select3_list;
	afx_msg void OnBnClickedSelect3QueryBtn();
	virtual BOOL OnInitDialog();
};
