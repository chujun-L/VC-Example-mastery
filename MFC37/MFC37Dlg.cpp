
// MFC37Dlg.cpp: 实现文件
//
#include "pch.h"
#include "framework.h"
#include "MFC37.h"
#include "MFC37Dlg.h"
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


// CMFC37Dlg 对话框



CMFC37Dlg::CMFC37Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC37_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC37Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFC37Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFC37Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFC37Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFC37Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFC37Dlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CMFC37Dlg 消息处理程序

// 打印GetLastError的错误信息文本
void CMFC37Dlg::ErrorExit(LPCTSTR lpszFun)
{
	DWORD dwMessageID = GetLastError();
	TCHAR *szMessage = NULL;
	TCHAR szTitle[64] = {0};

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
				FORMAT_MESSAGE_FROM_SYSTEM,
				NULL, dwMessageID, 0, (LPWSTR)&szMessage, 0, NULL);

	_stprintf_s(szTitle, TEXT("执行%s时GetLastError() = %d"), lpszFun, dwMessageID);

	MessageBox(szMessage, szTitle, MB_OK);
}

BOOL CMFC37Dlg::OnInitDialog()
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

void CMFC37Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFC37Dlg::OnPaint()
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
HCURSOR CMFC37Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC37Dlg::OnBnClickedButton1()
{
	// 方法1：
	WinExec("calc.exe", SW_SHOW);
}


void CMFC37Dlg::OnBnClickedButton2()
{
	// 方法2：
	//long lRet;

	ShellExecute(NULL,TEXT("open"), TEXT("test.txt"), NULL, NULL, SW_SHOW);
	/*if (lRet == ERROR_FILE_NOT_FOUND) {

	}*/
	
}


void CMFC37Dlg::OnBnClickedButton3()
{
	// 方法3：
	SHELLEXECUTEINFO info;

	memset(&info, 0, sizeof(info));
	info.lpVerb = TEXT("open");
	info.lpFile = TEXT("test.txt");
	info.lpParameters = NULL;
	info.fMask = SEE_MASK_NOCLOSEPROCESS;
	info.nShow = SW_SHOWDEFAULT;

	if (!ShellExecuteEx(&info)) {
		ErrorExit(TEXT("ShellExecuteEx"));
	}
}


void CMFC37Dlg::OnBnClickedButton4()
{
	/* 
		旧的windows版本用的:
			WinExec()
			ShellExecute()
			ShellExecuteEx()
	*/
	
	// 方法4： 
	PROCESS_INFORMATION pi;
	STARTUPINFO si;

	//memset(&si, 0, sizeof(si));
	::ZeroMemory(&pi, sizeof(pi));
	::ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	si.wShowWindow = SW_SHOW;
	si.dwFlags = STARTF_USESHOWWINDOW;

	::CreateProcess(TEXT("C://Windows//System32//calc.exe"),
					NULL, NULL, FALSE, NULL, NULL, NULL, NULL,
					&si, &pi);

	// 等待子进程退出 
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}
