// CSelectTab5.cpp: 구현 파일
//

#include "pch.h"
#include "Matzip.h"
#include "CSelectTab5.h"
#include "afxdialogex.h"
#include "MatzipDlg.h"


// CSelectTab5 대화 상자

IMPLEMENT_DYNAMIC(CSelectTab5, CDialogEx)

CSelectTab5::CSelectTab5(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SELECT_TAB5, pParent)
{

}

CSelectTab5::~CSelectTab5()
{
}

void CSelectTab5::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SELECT1_LIST, Select5_list);
}


BEGIN_MESSAGE_MAP(CSelectTab5, CDialogEx)

	ON_BN_CLICKED(IDC_SELECT5_QUERY_BTN, &CSelectTab5::OnBnClickedSelect5QueryBtn)
	ON_BN_CLICKED(IDC_RETURN_BTN, &CSelectTab5::OnBnClickedReturnBtn)
END_MESSAGE_MAP()


// CSelectTab5 메시지 처리기


BOOL CSelectTab5::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	Select5_list.InsertColumn(0, "User ID", LVCFMT_CENTER, 70);
	Select5_list.InsertColumn(1, "식당 ID", LVCFMT_CENTER, 70);
	Select5_list.InsertColumn(2, "Review ID", LVCFMT_CENTER, 85);
	Select5_list.InsertColumn(3, "음식점 이름", LVCFMT_CENTER, 150);
	Select5_list.InsertColumn(4, "별점", LVCFMT_CENTER, 50);
	Select5_list.InsertColumn(5, "Content", LVCFMT_CENTER, 240);

	if (!Update_listControl()) {
		AfxMessageBox("데이터를 불러오는 과정에서 오류가 발생했습니다.");
		CDialogEx::OnCancel();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL CSelectTab5::Update_listControl(char* restname) {
	if (!db_connect())
	{
		AfxMessageBox("서버 접속에 실패하여 종료합니다.");
		return false;
	}
	Select5_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	Select5_list.DeleteAllItems();

	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[201];

	SQLSMALLINT colCount = -1;
	SQLCHAR data[50][31];
	SQLINTEGER nulldata[50];

	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
	{
		if (restname=="NULL")
			sprintf_s((char*)query, 201, "SELECT USERID, RESTID, REVIEWID, S.RESTNAME, STAR, CONTENT "
				"FROM REVIEW R, RESTAURANT S "
				"WHERE R.RESTID = S.RESTNO AND USERID = '%s';", userid);
		else
			sprintf_s((char*)query, 201, "SELECT USERID, RESTID, REVIEWID, S.RESTNAME, STAR, CONTENT "
				"FROM REVIEW R, RESTAURANT S "
				"WHERE R.RESTID = S.RESTNO AND USERID = '%s' AND S.RESTNAME='%s';", userid, restname);

		SQLExecDirect(hStmt, query, SQL_NTS);
		SQLNumResultCols(hStmt, &colCount);
		for (int i = 0; i < colCount; ++i) {
			SQLBindCol(hStmt, i + 1, SQL_C_CHAR, data[i], sizeof(data[i]), (SQLLEN*)&nulldata[i]);
		}

		int row_item;
		while (SQLFetch(hStmt) != SQL_NO_DATA)
		{
			row_item = Select5_list.InsertItem(0, (char*)data[0]);
			for (int i = 1; i < colCount; ++i) {
				Select5_list.SetItemText(row_item, i, (char*)data[i]);
			}
		}

		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
	else {
		AfxMessageBox("오류가 발생했습니다.");
		db_disconnect();
		return false;
	}

	return true;
}



void CSelectTab5::OnBnClickedSelect5QueryBtn()
{
	char restname[128];
	GetDlgItemText(IDC_RESTNAME_EDIT, str);
	strcpy_s(restname, CStringA(str).GetString());

	Update_listControl(restname);
}


void CSelectTab5::OnBnClickedReturnBtn()
{
	Update_listControl();
}
