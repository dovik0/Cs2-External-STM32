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
    extern HWND Window;
    extern WNDCLASSEXA wcex;

    extern ULONG G_Width;
    extern ULONG G_Height;

    extern ID3D11Device* g_pd3dDevice;
    extern ID3D11DeviceContext* g_pd3dDeviceContext;
    extern IDXGISwapChain* g_pSwapChain;
    extern bool g_SwapChainOccluded;
    extern ID3D11RenderTargetView* g_mainRenderTargetView;
    extern bool ShouldQuit;
    extern HANDLE waitableObject;
    extern bool vsync;

    VOID CreateRenderTarget();
    VOID SetupWindow();
    bool CreateDeviceD3D(HWND hWnd);
    VOID CleanupDeviceD3D();
    VOID CloseOverlay();
    VOID Render();
    VOID EndRender();
}