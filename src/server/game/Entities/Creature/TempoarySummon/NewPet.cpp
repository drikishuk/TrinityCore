
#include "NewPet.h"
#include "DBCStores.h"
#include "ObjectMgr.h"
#include "SpellMgr.h"
#include "SpellInfo.h"

NewPet::NewPet(SummonPropertiesEntry const* properties, Unit* summoner, bool isWorldObject, bool isClassPet) :
    NewGuardian(properties, summoner, isWorldObject), _isClassPet(isClassPet)
{
    m_unitTypeMask |= UNIT_MASK_PET;
    InitCharmInfo();
}

void NewPet::AddToWorld()
{
    // Setting the guid before adding to world to reduce building unnecessary object update packets
    SetSummonerGUID(GetInternalSummonerGUID());

    NewGuardian::AddToWorld();

    if (Unit* summoner = GetSummoner())
        summoner->SetActivelyControlledSummon(this, true);
}

void NewPet::RemoveFromWorld()
{
    if (Unit* summoner = GetSummoner())
        summoner->SetActivelyControlledSummon(this, false);

    NewGuardian::RemoveFromWorld();
}

void NewPet::HandlePreSummonActions(uint8 creatureLevel)
{
    NewGuardian::HandlePreSummonActions(creatureLevel);

    // Initialize the action bar after initializing the stats
    m_charmInfo->InitCharmCreateSpells();
}

void NewPet::HandlePostSummonActions()
{
    NewGuardian::HandlePostSummonActions();
}
