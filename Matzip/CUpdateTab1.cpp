// CUpdateTab1.cpp: 구현 파일
//

#include "pch.h"
#include "Matzip.h"
#include "CUpdateTab1.h"
#include "afxdialogex.h"
#include "MatzipDlg.h"
#include <string>


// CUpdateTab1 대화 상자

IMPLEMENT_DYNAMIC(CUpdateTab1, CDialogEx)
CUpdateTab1::CUpdateTab1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UPDATE_TAB1, pParent)
	//, m_birth(COleDateTime::GetCurrentTime())
	, m_update_radio(0)
{

}

CUpdateTab1::~CUpdateTab1()
{
}

void CUpdateTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_DateTimeCtrl(pDX, IDC_UPDATE_BIRTH_PICKER, m_birth);
	DDX_Control(pDX, IDC_UPDATE_BIRTH_PICKER, m_birth_ctrl);
	DDX_Radio(pDX, IDC_UPDATE_MALE_RADIO, m_update_radio);
}


BEGIN_MESSAGE_MAP(CUpdateTab1, CDialogEx)

	ON_BN_CLICKED(IDC_UPDATE_BTN, &CUpdateTab1::OnBnClickedUpdateBtn)
END_MESSAGE_MAP()


// CUpdateTab1 메시지 처리기



BOOL CUpdateTab1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (!db_connect())
	{
		AfxMessageBox("서버 접속에 실패하여 종료합니다.");
		CDialogEx::OnCancel();
	}

	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[101];

	SQLSMALLINT colCount = -1;
	SQLCHAR ID[31], PW[21], NAME[21], BIRTH[21], SEX[5];

	//SQLINTEGER nulldata[50];


	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 101, "SELECT * FROM USERS WHERE USERID='%s';",userid);

		SQLExecDirect(hStmt, query, SQL_NTS);

		SQLBindCol(hStmt, 1, SQL_C_CHAR, ID, sizeof(ID), NULL);
		SQLBindCol(hStmt, 2, SQL_C_CHAR, PW, sizeof(PW), NULL);
		SQLBindCol(hStmt, 3, SQL_C_CHAR, NAME, sizeof(NAME), NULL);
		SQLBindCol(hStmt, 4, SQL_C_CHAR, BIRTH, sizeof(BIRTH), NULL);
		SQLBindCol(hStmt, 5, SQL_C_CHAR, SEX, sizeof(SEX), NULL);


		while (SQLFetch(hStmt) != SQL_NO_DATA)
		{
			strcpy_s(id, (char*)ID);
			strcpy_s(pw, (char*)PW);
			strcpy_s(name, (char*)NAME);
			strcpy_s(birth, (char*)BIRTH);
			strcpy_s(sex, (char*)SEX);
		}

		SetDlgItemText(IDC_UPDATE_ID_EDIT, id);
		SetDlgItemText(IDC_UPDATE_PW_EDIT, pw);
		SetDlgItemText(IDC_UPDATE_NAME_EDIT, name);

		
		// 날짜 세팅과정 (char* -> Cstring -> string -> int)
		cStr.Format("%s", birth);
		CT2CA convertedString(cStr);
		std::string str = std::string(convertedString);

		std::string year = str.substr(0, 4);
		std::string month = str.substr(5, 2);
		std::string day = str.substr(8, 2);
		/*
		//COleDateTime date_temp = COleDateTime(stoi(year), stoi(month), stoi(day), 0, 0, 0);
		CTime date_temp = CTime(stoi(year), stoi(month), stoi(day), 0, 0, 0);
		m_birth_ctrl.SetTime(&date_temp);
		*/

		SYSTEMTIME sysTime;
		memset(&sysTime, 0, sizeof(sysTime));
		sysTime.wYear = stoi(year);
		sysTime.wMonth = stoi(month);
		sysTime.wDay = stoi(day);
		m_birth_ctrl.SetTime(&sysTime);

		cStr.Format("%d", sex[0] - '0');

		m_update_radio = sex[0] - '0'; //char to int
		UpdateData(false);

		//SetDlgItemText(IDC_UPDATE_ID_EDIT, userid);
		//SetDlgItemText(IDC_UPDATE_ID_EDIT, userid);

		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
	else {
		AfxMessageBox("데이터 불러들이기에 실패하였습니다.");
		db_disconnect();
		CDialogEx::OnCancel();
	}


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CUpdateTab1::OnBnClickedUpdateBtn()
{
	GetDlgItemText(IDC_UPDATE_PW_EDIT, cStr);
	strcpy_s(pw, CStringA(cStr).GetString());
	GetDlgItemText(IDC_UPDATE_NAME_EDIT, cStr);
	strcpy_s(name, CStringA(cStr).GetString());

	//cStr.Format("ID: %s, pw: %s, name: %s", userid, pw, name);
	//AfxMessageBox(cStr);


	CTime birth_date;
	int year, month, day;
	m_birth_ctrl.GetTime(birth_date);
	year = birth_date.GetYear();
	month = birth_date.GetMonth();
	day = birth_date.GetDay();

	UpdateData(true); //dlg->cpp로 변수값이동 (0=남자/1=여자)

	//cStr.Format("ID: %s, pw: %s, name: %s, birth: %4d-%02d-%02d, sex: %d",userid, pw, name, year,month, day, m_update_radio);
	//AfxMessageBox(cStr);

	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[201];
	SQLRETURN retCode;

	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 201, "UPDATE USERS "
			"SET PASSWORD = '%s', NAME = '%s', BIRTH = '%4d-%02d-%02d', SEX = %d "
			"WHERE USERID = '%s'; ", pw, name, year, month, day, m_update_radio, userid);

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
