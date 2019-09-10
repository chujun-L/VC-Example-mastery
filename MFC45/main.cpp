
// 工程属性->连接器->输入 添加psapi.lib
// 有些系统运行时需要提升权限

#include <Windows.h>
#include <iostream>
#include <Psapi.h>

using namespace std;

int main()
{
	DWORD ProcID[1024];
	DWORD cbNeeded;
	DWORD procNum;
	HMODULE hModes[1024];
	TCHAR szModName[MAX_PATH];

	if (!EnumProcesses(ProcID, sizeof(ProcID), &cbNeeded)) {
		cout << "EnumProcesses() failed" << endl;
		return -1;
	}

	// 计算进程的个数
	procNum = cbNeeded / sizeof(DWORD);
	cout << "进程的个数: " << procNum  << endl;

	for (DWORD i = 0; i < procNum; ++i) {
		HANDLE hProc = ::OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
									FALSE, ProcID[i]);
		if (!hProc) {
			cout << "进程" << ProcID[i] << " 打开失败" << endl;
		}

		cout << "进程" << ProcID[i] << " 打开成功" << endl;

		if (::EnumProcessModules(hProc, hModes, sizeof(hModes), &cbNeeded)) {
			for (DWORD j = 0; j < cbNeeded / sizeof(HMODULE); ++j) {
				if (::GetModuleFileNameEx(hProc, hModes[j], szModName, 
										sizeof(szModName) / sizeof(TCHAR))) {
					cout << j << ":" << szModName << ":" << hModes[j] << endl;
				}
			}
		}
		CloseHandle(hProc);
	}


	system("pause");
	return 0;
}