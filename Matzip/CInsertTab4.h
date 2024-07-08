#pragma once


// CInsertTab4 대화 상자

class CInsertTab4 : public CDialogEx
{
	DECLARE_DYNAMIC(CInsertTab4)
private:
	CString str;
	int reviewid;
	int restid;
	int agreeid;
	char restname[30];
public:
	CInsertTab4(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CInsertTab4();
	bool insert_agree(int agreetype);
	bool search_agreeid();
	void search_restid();
	void set_button_color(int agreetype);

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INSERT_TAB4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl update4_list;
	CListCtrl insert4_list;
	afx_msg void OnBnClickedAgreeBtn();
	afx_msg void OnBnClickedNotAgreeBtn();
	afx_msg void OnBnClickedGoodBtn();
	CMFCButton agree;
	CMFCButton not_agree;
	CMFCButton good;
	afx_msg void OnBnClickedInsert4QueryBtn();
	afx_msg void OnNMDblclkInsert4List(NMHDR* pNMHDR, LRESULT* pResult);
};
