// SchemaCheckDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Matzip.h"
#include "SchemaCheckDlg.h"
#include "afxdialogex.h"
#include "MatzipDlg.h"


// SchemaCheckDlg 대화 상자

IMPLEMENT_DYNAMIC(SchemaCheckDlg, CDialogEx)

SchemaCheckDlg::SchemaCheckDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SCHEMA_CHECK_DLG, pParent)
	, m_combo_str(_T(""))
{

}

SchemaCheckDlg::~SchemaCheckDlg()
{
}

void SchemaCheckDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Table_COMBO, m_combo);
	DDX_CBString(pDX, IDC_Table_COMBO, m_combo_str);
	DDX_Control(pDX, IDC_Schema_LIST, Schema_list);
}


BEGIN_MESSAGE_MAP(SchemaCheckDlg, CDialogEx)

	ON_CBN_SELCHANGE(IDC_Table_COMBO, &SchemaCheckDlg::OnCbnSelchangeTableCombo)
END_MESSAGE_MAP()


// SchemaCheckDlg 메시지 처리기


BOOL SchemaCheckDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_combo.AddString("RESTAURANT");
	m_combo.AddString("RESTTYPE");
	m_combo.AddString("USERS");
	m_combo.AddString("REVIEW");
	m_combo.AddString("AGREEMENT");
	m_combo.AddString("AGREETYPE");
	m_combo.AddString("FAVORITE");
	m_combo.AddString("FOLLOWING");
	m_combo.SetCurSel(0);

	Schema_list.InsertColumn(0, "Column Name", LVCFMT_CENTER, 120);
	Schema_list.InsertColumn(1, "Name Length", LVCFMT_CENTER, 130);
	Schema_list.InsertColumn(2, "Data Type", LVCFMT_CENTER, 100);
	Schema_list.InsertColumn(3, "Data Size", LVCFMT_CENTER, 100);
	Schema_list.InsertColumn(4, "Data Decimal digits", LVCFMT_CENTER, 180);
	Schema_list.InsertColumn(5, "Data nullable", LVCFMT_CENTER, 130);
	Schema_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	return TRUE;  // return TRUE unless you set the focus to a control
			  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void SchemaCheckDlg::OnCbnSelchangeTableCombo()
{
	char table_name[MAX_PATH];
	m_combo.GetLBText(m_combo.GetCurSel(), table_name);
	//AfxMessageBox(table_name);

	if (!db_connect())
	{
		AfxMessageBox("서버 접속에 실패하여 종료합니다.");
		CDialogEx::OnCancel();
	}

	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[101];

	SQLSMALLINT numCols = -1;// number of columns
	SQLCHAR columnName[50][31];
	SQLSMALLINT columnNameLen[50];
	SQLSMALLINT columnDataType[50];
	SQLULEN columnDataSize[50];
	SQLSMALLINT columnDataDecimalDigits[50];
	SQLSMALLINT columnDataNullable[50];
	SQLRETURN retCode;
	int row_item;

	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 101, "SELECT * FROM %s", table_name);
		//AfxMessageBox((char*)query);
		retCode = SQLExecDirect(hStmt, query, SQL_NTS);

		if (retCode == SQL_ERROR)
		{
			AfxMessageBox("Query execution error!");
			CDialogEx::OnCancel();

		}
		if (retCode == SQL_NO_DATA_FOUND) {
			AfxMessageBox("No data found!");
			CDialogEx::OnCancel();
		}

		SQLNumResultCols(hStmt, &numCols);
		CString str;
		/*str.Format(_T("%d"), numCols);
		AfxMessageBox(str);*/

		for (int i = 0; i < numCols; ++i)
		{
			SQLDescribeCol(hStmt, i + 1, columnName[i], 30, &columnNameLen[i], &columnDataType[i],
				&columnDataSize[i], &columnDataDecimalDigits[i], &columnDataNullable[i]);

			row_item = Schema_list.InsertItem(0, (char*)columnName[i]);
			str.Format(_T("%d"), columnNameLen[i]);
			Schema_list.SetItemText(row_item, 1, str);
			Schema_list.SetItemText(row_item, 2, get_data_type_in_string(columnDataType[i]));
			str.Format(_T("%d"), columnDataSize[i]);
			Schema_list.SetItemText(row_item, 3, str);
			str.Format(_T("%d"), columnDataDecimalDigits[i]);
			Schema_list.SetItemText(row_item, 4, str);
			if (columnDataNullable[i] == 1) str = "Nullable";
			else str = "Not nullable";
			Schema_list.SetItemText(row_item, 5, str);
		}

	}
	else {
		AfxMessageBox("실패했습니다1");
		db_disconnect();
		CDialogEx::OnCancel();
	}


	SQLCloseCursor(hStmt);
	SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
}


const char* SchemaCheckDlg::get_data_type_in_string(SQLSMALLINT dataType)
{
	switch (dataType)
	{
	case SQL_CHAR:
		return "CHAR";
		break;
	case SQL_VARCHAR:
		return "VARCHAR";
		break;
	case SQL_LONGVARCHAR:
		return "LONGVARCHAR";
		break;
	case SQL_WCHAR:
		return "WCHAR";
		break;
	case SQL_WVARCHAR:
		return "WVARCHAR";
		break;
	case SQL_WLONGVARCHAR:
		return "WLONGVARCHAR";
		break;
	case SQL_NUMERIC:
		return "NUMERIC";
		break;
	case SQL_SMALLINT:
		return "SMALLINT";
		break;
	case SQL_INTEGER:
		return "INTEGER";
		break;
	case SQL_REAL:
		return "REAL";
		break;
	case SQL_FLOAT:
		return "FLOAT";
		break;
	case SQL_DOUBLE:
		return "DOUBLE";
		break;
	case SQL_BIT:
		return "BIT";
		break;
	case SQL_TINYINT:
		return "TINYINT";
		break;
	case SQL_BIGINT:
		return "BIGINT";
		break;
	case SQL_BINARY:
		return "BINARY";
		break;
	case SQL_VARBINARY:
		return "VARBINARY";
		break;
	case SQL_LONGVARBINARY:
		return "LONGVARBINARY";
		break;
	case SQL_TYPE_DATE:
		return "TYPE_DATE";
		break;
	case SQL_TYPE_TIME:
		return "TYPE_TIME";
		break;
	case SQL_TYPE_TIMESTAMP:
		return "TYPE_TIMESTAMP";
		break;
	case SQL_INTERVAL_MONTH:
		return "INTERVAL_MONTH";
		break;
	case SQL_INTERVAL_YEAR:
		return "INTERVAL_YEAR";
		break;
	case SQL_INTERVAL_YEAR_TO_MONTH:
		return "INTERVAL_YEAR_TO_MONTH";
		break;
	case SQL_INTERVAL_DAY:
		return "INTERVAL_DAY";
		break;
	case SQL_INTERVAL_HOUR:
		return "INTERVAL_HOUR";
		break;
	case SQL_INTERVAL_MINUTE:
		return "INTERVAL_MINUTE";
		break;
	case SQL_INTERVAL_SECOND:
		return "INTERVAL_SECOND";
		break;
	case SQL_INTERVAL_DAY_TO_HOUR:
		return "INTERVAL_DAY_TO_HOUR";
		break;
	case SQL_INTERVAL_DAY_TO_MINUTE:
		return "INTERVAL_DAY_TO_MINUTE";
		break;
	case SQL_INTERVAL_DAY_TO_SECOND:
		return "INTERVAL_DAY_TO_SECOND";
		break;
	case SQL_INTERVAL_HOUR_TO_MINUTE:
		return "INTERVAL_HOUR_TO_MINUTE";
		break;
	case SQL_INTERVAL_HOUR_TO_SECOND:
		return "INTERVAL_HOUR_TO_SECOND";
		break;
	case SQL_INTERVAL_MINUTE_TO_SECOND:
		return "INTERVAL_MINUTE_TO_SECOND";
		break;
	case SQL_GUID:
		return "GUID";
		break;
	default:
		return "UNKNOWN";
	}
}
