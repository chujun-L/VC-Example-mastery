
// MFC42Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFC42.h"
#include "MFC42Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC42Dlg 对话框



CMFC42Dlg::CMFC42Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC42_DIALOG, pParent)
	, m_strText(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

// 数据交换
void CMFC42Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TEXT, m_strText);
}

BEGIN_MESSAGE_MAP(CMFC42Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CMFC42Dlg 消息处理程序

BOOL CMFC42Dlg::LoadFile(CString strFileName)
{
	HANDLE hFile;
	HANDLE hFileMapping;
	void *pBase;

	// step 1
	hFile = ::CreateFile(strFileName, GENERIC_READ, FILE_SHARE_READ, 0,
				OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, 0);
	if (hFile == INVALID_HANDLE_VALUE) {
		AfxMessageBox(TEXT("CreateFile() failed"));
		return FALSE;
	}

	// step 2
	hFileMapping = ::CreateFileMapping(hFile, 0, PAGE_READONLY, 0, 0, NULL);
	if (!hFileMapping) {
		AfxMessageBox(TEXT("CreateFileMapping() failed"));
		CloseHandle(hFile);
		return FALSE;
	}

	// step 3
	pBase = ::MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, 0);
	if (!pBase) {
		AfxMessageBox(TEXT("MapViewOfFile() failed"));
		CloseHandle(hFileMapping);
		CloseHandle(hFile);
		return FALSE;
	}

	// 读映射文件的内容
	m_strText = (LPTSTR)pBase;

	// step 4
	UnmapViewOfFile(pBase);
	CloseHandle(hFileMapping);
	CloseHandle(hFile);

	return TRUE;
}

BOOL CMFC42Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	LoadFile(TEXT("test.txt"));
	UpdateData(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFC42Dlg::OnPaint()
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
HCURSOR CMFC42Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

