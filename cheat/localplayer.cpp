#include "localplayer.h"
#include <thread>
#include <iostream>

namespace localplayer {
    void loop()
    {
        while (true)
        {
            teamid = memory->read<int>(G_Pawn() + Offsets::m_iTeamNum);
            health = memory->read<int>(G_Pawn() + Offsets::m_iHealth);
            pawn = memory->read<uintptr_t>(client + Offsets::dwLocalPlayerPawn);
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
    }

    void init()
    {
        std::thread([&]() { loop(); }).detach();
    }

    uintptr_t G_Pawn()
    {
        return memory->read<uintptr_t>(client + Offsets::dwLocalPlayerPawn);
    }

    int G_Team()
    {
        return memory->read<int>(G_Pawn() + Offsets::m_iTeamNum);
    }

    int G_Health()
    {
        return memory->read<int>(G_Pawn() + Offsets::m_iHealth);
    }

    Vec3 G_Pos()
    {
        return memory->read<Vec3>(G_Pawn() + Offsets::m_vOldOrigin);
    }

    bool B_Dead()
    {
        return G_Health() <= 0;
    }
}