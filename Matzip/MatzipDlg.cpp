
// MatzipDlg.cpp: 구현 파일
//
#include "pch.h"
#include "framework.h"
#include "Matzip.h"
#include "MatzipDlg.h"
#include "afxdialogex.h"
#include "LoginDlg.h"
#include "CustomDlg.h"
#include "SchemaCheckDlg.h"
#include "SelectDlg.h"
#include "InsertDlg.h"
#include "DeleteDlg.h"
#include "UpdateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//ODBC API 사용을 위한 라이브러리
#pragma comment(lib, "odbc32.lib")


// CMatzipDlg 대화 상자
//CString id;
//CString pw;

//ODBC 연결을 위한 전역변수 및 함수 선언 (클래스들 모두 공유가능)
/*const char* dataSourceName = "DB_MATZIP_Server";
const char* serverId = "qwer";
const char* serverPw = "qwer";
*/
const char* dataSourceName = "DB01_Server";
const char* serverId = "KIM";
const char* serverPw = "1234";
SQLHENV hEnv = NULL;
SQLHDBC hDbc = NULL;
//const char* userid = "Yujin4";

bool db_connect() {
	SQLRETURN Ret;

	// Allocate the Environment Handle (hEnv)
	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv) != SQL_SUCCESS)
	{
		return false;
	}

	// Set attributes of the Environment Handle (hEnv)
	if (SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER) != SQL_SUCCESS)
	{
		return false;
	}

	// Allocate the Connection Handle (hDbc)
	if (SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc) != SQL_SUCCESS)
	{
		return false;
	}

	// Connect to the SQL Sever with ODBC name, ID, and PW
	Ret = SQLConnect(hDbc, (SQLCHAR*)dataSourceName, SQL_NTS, (SQLCHAR*)serverId, SQL_NTS, (SQLCHAR*)serverPw, SQL_NTS);

	if ((Ret != SQL_SUCCESS) && (Ret != SQL_SUCCESS_WITH_INFO))
	{
		return false;
	}

	return true;
}
void db_disconnect() {
	SQLDisconnect(hDbc);					// Disconnect from the SQL Server
	SQLFreeHandle(SQL_HANDLE_DBC, hDbc);	// Free the Connection Handle
	SQLFreeHandle(SQL_HANDLE_ENV, hEnv);	// Free the Environment Handle
}


CMatzipDlg::CMatzipDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MATZIP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMatzipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_DATA_LIST, data_list);
	DDX_Control(pDX, IDC_STATIC_TEXT, static_text);
}

BEGIN_MESSAGE_MAP(CMatzipDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMatzipDlg::OnBnClickedOk)
	//ON_BN_CLICKED(IDC_READ_BTN, &CMatzipDlg::OnBnClickedReadBtn)
	ON_BN_CLICKED(IDCANCEL, &CMatzipDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CUSTOM_BTN, &CMatzipDlg::OnBnClickedCustomBtn)
	ON_BN_CLICKED(IDC_SCHEMA_CHECK_BTN, &CMatzipDlg::OnBnClickedSchemaCheckBtn)
	ON_BN_CLICKED(IDC_SELECT_BTN, &CMatzipDlg::OnBnClickedSelectBtn)
	ON_BN_CLICKED(IDC_INSERT_BTN, &CMatzipDlg::OnBnClickedInsertBtn)
	ON_BN_CLICKED(IDC_DELETE_BTN, &CMatzipDlg::OnBnClickedDeleteBtn)
	ON_BN_CLICKED(IDC_UPDATE_BTN, &CMatzipDlg::OnBnClickedUpdateBtn)
END_MESSAGE_MAP()


// CMatzipDlg 메시지 처리기

BOOL CMatzipDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.


	//ODBC 연결
	if (!db_connect())
	{
		AfxMessageBox("서버 접속에 실패하여 종료합니다.");
		CDialogEx::OnCancel();
	}

	//로그인 과정 추가
	LoginDlg login;
	login.DoModal();

	CString str;
	str.Format("%s님, 맛집 리뷰 서비스 MATZIP에 오신것을 환영합니다.", userid);
	static_text.SetWindowText(str);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMatzipDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMatzipDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMatzipDlg::OnBnClickedOk()
{
	db_disconnect();
	CDialogEx::OnOK();
}

void CMatzipDlg::OnBnClickedCancel()
{
	db_disconnect();
	CDialogEx::OnCancel();
}

void CMatzipDlg::OnBnClickedCustomBtn()
{
	CustomDlg login;
	login.DoModal();
}


void CMatzipDlg::OnBnClickedSchemaCheckBtn()
{
	SchemaCheckDlg schema;
	schema.DoModal();
}


void CMatzipDlg::OnBnClickedSelectBtn()
{
	SelectDlg select;
	select.DoModal();
}


void CMatzipDlg::OnBnClickedInsertBtn()
{
	InsertDlg insert;
	insert.DoModal();
}


void CMatzipDlg::OnBnClickedDeleteBtn()
{
	DeleteDlg Delete;
	Delete.DoModal();
}


void CMatzipDlg::OnBnClickedUpdateBtn()
{
	UpdateDlg update;
	update.DoModal();
}
