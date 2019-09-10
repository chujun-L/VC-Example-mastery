
// MFC39Dlg.h: 头文件
//

#pragma once


// CMFC39Dlg 对话框
class CMFC39Dlg : public CDialogEx
{
// 构造
public:
	CMFC39Dlg(CWnd* pParent = nullptr);	// 标准构造函数
	~CMFC39Dlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC39_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	HANDLE m_hInRead;
	HANDLE m_hOutWrite;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRunCmd();
};
