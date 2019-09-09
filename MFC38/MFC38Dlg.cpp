
// MFC38Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFC38.h"
#include "MFC38Dlg.h"
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


// CMFC38Dlg 对话框



CMFC38Dlg::CMFC38Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC38_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_hProc = 0;
}

void CMFC38Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFC38Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFC38Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFC38Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFC38Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFC38Dlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CMFC38Dlg 消息处理程序

BOOL CMFC38Dlg::OnInitDialog()
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

void CMFC38Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFC38Dlg::OnPaint()
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
HCURSOR CMFC38Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC38Dlg::OnBnClickedButton1()
{
	// * 在这可以不提升权限
	RaisePrivileges();
	// processId = 3256
	m_hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, 3256);
	if (m_hProc == NULL) {
		AfxMessageBox(TEXT("OpenProcess failed"));
	} else {
		AfxMessageBox(TEXT("OpenProcess success"));
	}
}

void CMFC38Dlg::OnBnClickedButton2()
{
	TerminateProcess(m_hProc, 0);
}

// 提升权限
void CMFC38Dlg::RaisePrivileges()
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken)) {
		AfxMessageBox(TEXT("OpenProcessToken() failed"));
		return;
	}

	if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tkp.Privileges[0].Luid)) {
		AfxMessageBox(TEXT("LookupPrivilegeValue() failed"));
		return;
	}

	if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, NULL, (PTOKEN_PRIVILEGES)NULL, NULL)) {
		AfxMessageBox(TEXT("AdjustTokenPrivileges() failed"));
		CloseHandle(hToken);
		return;
	}
	AfxMessageBox(TEXT("AdjustTokenPrivileges() success"));
}


void CMFC38Dlg::OnBnClickedButton3()
{
	DWORD pid;
	// CalcFrame可以用spy++获取
	HWND hCalc = ::FindWindow(TEXT("CalcFrame"), TEXT("计算器"));
	GetWindowThreadProcessId(hCalc, &pid);

	RaisePrivileges();
	m_hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (m_hProc) {
		AfxMessageBox(TEXT("OpenProcess success"));
	} else {
		AfxMessageBox(TEXT("OpenProcess failed"));
		return;
	}
}


// 当应用程序的标题会发生变化时，可以设置FindWindow()第二个参数为NULL
void CMFC38Dlg::OnBnClickedButton4()
{
	DWORD pid;
	// CalcFrame可以用spy++获取
	HWND hNotepad = ::FindWindow(TEXT("Notepad"), NULL);
	GetWindowThreadProcessId(hNotepad, &pid);

	RaisePrivileges();
	m_hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (m_hProc) {
		AfxMessageBox(TEXT("OpenProcess success"));
	} else {
		AfxMessageBox(TEXT("OpenProcess failed"));
		return;
	}
}
