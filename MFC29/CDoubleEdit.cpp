#include "pch.h"
#include "CDoubleEdit.h"

#define	DOUBLE_EDIT_PROP_NAME TEXT("DOUBLE_EDIT_PROP_NAME")

CDoubleEdit::CDoubleEdit()
{
}

CDoubleEdit::~CDoubleEdit()
{
}

BOOL CDoubleEdit::Attach(HWND hWnd)
{
	if (m_hWnd != NULL) {
		DebugBreak();
		return FALSE;
	}

	m_hWnd = hWnd;

	// 设定一个属性
	SetProp(m_hWnd, DOUBLE_EDIT_PROP_NAME, this);

	// GWL_WNDPROC	设置窗口过程的新地址
	m_lOldProc = SetWindowLong(m_hWnd, GWL_WNDPROC, (LONG)NewEditProc);
	if (m_lOldProc == 0) {
		m_lOldProc = NULL;
		return FALSE;
	}

	return TRUE;
}

BOOL CDoubleEdit::GetStringValue(LPTSTR lpBuffer, int nLen)
{
	return GetWindowText(m_hWnd, lpBuffer, nLen);
}

LRESULT APIENTRY CDoubleEdit::NewEditProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CDoubleEdit *pEdit = (CDoubleEdit *)GetProp(hWnd, DOUBLE_EDIT_PROP_NAME);
	if (pEdit == NULL) {
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	// 拦截WM_CHAR消息
	BOOL bCanceled = FALSE;
	TCHAR szBuf[32] = {0};

	if (uMsg == WM_CHAR) {
		pEdit->GetStringValue(szBuf, 32);

		switch (wParam) {
		case '.':
			// 只允许输入1个小数点
			if (_tcschr(szBuf, '.')) {
				bCanceled = TRUE;
			}
			break;

		case '-':
			// 只允许在开始的位置输入'-'负号
			if (_tcschr(szBuf, '-')) {
				bCanceled = TRUE;
			} else if (LOWORD(SendMessage(hWnd, EM_GETSEL, 0, 0)) != 0) {
				bCanceled = TRUE;
			}
			break;

		default:
			// 允许输入0~9及backspace键
			if ((wParam > '9' || wParam < '0') && wParam != VK_BACK) {
				bCanceled = TRUE;
			}
		}

		if (bCanceled) {
			MessageBeep(-1);
			return 0;
		}
	}

	return CallWindowProc((WNDPROC)pEdit->m_lOldProc, hWnd, uMsg, wParam, lParam);
}
