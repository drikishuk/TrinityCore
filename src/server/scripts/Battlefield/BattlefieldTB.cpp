/*
* This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*/

// TO-DO:
//  - Implement proper support for vehicles (Player::VehicleSpellInitialize())
//     - Siege Engine Turret (45564) crashing server (Auras: Unknown Shapeshift Type: 24)
//  - Graveyard spirit phasing, ressurection, Spiritual Immunity aura for players nearby
//  - Warn and teleport players out of the Baradin Hold instance (need sniffs; spell 94964?)
//  - Not sure, but players should probably be able to ressurect from guide spirits when there's no battle
//  - Check and script achievements

#include "BattlefieldTB.h"
#include "Battleground.h"
#include "Creature.h"
#include "GameObject.h"
#include "GameTime.h"
#include "ObjectAccessor.h"
#include "Player.h"
#include "Random.h"
#include "ScriptMgr.h"
#include "World.h"
#include "WorldStateMgr.h"

const uint32 TBFactions[BG_TEAMS_COUNT] = { 1610, 1732 };

// Stalker
Position const TolBaradDebugAnnouncerPos = { -1234.25f, 961.903f, 159.4913f, 0.0f };

uint32 const TB_QUEST_INFANTRY[BG_TEAMS_COUNT][4] =
{
    { NPC_HORDE_DRUID_INFANTRY, NPC_HORDE_MAGE_INFANTRY, NPC_HORDE_ROGUE_INFANTRY, NPC_HORDE_SHAMAN_INFANTRY },
    { NPC_ALLIANCE_WARRIOR_INFANTRY, NPC_ALLIANCE_PALADIN_INFANTRY, NPC_ALLIANCE_HUNTER_INFANTRY, NPC_ALLIANCE_MAGE_INFANTRY },
};

uint8 const TB_QUEST_INFANTRY_MAX = 37;
Position const TBQuestInfantrySpawnData[TB_QUEST_INFANTRY_MAX] =
{
    { -930.4685f, 1020.178f, 121.5658f, 0.1537642f  },
    { -831.5157f, 975.816f,  121.5255f, 5.022717f   },
    { -837.0773f, 943.9008f, 121.5055f, 5.461119f   },
    { -839.1646f, 1024.046f, 121.5505f, 4.782219f   },
    { -881.283f,  1033.25f,  121.5243f, 0.0f        },
    { -883.038f,  924.955f,  121.5243f, 0.0f        },
    { -883.913f,  978.059f,  121.5243f, 3.388291f   },
    { -883.6224f, 950.8459f, 121.5122f, 0.8307042f  },
    { -895.181f,  1015.2f,   121.5505f, 2.652318f   },
    { -943.4023f, 961.7462f, 121.5658f, 5.258394f   },
    { -958.649f,  926.877f,  121.5243f, 0.0f        },
    { -959.743f,  1029.09f,  121.5243f, 0.0f        },
    { -964.6652f, 978.5373f, 121.5257f, 0.02025719f },
    { -1407.14f,  721.42f,   123.5033f, 0.0f        },
    { -1414.46f,  671.66f,   123.5043f, 0.0f        },
    { -1431.7f,   623.073f,  123.5043f, 0.0f        },
    { -1434.162f, 655.8566f, 123.5051f, 4.84886f    },
    { -1445.19f,  739.729f,  123.5457f, 5.767949f   },
    { -1460.954f, 718.418f,  123.6453f, 5.178094f   },
    { -1462.48f,  694.378f,  123.5463f, 0.3441857f  },
    { -1372.23f,  683.707f,  123.5043f, 0.0f        },
    { -1479.46f,  635.799f,  123.5043f, 0.0f        },
    { -1491.259f, 734.5692f, 123.4525f, 1.529741f   },
    { -1509.024f, 688.8625f, 123.5463f, 6.243045f   },
    { -1419.311f, 1310.25f,  133.8389f, 0.0f        },
    { -1444.24f,  1266.439f, 133.8229f, 0.0f        },
    { -1450.569f, 1337.351f, 133.914f,  0.0f        },
    { -1479.819f, 1331.34f,  153.2f,    0.0f        },
    { -1497.62f,  1276.429f, 133.6676f, 3.147845f   },
    { -1498.37f,  1379.689f, 133.827f,  0.0f        },
    { -1499.97f,  1232.87f,  133.8239f, 0.0f        },
    { -1505.7f,   1261.99f,  133.7089f, 0.6167698f  },
    { -1531.84f,  1316.569f, 153.2f,    0.0f        },
    { -1533.141f, 1267.66f,  133.836f,  0.0f        },
    { -1547.59f,  1300.21f,  133.7094f, 1.908187f   },
    { -1563.3f,   1325.79f,  133.6673f, 0.0f        },
};

uint8 const TB_GUARDS_MAX = 8;
Position const GuardNPCSpawns[TB_GUARDS_MAX] =
{
//  { -837.3768f, 1196.082f, 114.2994f, 3.036873f },
//  { -762.118f,  1195.259f, 107.2007f, 3.036873f },
//  { -837.809f,  1179.842f, 114.1356f, 3.159046f },
//  { -762.5504f, 1179.019f, 107.2137f, 3.159046f },
    { -1272.951f, 964.8854f, 119.5782f, 3.193953f },
    { -1274.394f, 997.6511f, 119.5743f, 3.193953f },
    { -1248.226f, 1018.476f, 119.8113f, 1.605703f },
    { -1218.948f, 943.5695f, 119.5994f, 4.625123f },
    { -1195.417f, 965.5364f, 119.8113f, 0.0f },
    { -1220.832f, 1018.497f, 119.8113f, 1.605703f },
    { -1196.151f, 999.5121f, 119.5966f, 0.0f },
    { -1249.304f, 942.9063f, 119.5782f, 4.625123f },
};

struct TBFactionNPCInfo
{
    Position pos;
    uint32 entryAlliance;
    uint32 entryHorde;
};

uint8 const TB_FACTION_NPC_MAX = 4;
TBFactionNPCInfo const FactionNPCSpawns[TB_FACTION_NPC_MAX] =
{
    { { -1259.356f, 1057.108f, 107.0786f, 4.956735f }, NPC_BARADIN_GUARD_1, NPC_BARADIN_GRUNT_1 },
    { { -1254.174f, 1061.094f, 107.0772f, 5.445427f }, NPC_BARADIN_GUARD_2, NPC_BARADIN_GRUNT_2 },
    { { -1256.365f, 1058.47f, 107.0776f, 2.216568f  }, NPC_MAVEN_ZARA, NPC_RHAGHA },
    { { -1231.38f, 985.681f, 121.2403f, 0.6108652f  }, NPC_SERGEANT_PARKER, NPC_COMMANDER_ZANOTH },
};

Position const RandomQuestgiverPos = { -1228.93f, 975.038f, 121.7153f, 5.969026f };

struct TBQuestAreaInfo
{
    uint32 entry;
    uint32 teleportSpell;
};

TBQuestAreaInfo const TBQuestAreas[CELLBLOCK_MAX] =
{
    { AREA_THE_HOLE, SPELL_TB_THE_HOLE_TELEPORT },
    { AREA_D_BLOCK, SPELL_TB_D_BLOCK_TELEPORT },
    { AREA_CURSED_DEPTHS, SPELL_TB_CURSED_DEPTHS_TELEPORT },
};

uint32 const RandomQuestgivers[BG_TEAMS_COUNT][CELLBLOCK_MAX] =
{
    { NPC_MARSHAL_FALLOWS, NPC_2ND_LIEUTENANT_WANSWORTH, NPC_COMMANDER_STEVENS },
    { NPC_DRILLMASTER_RAZGOTH, NPC_STAFF_SERGEANT_LAZGAR, NPC_PRIVATE_GARNOTH },
};

struct TBCapturePointSpawnData
{
    Position pos;
    QuaternionData rot;
    TBCapturePointId id;
    uint32 entryFlagPole[2];
    uint32 wsControlled[2];
    uint32 wsCapturing[2];
    uint32 wsNeutral;
    uint32 textGained[2];
    uint32 textLost[2];
};

TBCapturePointSpawnData const TBCapturePoints[TB_BASE_COUNT] =
{
    { { -896.96f, 979.497f, 121.441f, 3.124123f  }, { 0.f, 0.f, 0.99996185f, 0.00873472f },TB_BASE_IRONCLAD_GARRISON, { GO_CAPTURE_POINT_NORTH_A_DEFENDING, GO_CAPTURE_POINT_NORTH_H_DEFENDING }, { WS_BATTLEFIELD_TB_GARRISON_ALLIANCE_CONTROLLED, WS_BATTLEFIELD_TB_GARRISON_HORDE_CONTROLLED }, { WS_BATTLEFIELD_TB_GARRISON_ALLIANCE_CAPTURING, WS_BATTLEFIELD_TB_GARRISON_HORDE_CAPTURING }, WS_BATTLEFIELD_TB_GARRISON_NEUTRAL, { TB_TEXT_GARRISON_ALLIANCE_GAINED, TB_TEXT_GARRISON_HORDE_GAINED }, { TB_TEXT_GARRISON_ALLIANCE_LOST, TB_TEXT_GARRISON_HORDE_LOST } },
    { { -1492.34f, 1309.87f, 152.961f, 5.462882f }, { 0.f, 0.f, 0.39874841f, -0.91706036f }, TB_BASE_WARDENS_VIGIL, { GO_CAPTURE_POINT_WEST_A_DEFENDING, GO_CAPTURE_POINT_WEST_H_DEFENDING }, { WS_BATTLEFIELD_TB_VIGIL_ALLIANCE_CONTROLLED, WS_BATTLEFIELD_TB_VIGIL_HORDE_CONTROLLED }, { WS_BATTLEFIELD_TB_VIGIL_ALLIANCE_CAPTURING, WS_BATTLEFIELD_TB_VIGIL_HORDE_CAPTURING }, WS_BATTLEFIELD_TB_VIGIL_NEUTRAL, { TB_TEXT_VIGIL_ALLIANCE_GAINED, TB_TEXT_VIGIL_HORDE_GAINED }, { TB_TEXT_VIGIL_ALLIANCE_LOST, TB_TEXT_VIGIL_HORDE_LOST } },
    { { -1437.f, 685.556f, 123.421f, 0.802851f   }, { 0.f, 0.f, 0.39073092f, 0.92050494f },TB_BASE_SLAGWORKS, { GO_CAPTURE_POINT_EAST_A_DEFENDING, GO_CAPTURE_POINT_EAST_H_DEFENDING }, { WS_BATTLEFIELD_TB_SLAGWORKS_ALLIANCE_CONTROLLED, WS_BATTLEFIELD_TB_SLAGWORKS_HORDE_CONTROLLED }, { WS_BATTLEFIELD_TB_SLAGWORKS_ALLIANCE_CAPTURING, WS_BATTLEFIELD_TB_SLAGWORKS_HORDE_CAPTURING }, WS_BATTLEFIELD_TB_SLAGWORKS_NEUTRAL, { TB_TEXT_SLAGWORKS_ALLIANCE_GAINED, TB_TEXT_SLAGWORKS_HORDE_GAINED }, { TB_TEXT_SLAGWORKS_ALLIANCE_LOST, TB_TEXT_SLAGWORKS_HORDE_LOST } },
};

struct TBTowerInfo
{
    Position pos;
    QuaternionData rot;
    uint32 entry;
    uint32 textDamaged;
    uint32 textDestroyed;
    uint32 wsIntact[BG_TEAMS_COUNT];
    uint32 wsDamaged[BG_TEAMS_COUNT];
    uint32 wsDestroyed;
};

TBTowerInfo const TBTowers[TB_TOWERS_COUNT] =
{
    { { -1013.279f, 529.5382f, 146.427f, 1.97222f   }, { 0.f, 0.f, 0.83388526f, 0.55193784f }, GO_EAST_SPIRE, TB_TEXT_EAST_SPIRE_DAMAGED, TB_TEXT_EAST_SPIRE_DESTROYED, { WS_BATTLEFIELD_TB_EAST_INTACT_ALLIANCE, WS_BATTLEFIELD_TB_EAST_INTACT_HORDE }, { WS_BATTLEFIELD_TB_EAST_DAMAGED_ALLIANCE, WS_BATTLEFIELD_TB_EAST_DAMAGED_HORDE }, WS_BATTLEFIELD_TB_EAST_DESTROYED_NEUTRAL },
    { { -1618.91f, 954.5417f, 168.601f, 0.06981169f }, { 0.f, 0.f, 0.03489876f, 0.99939085f }, GO_SOUTH_SPIRE, TB_TEXT_SOUTH_SPIRE_DAMAGED, TB_TEXT_SOUTH_SPIRE_DESTROYED, { WS_BATTLEFIELD_TB_SOUTH_INTACT_ALLIANCE, WS_BATTLEFIELD_TB_SOUTH_INTACT_HORDE }, { WS_BATTLEFIELD_TB_SOUTH_DAMAGED_ALLIANCE, WS_BATTLEFIELD_TB_SOUTH_DAMAGED_HORDE }, WS_BATTLEFIELD_TB_SOUTH_DESTROYED_NEUTRAL },
    { { -950.4097f, 1469.101f, 176.596f, 4.180066f  }, { 0.f, 0.f, 0.86819821f, -0.49621756f }, GO_WEST_SPIRE, TB_TEXT_WEST_SPIRE_DAMAGED, TB_TEXT_WEST_SPIRE_DESTROYED, { WS_BATTLEFIELD_TB_WEST_INTACT_ALLIANCE, WS_BATTLEFIELD_TB_WEST_INTACT_HORDE }, { WS_BATTLEFIELD_TB_WEST_DAMAGED_ALLIANCE, WS_BATTLEFIELD_TB_WEST_DAMAGED_HORDE }, WS_BATTLEFIELD_TB_WEST_DESTROYED_NEUTRAL },
};

int8 const TB_ABANDONED_SIEGE_ENGINE_COUNT = 6;
Position const TBAbandonedSiegeEngineSpawnData[TB_ABANDONED_SIEGE_ENGINE_COUNT] =
{
    { -1106.57f, 1196.34f, 121.8023f, 0.4014257f },
    { -1108.52f, 1111.33f, 121.2783f, 1.37881f },
    { -1213.01f, 782.236f, 121.4473f, 1.675516f },
    { -1258.26f, 780.497f, 122.4413f, 1.48353f },
    { -1438.3f, 1095.24f, 121.1363f, 5.288348f },
    { -1442.3f, 1141.07f, 123.6323f, 4.24115f },
};

uint32 const TBBannerEntry[BG_TEAMS_COUNT] = { GO_BARADINS_WARDEN_BANNER, GO_HELLSCREAM_REACH_BANNER };

struct TBBannerData
{
    Position pos;
    QuaternionData rot;
};

uint8 const TB_BANNER_MAX = 23;
TBBannerData const TBBanners[TB_BANNER_MAX] =
{
    { { -987.6129f, 963.9861f, 121.4506f, 2.617989f }, { 0.f, 0.f, 0.96592520f, 0.25882140f } },
    { { -988.118f, 993.0087f, 121.6746f, 3.612838f }, { 0.f, 0.f, 0.97236917f, -0.23344850f } },
    { { -1195.941f, 964.342f, 119.728f, 0.8901166f }, { 0.f, 0.f, 0.43051050f, 0.90258557f } },
    { { -1196.892f, 1000.957f, 119.8211f, 5.445428f }, { 0.f, 0.f, 0.40673631f, -0.91354561f } },
    { { -1198.236f, 1081.898f, 120.2007f, 1.06465f }, { 0.f, 0.f, 0.50753800f, 0.86162937f } },
    { { -1089.337f, 1157.161f, 120.2749f, 3.036838f }, { 0.f, 0.f, 0.99862862f, 0.05235338f } },
    { { -1090.033f, 1143.476f, 120.2656f, 3.036838f }, { 0.f, 0.f, 0.99862862f, 0.05235338f } },
    { { -1217.495f, 944.0261f, 119.4949f, 1.989672f }, { 0.f, 0.f, 0.83866966f, 0.54464044f } },
    { { -1219.226f, 1018.168f, 119.728f, 2.251473f }, { 0.f, 0.f, 0.90258491f, 0.43051188f } },
    { { -1210.319f, 1081.885f, 120.2396f, 2.007128f }, { 0.f, 0.f, 0.84339127f, 0.53729988f } },
    { { -1226.903f, 786.7656f, 119.4592f, 1.553341f }, { 0.f, 0.f, 0.70090854f, 0.71325116f } },
    { { -1228.464f, 979.7379f, 119.3814f, 0.03490625f }, { 0.f, 0.f, 0.01745224f, 0.99984770f } },
    { { -1239.668f, 786.7899f, 119.4271f, 1.553341f }, { 0.f, 0.f, 0.70090854f, 0.71325116f } },
    { { -1250.262f, 1017.887f, 119.728f, 0.8377575f }, { 0.f, 0.f, 0.40673640f, 0.91354557f } },
    { { -1250.693f, 943.4496f, 119.4949f, 5.305802f }, { 0.f, 0.f, 0.46947109f, -0.88294784f } },
    { { -1272.29f, 963.5208f, 119.4949f, 2.617989f }, { 0.f, 0.f, 0.96592520f, 0.25882140f } },
    { { -1273.997f, 998.7934f, 119.4884f, 3.665196f }, { 0.f, 0.f, 0.96592523f, -0.25882125f } },
    { { -1378.363f, 725.0087f, 124.2978f, 1.326448f }, { 0.f, 0.f, 0.61566060f, 0.78801144f } },
    { { -1401.97f, 747.0972f, 123.2302f, 0.2443456f }, { 0.f, 0.f, 0.12186910f, 0.99254618f } },
    { { -1421.953f, 1263.559f, 133.6141f, 5.009095f }, { 0.f, 0.f, 0.59482277f, -0.80385687f } },
    { { -1446.497f, 1238.964f, 133.7601f, 5.969027f }, { 0.f, 0.f, 0.15643399f, -0.98768842f } },
    { { -1488.908f, 1118.747f, 124.9255f, 6.248279f }, { 0.f, 0.f, 0.01745227f, -0.99984770f } },
    { { -1488.533f, 1131.608f, 124.6363f, 6.248279f }, { 0.f, 0.f, 0.01745227f, -0.99984770f } },
};

uint32 const TBPortalEntry[BG_TEAMS_COUNT] = { TB_PORTAL_ALLIANCE, TB_PORTAL_HORDE };

struct TBPortalData
{
    Position pos;
    QuaternionData rot;
};

uint8 const TB_PORTAL_MAX = 2;
TBPortalData const TBPortals[TB_PORTAL_MAX] =
{
    { { -598.7656f, 1377.974f, 21.91898f, 0.0f }, { 0.f, 0.f, 0.00000000f, 1.00000000f } },
	{ { -1257.729f, 1060.365f, 106.9938f, 5.462882f }, { 0.f, 0.f, 0.39874841f, -0.91706036f } },
};

struct TBGraveyardInfo
{
    Position pos;
    uint32 phaseId;
    uint32 gyid;
    uint32 spiritEntry[BG_TEAMS_COUNT];
    bool defenderControls;
};

TBGraveyardInfo const TBGraveyards[BATTLEFIELD_TB_GRAVEYARD_MAX] =
{
    { { -1247.42f, 981.25f, 155.35f, 6.28f  }, 128, TB_GY_BARADIN_HOLD, { NPC_TB_GY_SPIRIT_BARADIN_HOLD_A, NPC_TB_GY_SPIRIT_BARADIN_HOLD_H }, true },
    { { -974.28f, 1089.47f, 132.99f, 5.90f  }, 64, TB_GY_IRONCLAD_GARRISON, { NPC_TB_GY_SPIRIT_IRONCLAD_GARRISON_A, NPC_TB_GY_SPIRIT_IRONCLAD_GARRISON_H }, false },
    { { -1570.44f, 1167.57f, 159.50f, 2.20f }, 64, TB_GY_WARDENS_VIGIL, { NPC_TB_GY_SPIRIT_WARDENS_VIGIL_A, NPC_TB_GY_SPIRIT_WARDENS_VIGIL_H }, false },
    { { -1343.32f, 565.24f, 139.04f, 1.66f  }, 64, TB_GY_SLAGWORKS, { NPC_TB_GY_SPIRIT_SLAGWORKS_A, NPC_TB_GY_SPIRIT_SLAGWORKS_H }, false },
    { { -1052.02f, 1494.05f, 191.41f, 4.13f }, 64, TB_GY_WEST_SPIRE, { NPC_TB_GY_SPIRIT_WEST_SPIRE_A, NPC_TB_GY_SPIRIT_WEST_SPIRE_H }, false },
    { { -1603.34f, 874.29f, 193.69f, 5.27f  }, 64, TB_GY_SOUTH_SPIRE, { NPC_TB_GY_SPIRIT_SOUTH_SPIRE_A, NPC_TB_GY_SPIRIT_SOUTH_SPIRE_H }, false },
    { { -943.66f, 572.36f, 157.54f, 1.74f   }, 64, TB_GY_EAST_SPIRE, { NPC_TB_GY_SPIRIT_EAST_SPIRE_A, NPC_TB_GY_SPIRIT_EAST_SPIRE_H }, false },
};

BattlefieldTB::~BattlefieldTB() { }

bool BattlefieldTB::SetupBattlefield()
{
    m_TypeId = BATTLEFIELD_TB;                              // See enum BattlefieldTypes
    m_BattleId = BATTLEFIELD_BATTLEID_TB;
    m_ZoneId = BATTLEFIELD_TB_ZONEID;

    InitStalker(NPC_DEBUG_ANNOUNCER, TolBaradDebugAnnouncerPos);

    m_MaxPlayer = sWorld->getIntConfig(CONFIG_TOLBARAD_PLR_MAX);
    m_IsEnabled = sWorld->getBoolConfig(CONFIG_TOLBARAD_ENABLE);
    m_MinPlayer = sWorld->getIntConfig(CONFIG_TOLBARAD_PLR_MIN);
    m_MinLevel = sWorld->getIntConfig(CONFIG_TOLBARAD_PLR_MIN_LVL);
    m_BattleTime = sWorld->getIntConfig(CONFIG_TOLBARAD_BATTLETIME) * MINUTE * IN_MILLISECONDS;
    m_BonusTime = sWorld->getIntConfig(CONFIG_TOLBARAD_BONUSTIME) * MINUTE * IN_MILLISECONDS;
    m_NoWarBattleTime = sWorld->getIntConfig(CONFIG_TOLBARAD_NOBATTLETIME) * MINUTE * IN_MILLISECONDS;
    m_RestartAfterCrash = sWorld->getIntConfig(CONFIG_TOLBARAD_RESTART_AFTER_CRASH) * MINUTE * IN_MILLISECONDS;

    m_TimeForAcceptInvite = 20;
    m_StartGroupingTimer = 15 * MINUTE * IN_MILLISECONDS;
    m_StartGrouping = false;
    m_isActive = false;

    KickPosition.Relocate(-605.5f, 1181.31f, 95.96f, 6.177155f);
    KickPosition.m_mapId = m_MapId;

    RegisterZone(m_ZoneId);

    m_Data32.resize(BATTLEFIELD_TB_DATA_MAX);

    updatedNPCAndObjects = true;
    m_updateObjectsTimer = 0;

    // Was there a battle going on or time isn't set yet? Then use m_RestartAfterCrash
    if (sWorldStateMgr->GetValue(WS_BATTLEFIELD_TB_STATE_BATTLE, m_Map) == 1 || sWorldStateMgr->GetValue(WS_BATTLEFIELD_TB_TIME_NEXT_BATTLE, m_Map) < GameTime::GetGameTime())
    {
        sWorldStateMgr->SetValueAndSaveInDb(WS_BATTLEFIELD_TB_STATE_BATTLE, 0, false, m_Map);
        sWorldStateMgr->SetValue(WS_BATTLEFIELD_TB_TIME_NEXT_BATTLE, GameTime::GetGameTime() + m_RestartAfterCrash / IN_MILLISECONDS, false, m_Map);
    }

    // Set timer
    m_Timer = sWorldStateMgr->GetValue(WS_BATTLEFIELD_TB_TIME_NEXT_BATTLE, m_Map) - GameTime::GetGameTime();

    // Defending team isn't set yet? Choose randomly.
    if (sWorldStateMgr->GetValue(WS_BATTLEFIELD_TB_FACTION_CONTROLLING, m_Map) == 0)
        sWorldStateMgr->SetValue(WS_BATTLEFIELD_TB_FACTION_CONTROLLING, uint32(urand(1, 2)), false, m_Map);

    // Set defender team
    SetDefenderTeam(TeamId(sWorldStateMgr->GetValue(WS_BATTLEFIELD_TB_FACTION_CONTROLLING, m_Map) - 1));

    sWorldStateMgr->SetValue(WS_BATTLEFIELD_TB_TIME_NEXT_BATTLE_SHOW, 1, false, m_Map);
    sWorldStateMgr->SetValueAndSaveInDb(WS_BATTLEFIELD_TB_TIME_NEXT_BATTLE, GameTime::GetGameTime() + m_Timer / IN_MILLISECONDS, false, m_Map);

    sWorldStateMgr->SetValueAndSaveInDb(WS_BATTLEFIELD_TB_FACTION_CONTROLLING, GetDefenderTeam() + 1, false, m_Map);
    sWorldStateMgr->SetValue(WS_BATTLEFIELD_TB_ALLIANCE_CONTROLS_SHOW, GetDefenderTeam() == TEAM_ALLIANCE ? 1 : 0, false, m_Map);
    sWorldStateMgr->SetValue(WS_BATTLEFIELD_TB_HORDE_CONTROLS_SHOW, GetDefenderTeam() == TEAM_HORDE ? 1 : 0, false, m_Map);
    sWorldStateMgr->SetValue(WS_BATTLEFIELD_TB_KEEP_ALLIANCE, GetDefenderTeam() == TEAM_ALLIANCE ? 1 : 0, false, m_Map);
    sWorldStateMgr->SetValue(WS_BATTLEFIELD_TB_KEEP_HORDE, GetDefenderTeam() == TEAM_HORDE ? 1 : 0, false, m_Map);

    // Create capture points
    for (uint8 i = 0; i < TB_BASE_COUNT; i++)
    {
        TolBaradCapturePoint* capturePoint = new TolBaradCapturePoint(this, GetDefenderTeam());

        //Spawn flag pole
        if (GameObject* go = SpawnGameObject(TBCapturePoints[i].entryFlagPole[GetDefenderTeam()], TBCapturePoints[i].pos, TBCapturePoints[i].rot))
        {
            go->SetGoArtKit(GetDefenderTeam() == TEAM_ALLIANCE ? TB_GO_ARTKIT_FLAG_ALLIANCE : TB_GO_ARTKIT_FLAG_HORDE);
            capturePoint->SetCapturePointData(go);
        }
        AddCapturePoint(capturePoint);
    }

    // Spawn towers
    for (uint8 i = 0; i < TB_TOWERS_COUNT; i++)
        if (GameObject* go = SpawnGameObject(TBTowers[i].entry, TBTowers[i].pos, TBTowers[i].rot))
            Towers.insert(go->GetGUID());

    // Init Graveyards
    SetGraveyardNumber(BATTLEFIELD_TB_GRAVEYARD_MAX);

    // Graveyards
    for (uint8 i = 0; i < BATTLEFIELD_TB_GRAVEYARD_MAX; i++)
    {
        BfGraveyard* graveyard = new BfGraveyard(this);

        // When between games, the graveyard is controlled by the defending team
        graveyard->Initialize(GetDefenderTeam(), TBGraveyards[i].gyid);

        // Spawn spirits
        for (uint8 team = 0; team < 2; team++)
            if (Creature* creature = SpawnCreature(TBGraveyards[i].spiritEntry[team], TBGraveyards[i].pos))
                graveyard->SetSpirit(creature, TeamId(team));

        m_GraveyardList[i] = graveyard;
    }

    // Time warning vars
    warnedFiveMinutes = false;
    warnedTwoMinutes = false;
    warnedOneMinute = false;

    UpdateNPCsAndGameObjects();

    return true;
}

bool BattlefieldTB::Update(uint32 diff)
{
    bool m_return = Battlefield::Update(diff);

    // Minutes till battle preparation warnings
    if (GetState() == BATTLEFIELD_INACTIVE)
    {
        if (m_Timer <= 5 * MINUTE * IN_MILLISECONDS + m_StartGroupingTimer && !warnedFiveMinutes)
        {
            warnedFiveMinutes = true;
            SendWarning(TB_TEXT_PREPARATIONS_IN_5_MIN);
        }

        if (m_Timer <= 2 * MINUTE * IN_MILLISECONDS + m_StartGroupingTimer && !warnedTwoMinutes)
        {
            warnedTwoMinutes = true;
            SendWarning(TB_TEXT_PREPARATIONS_IN_2_MIN);
        }

        if (m_Timer <= 1 * MINUTE * IN_MILLISECONDS + m_StartGroupingTimer && !warnedOneMinute)
        {
            warnedOneMinute = true;
            SendWarning(TB_TEXT_PREPARATIONS_IN_1_MIN);
        }
    }

    if (!updatedNPCAndObjects)
    {
        if (m_updateObjectsTimer <= diff)
        {
            UpdateNPCsAndGameObjects();
            updatedNPCAndObjects = true;
        }
        else
            m_updateObjectsTimer -= diff;
    }

    return m_return;
}

void BattlefieldTB::OnPlayerEnterZone(Player* player)
{
    if (!m_isActive)
        RemoveAurasFromPlayer(player);
}

void BattlefieldTB::OnPlayerLeaveZone(Player* player)
{
    if (!m_isActive)
        RemoveAurasFromPlayer(player);
}

void BattlefieldTB::OnPlayerJoinWar(Player* player)
{
    RemoveAurasFromPlayer(player);

    player->SetPvP(true);

    // Bonus damage buff for attackers
    if (player->GetTeamId() == GetAttackerTeam())
    {
        int32 towersDestroyed = sWorldStateMgr->GetValue(WS_BATTLEFIELD_TB_TOWERS_DESTROYED, m_Map);
        if (towersDestroyed > 0)
            player->CastSpell(player, SPELL_TOWER_ATTACK_BONUS, CastSpellExtraArgs(TRIGGERED_FULL_MASK).AddSpellMod(SPELLVALUE_AURA_STACK, towersDestroyed));
    }
}

void BattlefieldTB::OnPlayerLeaveWar(Player* player)
{
    RemoveAurasFromPlayer(player);
}

void BattlefieldTB::RemoveAurasFromPlayer(Player* player)
{
    player->RemoveAurasDueToSpell(SPELL_TB_SLOW_FALL);
    player->RemoveAurasDueToSpell(SPELL_TB_VETERAN);
    player->RemoveAurasDueToSpell(SPELL_TOWER_ATTACK_BONUS);
    player->RemoveAurasDueToSpell(SPELL_TB_SPIRITUAL_IMMUNITY);
}

void BattlefieldTB::OnStartGrouping()
{
    UpdateNPCsAndGameObjects();

    sWorldStateMgr->SetValue(WS_BATTLEFIELD_TB_STATE_PREPARATIONS, 1, false, m_Map);

    // Teleport players out of questing area
    for (uint8 team = 0; team < BG_TEAMS_COUNT; ++team)
        for (auto itr = m_players[team].begin(); itr != m_players[team].end(); ++itr)
            if (Player* player = ObjectAccessor::FindPlayer(*itr))
                if (player->GetAreaId() == TBQuestAreas[m_iCellblockRandom].entry)
                    player->CastSpell(player, TBQuestAreas[m_iCellblockRandom].teleportSpell, true);

    // Should we also teleport players out of Baradin Hold underground area?
}

void BattlefieldTB::OnBattleStart()
{
    SetData(BATTLEFIELD_TB_DATA_TOWERS_INTACT, uint32(3));

    UpdateNPCsAndGameObjects();

    sWorldStateMgr->SetValue(WS_BATTLEFIELD_TB_TIME_BATTLE_END_SHOW, 1, false, m_Map);
    sWorldStateMgr->SetValue(WS_BATTLEFIELD_TB_TIME_BATTLE_END, GameTime::GetGameTime() + m_Timer / IN_MILLISECONDS, false, m_Map);

    sWorldStateMgr->SetValue(WS_BATTLEFIELD_TB_TIME_NEXT_BATTLE_SHOW, 0, false, m_Map);
    sWorldStateMgr->SetValueAndSaveInDb(WS_BATTLEFIELD_TB_TIME_NEXT_BATTLE, 0, false, m_Map);

    sWorldStateMgr->SetValue(WS_BATTLEFIELD_TB_ALLIANCE_ATTACKING_SHOW, GetAttackerTeam() == TEAM_ALLIANCE ? 1 : 0, false, m_Map);
    sWorldStateMgr->SetValue(WS_BATTLEFIELD_TB_HORDE_ATTACKING_SHOW, GetAttackerTeam() == TEAM_HORDE ? 1 : 0, false, m_Map);

    sWorldStateMgr->SetValue(WS_BATTLEFIELD_TB_ALLIANCE_CONTROLS_SHOW, 0, false, m_Map);
    sWorldStateMgr->SetValue(WS_BATTLEFIELD_TB_HORDE_CONTROLS_SHOW, 0, false, m_Map);

    sWorldStateMgr->SetValue(WS_BATTLEFIELD_TB_BUILDINGS_CAPTURED_SHOW, 1, false, m_Map);
    sWorldStateMgr->SetValue(WS_BATTLEFIELD_TB_BUILDINGS_CAPTURED, 0, false, m_Map);

    sWorldStateMgr->SetValue(WS_BATTLEFIELD_TB_TOWERS_DESTROYED_SHOW, 0, false, m_Map);
    sWorldStateMgr->SetValue(WS_BATTLEFIELD_TB_TOWERS_DESTROYED, 0, false, m_Map);

    sWorldStateMgr->SetValue(WS_BATTLEFIELD_TB_STATE_PREPARATIONS, 0, false, m_Map);
    sWorldStateMgr->SetValueAndSaveInDb(WS_BATTLEFIELD_TB_STATE_BATTLE, 1, false, m_Map);

    // Towers/spires
    for (uint8 i = 0; i < TB_TOWERS_COUNT; i++)
    {
        sWorldStateMgr->SetValue(TBTowers[i].wsIntact[GetDefenderTeam()], 1, false, m_Map);
        sWorldStateMgr->SetValue(TBTowers[i].wsDamaged[GetDefenderTeam()], 0, false, m_Map);
        sWorldStateMgr->SetValue(TBTowers[i].wsDestroyed, 0, false, m_Map);
        sWorldStateMgr->SetValue(TBTowers[i].wsDamaged[GetAttackerTeam()], 0, false, m_Map);
        sWorldStateMgr->SetValue(TBTowers[i].wsIntact[GetAttackerTeam()], 0, false, m_Map);
    }
}

void BattlefieldTB::OnBattleEnd(bool endByTimer)
{
    if (!endByTimer) // Attackers win (but now they are defenders already)
        SendWarning(GetDefenderTeam() == TEAM_ALLIANCE ? TB_TEXT_FORTRESS_CAPTURE_ALLIANCE : TB_TEXT_FORTRESS_CAPTURE_HORDE);
    else // Defenders win
        SendWarning(GetDefenderTeam() == TEAM_ALLIANCE ? TB_TEXT_FORTRESS_DEFEND_ALLIANCE : TB_TEXT_FORTRESS_DEFEND_HORDE);

    // UpdateNPCsAndGameObjects() must be called 1 minute after battle ends
    m_updateObjectsTimer = 1 * MINUTE * IN_MILLISECONDS;
    updatedNPCAndObjects = false;

    // Complete quest
    TeamCastSpell(GetDefenderTeam(), GetDefenderTeam() == TEAM_ALLIANCE ? SPELL_VICTORY_ALLIANCE : SPELL_VICTORY_HORDE);

    // Rewards
    TeamCastSpell(GetDefenderTeam(), GetDefenderTeam() == TEAM_ALLIANCE ? SPELL_REWARD_VICTORY_ALLIANCE : SPELL_REWARD_VICTORY_HORDE);
    for (uint32 i = 0; i < GetData(BATTLEFIELD_TB_DATA_TOWERS_INTACT); i++) // Unsure, for each intact tower or only once for having any tower intact?
        TeamCastSpell(GetDefenderTeam(), SPELL_REWARD_TOWER_INTACT);
    TeamCastSpell(GetAttackerTeam(), SPELL_REWARD_DEFEAT);

    for (uint8 team = 0; team < 2; ++team)
    {
        for (auto itr = m_PlayersInWar[team].begin(); itr != m_PlayersInWar[team].end(); ++itr)
            if (Player* player = ObjectAccessor::FindPlayer(*itr))
                RemoveAurasFromPlayer(player);

        m_PlayersInWar[team].clear();
    }

    // Reset time warning vars
    warnedFiveMinutes = false;
    warnedTwoMinutes = false;
    warnedOneMinute = false;

    sWorldStateMgr->SetValue(WS_BATTLEFIELD_TB_TIME_BATTLE_END_SHOW, 0, false, m_Map);
    sWorldStateMgr->SetValue(WS_BATTLEFIELD_TB_TIME_BATTLE_END, 0, false, m_Map);

    sWorldStateMgr->SetValue(WS_BATTLEFIELD_TB_TIME_NEXT_BATTLE_SHOW, 1, false, m_Map);
    sWorldStateMgr->SetValueAndSaveInDb(WS_BATTLEFIELD_TB_TIME_NEXT_BATTLE, GameTime::GetGameTime() + m_NoWarBattleTime / IN_MILLISECONDS, false, m_Map);

    sWorldStateMgr->SetValue(WS_BATTLEFIELD_TB_ALLIANCE_ATTACKING_SHOW, 0, false, m_Map);
    sWorldStateMgr->SetValue(WS_BATTLEFIELD_TB_HORDE_ATTACKING_SHOW, 0, false, m_Map);

    sWorldStateMgr->SetValueAndSaveInDb(WS_BATTLEFIELD_TB_FACTION_CONTROLLING, GetDefenderTeam() + 1, false, m_Map);
    sWorldStateMgr->SetValue(WS_BATTLEFIELD_TB_ALLIANCE_CONTROLS_SHOW, GetDefenderTeam() == TEAM_ALLIANCE ? 1 : 0, false, m_Map);
    sWorldStateMgr->SetValue(WS_BATTLEFIELD_TB_HORDE_CONTROLS_SHOW, GetDefenderTeam() == TEAM_HORDE ? 1 : 0, false, m_Map);
    sWorldStateMgr->SetValue(WS_BATTLEFIELD_TB_KEEP_ALLIANCE, GetDefenderTeam() == TEAM_ALLIANCE ? 1 : 0, false, m_Map);
    sWorldStateMgr->SetValue(WS_BATTLEFIELD_TB_KEEP_HORDE, GetDefenderTeam() == TEAM_HORDE ? 1 : 0, false, m_Map);

    sWorldStateMgr->SetValue(WS_BATTLEFIELD_TB_BUILDINGS_CAPTURED_SHOW, 0, false, m_Map);

    sWorldStateMgr->SetValueAndSaveInDb(WS_BATTLEFIELD_TB_STATE_BATTLE, 0, false, m_Map);
}

void BattlefieldTB::UpdateNPCsAndGameObjects()
{
    for (ObjectGuid guid : BattleInactiveNPCs)
        if (Creature* creature = GetCreature(guid))
            HideNpc(creature);

    for (ObjectGuid guid : BattleInactiveGOs)
        if (GameObject* gameobject = GetGameObject(guid))
            gameobject->SetRespawnTime(RESPAWN_ONE_DAY);

    for (ObjectGuid guid : TemporaryNPCs)
        if (Creature* creature = GetCreature(guid))
            creature->RemoveFromWorld();
    TemporaryNPCs.clear();

    for (ObjectGuid guid : TemporaryGOs)
        if (GameObject* gameobject = GetGameObject(guid))
            gameobject->Delete();
    TemporaryGOs.clear();

    // Tol Barad gates - closed during warmup
    if (GameObject* gates = GetGameObject(TBGatesGUID))
        gates->SetGoState(GetState() == AsUnderlyingType(BATTLEFIELD_WARMUP) ? GO_STATE_READY : GO_STATE_ACTIVE);

    // Baradin Hold door - open when inactive
    if (GameObject* door = GetGameObject(TBDoorGUID))
        door->SetGoState(GetState() == AsUnderlyingType(BATTLEFIELD_INACTIVE) ? GO_STATE_ACTIVE : GO_STATE_READY);

    // Decide which cellblock and questgiver will be active.
    m_iCellblockRandom = GetState() == AsUnderlyingType(BATTLEFIELD_INACTIVE) ? urand(0, CELLBLOCK_MAX - 1) : uint8(CELLBLOCK_NONE);

    // To The Hole gate
    if (GameObject* door = GetGameObject(m_gateToTheHoleGUID))
        door->SetGoState(m_iCellblockRandom == AsUnderlyingType(CELLBLOCK_THE_HOLE) ? GO_STATE_ACTIVE : GO_STATE_READY);

    // D-Block gate
    if (GameObject* door = GetGameObject(m_gateDBlockGUID))
        door->SetGoState(m_iCellblockRandom == AsUnderlyingType(CELLBLOCK_D_BLOCK) ? GO_STATE_ACTIVE : GO_STATE_READY);

    // Cursed Depths gate
    if (GameObject* door = GetGameObject(m_gateCursedDepthsGUID))
        door->SetGoState(m_iCellblockRandom == AsUnderlyingType(CELLBLOCK_CURSED_DEPTHS) ? GO_STATE_ACTIVE : GO_STATE_READY);

    if (GetState() == BATTLEFIELD_INACTIVE)
    {
        // Delete capture points
        for (BfCapturePointMap::iterator itr = m_capturePoints.begin(); itr != m_capturePoints.end(); ++itr)
            itr->second->DelCapturePoint();
        m_capturePoints.clear();

        // Create capture points
        for (uint8 i = 0; i < TB_BASE_COUNT; i++)
        {
            TolBaradCapturePoint* capturePoint = new TolBaradCapturePoint(this, GetDefenderTeam());

            //Spawn flag pole
            if (GameObject* go = SpawnGameObject(TBCapturePoints[i].entryFlagPole[GetDefenderTeam()], TBCapturePoints[i].pos, TBCapturePoints[i].rot))
            {
                go->SetGoArtKit(GetDefenderTeam() == TEAM_ALLIANCE ? TB_GO_ARTKIT_FLAG_ALLIANCE : TB_GO_ARTKIT_FLAG_HORDE);
                capturePoint->SetCapturePointData(go);
            }

            AddCapturePoint(capturePoint);
        }

        for (ObjectGuid guid : BattleInactiveNPCs)
            if (Creature* creature = GetCreature(guid))
                ShowNpc(creature, true);

        for (ObjectGuid guid : BattleInactiveGOs)
            if (GameObject* gameobject = GetGameObject(guid))
                gameobject->SetRespawnTime(RESPAWN_IMMEDIATELY);

        for (uint8 i = 0; i < TB_QUEST_INFANTRY_MAX; i++)
        {
            uint32 entry = TB_QUEST_INFANTRY[GetDefenderTeam()][urand(0,3)];
            if (Creature* creature = SpawnCreature(entry, TBQuestInfantrySpawnData[i]))
                TemporaryNPCs.insert(creature->GetGUID());
        }

        for (uint8 i = 0; i < TB_GUARDS_MAX; i++)
            if (Creature* creature = SpawnCreature(GetDefenderTeam() == TEAM_ALLIANCE ? NPC_BARADIN_GUARD : NPC_HELLSCREAMS_SENTRY, GuardNPCSpawns[i]))
                TemporaryNPCs.insert(creature->GetGUID());

        for (uint8 i = 0; i < TB_FACTION_NPC_MAX; i++)
            if (Creature* creature = SpawnCreature(GetDefenderTeam() == TEAM_ALLIANCE ? FactionNPCSpawns[i].entryAlliance : FactionNPCSpawns[i].entryHorde, FactionNPCSpawns[i].pos))
                TemporaryNPCs.insert(creature->GetGUID());

        if (Creature* creature = SpawnCreature(RandomQuestgivers[GetDefenderTeam()][m_iCellblockRandom], RandomQuestgiverPos))
            TemporaryNPCs.insert(creature->GetGUID());

        // Spawn portals
        for (uint8 i = 0; i < TB_PORTAL_MAX; i++)
            if (GameObject* go = SpawnGameObject(TBPortalEntry[GetDefenderTeam()], TBPortals[i].pos, TBPortals[i].rot))
                TemporaryGOs.insert(go->GetGUID());

        // Update towers
        for (ObjectGuid guid : Towers)
            if (GameObject* go = GetGameObject(guid))
                go->SetDestructibleState(GO_DESTRUCTIBLE_REBUILDING);
    }
    else if (GetState() == BATTLEFIELD_IN_PROGRESS)
    {
        for (uint8 i = 0; i < TB_ABANDONED_SIEGE_ENGINE_COUNT; i++)
            if (Creature* creature = SpawnCreature(NPC_ABANDONED_SIEGE_ENGINE, TBAbandonedSiegeEngineSpawnData[i]))
                TemporaryNPCs.insert(creature->GetGUID());

        for (ObjectGuid guid : Towers)
        {
            if (GameObject* go = GetGameObject(guid))
            {
                go->SetDestructibleState(GO_DESTRUCTIBLE_INTACT);
                go->ModifyHealth(go->GetGOValue()->Building.MaxHealth);
            }
        }
    }

    // Spawn banners
    for (uint8 i = 0; i < TB_BANNER_MAX; i++)
        if (GameObject* go = SpawnGameObject(TBBannerEntry[GetDefenderTeam()], TBBanners[i].pos, TBBanners[i].rot))
            TemporaryGOs.insert(go->GetGUID());

    // Set graveyard controls
    for (uint8 i = 0; i < BATTLEFIELD_TB_GRAVEYARD_MAX; i++)
        if (BfGraveyard* graveyard = GetGraveyardById(i))
            graveyard->GiveControlTo(!IsWarTime() || TBGraveyards[i].defenderControls ? GetDefenderTeam() : GetAttackerTeam());
}

void BattlefieldTB::OnCreatureCreate(Creature* creature)
{
    switch (creature->GetEntry())
    {
        // Store NPCs that need visibility toggling
        case NPC_TOLBARAD_CAPTIVE_SPIRIT:
        case NPC_TOLBARAD_CELLBLOCK_OOZE:
        case NPC_TOLBARAD_ARCHMAGE_GALUS:
        case NPC_TOLBARAD_GHASTLY_CONVICT:
        case NPC_TOLBARAD_SHIVARRA_DESTROYER:
        case NPC_TOLBARAD_CELL_WATCHER:
        case NPC_TOLBARAD_SVARNOS:
        case NPC_TOLBARAD_JAILED_WRATHGUARD:
        case NPC_TOLBARAD_IMPRISONED_IMP:
        case NPC_TOLBARAD_WARDEN_SILVA:
        case NPC_TOLBARAD_WARDEN_GUARD:
        case NPC_TOLBARAD_IMPRISONED_WORKER:
        case NPC_TOLBARAD_EXILED_MAGE:
        case NPC_CROCOLISK:
        case NPC_PROBLIM:
            BattleInactiveNPCs.insert(creature->GetGUID());
            if (GetState() == BATTLEFIELD_WARMUP) // If battle is about to start, we must hide these.
                HideNpc(creature);
            break;
        case NPC_ABANDONED_SIEGE_ENGINE:
            creature->SetFaction(TBFactions[GetDefenderTeam()]);
            creature->CastSpell(creature, SPELL_THICK_LAYER_OF_RUST, true);
            break;
        case NPC_SIEGE_ENGINE_TURRET:
            if (Unit* vehiclebase = creature->GetCharmerOrOwner()->GetVehicleBase())
                creature->EnterVehicle(vehiclebase);
            break;
        case NPC_TOWER_RANGE_FINDER:
            creature->CastSpell(creature, SPELL_TOWER_RANGE_FINDER_PERIODIC, true);
            break;
        case NPC_TB_GY_SPIRIT_BARADIN_HOLD_A:
        case NPC_TB_GY_SPIRIT_BARADIN_HOLD_H:
        case NPC_TB_GY_SPIRIT_IRONCLAD_GARRISON_A:
        case NPC_TB_GY_SPIRIT_WARDENS_VIGIL_A:
        case NPC_TB_GY_SPIRIT_EAST_SPIRE_A:
        case NPC_TB_GY_SPIRIT_SOUTH_SPIRE_A:
        case NPC_TB_GY_SPIRIT_WEST_SPIRE_A:
        case NPC_TB_GY_SPIRIT_SLAGWORKS_A:
        case NPC_TB_GY_SPIRIT_IRONCLAD_GARRISON_H:
        case NPC_TB_GY_SPIRIT_WARDENS_VIGIL_H:
        case NPC_TB_GY_SPIRIT_SLAGWORKS_H:
        case NPC_TB_GY_SPIRIT_WEST_SPIRE_H:
        case NPC_TB_GY_SPIRIT_EAST_SPIRE_H:
        case NPC_TB_GY_SPIRIT_SOUTH_SPIRE_H:
            creature->CastSpell(creature, SPELL_TB_SPIRITUAL_IMMUNITY, true);
            creature->CastSpell(creature, SPELL_TB_SPIRIT_HEAL_CHANNEL, true);
            break;
        default:
            break;
    }
}

void BattlefieldTB::OnGameObjectCreate(GameObject* go)
{
    switch (go->GetEntry())
    {
        case GO_TOLBARAD_GATES:
            TBGatesGUID = go->GetGUID();
            go->SetGoState(GetState() == AsUnderlyingType(BATTLEFIELD_WARMUP) ? GO_STATE_READY : GO_STATE_ACTIVE);
            break;
        case GO_TOLBARAD_DOOR:
            TBDoorGUID = go->GetGUID();
            go->SetGoState(GetState() == AsUnderlyingType(BATTLEFIELD_INACTIVE) ? GO_STATE_ACTIVE : GO_STATE_READY);
            break;
        case GO_GATE_TO_THE_HOLE:
            m_gateToTheHoleGUID = go->GetGUID();
            go->SetGoState(m_iCellblockRandom == AsUnderlyingType(CELLBLOCK_THE_HOLE) ? GO_STATE_ACTIVE : GO_STATE_READY);
            break;
        case GO_GATE_D_BLOCK:
            m_gateDBlockGUID = go->GetGUID();
            go->SetGoState(m_iCellblockRandom == AsUnderlyingType(CELLBLOCK_D_BLOCK) ? GO_STATE_ACTIVE : GO_STATE_READY);
            break;
        case GO_CURSED_DEPTHS_GATE:
            m_gateCursedDepthsGUID = go->GetGUID();
            go->SetGoState(m_iCellblockRandom == AsUnderlyingType(CELLBLOCK_CURSED_DEPTHS) ? GO_STATE_ACTIVE : GO_STATE_READY);
            break;
        case GO_CRATE_OF_CELLBLOCK_RATIONS:
        case GO_CURSED_SHACKLES:
        case GO_DUSTY_PRISON_JOURNAL:
        case GO_TB_MEETING_STONE:
        case GO_TB_INSTANCE_VISUAL_1:
        case GO_TB_INSTANCE_VISUAL_2:
        case GO_TB_INSTANCE_VISUAL_3:
        case GO_TB_INSTANCE_VISUAL_4:
            BattleInactiveGOs.insert(go->GetGUID());
            if (GetState() == BATTLEFIELD_WARMUP) // If battle is about to start, we must hide these.
                go->SetRespawnTime(RESPAWN_ONE_DAY);
            break;
        default:
            break;
    }
}

void BattlefieldTB::ProcessEvent(WorldObject* obj, uint32 eventId, WorldObject* /*invoker*/)
{
    if (!IsWarTime())
        return;

    if (eventId == EVENT_COUNT_CAPTURED_BASE)
    {
        UpdateCapturedBaseCount();
        return;
    }

    if (!obj)
        return;

    GameObject* go = obj->ToGameObject();
    if (!go)
        return;

    TBTowerId towerId;
    switch (go->GetEntry())
    {
        case GO_WEST_SPIRE:
            towerId = TB_TOWER_WEST_SPIRE;
            break;
        case GO_EAST_SPIRE:
            towerId = TB_TOWER_EAST_SPIRE;
            break;
        case GO_SOUTH_SPIRE:
            towerId = TB_TOWER_SOUTH_SPIRE;
            break;
        default:
            return;
    }

    if (go->GetDestructibleState() == GO_DESTRUCTIBLE_DAMAGED)
        TowerDamaged(towerId);
    else if (go->GetDestructibleState() == GO_DESTRUCTIBLE_DESTROYED)
        TowerDestroyed(towerId);
}

void BattlefieldTB::TowerDamaged(TBTowerId tbTowerId)
{
    if (!IsWarTime())
        return;

    SendWarning(TBTowers[tbTowerId].textDamaged);

    SetData(BATTLEFIELD_TB_DATA_TOWERS_INTACT, GetData(BATTLEFIELD_TB_DATA_TOWERS_INTACT) - 1);

    sWorldStateMgr->SetValue(TBTowers[tbTowerId].wsIntact[GetDefenderTeam()], 0, false, m_Map);
    sWorldStateMgr->SetValue(TBTowers[tbTowerId].wsDamaged[GetDefenderTeam()], 1, false, m_Map);

    TeamCastSpell(GetAttackerTeam(), SPELL_REWARD_TOWER_DAMAGED);
}

void BattlefieldTB::TowerDestroyed(TBTowerId tbTowerId)
{
    if (!IsWarTime())
        return;

    // Add 5 minute bonus time
    m_Timer += m_BonusTime;
    sWorldStateMgr->SetValue(WS_BATTLEFIELD_TB_TIME_BATTLE_END, GameTime::GetGameTime() + m_Timer / IN_MILLISECONDS, false, m_Map);

    SendWarning(TBTowers[tbTowerId].textDestroyed);

    sWorldStateMgr->SetValue(WS_BATTLEFIELD_TB_TOWERS_DESTROYED_SHOW, 1, false, m_Map);
    int32 towersDestroyed = sWorldStateMgr->GetValue(WS_BATTLEFIELD_TB_TOWERS_DESTROYED,m_Map) + 1;
    sWorldStateMgr->SetValue(WS_BATTLEFIELD_TB_TOWERS_DESTROYED, towersDestroyed, false, m_Map);

    sWorldStateMgr->SetValue(TBTowers[tbTowerId].wsDamaged[GetDefenderTeam()], 0, false, m_Map);
    sWorldStateMgr->SetValue(TBTowers[tbTowerId].wsDestroyed, 1, false, m_Map);

    // Attack bonus buff
    for (ObjectGuid const& guid : m_PlayersInWar[GetAttackerTeam()])
        if (Player* player = ObjectAccessor::FindPlayer(guid))
            player->CastSpell(player, SPELL_TOWER_ATTACK_BONUS, CastSpellExtraArgs(TRIGGERED_FULL_MASK).AddSpellMod(SPELLVALUE_AURA_STACK, towersDestroyed));

    // Honor reward
    TeamCastSpell(GetAttackerTeam(), SPELL_REWARD_TOWER_DESTROYED);
}

void BattlefieldTB::UpdateCapturedBaseCount()
{
    uint32 numCapturedBases = 0; // How many bases attacker has captured

    for (BfCapturePointMap::iterator itr = m_capturePoints.begin(); itr != m_capturePoints.end(); ++itr)
        if (itr->second->GetTeamId() == GetAttackerTeam())
            numCapturedBases += 1;

    sWorldStateMgr->SetValue(WS_BATTLEFIELD_TB_BUILDINGS_CAPTURED, numCapturedBases, false, m_Map);

    // Check if attackers won
    if (numCapturedBases == TB_BASE_COUNT)
        EndBattle(false);
}

// Called when player kill a unit in wg zone
void BattlefieldTB::HandleKill(Player* killer, Unit* victim)
{
    if (killer == victim || victim->GetTypeId() != TYPEID_PLAYER)
        return;

    TeamId killerTeam = killer->GetTeamId();
    for (auto itr = m_PlayersInWar[killerTeam].begin(); itr != m_PlayersInWar[killerTeam].end(); ++itr)
        if (Player* player = ObjectAccessor::FindPlayer(*itr))
            if (player->GetDistance2d(killer) < 40.0f)
                PromotePlayer(player);
}

void BattlefieldTB::PromotePlayer(Player* killer)
{
    if (!m_isActive || killer->HasAura(SPELL_TB_VETERAN))
        return;

    killer->CastSpell(killer, SPELL_TB_VETERAN, true);
}

TolBaradCapturePoint::TolBaradCapturePoint(BattlefieldTB* battlefield, TeamId teamInControl) : BfCapturePoint(battlefield)
{
    m_Bf = battlefield;
    m_team = teamInControl;
    m_value = teamInControl == TEAM_ALLIANCE ? m_maxValue : -m_maxValue;
    m_State = teamInControl == TEAM_ALLIANCE ? BF_CAPTUREPOINT_OBJECTIVESTATE_ALLIANCE : BF_CAPTUREPOINT_OBJECTIVESTATE_HORDE;
}

void TolBaradCapturePoint::SendChangePhase()
{
    if (m_OldState == m_State)
        return;

    // Find out index
    uint8 iBase = TB_BASE_COUNT;
    for (uint8 i = 0; i < TB_BASE_COUNT; i++)
        if (GetCapturePointEntry() == TBCapturePoints[i].entryFlagPole[m_Bf->GetDefenderTeam()])
            iBase = i;

    if (iBase == TB_BASE_COUNT)
        return;

    // Turn off previous world state icon
    switch (m_OldState)
    {
        case BF_CAPTUREPOINT_OBJECTIVESTATE_ALLIANCE:
        case BF_CAPTUREPOINT_OBJECTIVESTATE_HORDE:
            sWorldStateMgr->SetValue(TBCapturePoints[iBase].wsControlled[GetTeamId()], 0, false, m_Bf->GetMap());
            break;
        case BF_CAPTUREPOINT_OBJECTIVESTATE_HORDE_ALLIANCE_CHALLENGE:
        case BF_CAPTUREPOINT_OBJECTIVESTATE_NEUTRAL_ALLIANCE_CHALLENGE:
            sWorldStateMgr->SetValue(TBCapturePoints[iBase].wsCapturing[TEAM_ALLIANCE], 0, false, m_Bf->GetMap());
            break;
        case BF_CAPTUREPOINT_OBJECTIVESTATE_ALLIANCE_HORDE_CHALLENGE:
        case BF_CAPTUREPOINT_OBJECTIVESTATE_NEUTRAL_HORDE_CHALLENGE:
            sWorldStateMgr->SetValue(TBCapturePoints[iBase].wsCapturing[TEAM_HORDE], 0, false, m_Bf->GetMap());
            break;
        default:
            break;
    }

    // Turn on new world state icon and send warning
    switch (m_State)
    {
        case BF_CAPTUREPOINT_OBJECTIVESTATE_ALLIANCE:
        case BF_CAPTUREPOINT_OBJECTIVESTATE_HORDE:
            m_Bf->SendWarning(TBCapturePoints[iBase].textGained[GetTeamId()]);
            sWorldStateMgr->SetValue(TBCapturePoints[iBase].wsControlled[GetTeamId()], 1, false, m_Bf->GetMap());
            GetCapturePointGo()->SetGoArtKit(GetTeamId() == TEAM_ALLIANCE ? TB_GO_ARTKIT_FLAG_ALLIANCE : TB_GO_ARTKIT_FLAG_HORDE);
            break;
        case BF_CAPTUREPOINT_OBJECTIVESTATE_HORDE_ALLIANCE_CHALLENGE:
            m_Bf->SendWarning(TBCapturePoints[iBase].textLost[TEAM_HORDE]);
            [[fallthrough]];
        case BF_CAPTUREPOINT_OBJECTIVESTATE_NEUTRAL_ALLIANCE_CHALLENGE:
            sWorldStateMgr->SetValue(TBCapturePoints[iBase].wsCapturing[TEAM_ALLIANCE], 1, false, m_Bf->GetMap());
            GetCapturePointGo()->SetGoArtKit(TB_GO_ARTKIT_FLAG_NONE);
            break;
        case BF_CAPTUREPOINT_OBJECTIVESTATE_ALLIANCE_HORDE_CHALLENGE:
            m_Bf->SendWarning(TBCapturePoints[iBase].textLost[TEAM_ALLIANCE]);
            [[fallthrough]];
        case BF_CAPTUREPOINT_OBJECTIVESTATE_NEUTRAL_HORDE_CHALLENGE:
            sWorldStateMgr->SetValue(TBCapturePoints[iBase].wsCapturing[TEAM_HORDE], 1, false, m_Bf->GetMap());
            GetCapturePointGo()->SetGoArtKit(TB_GO_ARTKIT_FLAG_NONE);
            break;
        default:
            break;
    }

    // Update counter
    m_Bf->ProcessEvent(nullptr, EVENT_COUNT_CAPTURED_BASE, nullptr);
}

class Battlefield_tol_barad : public BattlefieldScript
{
public:
    Battlefield_tol_barad() : BattlefieldScript("battlefield_tb") { }

    Battlefield* GetBattlefield(Map* map) const override
    {
        return new BattlefieldTB(map);
    }
};

void AddSC_BF_tol_barad()
{
    new Battlefield_tol_barad();
}
