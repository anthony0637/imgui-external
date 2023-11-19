#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>


DWORD GetProcId(const char* procName);

uintptr_t GetModuleBaseAddress(DWORD procId, const char* modName);