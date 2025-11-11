#include "memory.h"

Memory::Memory(std::wstring_view processName) noexcept
{
    ::PROCESSENTRY32W entry = { };
    entry.dwSize = sizeof(::PROCESSENTRY32W);

    const HANDLE snapShot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    while (::Process32NextW(snapShot, &entry))
    {
        if (!processName.compare(entry.szExeFile))
        {
            processId = entry.th32ProcessID;
            processHandle = ::OpenProcess(PROCESS_VM_READ, FALSE, processId);
            break;
        }
    }

    if (snapShot)
        ::CloseHandle(snapShot);
}

Memory::~Memory()
{
    if (processHandle)
        ::CloseHandle(processHandle);
}

std::uintptr_t Memory::GetModuleBase(std::wstring_view moduleName) const noexcept
{
    ::MODULEENTRY32W entry = { };
    entry.dwSize = sizeof(::MODULEENTRY32W);

    const HANDLE snapShot = ::CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processId);

    std::uintptr_t result = 0;

    while (::Module32NextW(snapShot, &entry))
    {
        if (!moduleName.compare(entry.szModule))
        {
            result = reinterpret_cast<std::uintptr_t>(entry.modBaseAddr);
            break;
        }
    }

    if (snapShot)
        ::CloseHandle(snapShot);

    return result;
}