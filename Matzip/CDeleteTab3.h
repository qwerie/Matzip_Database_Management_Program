#pragma once


// CDeleteTab3 대화 상자

class CDeleteTab3 : public CDialogEx
{
	DECLARE_DYNAMIC(CDeleteTab3)
private:
	CString str;
	int restid;
public:
	CDeleteTab3(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDeleteTab3();
	bool find_restid(CString restname);
	bool insert_fav();
	bool delete_fav();
	int is_in_fav();
	bool update_fav_list();
	bool update_rest_list();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DELETE_TAB3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl delete3_list;
	CListCtrl fav_list;
	virtual BOOL OnInitDialog();
	afx_msg void OnNMDblclkRestList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMDblclkFavList(NMHDR* pNMHDR, LRESULT* pResult);
};
