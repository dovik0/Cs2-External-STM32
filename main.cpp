#include <iostream>
#include <thread>
#include "cheat/menu.h"
#include "cheat/cstrike.h"
#include "cheat/aimbot.h"
#include "cheat/simpleFovCircle.h"
#include "cheat/localplayer.h" 
#include "cheat/entity.h"  
#include "cheat/cfg.h"

void aimbotThread() {
    while (true) {
        if (cfg::aimbot)
            aimbot::doAimbot();
        cstrike::matrix = memory->read<view_matrix_t>(client + Offsets::dwViewMatrix);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

HWND WaitForCSWindow() {
    HWND hwnd = nullptr;
    std::wcout << L"[Dovik] Waiting for Counter-Strike..." << std::endl;
    while ((hwnd = FindWindowW(nullptr, L"Counter-Strike 2")) == nullptr) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::wcout << L"[Dovik] Counter-Strike found" << std::endl;
    return hwnd;
}

int main() {
    SetConsoleTitleA("CS2 Dovik External STM32");

    WaitForCSWindow();
    std::cout << "[Dovik] Waiting for game to be ready...\n";
    while (!cfg::isGameReady) {
        client = memory->GetModuleBase(L"client.dll");
        if (client != 0)
			cfg::isGameReady = true;
	}
    std::cout << "[Dovik] client.dll -> " << std::hex << client << std::dec << "\n";
    localplayer::init();
    entities::init();
    std::thread(aimbotThread).detach();
    overlay::SetupWindow();

    if (!(overlay::CreateDeviceD3D(overlay::Window)))
        return 1;

    Menu::ApplyCustomStyle();

    while (!overlay::ShouldQuit) {
        overlay::Render();
        if (GetAsyncKeyState(cfg::menuKey) & 1) {
            Menu::Toggle();
        }
        if (cfg::drawFov && cfg::aimbot) {
            ImColor fovCol(cfg::fovColor[0], cfg::fovColor[1], cfg::fovColor[2], cfg::fovColor[3]);
            SimpleFOV::DrawCircle(SDK::screenCenter, cfg::fovSize, fovCol);
        }
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

        Menu::Render();

        overlay::EndRender();
    }

    overlay::CloseOverlay();
    return 0;
}