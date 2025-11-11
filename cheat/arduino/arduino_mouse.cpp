#include "arduino_mouse.h"

HANDLE openSerialPort(const char* portName, DWORD baudRate) {
    HANDLE hSerial = CreateFileA(
        portName,
        GENERIC_READ | GENERIC_WRITE,
        0,
        nullptr,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        nullptr
    );

    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "[Serial] Failed to open " << portName << std::endl;
        return INVALID_HANDLE_VALUE;
    }

    DCB params = { 0 };
    params.DCBlength = sizeof(params);
    if (!GetCommState(hSerial, &params)) {
        std::cerr << "[Serial] GetCommState failed" << std::endl;
        CloseHandle(hSerial);
        return INVALID_HANDLE_VALUE;
    }

    params.BaudRate = baudRate;
    params.ByteSize = 8;
    params.StopBits = ONESTOPBIT;
    params.Parity = NOPARITY;

    if (!SetCommState(hSerial, &params)) {
        std::cerr << "[Serial] SetCommState failed" << std::endl;
        CloseHandle(hSerial);
        return INVALID_HANDLE_VALUE;
    }

    COMMTIMEOUTS timeouts = { 0 };
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    SetCommTimeouts(hSerial, &timeouts);

    std::cout << "[Serial] Port " << portName << " opened at " << baudRate << " baud." << std::endl;
    return hSerial;
}

bool sendMouseCommand(HANDLE hSerial, char cmd, int8_t x, int8_t y) {
    if (!hSerial || hSerial == INVALID_HANDLE_VALUE)
        return false;

    static auto lastSend = std::chrono::steady_clock::now();
    auto now = std::chrono::steady_clock::now();

    // Limit to ~60 Hz (16 ms between sends)
    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastSend).count() < 16)
        return true;
    lastSend = now;

    unsigned char buffer[3] = {
        static_cast<unsigned char>(cmd),
        static_cast<unsigned char>(x),
        static_cast<unsigned char>(y)
    };

    DWORD bytesWritten = 0;
    BOOL ok = WriteFile(hSerial, buffer, sizeof(buffer), &bytesWritten, nullptr);
    if (!ok || bytesWritten != sizeof(buffer)) {
        std::cerr << "[Serial] WriteFile failed (" << bytesWritten << " bytes written)" << std::endl;
        return false;
    }

    return true;
}
