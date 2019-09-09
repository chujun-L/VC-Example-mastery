
// MFC39Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFC39.h"
#include "MFC39Dlg.h"
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


// CMFC39Dlg 对话框



CMFC39Dlg::CMFC39Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC39_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC39Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFC39Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RUN_CMD, &CMFC39Dlg::OnBnClickedRunCmd)
END_MESSAGE_MAP()


// CMFC39Dlg 消息处理程序

BOOL CMFC39Dlg::OnInitDialog()
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

void CMFC39Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFC39Dlg::OnPaint()
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
HCURSOR CMFC39Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 设置工程属性：作用多字节字符集
void CMFC39Dlg::OnBnClickedRunCmd()
{
	// 管道的读、写句柄
	HANDLE hPWrite, hPRead;

	SECURITY_ATTRIBUTES sa;
	::ZeroMemory(&sa, sizeof(sa));
	sa.nLength = sizeof(sa);
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;

	TCHAR szBuf[4096] = {0};
	DWORD dwRead;
	CString strOutput;
	
	BOOL bCreatProc;
	TCHAR szCmd[MAX_PATH * 2] = {0};
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	::ZeroMemory(&si, sizeof(si));
	::ZeroMemory(&pi, sizeof(pi));
	si.cb = sizeof(si);
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);

	bCreatProc = ::CreatePipe(&hPRead, &hPWrite, &sa, 0);
	if (!bCreatProc) {
		MessageBox(TEXT("CreatePipe() failed"));
		return;
	}
	si.hStdOutput = hPWrite;
	si.hStdError = hPWrite;

	GetDlgItemText(IDC_EDIT_CMD, szCmd, MAX_PATH * 2);
	bCreatProc = ::CreateProcess(NULL, szCmd, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi);
	// 防止句柄泄露警告
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	if (!bCreatProc) {
		MessageBox(TEXT("CreateProcess() failed"));
		CloseHandle(hPWrite);
		CloseHandle(hPRead);
		return;
	} else {
		// 读管道前先关掉写管道的句柄
		CloseHandle(hPWrite);
		// 循环读
		while (1) {
			/*::ZeroMemory(szBuf, sizeof(szBuf));*/
			memset(szBuf, 0, sizeof(szBuf));
			if (!ReadFile(hPRead, szBuf, 4096, &dwRead, NULL)) {
				// 没读取的内容时退出循环
				break;
			}

			strOutput += szBuf;
			SetDlgItemText(IDC_EDIT_OUTPUT, strOutput);
		}

		CloseHandle(hPRead);
	}
}
