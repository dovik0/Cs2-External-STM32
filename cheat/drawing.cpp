#include "drawing.h"
#include "../ext/imgui/imgui.h"
#include <algorithm>

void Drawing::drawBox(const ImVec2& topLeft, const ImVec2& bottomRight, const ImColor& color, float thickness, float rounding) {
    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    drawList->AddRect(topLeft, bottomRight, color, rounding, 0, thickness);
}

void Drawing::drawFilledBox(const ImVec2& topLeft, const ImVec2& bottomRight, const ImColor& color, float rounding) {
    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    drawList->AddRectFilled(topLeft, bottomRight, color, rounding);
}

void Drawing::drawLine(const ImVec2& start, const ImVec2& end, const ImColor& color, float thickness) {
    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    drawList->AddLine(start, end, color, thickness);
}

void Drawing::drawCircle(const ImVec2& center, float radius, const ImColor& color, float thickness) {
    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    drawList->AddCircle(center, radius, color, 0, thickness);
}

void Drawing::drawFilledCircle(const ImVec2& center, float radius, const ImColor& color) {
    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    drawList->AddCircleFilled(center, radius, color);
}

void Drawing::drawHealthBar(const ImVec2& pos, const ImVec2& size, float health) {
    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    drawList->AddRectFilled(pos, ImVec2(pos.x + size.x, pos.y + size.y), ImColor(40, 40, 40, 255));
    float healthPercent = health / 100.0f;
    healthPercent = std::max(0.0f, std::min(healthPercent, 1.0f)); // Manual clamp
    float fillHeight = size.y * healthPercent;

    ImColor healthColor = GetColorHealth((int)health);
    drawList->AddRectFilled(
        ImVec2(pos.x, pos.y + size.y - fillHeight),
        ImVec2(pos.x + size.x, pos.y + size.y),
        healthColor
    );
    drawList->AddRect(pos, ImVec2(pos.x + size.x, pos.y + size.y), ImColor(0, 0, 0, 255), 0.0f, 0, 1.0f);
}

ImColor Drawing::GetColorHealth(int health) {
    if (health > 75) return ImColor(0, 255, 0, 255);
    if (health > 50) return ImColor(255, 255, 0, 255);
    if (health > 25) return ImColor(255, 165, 0, 255);
    return ImColor(255, 0, 0, 255);
}