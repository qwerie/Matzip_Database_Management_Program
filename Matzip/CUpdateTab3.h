#pragma once


// CUpdateTab3 대화 상자

class CUpdateTab3 : public CDialogEx
{
	DECLARE_DYNAMIC(CUpdateTab3)
private:
	CString str;
	int restid;
public:
	CUpdateTab3(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CUpdateTab3();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UPDATE_TAB3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl update3_list;
	afx_msg void OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedUpdateBtn();
};
