#pragma once
#include "../ext/imgui/imgui.h"

namespace SimpleFOV {
    inline void DrawCircle(const ImVec2& center, float radius, ImColor color) {
        ImGui::GetBackgroundDrawList()->AddCircle(center, radius, color, 64, 1.0f);
    }
}