#pragma once
#include "cstrike.h"

namespace SDK {
    inline const ImVec2 screenCenter(GetSystemMetrics(SM_CXSCREEN) / 2.0f, GetSystemMetrics(SM_CYSCREEN) / 2.0f);

    inline bool IsOnScreen(const ImVec2& point) {
        int screenWidth = GetSystemMetrics(SM_CXSCREEN);
        int screenHeight = GetSystemMetrics(SM_CYSCREEN);
        return (point.x >= 0 && point.x <= screenWidth && point.y >= 0 && point.y <= screenHeight);
    }

    inline ImVec2 getBonePosition(entities::PLAYER actor, view_matrix_t matrix, int boneId, ImDrawList* drawList) {
        if (actor.health <= 0 || boneId < 0 || boneId >= 13 || actor.bones.empty())
            return ImVec2(-1, -1);

        if (boneId >= static_cast<int>(actor.bones.size()) || actor.bones[boneId].IsNull() || actor.bones[boneId].IsZero())
            return ImVec2(-1, -1);

        Vec3 bonePos;
        if (!W2S(actor.bones[boneId], bonePos, matrix)) {
            return ImVec2(-1, -1);
        }

        ImVec2 screenPos(bonePos.x, bonePos.y);
        if (!IsOnScreen(screenPos))
            return ImVec2(-1, -1);

        return screenPos;
    }
}