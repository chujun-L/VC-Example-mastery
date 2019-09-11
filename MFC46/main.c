#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <WtsApi32.h>

#pragma comment(lib, "WtsApi32.lib")


int main()
{
	// 本计算机的名称
	char *szServerName = "DESKTOP-UVKHP3U";
	PWTS_PROCESS_INFO pWtspi;
	DWORD pCount;

	HANDLE hWtsServer = WTSOpenServer(szServerName);

	if (!WTSEnumerateProcesses(hWtsServer, 0, 1, &pWtspi, &pCount)) {
		printf("Error");
		return -1;
	}

	for (DWORD i = 0; i < pCount; ++i) {
		printf("ProcessID: %d (%s)\n", pWtspi[i].ProcessId, pWtspi[i].pProcessName);
	}

	WTSCloseServer(hWtsServer);

	system("pause");
	return 0;
}