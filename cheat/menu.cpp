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

void Menu::ApplyCustomStyle()
{
    ImGuiIO& io = ImGui::GetIO();
    // 🔤 Import d'une bonne police système (Windows)
    io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\segoeui.ttf", 13.0f);
    io.FontDefault = io.Fonts->Fonts.back();

    ImGuiStyle& style = ImGui::GetStyle();

    // 📏 Espacements et tailles
    style.WindowPadding = ImVec2(10, 10);
    style.FramePadding = ImVec2(8, 5);
    style.ItemSpacing = ImVec2(10, 6);
    style.ItemInnerSpacing = ImVec2(6, 5);
    style.IndentSpacing = 25;
    style.ScrollbarSize = 14;
    style.GrabMinSize = 12;

    // 📐 Bords et arrondis
    style.WindowBorderSize = 1.0f;
    style.FrameBorderSize = 0.0f;
    style.PopupBorderSize = 1.0f;
    style.WindowRounding = 8.0f;
    style.FrameRounding = 6.0f;
    style.GrabRounding = 5.0f;
    style.ScrollbarRounding = 6.0f;
    style.TabRounding = 5.0f;

    // 🌈 Couleurs
    ImVec4* colors = style.Colors;
    colors[ImGuiCol_Text] = ImVec4(0.92f, 0.94f, 0.96f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.55f, 0.60f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.07f, 0.08f, 0.09f, 0.95f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.10f, 0.11f, 0.12f, 1.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.09f, 0.10f, 0.98f);
    colors[ImGuiCol_Border] = ImVec4(0.18f, 0.20f, 0.23f, 1.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.18f, 0.20f, 0.25f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.22f, 0.25f, 0.30f, 1.00f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.11f, 0.12f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.12f, 0.14f, 0.16f, 1.00f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.11f, 0.12f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.07f, 0.08f, 0.09f, 1.00f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.25f, 0.26f, 0.29f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.30f, 0.32f, 0.36f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.35f, 0.37f, 0.42f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.00f, 0.75f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 0.70f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.00f, 0.85f, 1.00f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.18f, 0.19f, 0.22f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.25f, 0.27f, 0.33f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.30f, 0.35f, 0.42f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.18f, 0.19f, 0.22f, 1.00f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 0.27f, 0.33f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.30f, 0.35f, 0.42f, 1.00f);
    colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.22f, 0.25f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.20f, 0.23f, 0.28f, 1.00f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.25f, 0.28f, 0.34f, 1.00f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.30f, 0.35f, 0.42f, 1.00f);
    colors[ImGuiCol_Tab] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.20f, 0.22f, 0.28f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.16f, 0.18f, 0.22f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.16f, 0.18f, 0.22f, 1.00f);
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
    ImGui::TextColored(ImVec4(0.0f, 0.75f, 1.0f, 1.0f), "CS2 Base");
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