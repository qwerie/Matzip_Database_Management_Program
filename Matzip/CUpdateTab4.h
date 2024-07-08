#pragma once


// CUpdateTab4 대화 상자

class CUpdateTab4 : public CDialogEx
{
	DECLARE_DYNAMIC(CUpdateTab4)
private: 	
	CString str;
	int reviewid;
	int restid;
	int agreeid;
	char restname[30];
public:
	CUpdateTab4(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CUpdateTab4();
	bool insert_agree(int agreetype);
	bool delete_agree();
	bool update_agree(int agreetype);
	bool search_agreeid();
	void search_restid();
	void set_button_color(int agreetype);

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UPDATE_TAB4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl update4_list;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedUpdate4QueryBtn();
	afx_msg void OnNMDblclkUpdate4List(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedAgreeBtn();
//	CButton agree;
//	CButton not_agree;
//	CButton good;
	CMFCButton agree;
	afx_msg void OnBnClickedMfcbutton3();
	CMFCButton not_agree;
	CMFCButton good;
	afx_msg void OnBnClickedNotAgreeBtn();
	afx_msg void OnBnClickedGoodBtn();
};
