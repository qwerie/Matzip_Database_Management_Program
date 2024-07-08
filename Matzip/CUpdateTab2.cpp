// CUpdateTab2.cpp: 구현 파일
//

#include "pch.h"
#include "Matzip.h"
#include "CUpdateTab2.h"
#include "afxdialogex.h"
#include "MatzipDlg.h"
#include <string>


// CUpdateTab2 대화 상자

IMPLEMENT_DYNAMIC(CUpdateTab2, CDialogEx)

CUpdateTab2::CUpdateTab2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UPDATE_TAB2, pParent)
{

}

CUpdateTab2::~CUpdateTab2()
{
}

void CUpdateTab2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SELECT1_LIST, update2_list);
}


BEGIN_MESSAGE_MAP(CUpdateTab2, CDialogEx)

	ON_NOTIFY(UDN_DELTAPOS, IDC_STAR_SPIN, &CUpdateTab2::OnDeltaposStarSpin)
	ON_BN_CLICKED(IDC_REVIEW_ENTER_BTN, &CUpdateTab2::OnBnClickedReviewEnterBtn)
	ON_BN_CLICKED(IDC_UPDATE2_QUERY_BTN, &CUpdateTab2::OnBnClickedUpdate2QueryBtn)
END_MESSAGE_MAP()


// CUpdateTab2 메시지 처리기


BOOL CUpdateTab2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (!db_connect())
	{
		AfxMessageBox("서버 접속에 실패하여 종료합니다.");
		CDialogEx::OnCancel();
	}

	update2_list.InsertColumn(0, "식당 ID", LVCFMT_CENTER, 100);
	update2_list.InsertColumn(1, "Review ID", LVCFMT_CENTER, 100);
	update2_list.InsertColumn(2, "음식점 이름", LVCFMT_CENTER, 100);
	update2_list.InsertColumn(3, "별점", LVCFMT_CENTER, 80);
	update2_list.InsertColumn(4, "Content", LVCFMT_CENTER, 150);

	spin_val = 5.0;

	str.Format("%.1f", spin_val);
	SetDlgItemText(IDC_STAR_EDIT2, str);
	

	if (!Update_listControl()) {
		AfxMessageBox("오류가 발생했습니다.");
		CDialogEx::OnCancel();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CUpdateTab2::OnDeltaposStarSpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	if (pNMUpDown->iDelta < 0)//위 버튼을 눌렀을 때
	{
		if (spin_val >= 5) return;
		spin_val += 0.5;
	}
	else {
		if (spin_val <= 0) return;
		spin_val -= 0.5;
	}
	CString str;
	str.Format("%.1f", spin_val);
	SetDlgItemText(IDC_STAR_EDIT2, str);

	*pResult = 0;
}


void CUpdateTab2::OnBnClickedUpdate2QueryBtn()
{
	GetDlgItemText(IDC_RESTID_EDIT, str);
	strcpy_s(restid, CStringA(str).GetString());
	GetDlgItemText(IDC_REVIEWID_EDIT, str);
	strcpy_s(reviewid, CStringA(str).GetString());

	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[201];

	SQLCHAR star[20];
	SQLCHAR content[256];

	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 201, "SELECT STAR, CONTENT "
			"FROM REVIEW R "
			"WHERE USERID = '%s' AND RESTID= %s AND REVIEWID=%s;", userid, restid, reviewid);

		SQLExecDirect(hStmt, query, SQL_NTS);
		SQLBindCol(hStmt, 1, SQL_C_CHAR, star, sizeof(star), NULL);
		SQLBindCol(hStmt, 2, SQL_C_CHAR, content, sizeof(content), NULL);

		while (SQLFetch(hStmt) != SQL_NO_DATA)
		{
			spin_val = atof((char*)star);

			str.Format("%s", (char*)content);
			SetDlgItemText(IDC_CONTENT_EDIT, str);
		}
		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
	else {
		AfxMessageBox("오류가 발생했습니다.");
		db_disconnect();
		CDialogEx::OnCancel();
	}

}


void CUpdateTab2::OnBnClickedReviewEnterBtn()
{
	char star[256];
	char content[256];

	GetDlgItemText(IDC_STAR_EDIT2, str);
	strcpy_s(star, CStringA(str).GetString());
	GetDlgItemText(IDC_CONTENT_EDIT, str);
	strcpy_s(content, CStringA(str).GetString());

	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[201];

	SQLRETURN retCode;

	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
	{
		//리뷰 업데이트
		sprintf_s((char*)query, 201, "UPDATE REVIEW SET STAR=%s, CONTENT='%s' WHERE RESTID=%s AND REVIEWID=%s;", star, content, restid, reviewid);

		retCode = SQLExecDirect(hStmt, query, SQL_NTS);
		if (retCode == SQL_ERROR || retCode == SQL_NO_DATA_FOUND)
		{
			AfxMessageBox("Query execution error!");
			CDialogEx::OnCancel();
		}
		else {
			AfxMessageBox("성공적으로 업데이트했습니다!");

			if (!Update_listControl()) {
				AfxMessageBox("오류가 발생했습니다.");
				db_disconnect();
				CDialogEx::OnCancel();
			}
			else {
				AfxMessageBox("정상적으로 업데이트했습니다.");
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

}

BOOL CUpdateTab2::Update_listControl() {

	if (!db_connect())
	{
		AfxMessageBox("서버 접속에 실패하여 종료합니다.");
		return false;
	}

	update2_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	update2_list.DeleteAllItems();

	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[201];

	SQLSMALLINT colCount = -1;
	SQLCHAR data[50][31];
	SQLINTEGER nulldata[50];
	SQLRETURN retCode;

	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 201, "SELECT RESTID, REVIEWID, S.RESTNAME, STAR, CONTENT "
			"FROM REVIEW R, RESTAURANT S "
			"WHERE R.RESTID = S.RESTNO AND USERID = '%s';", userid);
		retCode=SQLExecDirect(hStmt, query, SQL_NTS);
		if (retCode == SQL_ERROR || retCode == SQL_NO_DATA_FOUND)
		{
			AfxMessageBox("Query execution error!");
			
		}
		else {
			SQLNumResultCols(hStmt, &colCount);
			for (int i = 0; i < colCount; ++i) {
				SQLBindCol(hStmt, i + 1, SQL_C_CHAR, data[i], sizeof(data[i]), (SQLLEN*)&nulldata[i]);
			}

			int row_item;
			while (SQLFetch(hStmt) != SQL_NO_DATA)
			{
				row_item = update2_list.InsertItem(0, (char*)data[0]);
				for (int i = 1; i < colCount; ++i) {
					update2_list.SetItemText(row_item, i, (char*)data[i]);
				}
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