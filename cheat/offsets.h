#pragma once
#include <cstdint>
#include <fstream>
#include <string>
#include <iostream>
#include <Windows.h>

#include "../ext/dumper/buttons.hpp"
#include "../ext/dumper/client_dll.hpp"
#include "../ext/dumper/offsets.hpp"

namespace Offsets {
    // OFFSETS.HPP -> https://github.com/a2x/cs2-dumper/blob/main/output/offsets.hpp
    inline DWORD dwEntityList = cs2_dumper::offsets::client_dll::dwEntityList;
    inline DWORD dwLocalPlayerPawn = cs2_dumper::offsets::client_dll::dwLocalPlayerPawn;
    inline DWORD dwViewMatrix = cs2_dumper::offsets::client_dll::dwViewMatrix;

    // CLIENT_DLL.HPP -> https://github.com/a2x/cs2-dumper/blob/main/output/client_dll.hpp
    inline DWORD m_hPlayerPawn = cs2_dumper::schemas::client_dll::CCSPlayerController::m_hPlayerPawn;
    inline DWORD m_iHealth = cs2_dumper::schemas::client_dll::C_BaseEntity::m_iHealth;
    inline DWORD m_iTeamNum = cs2_dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum;
    inline DWORD m_vOldOrigin = cs2_dumper::schemas::client_dll::C_BasePlayerPawn::m_vOldOrigin;
    inline DWORD m_pGameSceneNode = cs2_dumper::schemas::client_dll::C_BaseEntity::m_pGameSceneNode;
    inline DWORD m_modelState = cs2_dumper::schemas::client_dll::CSkeletonInstance::m_modelState;
    inline constexpr uintptr_t m_pWeaponServices = cs2_dumper::schemas::client_dll::C_BasePlayerPawn::m_pWeaponServices;
    inline constexpr uintptr_t m_hActiveWeapon = cs2_dumper::schemas::client_dll::CPlayer_WeaponServices::m_hActiveWeapon;
    inline constexpr uintptr_t m_szName = cs2_dumper::schemas::client_dll::CCSWeaponBaseVData::m_szName;
}