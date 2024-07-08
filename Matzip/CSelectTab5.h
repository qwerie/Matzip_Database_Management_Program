#pragma once


// CSelectTab5 대화 상자

class CSelectTab5 : public CDialogEx
{
	DECLARE_DYNAMIC(CSelectTab5)

private:
	BOOL Update_listControl(char* restname="NULL");
	CString str;
public:
	CSelectTab5(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSelectTab5();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SELECT_TAB5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl Select5_list;
	afx_msg void OnBnClickedSelect5QueryBtn();
	afx_msg void OnBnClickedReturnBtn();
};
