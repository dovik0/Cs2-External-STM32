#include "menu.h"
#include "cfg.h"
#include "cstrike.h"
#include "../ext/imgui/imgui.h"
#include "../ext/imgui/imgui_internal.h"
#include <string>
#include <Windows.h>

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

static bool showMenu = true;
static int selectedTab = 0;

bool Menu::IsVisible() {
    return showMenu;
}

void Menu::Toggle() {
    showMenu = !showMenu;
}


void Menu::Render() {
    if (!showMenu) return;

    ImGui::SetNextWindowSize(ImVec2(450, 300), ImGuiCond_FirstUseEver);
    ImGui::Begin("##CS2Base", &showMenu, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImVec2 window_pos = ImGui::GetWindowPos();
    ImVec2 window_size = ImGui::GetWindowSize();
    draw_list->AddRectFilled(window_pos, ImVec2(window_pos.x + window_size.x, window_pos.y + 30), ImColor(0.12f, 0.12f, 0.15f, 1.0f));
    ImGui::SetCursorPosY(8);
    ImGui::SetCursorPosX(12);
    ImGui::TextColored(ImVec4(0.0f, 0.75f, 1.0f, 1.0f), "CS2 External STM32");
    ImGui::SameLine(window_size.x - 80);
    ImGui::TextDisabled("INSERT");

    ImGui::SetCursorPosY(35);

    ImGui::BeginChild("##Sidebar", ImVec2(100, 0), true);
    if (ImGui::Selectable("AIMBOT", selectedTab == 1, 0, ImVec2(0, 30)))
        selectedTab = 1;
    if (ImGui::Selectable("VISUALS", selectedTab == 0, 0, ImVec2(0, 30)))
        selectedTab = 0;
    
        

    ImGui::EndChild();

    ImGui::SameLine();

    ImGui::BeginChild("##Content", ImVec2(0, 0), true);

    switch (selectedTab) {
    case 0: // Visuals
    {
        ImGui::Text("ESP Settings");
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Checkbox("Enable ESP", &cfg::espOn);
        ImGui::Checkbox("Team Check", &cfg::teamCheck);
        ImGui::Checkbox("Box ESP", &cfg::box);
        ImGui::Checkbox("HealthBar ESP", &cfg::healthBar);
        ImGui::Checkbox("Bone ESP", &cfg::bones);

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Text("Colors");
        ImGui::ColorEdit4("Box Color", cfg::boxColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
        ImGui::ColorEdit4("Bone Color", cfg::boneColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);

        break;
    }
    case 1: // Aimbot
    {
        ImGui::Text("Aimbot Settings");
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Checkbox("Enable Aimbot", &cfg::aimbot);
		ImGui::Checkbox("Team Check", &cfg::teamCheck);
        ImGui::Checkbox("Draw FOV", &cfg::drawFov);

        ImGui::Spacing();

        static bool waitingForKey = false;
        std::string keyLabel = waitingForKey ? "Press any key..." : ("Aim Key: " + GetKeyName(cfg::aimKey));

        if (ImGui::Button(keyLabel.c_str(), ImVec2(120, 0))) {
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

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Text("Aimbot Settings");
        ImGui::SliderFloat("FOV Size", &cfg::fovSize, 1.0f, 300.0f, "%.0f");
        ImGui::SliderFloat("Smoothness", &cfg::smoothing, 0.0f, 100.0f, "%.0f");
        ImGui::ColorEdit4("FOV Color", cfg::fovColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);

        break;
    }
    }

    ImGui::EndChild();

    ImGui::End();
}