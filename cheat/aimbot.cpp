#define NOMINMAX
#include "aimbot.h"
#include "localplayer.h" 
#include "entity.h"     
#include <Windows.h>
#include <cmath>
#include <algorithm>

namespace aimbot {
    float lerp(float a, float b, float t) {
        return a + (b - a) * t;
    }

    void AimAtClosestEnemy(float fov, float smooth, int aimBone) {
        float closestDistance = FLT_MAX;
        ImVec2 bestTarget(-1, -1);
        view_matrix_t viewMatrix = memory->read<view_matrix_t>(client + Offsets::dwViewMatrix);

        for (const auto& actor : entities::entities) {
            if (actor.health <= 0) continue;
            if (cfg::teamCheck)
                if (actor.team == localplayer::teamid) continue;

            ImVec2 bonePos = SDK::getBonePosition(actor, viewMatrix, aimBone, nullptr);
            if (!SDK::IsOnScreen(bonePos)) continue;

            if (actor.actorBase == localplayer::G_Pawn())
                continue;

            float distance = sqrtf(powf(bonePos.x - SDK::screenCenter.x, 2) + powf(bonePos.y - SDK::screenCenter.y, 2));
            if (distance <= fov && distance < closestDistance) {
                closestDistance = distance;
                bestTarget = bonePos;
            }
        }

        if (bestTarget.x > 0 && bestTarget.y > 0) {
            float deltaX = bestTarget.x - SDK::screenCenter.x;
            float deltaY = bestTarget.y - SDK::screenCenter.y;

            float smoothFactor = std::max(0.0f, std::min(smooth / 100.f, 0.99f));
            float moveX = lerp(0, deltaX, 1.f - smoothFactor);
            float moveY = lerp(0, deltaY, 1.f - smoothFactor);

            if (std::abs(moveX) < 0.5f && std::abs(moveY) < 0.5f)
                return;

            INPUT input = { 0 };
            input.type = INPUT_MOUSE;
            input.mi.dx = static_cast<LONG>(moveX);
            input.mi.dy = static_cast<LONG>(moveY);
            input.mi.dwFlags = MOUSEEVENTF_MOVE;
            SendInput(1, &input, sizeof(INPUT));
        }
    }

    void doAimbot() {
        if (GetAsyncKeyState(cfg::aimKey) & 0x8000)
            AimAtClosestEnemy(cfg::fovSize, cfg::smoothing, cfg::aimBone);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}