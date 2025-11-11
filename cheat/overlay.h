#pragma once
#include <Windows.h>
#include <dwmapi.h>
#include "../ext/imgui/imgui.h"
#include "../ext/imgui/imgui_impl_win32.h"
#include "../ext/imgui/imgui_impl_dx11.h"
#include "../ext/imgui/imgui_internal.h"
#include <d3d11.h>
#include <thread>
#include <chrono>

extern "C" {
    inline __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
    inline __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

namespace overlay
{
    // Variables
    inline HWND Window;
    inline WNDCLASSEXA wcex;

    inline static ULONG G_Width = GetSystemMetrics(SM_CXSCREEN);
    inline static ULONG G_Height = GetSystemMetrics(SM_CYSCREEN);

    inline static ID3D11Device* g_pd3dDevice = nullptr;
    inline static ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
    inline static IDXGISwapChain* g_pSwapChain = nullptr;
    inline static bool g_SwapChainOccluded = false;
    inline static ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;
    inline static bool ShouldQuit;
    inline static HANDLE waitableObject = nullptr;
    inline static bool vsync = true;

    VOID CreateRenderTarget();
    VOID SetupWindow();
    bool CreateDeviceD3D(HWND hWnd);
    VOID CleanupDeviceD3D();
    VOID CloseOverlay();
    VOID Render();
    VOID EndRender();
}