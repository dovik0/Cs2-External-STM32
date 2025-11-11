#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <TlHelp32.h>
#include <string_view>

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
    const T read(const std::uintptr_t address) const noexcept
    {
        T value = { };
        ::ReadProcessMemory(processHandle, reinterpret_cast<const void*>(address), &value, sizeof(T), NULL);
        return value;
    }

    template <typename T>
    void write(const std::uintptr_t address, const T& value) const noexcept
    {
        ::WriteProcessMemory(processHandle, reinterpret_cast<void*>(address), &value, sizeof(T), NULL);
    }
};

inline Memory* memory = new Memory{ L"cs2.exe" };
inline uintptr_t client = 0;