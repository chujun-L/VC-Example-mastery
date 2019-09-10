
// ��������->������->���� ���psapi.lib
// ��Щϵͳ����ʱ��Ҫ����Ȩ��

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

	// ������̵ĸ���
	procNum = cbNeeded / sizeof(DWORD);
	cout << "���̵ĸ���: " << procNum  << endl;

	for (DWORD i = 0; i < procNum; ++i) {
		HANDLE hProc = ::OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
									FALSE, ProcID[i]);
		if (!hProc) {
			cout << "����" << ProcID[i] << " ��ʧ��" << endl;
		}

		cout << "����" << ProcID[i] << " �򿪳ɹ�" << endl;

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