// CInsertTab2.cpp: 구현 파일
//
#include <string>
#include "pch.h"
#include "Matzip.h"
#include "CInsertTab2.h"
#include "afxdialogex.h"
#include "MatzipDlg.h"

int rest_id;
// CInsertTab2 대화 상자

IMPLEMENT_DYNAMIC(CInsertTab2, CDialogEx)

CInsertTab2::CInsertTab2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INSERT_TAB2, pParent)
{

}

CInsertTab2::~CInsertTab2()
{
}

void CInsertTab2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INSERT2_LIST, insert2_list);
}


BEGIN_MESSAGE_MAP(CInsertTab2, CDialogEx)
	ON_NOTIFY(UDN_DELTAPOS, IDC_STAR_SPIN, &CInsertTab2::OnDeltaposStarSpin)
	ON_BN_CLICKED(IDC_INSERT2_QUERY_BTN, &CInsertTab2::OnBnClickedInsert2QueryBtn)
	ON_BN_CLICKED(IDC_REVIEW_ENTER_BTN, &CInsertTab2::OnBnClickedReviewEnterBtn)
END_MESSAGE_MAP()


// CInsertTab2 메시지 처리기


BOOL CInsertTab2::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	if (!db_connect())
	{
		AfxMessageBox("서버 접속에 실패하여 종료합니다.");
		CDialogEx::OnCancel();
	}

	insert2_list.InsertColumn(0, "음식점 이름", LVCFMT_CENTER, 100);
	insert2_list.InsertColumn(1, "User ID", LVCFMT_CENTER, 100);
	insert2_list.InsertColumn(2, "별점", LVCFMT_CENTER, 80);
	insert2_list.InsertColumn(3, "Content", LVCFMT_CENTER, 350);

	spin_val = 5.0;

	str.Format("%.1f", spin_val);
	SetDlgItemText(IDC_STAR_EDIT, str);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CInsertTab2::OnDeltaposStarSpin(NMHDR* pNMHDR, LRESULT* pResult)
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

	str.Format("%.1f", spin_val);
	SetDlgItemText(IDC_STAR_EDIT, str);

	*pResult = 0;
}


void CInsertTab2::OnBnClickedInsert2QueryBtn()
{
	insert2_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	insert2_list.DeleteAllItems();

	GetDlgItemText(IDC_RESTNAME_EDIT, str);
	strcpy_s(restname, CStringA(str).GetString()); 

	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[201];

	SQLSMALLINT colCount = -1;
	SQLCHAR data[50][31];
	SQLINTEGER nulldata[50];

	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 201, "SELECT S.RESTNAME, USERID, STAR, CONTENT "
			"FROM REVIEW R, RESTAURANT S "
			"WHERE R.RESTID = S.RESTNO AND S.RESTNAME = '%s';", restname);

		SQLExecDirect(hStmt, query, SQL_NTS);
		SQLNumResultCols(hStmt, &colCount);
		for (int i = 0; i < colCount; ++i) {
			SQLBindCol(hStmt, i + 1, SQL_C_CHAR, data[i], sizeof(data[i]), (SQLLEN*)&nulldata[i]);
		}

		int row_item;
		while (SQLFetch(hStmt) != SQL_NO_DATA)
		{
			row_item = insert2_list.InsertItem(0, (char*)data[0]);
			for (int i = 1; i < colCount; ++i) {
				insert2_list.SetItemText(row_item, i, (char*)data[i]);
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


void CInsertTab2::OnBnClickedReviewEnterBtn()
{
	char star[256];
	char content[256];

	GetDlgItemText(IDC_STAR_EDIT, str);
	strcpy_s(star, CStringA(str).GetString());
	GetDlgItemText(IDC_CONTENT_EDIT, str);
	strcpy_s(content, CStringA(str).GetString());

	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[201];

	SQLSMALLINT colCount = -1;
	SQLRETURN retCode;

	//식당이름으로부터 RESTID 구하기
	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 201, "SELECT RESTNO FROM RESTAURANT WHERE RESTNAME = '%s';", restname);
		SQLExecDirect(hStmt, query, SQL_NTS);
		
		SQLCHAR s_rest_id[30];
		SQLBindCol(hStmt, 1, SQL_C_CHAR, s_rest_id, 30, NULL);
		
		while (SQLFetch(hStmt) != SQL_NO_DATA){
			str.Format("%s", s_rest_id);
		}
		
		strcpy_s(rest_id, CStringA(str).GetString());//RESTID 자료형 변환

		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
	else {
		AfxMessageBox("오류가 발생했습니다.");
		db_disconnect();
		CDialogEx::OnCancel();
	}

	//REVIEWID의 마지막 번호 구하기
	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 201, "SELECT MAX(REVIEWID) FROM REVIEW WHERE RESTID = %s;", rest_id);
		SQLExecDirect(hStmt, query, SQL_NTS);
		
		SQLCHAR s_review_id[30];
		SQLBindCol(hStmt, 1, SQL_C_CHAR, s_review_id, 30, NULL);
		
		while (SQLFetch(hStmt) != SQL_NO_DATA) {
			str.Format("%s", s_review_id);
		}
		
		strcpy_s(review_id_lastnum, CStringA(str).GetString());//REVIEWID 자료형 변환
		
		//새로운 리뷰가 들어갈 번호 구하기
		myturn = strtol(review_id_lastnum,NULL,10) + 1;
		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
	else {
		AfxMessageBox("오류가 발생했습니다.");
		db_disconnect();
		CDialogEx::OnCancel();
	}

	//리뷰 삽입
	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 201, "INSERT INTO REVIEW VALUES (%s,%d,%s,'%s','%s');",rest_id, myturn, star, content,userid);
		
		retCode=SQLExecDirect(hStmt, query, SQL_NTS);
		if (retCode == SQL_ERROR || retCode == SQL_NO_DATA_FOUND)
		{
			AfxMessageBox("Query execution error!");
			CDialogEx::OnCancel();
		}
		else {
			AfxMessageBox("리뷰를 성공적으로 등록하였습니다.");
			OnBnClickedInsert2QueryBtn();	//리뷰내역 갱신
			SetDlgItemText(IDC_CONTENT_EDIT, "");	//EDIT창 비워주기
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
