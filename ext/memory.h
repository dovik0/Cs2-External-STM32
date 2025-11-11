#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <TlHelp32.h>
#include <string_view>

extern "C" intptr_t Luck_ReadVirtualMemory(HANDLE ProcessHandle, PVOID BaseAddress, PVOID Buffer, ULONG NumberOfBytesToRead, PULONG NumberOfBytesRead);
extern "C" intptr_t Luck_WriteVirtualMemory(HANDLE Processhandle, PVOID BaseAddress, PVOID Buffer, ULONG NumberOfBytesToWrite, PULONG NumberOfBytesWritten);

class Memory
{
private:
    std::uintptr_t processId = 0;
    void* processHandle = nullptr;

public:
    Memory(std::wstring_view processName) noexcept;
    ~Memory();

    std::uintptr_t GetModuleBase(std::wstring_view moduleName) const noexcept;

    template <typename T>
    T read(const std::uintptr_t address) const noexcept
    {
        T value = { };
        ::Luck_ReadVirtualMemory(processHandle, reinterpret_cast<void*>(address), &value, sizeof(T), NULL);
        return value;
    }

    template <typename T>
    void write(const std::uintptr_t address, const T& value) const noexcept
    {
        ::Luck_WriteVirtualMemory(processHandle, reinterpret_cast<void*>(address), &value, sizeof(T), NULL);
    }
};

inline Memory* memory = new Memory{ L"cs2.exe" };
inline uintptr_t client = 0;