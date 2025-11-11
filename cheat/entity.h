#pragma once
#include "../ext/memory.h"
#include "offsets.h"
#include "math.h"
#include "cfg.h"
#include "localplayer.h"
#include <vector>

namespace entities {
    struct PLAYER {
        int health, team, armor;
        uintptr_t actorBase;
        std::vector<Vec3> bones;
        Vec3 PlayerPos;
        char name[32];
        short weaponame;
    };

    inline std::vector<PLAYER> entities;

    struct CacheEntry {
        PLAYER player;
        uint64_t lastUpdate;
    };
    inline std::vector<CacheEntry> entityCache;
    inline const uint64_t CACHE_UPDATE_INTERVAL = 1;

    void entityloop();
    void init();

    ImColor GetColorHealth(int health);
}