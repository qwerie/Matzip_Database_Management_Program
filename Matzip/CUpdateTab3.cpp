// CUpdateTab3.cpp: 구현 파일
//

#include "pch.h"
#include "Matzip.h"
#include "CUpdateTab3.h"
#include "afxdialogex.h"
#include "MatzipDlg.h"


// CUpdateTab3 대화 상자

IMPLEMENT_DYNAMIC(CUpdateTab3, CDialogEx)

CUpdateTab3::CUpdateTab3(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UPDATE_TAB3, pParent)
{

}

CUpdateTab3::~CUpdateTab3()
{
}

void CUpdateTab3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, update3_list);
}


BEGIN_MESSAGE_MAP(CUpdateTab3, CDialogEx)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CUpdateTab3::OnNMDblclkList1)
	ON_BN_CLICKED(IDC_UPDATE_BTN, &CUpdateTab3::OnBnClickedUpdateBtn)
END_MESSAGE_MAP()


// CUpdateTab3 메시지 처리기


BOOL CUpdateTab3::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (!db_connect())
	{
		AfxMessageBox("서버 접속에 실패하여 종료합니다.");
		CDialogEx::OnCancel();
	}

	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[201];

	SQLSMALLINT colCount = -1;
	SQLCHAR data[50][31];
	SQLINTEGER nulldata[50];
	SQLCHAR columnName[50][31];

	update3_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	update3_list.DeleteAllItems();


	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 201, "SELECT RESTNO, RESTNAME, PRICE, LOC, PHONE, STARTTIME, ENDTIME "
			"FROM RESTAURANT ;");

		SQLExecDirect(hStmt, query, SQL_NTS);
		SQLNumResultCols(hStmt, &colCount);

		for (int i = 0; i < colCount; ++i)
		{
			SQLColAttribute(hStmt, i + 1, SQL_DESC_NAME, columnName[i], 30, NULL, NULL); //칼럼명 추출
			update3_list.InsertColumn(i, (char*)columnName[i], LVCFMT_CENTER, 150);
	
			SQLBindCol(hStmt, i + 1, SQL_C_CHAR, data[i], sizeof(data[i]), (SQLLEN*)&nulldata[i]);
		}

		int row_item;
		while (SQLFetch(hStmt) != SQL_NO_DATA)
		{
			row_item = update3_list.InsertItem(0, (char*)data[0]);
			for (int i = 1; i < colCount; ++i) {
				update3_list.SetItemText(row_item, i, (char*)data[i]);
			}
		}

		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
	else {
		AfxMessageBox("오류가 발생했습니다.");
		db_disconnect();
		CDialogEx::OnCancel();
	}

	str.Format("");
	SetDlgItemText(IDC_RESTNAME_EDIT, str);
	SetDlgItemText(IDC_PRICE_EDIT, str);
	SetDlgItemText(IDC_LOC_EDIT, str);
	SetDlgItemText(IDC_PHONE_EDIT, str);
	SetDlgItemText(IDC_START_EDIT, str);
	SetDlgItemText(IDC_END_EDIT, str);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CUpdateTab3::OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	if (pNMItemActivate->iItem != -1) {
		str = update3_list.GetItemText(pNMItemActivate->iItem, 0);
		restid = _ttoi(str);
		//AfxMessageBox("선택되었습니다");
	}

	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[201];

	SQLCHAR RESTNAME[30], PRICE[10], LOC[50], PHONE[30], STARTTIME[10], ENDTIME[10];

	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 201, "SELECT RESTNAME, PRICE, LOC, PHONE, STARTTIME, ENDTIME "
			"FROM RESTAURANT " 
			"WHERE RESTNO=%d;", restid);

		SQLExecDirect(hStmt, query, SQL_NTS);

		SQLBindCol(hStmt, 1, SQL_C_CHAR, RESTNAME, sizeof(RESTNAME), NULL);
		SQLBindCol(hStmt, 2, SQL_C_CHAR, PRICE, sizeof(PRICE), NULL);
		SQLBindCol(hStmt, 3, SQL_C_CHAR, LOC, sizeof(LOC), NULL);
		SQLBindCol(hStmt, 4, SQL_C_CHAR, PHONE, sizeof(PHONE), NULL);
		SQLBindCol(hStmt, 5, SQL_C_CHAR, STARTTIME, sizeof(STARTTIME), NULL);
		SQLBindCol(hStmt, 6, SQL_C_CHAR, ENDTIME, sizeof(ENDTIME), NULL);

		while (SQLFetch(hStmt) != SQL_NO_DATA)
		{
			str.Format("%s", RESTNAME);
			SetDlgItemText(IDC_RESTNAME_EDIT, str);
			str.Format("%s", PRICE);
			SetDlgItemText(IDC_PRICE_EDIT, str);
			str.Format("%s", LOC);
			SetDlgItemText(IDC_LOC_EDIT, str);
			str.Format("%s", PHONE);
			SetDlgItemText(IDC_PHONE_EDIT, str);
			str.Format("%s", STARTTIME);
			SetDlgItemText(IDC_START_EDIT, str);
			str.Format("%s", ENDTIME);
			SetDlgItemText(IDC_END_EDIT, str);
		}
		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
	else {
		AfxMessageBox("오류가 발생했습니다.");
		db_disconnect();
		CDialogEx::OnCancel();
	}

	*pResult = 0;
}


void CUpdateTab3::OnBnClickedUpdateBtn()
{
	char RESTNAME[30], PRICE[10], LOC[50], PHONE[30], STARTTIME[10], ENDTIME[10];
	GetDlgItemText(IDC_RESTNAME_EDIT, str);
	strcpy_s(RESTNAME, CStringA(str).GetString());
	GetDlgItemText(IDC_PRICE_EDIT, str);
	strcpy_s(PRICE, CStringA(str).GetString());
	GetDlgItemText(IDC_LOC_EDIT, str);
	strcpy_s(LOC, CStringA(str).GetString());
	GetDlgItemText(IDC_PHONE_EDIT, str);
	strcpy_s(PHONE, CStringA(str).GetString());
	GetDlgItemText(IDC_START_EDIT, str);
	strcpy_s(STARTTIME, CStringA(str).GetString());
	GetDlgItemText(IDC_END_EDIT, str);
	strcpy_s(ENDTIME, CStringA(str).GetString());


	if (!db_connect())
	{
		AfxMessageBox("서버 접속에 실패하여 종료합니다.");
		CDialogEx::OnCancel();
	}

	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[201];

	SQLRETURN retCode;

	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 201, "UPDATE RESTAURANT "
			"SET RESTNAME='%s', PRICE='%s', LOC='%s', PHONE='%s', STARTTIME='%s', ENDTIME='%s' "
			"WHERE RESTNO=%d;", RESTNAME, PRICE, LOC, PHONE, STARTTIME, ENDTIME, restid);

		retCode = SQLExecDirect(hStmt, query, SQL_NTS);
		if (retCode == SQL_ERROR || retCode == SQL_NO_DATA_FOUND)
		{
			AfxMessageBox("Query execution error!");
			CDialogEx::OnCancel();
		}
		else {
			AfxMessageBox("음식점 정보가 정상적으로 업데이트 되었습니다!");
			OnInitDialog();
		}

		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
	else {
		AfxMessageBox("오류가 발생했습니다.");
		CDialogEx::OnCancel();
	}
}
