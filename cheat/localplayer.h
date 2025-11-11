#pragma once
#include "../ext/memory.h"
#include "offsets.h"
#include "math.h"
#include "cfg.h"

namespace localplayer {
    inline bool isdead = false;
    inline int teamid = 0;
    inline uintptr_t pawn = 0;
    inline int health = 0;

    uintptr_t G_Pawn();
    int G_Team();
    int G_Health();
    Vec3 G_Pos();
    bool B_Dead();

    void init();
    void loop();
}