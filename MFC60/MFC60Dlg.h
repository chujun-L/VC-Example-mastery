
// MFC60Dlg.h: 头文件
//

#pragma once

// 会在Debug目录生成msado15.tlh(类型库头文件)及msado15.tli(类型库实现文件)
#import "C:\Program Files\Common Files\system\ado\msado15.dll" no_namespace rename("EOF", "adoEOF")

// CMFC60Dlg 对话框
class CMFC60Dlg : public CDialogEx
{
// 构造
public:
	CMFC60Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC60_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	_ConnectionPtr m_pConnectionMysql;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonClose();
};
