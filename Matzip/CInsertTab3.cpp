﻿// CInsertTab3.cpp: 구현 파일
//

#include "pch.h"
#include "Matzip.h"
#include "CInsertTab3.h"
#include "afxdialogex.h"
#include "MatzipDlg.h"


// CInsertTab3 대화 상자

IMPLEMENT_DYNAMIC(CInsertTab3, CDialogEx)

CInsertTab3::CInsertTab3(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INSERT_TAB3, pParent)
{

}

CInsertTab3::~CInsertTab3()
{
}

void CInsertTab3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REST_LIST, insert3_list);
	DDX_Control(pDX, IDC_LIST1, fav_list);
}


BEGIN_MESSAGE_MAP(CInsertTab3, CDialogEx)
	ON_NOTIFY(NM_DBLCLK, IDC_REST_LIST, &CInsertTab3::OnNMDblclkRestList)
END_MESSAGE_MAP()


// CInsertTab3 메시지 처리기


BOOL CInsertTab3::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (!db_connect())
	{
		AfxMessageBox("서버 접속에 실패하여 종료합니다.");
		CDialogEx::OnCancel();
	}

	update_rest_list();
	update_fav_list();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CInsertTab3::OnNMDblclkRestList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if (pNMItemActivate->iItem != -1) {
		str = insert3_list.GetItemText(pNMItemActivate->iItem, 0);
		//AfxMessageBox(str);
	}
	
	find_restid(str);
	if (is_in_fav()==1)//즐겨찾기 목록에 이미 존재함
		AfxMessageBox("선택한 식당이 이미 즐겨찾기 목록에 존재합니다.");
	else  {//현재 즐겨찾기 목록에 없음
		insert_fav();
		update_fav_list();
		update_rest_list();
	}
	/*else {
		AfxMessageBox("is_in_fav 함수에서 문제가 발생했습니다.");
	}*/
	*pResult = 0;
}


bool CInsertTab3::find_restid(CString str) {
	char restname[30]; 
	strcpy_s(restname, CStringA(str).GetString());
	//str.Format("%s", restname);
	//AfxMessageBox(str);
	if (!db_connect())
	{
		AfxMessageBox("서버 접속에 실패하여 종료합니다.");
		CDialogEx::OnCancel();
	}

	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[201];
	SQLCHAR RESTID[10];
	SQLRETURN retCode;
	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 201, "SELECT RESTNO FROM RESTAURANT "
			"WHERE RESTNAME = '%s';", restname);

		retCode=SQLExecDirect(hStmt, query, SQL_NTS);
		if (retCode == SQL_ERROR || retCode == SQL_NO_DATA_FOUND)
		{
			AfxMessageBox("Query execution error!");
			return false;
		}
		SQLBindCol(hStmt, 1, SQL_C_CHAR, RESTID, sizeof(RESTID), NULL);

		if (SQLFetch(hStmt) != SQL_NO_DATA)
		{
			str.Format("%s", RESTID);
			//AfxMessageBox(str);
			restid = atoi(str);

			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		}
		else {
			AfxMessageBox("restid를 조회하는데에 에러가 발생했습니다.");
			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

			return false;
		}
	}
	else {
		AfxMessageBox("오류가 발생했습니다.");
		db_disconnect();
		CDialogEx::OnCancel();
	}
	return true;
}


bool CInsertTab3::insert_fav() {
	if (!db_connect())
	{
		AfxMessageBox("서버 접속에 실패하여 종료합니다.");
		CDialogEx::OnCancel();
	}

	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[101];

	SQLRETURN retCode;

	CTime ctime = CTime::GetCurrentTime();
	str.Format("%04d-%02d-%02d", ctime.GetYear(), ctime.GetMonth(), ctime.GetDay());
	//AfxMessageBox(str);
	char date[30];
	strcpy_s(date, CStringA(str).GetString());

	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 101, "INSERT INTO FAVORITE VALUES ('%s',%d,'%s');", userid, restid, date);

		retCode = SQLExecDirect(hStmt, query, SQL_NTS);
		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

		if (retCode == SQL_ERROR || retCode == SQL_NO_DATA_FOUND)
		{
			AfxMessageBox("Query execution error!");
			
			return false;
		}
		else {
			update_fav_list();

		}
	}
	else {
		AfxMessageBox("오류가 발생했습니다.");
		return false;
	}
	
	SQLHSTMT hStmt2;
	SQLCHAR FAVNUM[10];
	int favnum;
	//RESTAURANT 내의 FAVNUM도 업데이트
	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt2) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 101, "SELECT FAVNUM FROM RESTAURANT WHERE RESTNO=%d;", restid);

		retCode = SQLExecDirect(hStmt2, query, SQL_NTS);
		SQLCloseCursor(hStmt2);
		//SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

		if (retCode == SQL_ERROR || retCode == SQL_NO_DATA_FOUND)
		{
			AfxMessageBox("Query execution error!");
			
			return false;
		}
		else {
			SQLBindCol(hStmt2, 1, SQL_C_CHAR, FAVNUM, sizeof(FAVNUM), NULL);
			if (SQLFetch(hStmt2) != SQL_NO_DATA)
			{
				str.Format("%s", FAVNUM);
				favnum = _ttoi(str);
			}

		}
	}
	else {
		AfxMessageBox("오류가 발생했습니다.");
		return false;
	}

	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 101, "UPDATE RESTAURANT SET FAVNUM=%d WHERE RESTNO=%d ;", favnum+1, restid);

		retCode = SQLExecDirect(hStmt, query, SQL_NTS);
		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

		if (retCode == SQL_ERROR || retCode == SQL_NO_DATA_FOUND)
		{
			AfxMessageBox("Query execution error!");
			
			return false;
		}
		else {
			str.Format("%d", favnum);
			AfxMessageBox(str);

			update_rest_list();
			return true;
		}
	}
	else {
		AfxMessageBox("오류가 발생했습니다.");
		return false;
	}
}

int CInsertTab3::is_in_fav() {
	if (!db_connect())
	{
		AfxMessageBox("서버 접속에 실패하여 종료합니다.");
		CDialogEx::OnCancel();
	}

	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[101];
	SQLCHAR RESTID[10];
	SQLRETURN retCode;
	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 101, "SELECT * FROM FAVORITE "
			"WHERE RESTID = %d AND USERID = '%s';", restid, userid);

		retCode=SQLExecDirect(hStmt, query, SQL_NTS);
		if (retCode == SQL_ERROR || retCode == SQL_NO_DATA_FOUND)
		{
			AfxMessageBox("Query execution error!");
			return -1;
		}

		SQLBindCol(hStmt, 1, SQL_C_CHAR, RESTID, sizeof(RESTID), NULL);

		if (SQLFetch(hStmt) != SQL_NO_DATA)
		{
			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

			return 1;
		}
		else {
			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
			return 0;
		}
	}
	else {
		AfxMessageBox("오류가 발생했습니다.");
		db_disconnect();
		return -1;
		CDialogEx::OnCancel();
	}
}
bool CInsertTab3::update_rest_list() {
	insert3_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	insert3_list.DeleteAllItems();

	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[301];

	SQLSMALLINT colCount = -1;
	SQLCHAR columnName[50][31];
	SQLCHAR data[50][31];
	SQLINTEGER nulldata[50];
	SQLRETURN retCode;

	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 301, "SELECT S.RESTNAME, PRICE, STARTTIME, ENDTIME, T.RESTTYPE, PHONE, LOC, FAVNUM "
			"FROM RESTAURANT AS S, RESTTYPE AS T "
			"WHERE S.RESTTYPENO = T.RESTTYPENO ORDER BY RESTNO DESC; ");

		retCode = SQLExecDirect(hStmt, query, SQL_NTS);
		if (retCode == SQL_ERROR || retCode == SQL_NO_DATA_FOUND) {
			AfxMessageBox("Query execution error!");
			db_disconnect();
			return false;
			CDialogEx::OnCancel();
		}
		SQLNumResultCols(hStmt, &colCount);
		for (int i = 0; i < colCount; i++)
			insert3_list.DeleteColumn(0);
		for (int i = 0; i < colCount; ++i) {
			SQLBindCol(hStmt, i + 1, SQL_C_CHAR, data[i], sizeof(data[i]), (SQLLEN*)&nulldata[i]);
			SQLColAttribute(hStmt, i + 1, SQL_DESC_NAME, columnName[i], 30, NULL, NULL); //칼럼명 추출
			insert3_list.InsertColumn(i, (char*)columnName[i], LVCFMT_CENTER, 150);
		}

		int row_item;
		while (SQLFetch(hStmt) != SQL_NO_DATA)
		{
			row_item = insert3_list.InsertItem(0, (char*)data[0]);
			for (int i = 1; i < colCount; ++i) {
				insert3_list.SetItemText(row_item, i, (char*)data[i]);
			}
		}

		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		return true;
	}
	else {
		AfxMessageBox("오류가 발생했습니다.");
		db_disconnect();
		return false;
		CDialogEx::OnCancel();
	}
}

bool CInsertTab3::update_fav_list() {
	if (!db_connect())
	{
		AfxMessageBox("서버 접속에 실패하여 종료합니다.");
		CDialogEx::OnCancel();
	}

	fav_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	fav_list.DeleteAllItems();

	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[301];

	SQLSMALLINT colCount = -1;
	SQLCHAR columnName[50][31];
	SQLCHAR data[50][31];
	SQLINTEGER nulldata[50];
	SQLRETURN retCode;

	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 301, "SELECT USERID, FAVDATE, S.RESTNAME, PRICE, STARTTIME, ENDTIME, T.RESTTYPE, PHONE, LOC "
			"FROM FAVORITE, RESTAURANT AS S, RESTTYPE T "
			"WHERE FAVORITE.RESTID = S.RESTNO AND S.RESTTYPENO = T.RESTTYPENO AND USERID = '%s' ORDER BY FAVDATE ASC; ", userid);

		retCode = SQLExecDirect(hStmt, query, SQL_NTS);
		if (retCode == SQL_ERROR || retCode == SQL_NO_DATA_FOUND) {
			AfxMessageBox("Query execution error!");
			db_disconnect();
			return false;
			CDialogEx::OnCancel();
		}
		SQLNumResultCols(hStmt, &colCount);

		for (int i = 0; i < colCount; i++)
			fav_list.DeleteColumn(0);
		for (int i = 0; i < colCount; ++i) {
			SQLBindCol(hStmt, i + 1, SQL_C_CHAR, data[i], sizeof(data[i]), (SQLLEN*)&nulldata[i]);
			SQLColAttribute(hStmt, i + 1, SQL_DESC_NAME, columnName[i], 30, NULL, NULL); //칼럼명 추출
			fav_list.InsertColumn(i, (char*)columnName[i], LVCFMT_CENTER, 150);
		}

		int row_item;
		while (SQLFetch(hStmt) != SQL_NO_DATA)
		{
			row_item = fav_list.InsertItem(0, (char*)data[0]);
			for (int i = 1; i < colCount; ++i) {
				fav_list.SetItemText(row_item, i, (char*)data[i]);
			}
		}

		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
	else {
		AfxMessageBox("오류가 발생했습니다.");
		db_disconnect();
		return false;
		CDialogEx::OnCancel();
	}
	return true;
}