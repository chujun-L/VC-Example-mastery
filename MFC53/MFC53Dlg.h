
// MFC53Dlg.h: 头文件
//

#pragma once


// CMFC53Dlg 对话框
class CMFC53Dlg : public CDialogEx
{
// 构造
public:
	CMFC53Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC53_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	int m_nZoomPercent;
	CBitmap m_bmp;
	CBitmap *m_pOldBmp;
	CDC m_dc;

	void FreeObjects();

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOpenBitmap();
	afx_msg void OnDestroy();
	afx_msg void OnZoominBitmap();
	afx_msg void OnZoomoutBitmap();
};
