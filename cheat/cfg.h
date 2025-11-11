#pragma once
#include <Windows.h>

namespace cfg {
	inline bool vsync = false;
    const double maxFPS = 500.0;
    inline HANDLE hSerial = nullptr;                // variable globale unique
    inline const char* portName = "\\\\.\\COM9";

    inline bool teamCheck = true;
    inline bool espOn = false;
    inline bool bones = false;
	inline bool box = false;
	inline bool healthBar = false;

    inline bool aimbot = false;
    inline bool drawFov = false;
    inline float smoothing = 50.f;
    inline float fovSize = 25.f;
    inline int aimKey = 0x06;
    inline int menuKey = VK_INSERT;
	inline bool isGameReady = false;
    inline int aimBone = 0;

    inline float boxColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    inline float boneColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    inline float fovColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
}