#pragma once


// CInsertTab2 대화 상자

class CInsertTab2 : public CDialogEx
{
	DECLARE_DYNAMIC(CInsertTab2)
private:
	float spin_val;
	CString str;
	char restname[256];
	char rest_id[256];
	char review_id_lastnum[256];
	int myturn;

public:
	CInsertTab2(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CInsertTab2();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INSERT_TAB2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposStarSpin(NMHDR* pNMHDR, LRESULT* pResult);
	CListCtrl insert2_list;
	afx_msg void OnBnClickedInsert2QueryBtn();
	afx_msg void OnBnClickedReviewEnterBtn();
};
