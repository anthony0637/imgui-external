#include "snapshots.h"
#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>

DWORD GetProcId(const char* procName)
{
    DWORD procId = 0;

    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnap != INVALID_HANDLE_VALUE)
    {

        PROCESSENTRY32 procEntry;
        procEntry.dwSize = sizeof(procEntry);

        if (Process32First(hSnap, &procEntry))
        {
            do
            {
                if (!strcmp(procEntry.szExeFile, procName))
                {
                    procId = procEntry.th32ProcessID;
                    break;
                }

            } while (Process32Next(hSnap, &procEntry));
        }
    }
    CloseHandle(hSnap);
    return procId;
}

uintptr_t GetModuleBaseAddress(DWORD procId, const char* modName)
{
    uintptr_t module = 0;

    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);

    if (hSnap != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32 modEntry;
        modEntry.dwSize = sizeof(modEntry);

        if (Module32First(hSnap, &modEntry))
        {
            do
            {
                if (strcmp(modEntry.szModule, modName) == 0)
                {
                    module = (uintptr_t)modEntry.modBaseAddr;
                    break;
                }

            } while (Module32Next(hSnap, &modEntry));
        }
    }

    CloseHandle(hSnap);
    return module;
}