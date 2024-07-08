#pragma once


// CDeleteTab2 대화 상자

class CDeleteTab2 : public CDialogEx
{
	DECLARE_DYNAMIC(CDeleteTab2)

private:
	BOOL Update_listControl();
public:
	CDeleteTab2(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDeleteTab2();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DELETE_TAB2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl Delete2_list;
	afx_msg void OnBnClickedButton1();
};
