
// MFC56Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFC56.h"
#include "MFC56Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")


// CMFC56Dlg 对话框



CMFC56Dlg::CMFC56Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC56_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC56Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFC56Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFC56Dlg::OnBnClickedButton1)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON2, &CMFC56Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMFC56Dlg 消息处理程序

BOOL CMFC56Dlg::GetImageCLSID(const WCHAR *format, CLSID *pCLSID)
{
	UINT nNum = 0;
	UINT nSize = 0;
	ImageCodecInfo *pImageCodeInfo = NULL;

	// 获取系统的支持的图片格式
	GetImageEncodersSize(&nNum, &nSize);
	if (nSize == 0) {
		return FALSE;
	}

	// 分配被保存图片的内存空间
	pImageCodeInfo = (ImageCodecInfo *)malloc(nSize);
	if (pImageCodeInfo == NULL) {
		return FALSE;
	}

	GetImageEncoders(nNum, nSize, pImageCodeInfo);

	for (UINT i = 0; i < nNum; i++) {
		// 找到所需要保存的格式
		if (wcscmp(pImageCodeInfo[i].MimeType, format) == 0) {
			// 带回所需要的格式
			*pCLSID = pImageCodeInfo[i].Clsid;
			free(pImageCodeInfo);
			return TRUE;
		}
	}

	free(pImageCodeInfo);
	return FALSE;
}

BOOL CMFC56Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GdiplusStartup(&m_gdiPlusToken, &m_gdiplusStartupInput, NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFC56Dlg::OnPaint()
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
HCURSOR CMFC56Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC56Dlg::OnBnClickedButton1()
{
	Graphics g(this->m_hWnd);
	
	LPCTSTR lpszFilter = TEXT("*.bmp;*.jpg;*.gif;*.png;*.tif;|*.bmp;*.jpg;*.gif;*.png;*.tif;||");
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, lpszFilter, this);
	if (fileDlg.DoModal() == IDOK) {
		//m_pImage = Image::FromFile(TEXT("C:\\Users\\Alex\\Desktop\\新建文件夹\\1.gif"));

		m_pImage = Image::FromFile(fileDlg.GetPathName());
		g.DrawImage(m_pImage, PointF(0.0f, 0.0f));
	}
}


void CMFC56Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	GdiplusShutdown(m_gdiPlusToken);
}


void CMFC56Dlg::OnBnClickedButton2()
{
	LPCTSTR lpFilter = TEXT("*.bmp|*.bmp|*.jpg|*.jpg|*.gif|*.gif||");

	CFileDialog fdlg(FALSE, NULL, NULL, OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT, lpFilter, this);
	if (fdlg.DoModal() == IDOK) {
		//AfxMessageBox(fdlg.GetPathName());

		int nFilter = fdlg.m_ofn.nFilterIndex;
		CLSID fmt = {0};

		switch (nFilter) {
		case 1:
			GetImageCLSID(L"image/bmp", &fmt);
			break;
		case 2:
			GetImageCLSID(L"image/jpeg", &fmt);
			break;
		case 3:
			GetImageCLSID(L"image/gif", &fmt);
			break;
		}

		m_pImage->Save(fdlg.GetPathName(), &fmt);
	}
}
