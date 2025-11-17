#include <iostream>
#include "esp.h"

namespace esp {
	void drawAimbotCircle() {
		if (cfg::drawFov && cfg::aimbot) {
			ImColor fovCol(cfg::fovColor[0], cfg::fovColor[1], cfg::fovColor[2], cfg::fovColor[3]);
			SimpleFOV::DrawCircle(SDK::screenCenter, cfg::fovSize, fovCol);
		}
	}
	void drawGlabalESP() {
		ImColor boxCol(cfg::boxColor[0], cfg::boxColor[1], cfg::boxColor[2], cfg::boxColor[3]);
		ImColor boneCol(cfg::boneColor[0], cfg::boneColor[1], cfg::boneColor[2], cfg::boneColor[3]);

		for (entities::PLAYER& actor : entities::entities) {
			if (!cfg::espOn)
				continue;

			if (cfg::bones)
				cstrike::drawBones(actor, boneCol);
			if (cfg::box)
				cstrike::drawBox(actor, boxCol);
			if (cfg::healthBar)
				cstrike::drawHealthBar(actor, boxCol);
		}
	}

}
