#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>

using namespace std;


int main()
{
	PROCESSENTRY32 procEntry = {0};
	BOOL bRet;

	HANDLE hProcSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcSnap == INVALID_HANDLE_VALUE) return -1;

	procEntry.dwSize = sizeof(procEntry);
	bRet = ::Process32First(hProcSnap, &procEntry);
	while (bRet) {
		cout << "ProcessID: " << procEntry.th32ProcessID << " " 
							 << procEntry.szExeFile << endl;

		bRet = ::Process32Next(hProcSnap, &procEntry);
	}
	CloseHandle(hProcSnap);

	system("pause");
	return 0;
}