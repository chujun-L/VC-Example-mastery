
// MFC54Dlg.h: 头文件
//

#pragma once


// CMFC54Dlg 对话框
class CMFC54Dlg : public CDialogEx
{
// 构造
public:
	CMFC54Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC54_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	CBrush m_brush;
	CBitmap m_bMap;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor);
	CComboBox m_cmbBrush;
	afx_msg void OnCbnSelchangeComboSlbrush();
};
