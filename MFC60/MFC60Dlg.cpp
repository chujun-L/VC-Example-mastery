
// MFC60Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFC60.h"
#include "MFC60Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC60Dlg 对话框



CMFC60Dlg::CMFC60Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC60_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// 创建连接对象
	//if (!SUCCEEDED(m_pConnectionMysql.CreateInstance(__uuidof(Connection)))) {
	//	m_pConnectionMysql = NULL;
	//	AfxMessageBox(TEXT("创建连接对象失败"));
	//}

	// 创建连接对象
	try {
		m_pConnectionMysql.CreateInstance(__uuidof(Connection));
	} catch (_com_error e) {
		AfxMessageBox(e.Description());
	}
}

void CMFC60Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFC60Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CMFC60Dlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CMFC60Dlg::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_READ, &CMFC60Dlg::OnBnClickedButtonRead)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CMFC60Dlg::OnBnClickedButtonClear)
END_MESSAGE_MAP()


// CMFC60Dlg 消息处理程序

BOOL CMFC60Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFC60Dlg::OnPaint()
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
HCURSOR CMFC60Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC60Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	//m_pRecordsetMysql->Release();
	//m_pConnectionMysql->Release();
	CoUninitialize();
}


void CMFC60Dlg::OnBnClickedButtonOpen()
{
	// 防止二次打开连接
	if (m_pConnectionMysql->State & adStateOpen) {
		AfxMessageBox(TEXT("mysql已经打开连接"));
		return;
	}

	// 连接字符串
	// 写法1
	//CString strConnection = TEXT("Provider=MSDASQL.1; Persist Security Info=False; \
	//							Driver = MySQL ODBC 8.0 Unicode Driver; \
	//							SERVER = localhost; Data Source = mysql_ado");
	// 写法2 用户名、密码、数据库名已经在mysql_ado指定
	m_pConnectionMysql->ConnectionString = TEXT("Provider=MSDASQL.1; Persist Security Info=False; \
											Driver = MySQL ODBC 8.0 Unicode Driver; \
											SERVER = localhost; Data Source = mysql_ado");

	// 打开mysql
	try {
		// 写法1
		//m_pConnectionMysql->Open(_bstr_t(strConnection),
		//						TEXT(""), TEXT(""), adConnectUnspecified);

		// 写法2
		m_pConnectionMysql->Open(TEXT(""), TEXT(""), TEXT(""), adConnectUnspecified);
	} catch (_com_error e) {
		AfxMessageBox(e.Description());
	}
}


void CMFC60Dlg::OnBnClickedButtonClose()
{
	try {
		m_pConnectionMysql->Close();
		//m_pConnectionMysql->Release();
	} catch (_com_error e) {
		AfxMessageBox(e.Description());
	}
}


void CMFC60Dlg::OnBnClickedButtonRead()
{
	if (!(m_pConnectionMysql->State & adStateOpen)) {
		AfxMessageBox(TEXT("未打开连接"));
		return;
	}

	m_pRecordsetMysql = m_pConnectionMysql->Execute(TEXT("select * from t_booktype"), NULL, adCmdText);
	// 循环读数据库行
	while (!m_pRecordsetMysql->adoEOF) {
		((CListBox *)GetDlgItem(IDC_LIST1))->AddString((_bstr_t)m_pRecordsetMysql->GetCollect(TEXT("bookTypeName")));

		m_pRecordsetMysql->MoveNext();
	}

	//m_pRecordsetMysql->Close();
	//m_pRecordsetMysql->Release();
}


void CMFC60Dlg::OnBnClickedButtonClear()
{
	// 清空列表框的内容
	((CListBox *)GetDlgItem(IDC_LIST1))->ResetContent();
}
