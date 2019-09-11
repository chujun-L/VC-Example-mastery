#include <iostream>
#include <Windows.h>
#include <NTSecAPI.h>

using namespace std;

typedef DWORD (WINAPI *ZwQSInfo) (DWORD, PVOID, DWORD, PDWORD);

#define SystemProcessesAndThreadsInformation 5

// 进程信息结构体
typedef struct _SYSTEM_PROCESS_INFORMATION {
	DWORD NextEntryDalta;
	DWORD ThreadCount;
	DWORD Reserved1[6];
	FILETIME ftCreateTime;
	FILETIME ftUserTime;
	FILETIME ftKernelTime;
	UNICODE_STRING ProcessName;
	DWORD BasePriority;
	DWORD ProcessId;
	DWORD InheritedFromProcessId;
	DWORD HandleCount;
	DWORD Reserved2[2];
	DWORD VmCounters;
	DWORD dCommitCharege;
	PVOID ThreadInfos[1];
}SYSTEM_PROCESS_INFORMATION, *PSYSTEM_PROCESS_INFORMATION;

int main()
{
	ULONG cbBuf = 0x10000;
	LPVOID pBuf = NULL;

	pBuf = malloc(cbBuf);
	if (!pBuf) {
		cout << "malloc pBuf failed" << endl;
		return -1;
	}
	memset(pBuf, 0 , sizeof(cbBuf) / sizeof(ULONG));

	HMODULE hNtDLL = GetModuleHandle("ntdll.dll");
	if (!hNtDLL) {
		cout << "GetModuleHandle() failed" << endl;
		return -1;
	}

	ZwQSInfo zwqsinfo = (ZwQSInfo)GetProcAddress(hNtDLL, "ZwQuerySystemInformation");
	if (!zwqsinfo) {
		cout << "GetProcAddress() failed" << endl;
		return -1;
	}

	zwqsinfo(SystemProcessesAndThreadsInformation, pBuf, cbBuf, NULL);

	PSYSTEM_PROCESS_INFORMATION pInfo = (PSYSTEM_PROCESS_INFORMATION)pBuf;

	for (;;) {
		//printf("ProcessID: %d (%ls)\n", pInfo->ProcessId, pInfo->ProcessName.Buffer);

		// 产生读取访问权限的异常
		if (pInfo->NextEntryDalta == 0) break;

		pInfo = (PSYSTEM_PROCESS_INFORMATION)(((PUCHAR)pInfo) + pInfo->NextEntryDalta);
	}

	free(pBuf);
	system("pause");
	return 0;
}