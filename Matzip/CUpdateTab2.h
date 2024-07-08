#pragma once


// CUpdateTab2 대화 상자

class CUpdateTab2 : public CDialogEx
{
	DECLARE_DYNAMIC(CUpdateTab2)
private:
	float spin_val;
	CString str;
	char restid[256], reviewid[256];
public:
	CUpdateTab2(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CUpdateTab2();
	BOOL Update_listControl();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UPDATE_TAB2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
//	CListCtrl update_list1;
	CListCtrl update2_list;
	afx_msg void OnDeltaposStarSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedReviewEnterBtn();
	afx_msg void OnBnClickedUpdate2QueryBtn();
};
