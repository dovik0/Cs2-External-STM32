#pragma once
#ifndef SERIAL_MOUSE_H
#define SERIAL_MOUSE_H

#include <windows.h>
#include <cstdint>
#include <chrono>
#include <iostream>

HANDLE openSerialPort(const char* portName = "\\\\.\\COM9", DWORD baudRate = CBR_9600);
bool sendMouseCommand(HANDLE hSerial, char cmd, int8_t x = 0, int8_t y = 0);

#endif
