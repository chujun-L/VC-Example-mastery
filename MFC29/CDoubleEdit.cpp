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

	// �趨һ������
	SetProp(m_hWnd, DOUBLE_EDIT_PROP_NAME, this);

	// GWL_WNDPROC	���ô��ڹ��̵��µ�ַ
	m_lOldProc = SetWindowLong(m_hWnd, GWL_WNDPROC, (LONG)NewEditProc);
	if (m_lOldProc == 0) {
		m_lOldProc = NULL;
		return FALSE;
	}

	return TRUE;
}

LRESULT APIENTRY CDoubleEdit::NewEditProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CDoubleEdit *pEdit = (CDoubleEdit *)GetProp(hWnd, DOUBLE_EDIT_PROP_NAME);

	// ����WM_CHAR��Ϣ
	BOOL bCanceled = FALSE;

	if (uMsg == WM_CHAR) {
		switch (wParam) {
		default:
			// ��������0~9��backspace��
			if ((wParam >= '9' || wParam <= '0') && wParam != VK_BACK) {
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
