#pragma once
//ODBC 이용을 위한 헤더파일
#include <odbcinst.h>
#include <sqlext.h>

// CustomDlg 대화 상자

class CustomDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CustomDlg)
private:
	CString str;
	SQLSMALLINT colCount = -1;
public:
	CustomDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CustomDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CUSTOM_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

//	CListBox result_list;
	afx_msg void OnBnClickedQueryBtn();
	CListCtrl result_list;
};
