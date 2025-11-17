#include "cstrike.h"

view_matrix_t cstrike::updateMatrix() {
    return memory->read<view_matrix_t>(client + Offsets::dwViewMatrix);
}

void cstrike::drawHealthBar(entities::PLAYER actor, ImColor col) {
    if (actor.actorBase == localplayer::pawn)
        return;

    if (&actor == nullptr || actor.PlayerPos.IsZero())
        return;
    if (actor.health <= 0)
        return;

    Vec3 head_t = { actor.PlayerPos.x, actor.PlayerPos.y, actor.PlayerPos.z + 70.f };
    Vec3 screenPos, screenHead;

    if (!W2S(actor.PlayerPos, screenPos, cstrike::matrix) || !W2S(head_t, screenHead, matrix))
        return;

    float height = std::abs(screenPos.y - screenHead.y);
    float width = height / 2.0f;

    ImVec2 topLeft(screenHead.x - width / 2, screenHead.y);
    ImVec2 bottomRight(topLeft.x + width, topLeft.y + height);

    const float healthBarWidth = 3.f;
    const float healthBarOffset = 2.f;
    ImVec2 healthBarPos(topLeft.x - healthBarWidth - healthBarOffset, topLeft.y);
    ImVec2 healthBarSize(healthBarWidth, height);
    draw->drawHealthBar(healthBarPos, healthBarSize, actor.health);
}

void cstrike::drawBox(entities::PLAYER actor, ImColor col) {
    if (actor.actorBase == localplayer::pawn)
        return;

    if (&actor == nullptr || actor.PlayerPos.IsZero())
        return;
    if (actor.health <= 0)
        return;

    Vec3 head_t = { actor.PlayerPos.x, actor.PlayerPos.y, actor.PlayerPos.z + 70.f };
    Vec3 screenPos, screenHead;

    if (!W2S(actor.PlayerPos, screenPos, cstrike::matrix) || !W2S(head_t, screenHead, matrix))
        return;

    float height = std::abs(screenPos.y - screenHead.y);
    float width = height / 2.0f;

    ImVec2 topLeft(screenHead.x - width / 2, screenHead.y);
    ImVec2 bottomRight(topLeft.x + width, topLeft.y + height);

    draw->drawBox(topLeft, bottomRight, ImColor(0, 0, 0, 255), 2.0f, 0.f);
    draw->drawBox(topLeft, bottomRight, col, 1, 0.f);

}

void cstrike::drawBones(entities::PLAYER actor, ImColor col) {
    if (actor.health <= 0)
        return;

    Vec3 screenBones[13];
    bool allVisible = true;

    for (int i = 0; i < 13; ++i) {
        if (!W2S(actor.bones[i], screenBones[i], matrix)) {
            allVisible = false;
            break;
        }
    }

    if (!allVisible) return;

    ImVec2 boneScreen[13];
    for (int i = 0; i < 13; ++i) {
        boneScreen[i] = ImVec2(screenBones[i].x, screenBones[i].y);
    }

    auto drawBoneLine = [&](int a, int b) {
        if (a < 13 && b < 13) {
            float dx = boneScreen[b].x - boneScreen[a].x;
            float dy = boneScreen[b].y - boneScreen[a].y;
            //float length = std::sqrt(dx * dx + dy * dy);

            draw->drawLine(boneScreen[a], boneScreen[b], ImColor(0, 0, 0), 2.f);
            draw->drawLine(boneScreen[a], boneScreen[b], col, 1.f);
        }
        };

    drawBoneLine(0, 1);
    drawBoneLine(1, 2);
    drawBoneLine(1, 3);
    drawBoneLine(2, 4);
    drawBoneLine(3, 5);
    drawBoneLine(4, 6);
    drawBoneLine(5, 7);
    drawBoneLine(1, 8);
    drawBoneLine(8, 9);
    drawBoneLine(8, 10);
    drawBoneLine(9, 11);
    drawBoneLine(10, 12);
}

void cstrike::drawSnapline(entities::PLAYER actor, ImColor col) {
    if (actor.actorBase == localplayer::pawn)
        return;

    if (&actor == nullptr || actor.PlayerPos.IsZero())
        return;
    if (actor.health <= 0)
        return;

    Vec3 screenPos;
    if (!W2S(actor.PlayerPos, screenPos, matrix))
        return;

    ImVec2 screenCenter(ImGui::GetIO().DisplaySize.x / 2.0f, ImGui::GetIO().DisplaySize.y);
    draw->drawLine(screenCenter, ImVec2(screenPos.x, screenPos.y), ImColor(0, 0, 0), 3.0f);
    draw->drawLine(screenCenter, ImVec2(screenPos.x, screenPos.y), col, 1.0f);
}