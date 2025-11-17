#include "menu.h"
#include "cfg.h"
#include "cstrike.h"
#include "overlay.h"
#include "../ext/imgui/imgui.h"
#include "../ext/imgui/imgui_internal.h"
#include "../ext/customimgui/custom.hpp"
#include "../ext/customimgui/etc_element.h"
#include "../ext/customimgui/imgui_setting.h"
#include "../ext/customimgui/Image.h"
#include <string>
#include <Windows.h>
#include <D3DX11tex.h>
#pragma comment(lib, "D3DX11.lib")

ID3D11ShaderResourceView* users = nullptr;
int tabs = 0;
bool bTheme = true;

static std::string GetKeyName(int vk) {
    UINT scanCode = MapVirtualKeyA(vk, MAPVK_VK_TO_VSC);
    char keyName[128] = { 0 };
    if (GetKeyNameTextA(scanCode << 16, keyName, sizeof(keyName)))
        return std::string(keyName);
    switch (vk) {
    case VK_LBUTTON: return "LMB";
    case VK_RBUTTON: return "RMB";
    case VK_MBUTTON: return "MMB";
    case VK_XBUTTON1: return "X1";
    case VK_XBUTTON2: return "X2";
    case VK_INSERT: return "INSERT";
    default: return "Unknown";
    }
}

void CustomStyleColor()
{
    ImGuiStyle& s = ImGui::GetStyle();
    ImGuiContext& g = *GImGui;
    if (bTheme)
    {
        s.Colors[ImGuiCol_WindowBg] = ImLerp(s.Colors[ImGuiCol_WindowBg], bTheme ? ImColor(0.06f, 0.06f, 0.06f, 1.f) : ImColor(5.90f, 5.90f, 5.90f, 1.f), g.IO.DeltaTime * 5.f);
        settings::tabs::text = ImColor(255, 255, 255, 255);
        s.Colors[ImGuiCol_ChildBg] = ImLerp(s.Colors[ImGuiCol_ChildBg], bTheme ? ImColor(0.06f, 0.06f, 0.06f, 1.f) : ImColor(5.90f, 5.90f, 5.90f, 1.f), g.IO.DeltaTime * 5.f);
        s.Colors[ImGuiCol_Text] = ImLerp(s.Colors[ImGuiCol_Text], bTheme ? ImColor(1.f, 1.f, 1.f, 1.f) : ImColor(0.00f, 0.00f, 0.00f, 1.00f), g.IO.DeltaTime * 5.f);
    }
    if (bTheme == false)
    {
        s.Colors[ImGuiCol_WindowBg] = ImLerp(s.Colors[ImGuiCol_WindowBg], !bTheme ? ImColor(0.90f, 0.90f, 0.90f, 1.f) : ImColor(0.06f, 0.06f, 0.06f, 1.f), g.IO.DeltaTime * 5.f);
        settings::tabs::text = ImColor(0, 0, 0, 255);
        s.Colors[ImGuiCol_ChildBg] = ImLerp(s.Colors[ImGuiCol_ChildBg], !bTheme ? ImColor(0.90f, 0.90f, 0.90f, 1.f) : ImColor(0.06f, 0.06f, 0.06f, 1.f), g.IO.DeltaTime * 5.f);
        s.Colors[ImGuiCol_Text] = ImLerp(s.Colors[ImGuiCol_Text], !bTheme ? ImColor(0.f, 0.f, 0.f, 1.f) : ImColor(0.f, 0.f, 0.f, 1.f), g.IO.DeltaTime * 5.f);
    }

    /* if (bTheme)
     {
         s.Colors[ImGuiCol_WindowBg] = ImColor(255, 255, 255, 255);
         s.Colors[ImGuiCol_ChildBg] = ImColor(255, 255, 255, 255);
         //    s.Colors[ImGuiCol_ChildBg] = ImColor(165, 175, 185, 0);
         s.Colors[ImGuiCol_PopupBg] = ImColor(17, 16, 21, 255);
         s.Colors[ImGuiCol_Text] = ImColor(0, 0, 0, 255);
         s.Colors[ImGuiCol_TextDisabled] = ImColor(10, 10, 10, 255);
         //    s.Colors[ImGuiCol_FrameBg] = ImColor(11, 11, 16, 160);
         s.Colors[ImGuiCol_Border] = ImColor(14, 13, 19, 0);
         s.Colors[ImGuiCol_TextSelectedBg] = ImColor(35, 32, 43, 160);
     }
     */
    s.WindowPadding = ImVec2(0, 0);
    s.ChildRounding = 4.f;
    s.WindowRounding = 5.f;


}
bool Menu::IsVisible() {
    return cfg::showMenu;
}

void Menu::Toggle() {
    cfg::showMenu = !cfg::showMenu;
}


void Menu::Render() {
    if (!cfg::showMenu) return;
    CustomStyleColor();

    ImGui::SetNextWindowSize(ImVec2(550, 400), ImGuiCond_FirstUseEver);
    ImGui::Begin("CS2 External STM32", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus);
    {
        const auto& p = ImGui::GetWindowPos();
        ImVec2 wsize = ImGui::GetWindowSize();
        const char* t1 = "CS2 External ";
        const char* t2 = "STM32";
        const char* t3 = " By ";
        const char* t4 = "Dovik";
        float total_w = ImGui::CalcTextSize(t1).x + ImGui::CalcTextSize(t2).x + ImGui::CalcTextSize(t3).x + ImGui::CalcTextSize(t4).x;
        const float col1_x = 160.0f, col1_w = 190.0f;
        const float col2_x = 350.0f, col2_w = 190.0f;
        float mid_x = ( (col1_x + col1_w * 0.5f) + (col2_x + col2_w * 0.5f) ) * 0.5f;
        float start_x = mid_x - total_w * 0.5f - 8.0f;
        ImGui::SetCursorPos(ImVec2(start_x, 22));
        ImGui::TextUnformatted(t1);
        ImGui::SameLine(0.0f, 0.0f);
        ImGui::PushStyleColor(ImGuiCol_Text, ImColor(64, 150, 255).Value);
        ImGui::TextUnformatted(t2);
        ImGui::PopStyleColor();
        ImGui::SameLine(0.0f, 0.0f);
        ImGui::TextUnformatted(t3);
        ImGui::SameLine(0.0f, 0.0f);
        ImGui::PushStyleColor(ImGuiCol_Text, ImColor(64, 150, 255).Value);
        ImGui::TextUnformatted(t4);
        ImGui::PopStyleColor();
        ImGui::SetCursorPos(ImVec2(10, 160));

        if (!users && overlay::g_pd3dDevice)
        {
            HRESULT hr2 = D3DX11CreateShaderResourceViewFromMemory(overlay::g_pd3dDevice, Logo, sizeof Logo, nullptr, nullptr, &users, nullptr);
            (void)hr2;
        }
        if (users)
        {
            ImGui::GetForegroundDrawList()->AddImageRounded((ImTextureID)users, ImVec2(p.x + 0, p.y + 0), ImVec2(p.x + 180, p.y + 180), ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, 255), 0);
        }

        ImGui::SetCursorPos(ImVec2(10, 160));
        BeginGroup();
        {

            if (Tabs(0 == tabs, "F", "Aimbot", ImVec2(90, 40))) tabs = 0;

            if (Tabs(1 == tabs, "A", "Visuals", ImVec2(90, 40))) tabs = 1;

        }
        EndGroup();
        if (tabs == 1)
        {
            // Visuals
            ImGui::SetCursorPos(ImVec2(160, 20));
            if (e_elements::begin_child("ESP Settings", ImVec2(190, 300), false))
            {
                ImGui::SetCursorPos(ImVec2(10, 45));
                ImGui::BeginGroup();
                {
                    ImGui::Checkbox("Enable ESP", &cfg::espOn);
                    ImGui::Checkbox("Team Check", &cfg::teamCheck);
                    ImGui::Checkbox("Box ESP", &cfg::box);
                    ImGui::Checkbox("HealthBar ESP", &cfg::healthBar);
                    ImGui::Checkbox("Bone ESP", &cfg::bones);
                }
                ImGui::EndGroup();
            }
            e_elements::end_child();

            ImGui::SetCursorPos(ImVec2(350, 20));
            if (e_elements::begin_child("Colors", ImVec2(190, 300), false))
            {
                ImGui::SetCursorPos(ImVec2(10, 45));
                ImGui::BeginGroup();
                {
                    ImGui::ColorEdit4("Box Color", cfg::boxColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
                    ImGui::ColorEdit4("Bone Color", cfg::boneColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
                }
                ImGui::EndGroup();
            }
            e_elements::end_child();
        }
        else if (tabs == 0)
        {
            // Aimbot
            ImGui::SetCursorPos(ImVec2(160, 20));
            if (e_elements::begin_child("Aimbot Settings", ImVec2(190, 300), false))
            {
                ImGui::SetCursorPos(ImVec2(10, 45));
                ImGui::BeginGroup();
                {
                    ImGui::Checkbox("Enable Aimbot", &cfg::aimbot);
                    ImGui::Checkbox("Team Check", &cfg::teamCheck);
                    ImGui::Checkbox("Draw FOV", &cfg::drawFov);

                    ImGui::Spacing();
                    static bool waitingForKey = false;
                    std::string keyLabel = waitingForKey ? "Press any key..." : ("Aim Key: " + GetKeyName(cfg::aimKey));
                    if (ImGui::Button(keyLabel.c_str(), ImVec2(140, 0))) {
                        waitingForKey = true;
                    }
                    if (waitingForKey) {
                        for (int vk = 1; vk < 256; ++vk) {
                            if (GetAsyncKeyState(vk) & 0x8000) {
                                cfg::aimKey = vk;
                                waitingForKey = false;
                                break;
                            }
                        }
                    }
                }
                ImGui::EndGroup();
            }
            e_elements::end_child();

            ImGui::SetCursorPos(ImVec2(350, 20));
            if (e_elements::begin_child("FOV / Behavior", ImVec2(190, 300), false))
            {
                ImGui::SetCursorPos(ImVec2(10, 40));
                ImGui::BeginGroup();
                {
                    ImGui::SliderFloat("FOV Size", &cfg::fovSize, 1.0f, 300.0f, "%.0f");
                    ImGui::SliderFloat("Smoothness", &cfg::smoothing, 0.0f, 100.0f, "%.0f");
                    ImGui::ColorEdit4("FOV Color", cfg::fovColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
                }
                ImGui::EndGroup();
            }
            e_elements::end_child();
        }


    } ImGui::End();
}