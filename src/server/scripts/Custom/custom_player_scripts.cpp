#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "Unit.h"
#include "Player.h"
#include "SpellAuras.h"

class CharacterResilienceGain : public PlayerScript
{
public:
    CharacterResilienceGain() : PlayerScript("CharacterResilienceGain") { }

    void OnLogin(Player* player, bool /*firstLogin*/) override
    {
        const uint8 level = player->getLevel();
        const uint32 race = player->getRace();
        const uint32 pClass = player->getClass();
        PlayerLevelInfo info;

        sObjectMgr->GetPlayerLevelInfo(race, pClass, level, &info);

        player->ApplyRatingMod(CR_RESILIENCE_PLAYER_DAMAGE_TAKEN, info.resilience, true);
    }

    void OnLevelChanged(Player* player, uint8 oldLevel) override
    {
        const uint8 newLevel = player->getLevel();
        const uint32 race = player->getRace();
        const uint32 pClass = player->getClass();
        PlayerLevelInfo info;
        PlayerLevelInfo oldInfo;

        sObjectMgr->GetPlayerLevelInfo(race, pClass, newLevel, &info);
        sObjectMgr->GetPlayerLevelInfo(race, pClass, oldLevel, &oldInfo);

        player->ApplyRatingMod(CR_RESILIENCE_PLAYER_DAMAGE_TAKEN, newLevel > oldLevel ? info.resilience - oldInfo.resilience : oldInfo.resilience - info.resilience, newLevel > oldLevel);
    }
};

class CharacterDamageNerf : public PlayerScript
{
public:
    CharacterDamageNerf() : PlayerScript("CharacterDamageNerf") { }

    void OnLogin(Player* player, bool /*firstLogin*/) override
    {
        ApplyNerfAura(player);
    }

    void OnFreeTalentPointsChanged(Player* player, uint32 /*points*/) override
    {
        ApplyNerfAura(player);
    }

    void OnTalentsReset(Player* player, bool /*noCost*/) override
    {
        ApplyNerfAura(player);
    }

    void OnActivateSpec(Player* player, uint8 /*spec*/) override
    {
        ApplyNerfAura(player);
    }

private:
    uint32 GetActiveNerfAura(Player* player)
    {
        Unit::AuraMap& ownedAuras = player->GetOwnedAuras();
        for (uint32 nerfSpellId = ORIGINS_NERF_SPELLS_BEGIN; nerfSpellId < ORIGINS_NERF_SPELLS_END; ++nerfSpellId)
        {
            if (ownedAuras.contains(nerfSpellId))
                return nerfSpellId;
        }
        return 0;
    }

    void ApplyNerfAura(Player* player)
    {
        uint32 originsNerfSpell = ORIGINS_NERF_GENERIC;
        uint32 activeNerfSpell = GetActiveNerfAura(player);
        const uint8 activeSpec = player->GetActiveSpec();

        switch (player->GetPrimaryTalentTree(activeSpec))
        {
        case TALENT_TREE_WARRIOR_ARMS:
            originsNerfSpell = ORIGINS_NERF_WARRIOR_ARMS;
            break;
        case TALENT_TREE_WARRIOR_FURY:
            originsNerfSpell = ORIGINS_NERF_WARRIOR_FURY;
            break;
        case TALENT_TREE_WARRIOR_PROTECTION:
            originsNerfSpell = ORIGINS_NERF_WARRIOR_PROTECTION;
            break;
        case TALENT_TREE_PALADIN_HOLY:
            originsNerfSpell = ORIGINS_NERF_PALADIN_HOLY;
            break;
        case TALENT_TREE_PALADIN_PROTECTION:
            originsNerfSpell = ORIGINS_NERF_PALADIN_PROTECTION;
            break;
        case TALENT_TREE_PALADIN_RETRIBUTION:
            originsNerfSpell = ORIGINS_NERF_PALADIN_RETRIBUTION;
            break;
        case TALENT_TREE_HUNTER_BEAST_MASTERY:
            originsNerfSpell = ORIGINS_NERF_HUNTER_BEAST_MASTERY;
            break;
        case TALENT_TREE_HUNTER_MARKSMANSHIP:
            originsNerfSpell = ORIGINS_NERF_HUNTER_MARKSMANSHIP;
            break;
        case TALENT_TREE_HUNTER_SURVIVAL:
            originsNerfSpell = ORIGINS_NERF_HUNTER_SURVIVAL;
            break;
        case TALENT_TREE_ROGUE_ASSASSINATION:
            originsNerfSpell = ORIGINS_NERF_ROGUE_ASSASINATION;
            break;
        case TALENT_TREE_ROGUE_COMBAT:
            originsNerfSpell = ORIGINS_NERF_ROGUE_COMBAT;
            break;
        case TALENT_TREE_ROGUE_SUBTLETY:
            originsNerfSpell = ORIGINS_NERF_ROGUE_SUBTLETY;
            break;
        case TALENT_TREE_PRIEST_DISCIPLINE:
            originsNerfSpell = ORIGINS_NERF_PRIEST_DISCIPLINE;
            break;
        case TALENT_TREE_PRIEST_HOLY:
            originsNerfSpell = ORIGINS_NERF_PRIEST_HOLY;
            break;
        case TALENT_TREE_PRIEST_SHADOW:
            originsNerfSpell = ORIGINS_NERF_PRIEST_SHADOW;
            break;
        case TALENT_TREE_DEATH_KNIGHT_BLOOD:
            originsNerfSpell = ORIGINS_NERF_DK_BLOOD;
            break;
        case TALENT_TREE_DEATH_KNIGHT_FROST:
            originsNerfSpell = ORIGINS_NERF_DK_FROST;
            break;
        case TALENT_TREE_DEATH_KNIGHT_UNHOLY:
            originsNerfSpell = ORIGINS_NERF_DK_UNHOLY;
            break;
        case TALENT_TREE_SHAMAN_ELEMENTAL:
            originsNerfSpell = ORIGINS_NERF_SHAMAN_ELEMENTAL;
            break;
        case TALENT_TREE_SHAMAN_ENHANCEMENT:
            originsNerfSpell = ORIGINS_NERF_SHAMAN_ENHANCEMENT;
            break;
        case TALENT_TREE_SHAMAN_RESTORATION:
            originsNerfSpell = ORIGINS_NERF_SHAMAN_RESTORATION;
            break;
        case TALENT_TREE_MAGE_ARCANE:
            originsNerfSpell = ORIGINS_NERF_WARRIOR_PROTECTION;
            break;
        case TALENT_TREE_MAGE_FIRE:
            originsNerfSpell = ORIGINS_NERF_MAGE_FIRE;
            break;
        case TALENT_TREE_MAGE_FROST:
            originsNerfSpell = ORIGINS_NERF_MAGE_FROST;
            break;
        case TALENT_TREE_WARLOCK_AFFLICTION:
            originsNerfSpell = ORIGINS_NERF_WARLOCK_AFFLICTION;
            break;
        case TALENT_TREE_WARLOCK_DEMONOLOGY:
            originsNerfSpell = ORIGINS_NERF_WARLOCK_DEMONOLOGY;
            break;
        case TALENT_TREE_WARLOCK_DESTRUCTION:
            originsNerfSpell = ORIGINS_NERF_WARLOCK_DESTRUCTION;
            break;
        case TALENT_TREE_DRUID_BALANCE:
            originsNerfSpell = ORIGINS_NERF_DRUID_BALANCE;
            break;
        case TALENT_TREE_DRUID_FERAL_COMBAT:
            originsNerfSpell = ORIGINS_NERF_DRUID_FERAL;
            break;
        case TALENT_TREE_DRUID_RESTORATION:
            originsNerfSpell = ORIGINS_NERF_DRUID_RESTORATION;
            break;
        default:
            break;
        }

        // The nerf aura already active on player is same as one being applied; do nothing.
        if (activeNerfSpell == originsNerfSpell)
            return;

        // Remove active nerf spell and learn new nerf spell.
        player->RemoveSpell(activeNerfSpell, false, false);
        player->LearnSpell(originsNerfSpell, false);
    }
};

void AddSC_Player_Scripts()
{
    new CharacterResilienceGain();
    new CharacterDamageNerf();
}
