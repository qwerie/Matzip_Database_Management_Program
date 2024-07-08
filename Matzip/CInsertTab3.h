#pragma once


// CInsertTab3 대화 상자

class CInsertTab3 : public CDialogEx
{
	DECLARE_DYNAMIC(CInsertTab3)
private:
	CString str;
	int restid;
public:
	CInsertTab3(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CInsertTab3();
	bool find_restid(CString restname);
	bool insert_fav();
	int is_in_fav();
	bool update_fav_list();
	bool update_rest_list();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INSERT_TAB3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl insert3_list;
	CListCtrl fav_list;
	virtual BOOL OnInitDialog();
	afx_msg void OnNMDblclkRestList(NMHDR* pNMHDR, LRESULT* pResult);
};
