#pragma once


// CSelectTab6 대화 상자

class CSelectTab6 : public CDialogEx
{
	DECLARE_DYNAMIC(CSelectTab6)
private:
	CString str;
public:
	CSelectTab6(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSelectTab6();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SELECT_TAB6 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl Select6_list;
	CStatic Select6_text;
};
