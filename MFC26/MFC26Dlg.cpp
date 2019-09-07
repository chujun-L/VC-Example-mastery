
// MFC26Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFC26.h"
#include "MFC26Dlg.h"
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


// CMFC26Dlg 对话框



CMFC26Dlg::CMFC26Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC26_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC26Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFC26Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFC26Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFC26Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMFC26Dlg 消息处理程序

BOOL CMFC26Dlg::OnInitDialog()
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
	m_hCursor = LoadCursor(NULL, IDC_SIZEALL);
	GetDlgItem(IDC_CAP)->GetWindowRect(&m_rtCtrl);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFC26Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFC26Dlg::OnPaint()
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
HCURSOR CMFC26Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC26Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 检查鼠标是否在小图标上
	if (point.x >= m_rtCtrl.left && point.x <= m_rtCtrl.right
		|| point.y >= m_rtCtrl.top && point.y <= m_rtCtrl.bottom) {
		//AfxMessageBox(TEXT("hit"));

		m_bCapturing = TRUE;
		SetCapture();
		SetCursor(m_hCursor);
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFC26Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	TCHAR szBuf[MAX_PATH] = { 0 };

	if (m_bCapturing) {
		ReleaseCapture();
		m_bCapturing = FALSE;

		POINT pt = point;
		ClientToScreen(&pt);

		m_hwndDest = ::WindowFromPoint(pt);
		_stprintf_s(szBuf, TEXT("0x%.8X"), m_hwndDest);
		SetDlgItemText(IDC_EDIT_HWND, szBuf);
		GetClassName(m_hwndDest, szBuf, MAX_PATH);
		SetDlgItemText(IDC_EDIT_CLASS, szBuf);

		::SendMessage(m_hwndDest, WM_GETTEXT, MAX_PATH, (LPARAM)szBuf);
		SetDlgItemText(IDC_EDIT_TEXT, szBuf);
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CMFC26Dlg::OnBnClickedButton1()
{
	CString str;

	GetDlgItemText(IDC_EDIT_MODIFY, str);
	::SendMessage(m_hwndDest, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)str);
}


void CMFC26Dlg::OnBnClickedButton2()
{
	::SendMessage(m_hwndDest, WM_CLOSE, 0, 0);
}
