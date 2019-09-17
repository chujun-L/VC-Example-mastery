
// MFC63Dlg.h: 头文件
//

#pragma once

#import "C:\Program Files\Common Files\system\ado\msado15.dll" no_namespace rename("EOF", "adoEOF")

// CMFC63Dlg 对话框
class CMFC63Dlg : public CDialogEx
{
// 构造
public:
	CMFC63Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC63_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	_ConnectionPtr m_pCn;
	_RecordsetPtr m_pRs;

	void GetRecordset();
	void ExecuteSql(LPCTSTR lpSql);

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	CListCtrl m_list;
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonAdd();
};
