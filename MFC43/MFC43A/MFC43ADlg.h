
// MFC43ADlg.h: 头文件
//

#pragma once


// CMFC43ADlg 对话框
class CMFC43ADlg : public CDialogEx
{
// 构造
public:
	CMFC43ADlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC43A_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	HANDLE m_hMapObj;
	LPTSTR m_pszMapView;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSend();
	CString m_strSend;
};
