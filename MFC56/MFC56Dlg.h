
// MFC56Dlg.h: 头文件
//

#pragma once


// CMFC56Dlg 对话框
class CMFC56Dlg : public CDialogEx
{
// 构造
public:
	CMFC56Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC56_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	ULONG_PTR m_gdiPlusToken;
	Gdiplus::GdiplusStartupInput m_gdiplusStartupInput;

	Gdiplus::Image *m_pImage;

	BOOL GetImageCLSID(const WCHAR *format, CLSID *pCLSID);

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButton2();
};
