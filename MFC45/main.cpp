
// ��������->������->���� ���psapi.lib

#include <Windows.h>
#include <iostream>
#include <Psapi.h>

using namespace std;

int main()
{
	DWORD ProcID[1024];
	DWORD cbNeeded;
	DWORD procNum;

	if (!EnumProcesses(ProcID, sizeof(ProcID), &cbNeeded)) {
		cout << "EnumProcesses() failed" << endl;
		return -1;
	}

	// ������̵ĸ���
	procNum = cbNeeded / sizeof(DWORD);
	cout << "���̵ĸ���: " << procNum  << endl;


	system("pause");
	return 0;
}