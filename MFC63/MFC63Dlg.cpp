
// MFC63Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFC63.h"
#include "MFC63Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC63Dlg 对话框



CMFC63Dlg::CMFC63Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC63_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC63Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CMFC63Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CMFC63Dlg::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CMFC63Dlg::OnBnClickedButtonAdd)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CMFC63Dlg::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CMFC63Dlg::OnBnClickedButtonModify)
END_MESSAGE_MAP()


// CMFC63Dlg 消息处理程序

void CMFC63Dlg::GetRecordset()
{
	LPCTSTR lpSql = TEXT("select * from students order by StudentID");

	try {
		m_pRs->Open((_variant_t)lpSql, m_pCn.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
	} catch (_com_error e) {
		AfxMessageBox(e.Description());
	}

	// 读取数据内容显示在列表上
	m_list.DeleteAllItems();

	int nItem = 0;
	_variant_t StudentID, StudentName;
	CString	strStudentID, strStudentName;
	while (!m_pRs->adoEOF) {
		StudentID = m_pRs->GetCollect(TEXT("StudentID"));
		StudentName = m_pRs->GetCollect(TEXT("StudentName"));

		strStudentID.Format(TEXT("%d"), StudentID.intVal);
		strStudentName = (LPCTSTR)_bstr_t(StudentName);

		m_list.InsertItem(nItem, strStudentID);
		m_list.SetItemText(nItem, 1, strStudentName);
		m_list.SetItemData(nItem, StudentID.intVal);

		++nItem;

		m_pRs->MoveNext();
	}

	m_pRs->Close();
}

void CMFC63Dlg::ExecuteSql(LPCTSTR lpSql)
{
	try {
		//_variant_t ra;
		m_pCn->Execute((_bstr_t)lpSql, NULL, adCmdText);
	} catch (_com_error e) {
		AfxMessageBox(e.Description());
	}
}

BOOL CMFC63Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// 初始化显示列表
	LV_COLUMN listColumn;
	listColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	listColumn.fmt = LVCFMT_LEFT;
	TCHAR *listTile[2] = {TEXT("学号"), TEXT("姓名")};
	int nColCx[2] = {100, 120};
	for (int ncol = 0; ncol < 2; ++ncol) {
		listColumn.cx = nColCx[ncol];
		listColumn.iSubItem = ncol;
		listColumn.pszText = listTile[ncol];
		m_list.InsertColumn(ncol, &listColumn);
	}
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	// ADO初始化操作
	AfxOleInit();
	m_pCn.CreateInstance(__uuidof(Connection));
	m_pCn->ConnectionString = TEXT("Provider=MSDASQL.1; Persist Security Info=False; \
									Driver = MySQL ODBC 8.0 Unicode Driver; \
									SERVER = localhost; Data Source = student_ado");
	try {
		m_pCn->Open(TEXT(""), TEXT(""), TEXT(""), adModeUnknown);
	} catch (_com_error e) {
		AfxMessageBox(e.Description());
		m_pCn = NULL;
		return FALSE;
	}

	m_pRs.CreateInstance(__uuidof(Recordset));
	GetRecordset();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFC63Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFC63Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC63Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	if (m_pCn && m_pCn->State) {
		m_pCn->Close();
	}

	CoUninitialize();
}


void CMFC63Dlg::OnBnClickedButtonDelete()
{
	int nIndex = m_list.GetSelectionMark();
	if (nIndex < 0) {
		return;
	}

	int nStudentID = (int)m_list.GetItemData(nIndex);

	TCHAR szSql[256] = {0};
	_stprintf_s(szSql, TEXT("delete from students where StudentID=%d"), nStudentID);

	ExecuteSql(szSql);

	GetRecordset();
}


void CMFC63Dlg::OnBnClickedButtonAdd()
{
	int nStudentID = GetDlgItemInt(IDC_EDIT_ID);
	CString strStudentName;
	GetDlgItemText(IDC_EDIT_NAME, strStudentName);

	/*TODO: 检查nStudentID、strStudentName的合法性*/

	TCHAR szSql[256] = {0};
	_stprintf_s(szSql, TEXT("insert into students(StudentID, StudentName) value(%d,'%s')"),
							nStudentID, (LPCTSTR)strStudentName);

	ExecuteSql(szSql);
	GetRecordset();

	SetDlgItemInt(IDC_EDIT_ID, NULL, FALSE);
	SetDlgItemText(IDC_EDIT_NAME, NULL);
}


void CMFC63Dlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	// 状态发生变化并且被选中，然后把选中的显示在对应的文本框里
	if ((pNMLV->uChanged & LVIF_STATE) && (pNMLV->uNewState & LVIS_SELECTED)) {
		SetDlgItemText(IDC_EDIT_ID, m_list.GetItemText(pNMLV->iItem, 0));
		SetDlgItemText(IDC_EDIT_NAME, m_list.GetItemText(pNMLV->iItem, 1));
	}

	*pResult = 0;
}


void CMFC63Dlg::OnBnClickedButtonModify()
{
	int nNewStudentID = GetDlgItemInt(IDC_EDIT_ID);
	CString strNewStudentName;
	GetDlgItemText(IDC_EDIT_NAME, strNewStudentName);
	int nOldStudentID = (int)m_list.GetItemData(m_list.GetSelectionMark());

	/*TODO: 检查nNewStudentID、strNewStudentName的合法性*/

	TCHAR szSql[256] = {0};
	_stprintf_s(szSql, TEXT("update students set StudentID=%d, StudentName='%s' where StudentID=%d"),
							nNewStudentID, (LPCTSTR)strNewStudentName, nOldStudentID);

	ExecuteSql(szSql);
	GetRecordset();
}
