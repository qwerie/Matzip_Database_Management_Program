#pragma once


// CDeleteTab4 대화 상자

class CDeleteTab4 : public CDialogEx
{
	DECLARE_DYNAMIC(CDeleteTab4)
private:
	CString str;
	int reviewid;
	int restid;
	int agreeid;
	char restname[30];
public:
	CDeleteTab4(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDeleteTab4();
	bool insert_agree(int agreetype);
	bool delete_agree();
	bool search_agreeid();
	void search_restid();
	void set_button_color(int agreetype);

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DELETE_TAB4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl delete4_list;
	CMFCButton agree;
	afx_msg void OnBnClickedNotAgreeBtn();
	CMFCButton not_agree;
	CMFCButton good;
	afx_msg void OnBnClickedAgreeBtn();
	afx_msg void OnBnClickedGoodBtn();
	afx_msg void OnBnClickedDelete4QueryBtn();
	afx_msg void OnNMDblclkDelete4List(NMHDR* pNMHDR, LRESULT* pResult);
};
