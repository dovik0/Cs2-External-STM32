#define NOMINMAX
#include "aimbot.h"
#include "localplayer.h" 
#include "entity.h"     
#include <Windows.h>
#include <cmath>
#include <algorithm>
#include "arduino/arduino_mouse.h"

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
            float deltaX = bestTarget.x - GetSystemMetrics(SM_CXSCREEN) / 2.0f;
            float deltaY = bestTarget.y - GetSystemMetrics(SM_CYSCREEN) / 2.0f;

            float smoothFactor = std::clamp(smooth / 100.f, 0.0f, 0.99f);
            float moveX = lerp(0.0f, deltaX, 1.0f - smoothFactor);
            float moveY = lerp(0.0f, deltaY, 1.0f - smoothFactor);

            if (std::abs(moveX) < 0.5f && std::abs(moveY) < 0.5f)
                return;

            int8_t dx = static_cast<int8_t>(std::clamp(moveX, -127.0f, 127.0f));
            int8_t dy = static_cast<int8_t>(std::clamp(moveY, -127.0f, 127.0f));

            static auto lastSend = std::chrono::steady_clock::now();
            auto now = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastSend).count() < 16)
                return;
            lastSend = now;

            if (!cfg::hSerial || cfg::hSerial == INVALID_HANDLE_VALUE) {
                std::cerr << "[Aimbot] Port série non valide.\n";
                return;
            }

            if (!sendMouseCommand(cfg::hSerial, 'M', dx, dy)) {
                std::cerr << "[Aimbot] Erreur d'envoi série.\n";
            }
        }

    }

    void doAimbot() {
        if (GetAsyncKeyState(cfg::aimKey) & 0x8000)
            AimAtClosestEnemy(cfg::fovSize, cfg::smoothing, cfg::aimBone);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}