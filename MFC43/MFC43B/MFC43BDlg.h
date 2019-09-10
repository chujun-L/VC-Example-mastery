
// MFC43BDlg.h: 头文件
//

#pragma once


// CMFC43BDlg 对话框
class CMFC43BDlg : public CDialogEx
{
// 构造
public:
	CMFC43BDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC43B_DIALOG };
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
	afx_msg void OnBnClickedCancel();
	CString m_strText;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
