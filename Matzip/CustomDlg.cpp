// CustomDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Matzip.h"
#include "CustomDlg.h"
#include "afxdialogex.h"
#include "MatzipDlg.h"

// CustomDlg 대화 상자

IMPLEMENT_DYNAMIC(CustomDlg, CDialogEx)

//extern SQLHDBC hDbc;

CustomDlg::CustomDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CUSTOM_DLG, pParent)
{

}

CustomDlg::~CustomDlg()
{
}

void CustomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_RESULT_LIST, result_list);
	DDX_Control(pDX, IDC_RESULT_LIST, result_list);
}


BEGIN_MESSAGE_MAP(CustomDlg, CDialogEx)

	ON_BN_CLICKED(IDC_Query_BTN, &CustomDlg::OnBnClickedQueryBtn)
END_MESSAGE_MAP()




void CustomDlg::OnBnClickedQueryBtn()
{
	//column 이름을 넣어줘야하는데 schema check때 얻은 column 정보를 이용해야할 것 같다.
	result_list.DeleteAllItems();
	result_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	/*result_list.InsertColumn(0, "ID", LVCFMT_CENTER, 100);
	result_list.InsertColumn(1, "type", LVCFMT_CENTER, 100);
	result_list.InsertColumn(2, "gender", LVCFMT_CENTER, 100);*/

	if (!db_connect())
	{
		AfxMessageBox("서버 접속에 실패하여 종료합니다.");
		CDialogEx::OnCancel();
	}

	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[101];

	SQLCHAR data[50][31];
	SQLINTEGER nulldata[50];

	SQLCHAR columnName[50][31];
	SQLRETURN retCode;
	bool is_select=false;

	GetDlgItemText(IDC_CUSTOM_EDIT, str);
	if (str.Find("SELECT") != -1 || str.Find("select") != -1) is_select = true;

	sprintf_s((char*)query, 101, str);   //str=직접 입력한 쿼리문
	
	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
	{
		retCode=SQLExecDirect(hStmt, query, SQL_NTS);

		if (retCode == SQL_ERROR || retCode == SQL_NO_DATA_FOUND)
		{
			AfxMessageBox("Query execution error! Query문을 다시 입력해주세요.");
		}
		else {
			if (is_select) {
				for (int i = 0; i < colCount; i++)
					result_list.DeleteColumn(0);
				result_list.DeleteAllItems();

				SQLNumResultCols(hStmt, &colCount);

				for (int i = 0; i < colCount; ++i)
				{
					SQLColAttribute(hStmt, i + 1, SQL_DESC_NAME, columnName[i], 30, NULL, NULL); //칼럼명 추출
					result_list.InsertColumn(i, (char*)columnName[i], LVCFMT_CENTER, 100);

					SQLBindCol(hStmt, i + 1, SQL_C_CHAR, data[i], sizeof(data[i]), (SQLLEN*)&nulldata[i]);
				}
				//if 'select로 시작할 때 -> 띄어쓰기를 기준으로 from 다음 무슨 테이블인지 받아와서 -> schema check -> 칼럼 넣기 (테이블마다 다른 칼럼)
				//이 아래의 줄은 select에만 해당하는 query임. 따로 실행될 수 있게 코드 디버깅 필요함.
				int row_item;
				while (SQLFetch(hStmt) != SQL_NO_DATA)
				{
					row_item = result_list.InsertItem(0, (char*)data[0]);
					for (int i = 1; i < colCount; ++i) {
						result_list.SetItemText(row_item, i, (char*)data[i]);
					}
				}
			}
			else {
				AfxMessageBox("성공적으로 반영하였습니다!");
			}
			SetDlgItemText(IDC_CUSTOM_EDIT, ""); //성공적으로 쿼리문 처리를 완료했을 시 edit control을 비워준다.
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

