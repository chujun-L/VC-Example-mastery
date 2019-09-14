// MFC55Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFC55.h"
#include "MFC55Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")
using namespace Gdiplus;


// CMFC55Dlg 对话框



CMFC55Dlg::CMFC55Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC55_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC55Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFC55Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFC55Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMFC55Dlg 消息处理程序

BOOL CMFC55Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// 初始化GDI+
	Gdiplus::GdiplusStartup(&m_pGdiToken, &m_pGdiplusStartupInput, NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFC55Dlg::OnPaint()
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
HCURSOR CMFC55Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC55Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	Gdiplus::GdiplusShutdown(m_pGdiToken);
}


void CMFC55Dlg::OnBnClickedButton1()
{
	Gdiplus::Graphics g(this->m_hWnd);
	FontFamily fontFamily(L"Times New Roman");
	Gdiplus::Font font(&fontFamily, 24);
	PointF pointF(100.0f, 200.0f);
	SolidBrush brush(Color(255, 0, 0, 255));
	
	g.DrawString(L"Hello world", -1, &font, pointF, &brush);
}
