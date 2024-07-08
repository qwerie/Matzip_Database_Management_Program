// CInsertTab4.cpp: 구현 파일
//

#include "pch.h"
#include "Matzip.h"
#include "CInsertTab4.h"
#include "afxdialogex.h"
#include "MatzipDlg.h"
#include <string>


// CInsertTab4 대화 상자

IMPLEMENT_DYNAMIC(CInsertTab4, CDialogEx)

CInsertTab4::CInsertTab4(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INSERT_TAB4, pParent)
{

}

CInsertTab4::~CInsertTab4()
{
}

void CInsertTab4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INSERT4_LIST, insert4_list);
	DDX_Control(pDX, IDC_AGREE_BTN, agree);
	DDX_Control(pDX, IDC_NOT_AGREE_BTN, not_agree);
	DDX_Control(pDX, IDC_GOOD_BTN, good);
}


BEGIN_MESSAGE_MAP(CInsertTab4, CDialogEx)
	ON_BN_CLICKED(IDC_AGREE_BTN, &CInsertTab4::OnBnClickedAgreeBtn)
	ON_BN_CLICKED(IDC_NOT_AGREE_BTN, &CInsertTab4::OnBnClickedNotAgreeBtn)
	ON_BN_CLICKED(IDC_GOOD_BTN, &CInsertTab4::OnBnClickedGoodBtn)
	ON_BN_CLICKED(IDC_INSERT4_QUERY_BTN, &CInsertTab4::OnBnClickedInsert4QueryBtn)
	ON_NOTIFY(NM_DBLCLK, IDC_INSERT4_LIST, &CInsertTab4::OnNMDblclkInsert4List)
END_MESSAGE_MAP()


// CInsertTab4 메시지 처리기


BOOL CInsertTab4::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (!db_connect())
	{
		AfxMessageBox("서버 접속에 실패하여 종료합니다.");
		CDialogEx::OnCancel();
	}
	agree.EnableWindowsTheming(FALSE);
	not_agree.EnableWindowsTheming(FALSE);
	good.EnableWindowsTheming(FALSE);

	agree.SetFaceColor(RGB(255, 255, 255));
	not_agree.SetFaceColor(RGB(255, 255, 255));
	good.SetFaceColor(RGB(255, 255, 255));

	GetDlgItem(IDC_AGREE_BTN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_NOT_AGREE_BTN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_GOOD_BTN)->ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CInsertTab4::OnBnClickedInsert4QueryBtn()
{
	insert4_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	insert4_list.DeleteAllItems();

	GetDlgItemText(IDC_RESTNAME_EDIT, str);
	strcpy_s(restname, CStringA(str).GetString());

	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[201];

	SQLSMALLINT colCount = -1;
	SQLCHAR columnName[50][31];
	SQLCHAR data[50][31];
	SQLINTEGER nulldata[50];

	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 201, "SELECT S.RESTNAME, USERID, STAR, CONTENT, REVIEWID "
			"FROM REVIEW R, RESTAURANT S "
			"WHERE R.RESTID = S.RESTNO AND S.RESTNAME = '%s' ORDER BY REVIEWID DESC;", restname);

		SQLExecDirect(hStmt, query, SQL_NTS);
		SQLNumResultCols(hStmt, &colCount);
		for (int i = 0; i < colCount; ++i) {
			SQLBindCol(hStmt, i + 1, SQL_C_CHAR, data[i], sizeof(data[i]), (SQLLEN*)&nulldata[i]);
			SQLColAttribute(hStmt, i + 1, SQL_DESC_NAME, columnName[i], 30, NULL, NULL); //칼럼명 추출
			insert4_list.InsertColumn(i, (char*)columnName[i], LVCFMT_CENTER, 150);
		}

		int row_item;
		while (SQLFetch(hStmt) != SQL_NO_DATA)
		{
			row_item = insert4_list.InsertItem(0, (char*)data[0]);
			for (int i = 1; i < colCount; ++i) {
				insert4_list.SetItemText(row_item, i, (char*)data[i]);
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
	search_restid();
}

//칼럼 항목 더블클릭 이벤트
void CInsertTab4::OnNMDblclkInsert4List(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if (pNMItemActivate->iItem != -1) {
		str = insert4_list.GetItemText(pNMItemActivate->iItem, 4);
		reviewid = _ttoi(str);
		//AfxMessageBox("선택되었습니다");
	}

	GetDlgItem(IDC_AGREE_BTN)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_NOT_AGREE_BTN)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_GOOD_BTN)->ShowWindow(SW_SHOW);

	if (!search_agreeid())//방금 누른 리뷰에 어떤 공감을 남겼는지 찾기
		AfxMessageBox("agreeid를 찾는데에 에러가 발생했습니다.");

	//str.Format("지금 조회되는 agreetype: %d", agreeid);
	//AfxMessageBox(str);

	set_button_color(agreeid); //바로 위에서 search_agreeid한 것을 바탕으로 button색 변경

	*pResult = 0;
}


void CInsertTab4::OnBnClickedAgreeBtn()
{
	search_agreeid();
	if (agreeid == -1) {
		if (!insert_agree(0)) {
			AfxMessageBox("리뷰추천 내역 저장과정에서 오류가 발생했습니다.");
			CDialogEx::OnCancel();
		}
	}
	else {//이미 추천을 누른 내역이 있다면
		//무응답하기
	}
}


void CInsertTab4::OnBnClickedNotAgreeBtn()
{
	search_agreeid();
	if (agreeid == -1) {
		if (!insert_agree(1)) {
			AfxMessageBox("리뷰추천 내역 저장과정에서 오류가 발생했습니다.");
			CDialogEx::OnCancel();
		}
	}
	else { //이미 추천을 누른 내역이 있다면
		//무응답하기
	}
}


void CInsertTab4::OnBnClickedGoodBtn()
{
	search_agreeid();
	if (agreeid == -1) {
		if (!insert_agree(2)) {
			AfxMessageBox("리뷰추천 내역 저장과정에서 오류가 발생했습니다.");
			CDialogEx::OnCancel();
		}
	}
	else {//이미 추천을 누른 내역이 있다면
		//무응답하기
	}
}

//restid를 알아내기
void CInsertTab4::search_restid() {
	if (!db_connect())
	{
		AfxMessageBox("서버 접속에 실패하여 종료합니다.");
		CDialogEx::OnCancel();
	}

	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[201];
	SQLCHAR RESTID[10];
	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 201, "SELECT RESTNO "
			"FROM RESTAURANT "
			"WHERE RESTNAME = '%s';", restname);

		SQLExecDirect(hStmt, query, SQL_NTS);
		SQLBindCol(hStmt, 1, SQL_C_CHAR, RESTID, sizeof(RESTID), NULL);

		if (SQLFetch(hStmt) != SQL_NO_DATA)
		{
			str.Format("%s", RESTID);
			restid = _ttoi(str);
		}
		else {
			AfxMessageBox("restid를 조회하는데에 에러가 발생했습니다.");
		}
		/*str.Format("%d",restid);
		AfxMessageBox(str);*/
		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
	else {
		AfxMessageBox("오류가 발생했습니다.");
		db_disconnect();
		CDialogEx::OnCancel();
	}
}

bool CInsertTab4::search_agreeid() {

	//str.Format("현재 agreetype: %d, restid:%d, reviewid:%d", agreeid,restid,reviewid);
	//AfxMessageBox(str);

	if (!db_connect())
	{
		AfxMessageBox("서버 접속에 실패하여 종료합니다.");
		CDialogEx::OnCancel();
	}

	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[201];
	SQLCHAR AGREEID[10];
	SQLRETURN retCode;
	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 201, "SELECT AGREETYPE "
			"FROM AGREEMENT "
			"WHERE REVIEWID = %d AND RESTID = %d AND USERID = '%s';", reviewid, restid, userid);

		retCode = SQLExecDirect(hStmt, query, SQL_NTS);
		if (retCode == SQL_ERROR) return false;

		SQLBindCol(hStmt, 1, SQL_C_CHAR, AGREEID, sizeof(AGREEID), NULL);

		if (SQLFetch(hStmt) != SQL_NO_DATA)
		{
			str.Format("%s", AGREEID);
			agreeid = _ttoi(str);
		}
		else {
			agreeid = -1;
		}
		return true;
		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
	else {
		AfxMessageBox("오류가 발생했습니다.");
		db_disconnect();
		return false;
		CDialogEx::OnCancel();
	}
}


bool CInsertTab4::insert_agree(int agreetype) {

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
		sprintf_s((char*)query, 201, "INSERT INTO AGREEMENT VALUES (%d,%d,'%s',%d);", restid, reviewid, userid, agreetype);

		retCode = SQLExecDirect(hStmt, query, SQL_NTS);
		if (retCode == SQL_ERROR || retCode == SQL_NO_DATA_FOUND)
		{
			AfxMessageBox("Query execution error!");
			return false;
		}
		else {
			//버튼 선택 정상 반영 -> 버튼 색깔 바꿔주기
			set_button_color(agreetype);
		}

		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

		return true;
	}
	else {
		AfxMessageBox("오류가 발생했습니다.");
		return false;
	}

}

void CInsertTab4::set_button_color(int agreetype) {
	switch (agreetype) {
	case -1:
		agree.SetFaceColor(RGB(255, 255, 255));
		not_agree.SetFaceColor(RGB(255, 255, 255));
		good.SetFaceColor(RGB(255, 255, 255));
		break;
	case 0:
		agree.SetFaceColor(RGB(0, 255, 0));
		not_agree.SetFaceColor(RGB(255, 255, 255));
		good.SetFaceColor(RGB(255, 255, 255));
		break;
	case 1:
		agree.SetFaceColor(RGB(255, 255, 255));
		not_agree.SetFaceColor(RGB(0, 255, 0));
		good.SetFaceColor(RGB(255, 255, 255));
		break;
	case 2:
		agree.SetFaceColor(RGB(255, 255, 255));
		not_agree.SetFaceColor(RGB(255, 255, 255));
		good.SetFaceColor(RGB(0, 255, 0));
		break;
	}
}
