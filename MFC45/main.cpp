
// 工程属性->连接器->输入 添加psapi.lib

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

	// 计算进程的个数
	procNum = cbNeeded / sizeof(DWORD);
	cout << "进程的个数: " << procNum  << endl;


	system("pause");
	return 0;
}