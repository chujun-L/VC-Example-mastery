
// MFC53Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFC53.h"
#include "MFC53Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC53Dlg 对话框



CMFC53Dlg::CMFC53Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC53_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC53Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFC53Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_OPEN_BITMAP, &CMFC53Dlg::OnOpenBitmap)
	ON_WM_DESTROY()
	ON_COMMAND(ID_ZOOMIN_BITMAP, &CMFC53Dlg::OnZoominBitmap)
	ON_COMMAND(ID_ZOOMOUT_BITMAP, &CMFC53Dlg::OnZoomoutBitmap)
END_MESSAGE_MAP()


// CMFC53Dlg 消息处理程序

void CMFC53Dlg::FreeObjects()
{
	if (m_dc.GetSafeHdc()) {
		m_dc.SelectObject(m_pOldBmp);
		m_dc.DeleteDC();
		m_bmp.DeleteObject();
	}
}

BOOL CMFC53Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_nZoomPercent = 100;
	m_pOldBmp = NULL;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFC53Dlg::OnPaint()
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
		if (!m_dc.GetSafeHdc()) {
			// 没有位图时就不需要画图
			CDialogEx::OnPaint();
		} else {
			CPaintDC dc(this);
			CRect rect;
			GetClientRect(&rect);
			::FillRect(dc.GetSafeHdc(), rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
			BITMAP bm;
			m_bmp.GetBitmap(&bm);
			dc.StretchBlt(0, 0, bm.bmWidth * m_nZoomPercent / 100, bm.bmHeight * m_nZoomPercent / 100,
				&m_dc, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

		}	
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFC53Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC53Dlg::OnOpenBitmap()
{
	// 保证打开第二张图片时的原图的大小
	m_nZoomPercent = 100;

	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST,
					TEXT("*.bmp | *.bmp||"), this);
	if (dlg.DoModal() == IDOK) {
		HBITMAP hbmp = (HBITMAP)LoadImage(NULL, dlg.GetPathName(), 
						IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
		if (!hbmp) {
			AfxMessageBox(TEXT("LoadImage() failed"));
			return;
		}

		FreeObjects();

		m_bmp.Attach(hbmp);

		CDC *pDC = GetDC();
		m_dc.CreateCompatibleDC(pDC);
		ReleaseDC(pDC);
		m_pOldBmp = m_dc.SelectObject(&m_bmp);
		//  失效后会自动转到OnPaint()
		Invalidate(FALSE);
	}
}


void CMFC53Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	FreeObjects();
}


void CMFC53Dlg::OnZoominBitmap()
{
	m_nZoomPercent += 10;
	Invalidate(FALSE);
}


void CMFC53Dlg::OnZoomoutBitmap()
{
	if (m_nZoomPercent > 10) {
		m_nZoomPercent -= 10;
		Invalidate(FALSE);
	}
}
