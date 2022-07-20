
#include "NewGuardian.h"
#include "DBCStores.h"
#include "ObjectMgr.h"
#include "SpellMgr.h"
#include "SpellInfo.h"

NewGuardian::NewGuardian(SummonPropertiesEntry const* properties, Unit* summoner, bool isWorldObject) :
    NewTempoarySummon(properties, summoner, isWorldObject), _isUsingRealStats(false)
{
    m_unitTypeMask |= UNIT_MASK_GUARDIAN;
}

void NewGuardian::AddToWorld()
{
    // Setting the guid before adding to world to reduce building unnecessary object update packets
    SetCreatorGUID(GetInternalSummonerGUID());

    NewTempoarySummon::AddToWorld();
}

void NewGuardian::HandlePreSummonActions(uint8 creatureLevel)
{
    NewTempoarySummon::HandlePreSummonActions(creatureLevel);

    // Guardians inherit their summoner's faction and level unless a flag forbids it or the properties override it
    if (Unit* summoner = GetSummoner())
    {
        if (!_summonProperties || _summonProperties->Faction == 0)
            SetFaction(summoner->GetFaction());

        if (_summonProperties && !_summonProperties->GetFlags().HasFlag(SummonPropertiesFlags::UseCreatureLevel))
            SetLevel(summoner->getLevel());
    }

    CreatureTemplate const* creatureInfo = GetCreatureTemplate();
    if (!creatureInfo)
        return;

    SetMeleeDamageSchool(SpellSchools(creatureInfo->dmgschool));

    if (PetLevelInfo const* petLevelInfo = sObjectMgr->GetPetLevelInfo(creatureInfo->Entry, getLevel()))
    {
        for (uint8 i = 0; i < MAX_STATS; ++i)
            SetCreateStat(Stats(i), float(petLevelInfo->stats[i]));

        if (petLevelInfo->armor > 0)
            SetStatFlatModifier(UNIT_MOD_ARMOR, BASE_VALUE, float(petLevelInfo->armor));

        SetCreateHealth(petLevelInfo->health);
        SetCreateMana(petLevelInfo->mana);

        _isUsingRealStats = true;
    }
    else
    {
        // Guardian has no pet level data, fall back to default creature behavior of Creature::UpdateEntry
        printf("using fallback stats\n");
        printf("old maxhealth = %u \n", GetMaxHealth());
        uint32 previousHealth = GetHealth();
        UpdateLevelDependantStats();
        if (previousHealth > 0)
            SetHealth(previousHealth);

        printf("new maxhealth = %u \n", GetMaxHealth());

        SetMeleeDamageSchool(SpellSchools(creatureInfo->dmgschool));
        SetStatFlatModifier(UNIT_MOD_RESISTANCE_HOLY, BASE_VALUE, float(creatureInfo->resistance[SPELL_SCHOOL_HOLY]));
        SetStatFlatModifier(UNIT_MOD_RESISTANCE_FIRE, BASE_VALUE, float(creatureInfo->resistance[SPELL_SCHOOL_FIRE]));
        SetStatFlatModifier(UNIT_MOD_RESISTANCE_NATURE, BASE_VALUE, float(creatureInfo->resistance[SPELL_SCHOOL_NATURE]));
        SetStatFlatModifier(UNIT_MOD_RESISTANCE_FROST, BASE_VALUE, float(creatureInfo->resistance[SPELL_SCHOOL_FROST]));
        SetStatFlatModifier(UNIT_MOD_RESISTANCE_SHADOW, BASE_VALUE, float(creatureInfo->resistance[SPELL_SCHOOL_SHADOW]));
        SetStatFlatModifier(UNIT_MOD_RESISTANCE_ARCANE, BASE_VALUE, float(creatureInfo->resistance[SPELL_SCHOOL_ARCANE]));

        SetCanModifyStats(true);
    }

    UpdateAllStats();
}

void NewGuardian::HandlePostSummonActions()
{
    NewTempoarySummon::HandlePostSummonActions();

    CastPassiveAuras();
}

void NewGuardian::CastPassiveAuras()
{
    CreatureTemplate const* creatureInfo = GetCreatureTemplate();
    if (!creatureInfo)
        return;

    CreatureFamilyEntry const* creatureFamilyEntry = sCreatureFamilyStore.LookupEntry(creatureInfo->family);
    if (!creatureFamilyEntry)
        return;

    PetFamilySpellsStore::const_iterator petSpellStore = sPetFamilySpellsStore.find(creatureFamilyEntry->ID);
    if (petSpellStore == sPetFamilySpellsStore.end())
        return;

    for (uint32 spellId : petSpellStore->second)
        if (SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellId))
            if (spellInfo->IsPassive())
            {
                CastSpell(this, spellId);
                printf("casting %s\n", spellInfo->SpellName);
            }
}
