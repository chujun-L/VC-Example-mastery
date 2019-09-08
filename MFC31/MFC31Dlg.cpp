
// MFC31Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFC31.h"
#include "MFC31Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFC31Dlg 对话框



CMFC31Dlg::CMFC31Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC31_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC31Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFC31Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFC31Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_WRITE, &CMFC31Dlg::OnBnClickedButtonWrite)
	ON_BN_CLICKED(IDC_BUTTON_READ, &CMFC31Dlg::OnBnClickedButtonRead)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFC31Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMFC31Dlg 消息处理程序

BOOL CMFC31Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFC31Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFC31Dlg::OnPaint()
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
HCURSOR CMFC31Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC31Dlg::OnBnClickedButton1()
{
	long lRet;
	HKEY hKey;
	TCHAR tchData[64];
	DWORD dwSize;

	lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, 
		TEXT("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0"),
		0,
		KEY_QUERY_VALUE,
		&hKey);

	dwSize = sizeof(tchData);
	if (lRet == ERROR_SUCCESS) {
		lRet = RegQueryValueEx(hKey,
			TEXT("ProcessorNameString"),
			NULL,
			NULL,
			(LPBYTE)tchData,
			&dwSize);
		
		if (lRet == ERROR_SUCCESS) {
			SetDlgItemText(IDC_STATIC, tchData);
		} else {
			AfxMessageBox(TEXT("RegQueryValueEx failed"));
		}

	} else {
		AfxMessageBox(TEXT("RegOpenKeyEx failed"));
	}
	RegCloseKey(hKey);
}

/*
 * 1) 执行该程序时需要以管理员身份打开 visual studio 2019
 * 2) 在项目属性->链接器->清单文件->UAC执行级别(requireAdministrator (/level='requireAdministrator'))
 */
void CMFC31Dlg::OnBnClickedButtonWrite()
{
	HKEY hKey;
	long lRet;
	TCHAR *Class = TEXT("");
	DWORD dwDisposition;

	/*
	// 基于Win32的应用程序应使用RegCreateKeyEx功能
	lRet = RegCreateKey(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\MyAppTest"), &hKey);
	if (lRet == ERROR_SUCCESS) {
		AfxMessageBox(TEXT("RegCreateKey success"));
	} else {
		AfxMessageBox(TEXT("RegCreateKey failed"));
		return;
	}*/

	// 注册表的路径HKEY_LOCAL_MACHINE->SOFTWARE->WOW6432Node
	lRet = RegCreateKeyEx(HKEY_LOCAL_MACHINE,
						TEXT("SOFTWARE\\WOW6432Node\\MyAppTest"),
						0,
						Class,
						REG_OPTION_NON_VOLATILE, 
						KEY_WRITE | KEY_READ,
						NULL,
						&hKey,
						&dwDisposition);

	if (lRet == ERROR_SUCCESS) {
		AfxMessageBox(TEXT("RegCreateKeyEx success"));
	} else {
		AfxMessageBox(TEXT("RegCreateKeyEx failed"));
		return;
	}

	// 写数据
	RegSetValue(hKey, NULL, REG_SZ, TEXT("Liebao"), 6);

	DWORD dwAge = 30;
	RegSetValueEx(hKey, TEXT("age"), 0, REG_DWORD, (const BYTE *)&dwAge, 4);

	RegCloseKey(hKey);
}


void CMFC31Dlg::OnBnClickedButtonRead()
{
	LONG lValue = 0;
	
	RegQueryValue(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\WOW6432Node\\MyAppTest"), NULL, &lValue);
	TCHAR *pBuf = new TCHAR[lValue];
	RegQueryValue(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\WOW6432Node\\MyAppTest"), pBuf, &lValue);
	AfxMessageBox(pBuf);
	delete[] pBuf;
}


void CMFC31Dlg::OnBnClickedButton2()
{
	HKEY hKey;
	DWORD dwType = 0;
	DWORD dwData = 0;
	DWORD dwLen = 0;
	CString str;

	RegOpenKey(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\WOW6432Node\\MyAppTest"), &hKey);
	RegQueryValueEx(hKey, TEXT("age"), 0, &dwType, (LPBYTE)&dwData, &dwLen);

	str.Format(TEXT("age = %d"), dwData);
	AfxMessageBox(str);
}
