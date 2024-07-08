// CInsertTab1.cpp: 구현 파일
//

#include "pch.h"
#include "Matzip.h"
#include "CInsertTab1.h"
#include "afxdialogex.h"
#include "MatzipDlg.h"


// CInsertTab1 대화 상자

IMPLEMENT_DYNAMIC(CInsertTab1, CDialogEx)

CInsertTab1::CInsertTab1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INSERT_TAB1, pParent)
	, radio1(0)
{

}

CInsertTab1::~CInsertTab1()
{
}

void CInsertTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_MALE_RADIO, radio1);
	DDX_Control(pDX, IDC_BIRTH_DATE, m_birth);
}


BEGIN_MESSAGE_MAP(CInsertTab1, CDialogEx)
	ON_BN_CLICKED(IDC_REGISTER_BTN, &CInsertTab1::OnBnClickedRegisterBtn)
END_MESSAGE_MAP()


// CInsertTab1 메시지 처리기


void CInsertTab1::OnBnClickedRegisterBtn()
{
	CString str;
	GetDlgItemText(IDC_ID_EDIT, str);
	char id[256];
	strcpy_s(id, CStringA(str).GetString());
	GetDlgItemText(IDC_PW_EDIT, str);
	char pw[256];
	strcpy_s(pw, CStringA(str).GetString());
	GetDlgItemText(IDC_PW_EDIT, str);
	char pw2[256];
	strcpy_s(pw2, CStringA(str).GetString());
	GetDlgItemText(IDC_NAME_EDIT, str);
	char name[256];
	strcpy_s(name, CStringA(str).GetString());

	CTime birth_date;
	int year, month, day;
	m_birth.GetTime(birth_date);
	year = birth_date.GetYear();
	month = birth_date.GetMonth();
	day = birth_date.GetDay();
	
	UpdateData(true); //radio1=0 : 0(남자)

	
	if (!strcmp(pw, pw2)) {
		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[101];
		SQLRETURN retCode;

		if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 101, "INSERT INTO USERS VALUES('%s','%s','%s','%4d-%02d-%02d',%d);", id, pw, name, year, month, day, radio1);

			retCode = SQLExecDirect(hStmt, query, SQL_NTS);
			if (retCode == SQL_ERROR || retCode == SQL_NO_DATA_FOUND)
			{
				AfxMessageBox("Query execution error!");
				CDialogEx::OnCancel();
			}
			else
				AfxMessageBox("정상적으로 반영되었습니다.");
			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		}
		else {
			AfxMessageBox("오류가 발생했습니다.");
			db_disconnect();
			CDialogEx::OnCancel();
		}
	}
	else {
		AfxMessageBox("비밀번호가 서로 다릅니다.\n다시 입력해주세요.");
	}
}


BOOL CInsertTab1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (!db_connect())
	{
		AfxMessageBox("서버 접속에 실패하여 종료합니다.");
		CDialogEx::OnCancel();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
