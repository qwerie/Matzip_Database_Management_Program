
// MatzipDlg.h: 헤더 파일
//

#pragma once

//ODBC 이용을 위한 헤더파일
#include <odbcinst.h>
#include <sqlext.h>

extern SQLHENV hEnv; // Environment Handle
extern SQLHDBC hDbc; // Connection Handle
extern const char* dataSourceName;
extern const char* serverId;
extern const char* serverPw;

extern bool db_connect();
extern void db_disconnect();

extern char userid[256]; //전체 로그인 계정-> 임시로 cpp 파일에 정의해놓겠음.
extern char userpw[256];
// CMatzipDlg 대화 상자
class CMatzipDlg : public CDialogEx
{
// 생성입니다.

public:
	CMatzipDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	//BOOL CMatzipDlg::try_login();

	/*SQLHDBC	get_hDbc() {
		return hDbc;
	}*/

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MATZIP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	//CListBox data_list;
	//afx_msg void OnBnClickedReadBtn();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedCustomBtn();
	afx_msg void OnBnClickedSchemaCheckBtn();
	afx_msg void OnBnClickedSelectBtn();
	afx_msg void OnBnClickedInsertBtn();
	afx_msg void OnBnClickedDeleteBtn();
	afx_msg void OnBnClickedUpdateBtn();
	CStatic static_text;
};
