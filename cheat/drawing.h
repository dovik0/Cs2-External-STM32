#pragma once
#include "../ext/imgui/imgui.h"

class Drawing {
public:
    void drawBox(const ImVec2& topLeft, const ImVec2& bottomRight, const ImColor& color, float thickness = 1.0f, float rounding = 0.0f);
    void drawFilledBox(const ImVec2& topLeft, const ImVec2& bottomRight, const ImColor& color, float rounding = 0.0f);
    void drawLine(const ImVec2& start, const ImVec2& end, const ImColor& color, float thickness = 1.0f);
    void drawCircle(const ImVec2& center, float radius, const ImColor& color, float thickness = 1.0f);
    void drawFilledCircle(const ImVec2& center, float radius, const ImColor& color);
    void drawHealthBar(const ImVec2& pos, const ImVec2& size, float health);
    ImColor GetColorHealth(int health);
};