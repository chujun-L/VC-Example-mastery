
// MFC43ADlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFC43A.h"
#include "MFC43ADlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC43ADlg 对话框



CMFC43ADlg::CMFC43ADlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC43A_DIALOG, pParent)
	, m_strSend(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC43ADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SEND, m_strSend);
}

BEGIN_MESSAGE_MAP(CMFC43ADlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CMFC43ADlg::OnBnClickedButtonSend)
END_MESSAGE_MAP()


// CMFC43ADlg 消息处理程序

BOOL CMFC43ADlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// 创建文件映射
	m_hMapObj = ::CreateFileMapping((HANDLE)0xFFFFFFFF, NULL, PAGE_READWRITE,
						0, 0x1000, TEXT("shared_memory"));
	if (!m_hMapObj) {
		AfxMessageBox(TEXT("CreateFileMapping() failed"));
		return FALSE;
	}

	m_pszMapView = (LPTSTR)::MapViewOfFile(m_hMapObj, FILE_MAP_WRITE, 0, 0, 0);
	if (!m_pszMapView) {
		AfxMessageBox(TEXT("MapViewOfFile() failed"));
		CloseHandle(m_hMapObj);
		return FALSE;
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFC43ADlg::OnPaint()
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
HCURSOR CMFC43ADlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC43ADlg::OnBnClickedButtonSend()
{
	// 自动把文本框的内容获取到m_strSend变量里(动态数据交换/数据关联)
	UpdateData(TRUE);

	// 拷贝到共享内存
	lstrcpy(m_pszMapView, m_strSend);
}
