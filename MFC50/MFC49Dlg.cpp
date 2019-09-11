
// MFC49Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFC49.h"
#include "MFC49Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC49Dlg 对话框



CMFC49Dlg::CMFC49Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC49_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC49Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFC49Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFC49Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFC49Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFC49Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMFC49Dlg 消息处理程序

BOOL CMFC49Dlg::OnInitDialog()
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

void CMFC49Dlg::OnPaint()
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
HCURSOR CMFC49Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC49Dlg::OnBnClickedButton1()
{
	for (int i = 0; i < 100; ++i) {
		SetDlgItemInt(IDC_STATIC_1, i);
		// 会产生主线程阻塞
		Sleep(1000);
	}
}


void CMFC49Dlg::OnBnClickedButton2()
{
	AfxBeginThread(Button2Thread, NULL);
}

void CMFC49Dlg::OnBnClickedButton3()
{
	AfxBeginThread(Button3Thread, NULL);
}


// 因为Button2Thread()是全局函数，所以SetDlgItemInt也需要用全局的。
UINT Button2Thread(LPVOID pParam)
{
	for (int i = 0; i < 100; ++i) {
		::SetDlgItemInt(AfxGetApp()->m_pMainWnd->m_hWnd, IDC_STATIC_2, i, FALSE);
		Sleep(500);
	}

	return 0;
}

UINT Button3Thread(LPVOID pParam)
{
	for (int i = 100; i >=0; --i) {
		::SetDlgItemInt(AfxGetApp()->m_pMainWnd->m_hWnd, IDC_STATIC_3, i, FALSE);
		Sleep(500);
	}

	return 0;
}
