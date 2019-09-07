
// MFC28Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFC28.h"
#include "MFC28Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 自定义消息第1种方法
#define WM_DEFINED_MSG		(WM_USER + 100)
// 自定义消息第2种方法
#define MY_REGISTER_MSG_STR	TEXT("MY_MSG_STRING")

UINT MODE2_MSG_ID;

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


// CMFC28Dlg 对话框



CMFC28Dlg::CMFC28Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC28_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	MODE2_MSG_ID = RegisterWindowMessage(MY_REGISTER_MSG_STR);
}

void CMFC28Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFC28Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFC28Dlg::OnBnClickedButton1)
	ON_MESSAGE(WM_DEFINED_MSG, &CMFC28Dlg::OnDefindMsg)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFC28Dlg::OnBnClickedButton2)
	ON_REGISTERED_MESSAGE(MODE2_MSG_ID, &CMFC28Dlg::OnRegisterMsg)
END_MESSAGE_MAP()


// CMFC28Dlg 消息处理程序

BOOL CMFC28Dlg::OnInitDialog()
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

void CMFC28Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFC28Dlg::OnPaint()
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
HCURSOR CMFC28Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC28Dlg::OnBnClickedButton1()
{
	//PostMessage(WM_DEFINED_MSG, 0, 0);
	SendMessage(WM_DEFINED_MSG, 0, 0);
}

void CMFC28Dlg::OnBnClickedButton2()
{
	SendMessage(MODE2_MSG_ID, 0, 0);
}

LRESULT CMFC28Dlg::OnDefindMsg(WPARAM wParam, LPARAM lParam)
{
	TCHAR szBuf[128] = {0};

	_stprintf_s(szBuf, TEXT("收到自定义消息：WM_DEFINED_MSG, ID=0x%X"), WM_DEFINED_MSG);
	SetDlgItemText(IDC_OUTPUT, szBuf);

	return LRESULT();
}

LRESULT CMFC28Dlg::OnRegisterMsg(WPARAM wParam, LPARAM lParam)
{
	TCHAR szBuf[128] = { 0 };

	_stprintf_s(szBuf, TEXT("收到Register消息：WM_REGISTER_MSG, ID=0x%X"), MODE2_MSG_ID);
	SetDlgItemText(IDC_OUTPUT, szBuf);
	return LRESULT();
}