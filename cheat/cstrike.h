#pragma once
#include "entity.h"
#include "cfg.h"
#include "drawing.h"
#include "math.h"
#include "sdk.h"

namespace cstrike {
    inline view_matrix_t matrix;
    inline Drawing* draw = new Drawing();

    view_matrix_t updateMatrix();
    void drawBox(entities::PLAYER actor, ImColor col);
	void drawHealthBar(entities::PLAYER actor, ImColor col);
    void drawBones(entities::PLAYER actor, ImColor col);
    void drawSnapline(entities::PLAYER actor, ImColor col);
}