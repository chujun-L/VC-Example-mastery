#pragma once
class CDoubleEdit
{
public:
	CDoubleEdit();
	~CDoubleEdit();

	BOOL Attach(HWND hWnd);

private:
	HWND m_hWnd;
	long m_lOldProc;

	static LRESULT APIENTRY NewEditProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

