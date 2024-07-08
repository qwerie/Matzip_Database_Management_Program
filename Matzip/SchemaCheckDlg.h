#pragma once

//ODBC 이용을 위한 헤더파일
#include <sqlext.h>

// SchemaCheckDlg 대화 상자

class SchemaCheckDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SchemaCheckDlg)
private:
	const char* get_data_type_in_string(SQLSMALLINT dataType);
public:
	SchemaCheckDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SchemaCheckDlg();
	
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCHEMA_CHECK_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
private:
	CComboBox m_combo;
public:
	afx_msg void OnCbnSelchangeTableCombo();
	CString m_combo_str;
	CListCtrl Schema_list;
};
