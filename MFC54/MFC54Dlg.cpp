
// MFC54Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFC54.h"
#include "MFC54Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC54Dlg 对话框



CMFC54Dlg::CMFC54Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC54_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC54Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SLBRUSH, m_cmbBrush);
}

BEGIN_MESSAGE_MAP(CMFC54Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(IDC_COMBO_SLBRUSH, &CMFC54Dlg::OnCbnSelchangeComboSlbrush)
END_MESSAGE_MAP()


// CMFC54Dlg 消息处理程序

BOOL CMFC54Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_bMap.LoadBitmap(IDB_BITMAP1);

	// 图案画刷
	//m_brush.CreatePatternBrush(&m_bMap);

	// 纯色的逻辑画笔
	//m_brush.CreateSolidBrush(RGB(255, 200, 0));

	// 阴影画刷
	//m_brush.CreateHatchBrush(HS_DIAGCROSS, RGB(255, 200, 0));

	// 选中一个作为默认的
	m_cmbBrush.SetCurSel(2);
	OnCbnSelchangeComboSlbrush();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFC54Dlg::OnPaint()
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
HCURSOR CMFC54Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



HBRUSH CMFC54Dlg::OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	if (m_brush.GetSafeHandle() && nCtlColor == CTLCOLOR_DLG) {
		return m_brush;
	}

	return hbr;
}

// 通过组合框来选择不同的画刷
void CMFC54Dlg::OnCbnSelchangeComboSlbrush()
{
	if (m_brush.GetSafeHandle()) {
		m_brush.DeleteObject();
	}
	
	switch (m_cmbBrush.GetCurSel()) {
	case 0:
		m_brush.CreateSolidBrush(RGB(255, 200, 0));
		break;
	case 1:
		m_brush.CreateHatchBrush(HS_DIAGCROSS, RGB(255, 200, 0));
		break;
	case 2:
		m_brush.CreatePatternBrush(&m_bMap);
		break;
	}
	
	// 会调用OnCtlColor返回的画刷
	Invalidate(TRUE);
}
