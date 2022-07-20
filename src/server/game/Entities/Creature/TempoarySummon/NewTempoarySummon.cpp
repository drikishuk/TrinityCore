
#include "NewTempoarySummon.h"
#include "DBCStores.h"
#include "CreatureAI.h"
#include "Log.h"
#include "ObjectAccessor.h"
#include "Player.h"
#include "TotemPackets.h"

NewTempoarySummon::NewTempoarySummon(SummonPropertiesEntry const* properties, Unit* summoner, bool isWorldObject) :
    Creature(isWorldObject), _summonProperties(properties), _summonDuration(0ms), _originalSummonDuration(0ms),
    _summonType(TEMPSUMMON_MANUAL_DESPAWN)
{
    if (summoner)
        _internalSummonerGUID = summoner->GetGUID();

    m_unitTypeMask |= UNIT_MASK_SUMMON;
}

void NewTempoarySummon::AddToWorld()
{
    if (IsInWorld())
        return;

    Creature::AddToWorld();

    Unit* summoner = GetSummoner();

    if (_summonProperties)
    {
        if (summoner)
        {
            SummonPropertiesSlot slot = SummonPropertiesSlot(_summonProperties->Slot);

            if (slot > SummonPropertiesSlot::None)
            {
                // Unsummon previous summon in the slot that we are about to occupy
                if (NewTempoarySummon* summon = summoner->GetSummonInSlot(slot))
                    summon->Unsummon();

                summoner->AddSummonGUIDToSlot(GetGUID(), SummonPropertiesSlot(_summonProperties->Slot));
            }
            else if (slot == SummonPropertiesSlot::AnyAvailableTotem)
            {
                slot = SummonPropertiesSlot::Totem1;

                // @todo: handle. Basepoints of the summon spell determines the number of slots we may check.
                // in Cataclysm this is only being used for Wild Mushroom right now.
            }
            else
                summoner->AddSummonGUID(GetGUID());

            if (_summonProperties->GetFlags().HasFlag(SummonPropertiesFlags::UseSummonerFaction))
                SetFaction(summoner->GetFaction());
        }
    }
}

void NewTempoarySummon::RemoveFromWorld()
{
    if (!IsInWorld())
        return;

    if (_summonProperties)
    {
        if (Unit* summoner = GetSummoner())
        {
            SummonPropertiesSlot slot = SummonPropertiesSlot(_summonProperties->Slot);
            if (slot > SummonPropertiesSlot::None)
            {
                if (Unit* summoner = GetSummoner())
                    summoner->RemoveSummonGUIDFromSlot(GetGUID(), SummonPropertiesSlot(_summonProperties->Slot));
            }
            else if (slot == SummonPropertiesSlot::AnyAvailableTotem)
            {
                // @todo: handle.
            }
            else
                summoner->RemoveSummonGUID(GetGUID());
        }
    }

    Creature::RemoveFromWorld();
}

void NewTempoarySummon::Update(uint32 diff)
{
    Creature::Update(diff);

    switch (_summonType)
    {
        case TEMPSUMMON_MANUAL_DESPAWN:
            break;
        case TEMPSUMMON_DEAD_DESPAWN:
            if (m_deathState == DEAD)
                Unsummon();
            break;
        case TEMPSUMMON_TIMED_DESPAWN:
            if (_summonDuration <= Milliseconds(diff))
            {
                Unsummon();
                return;
            }
            _summonDuration -= Milliseconds(diff);
            break;
        case TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT:
            if (!IsInCombat())
            {
                if (_summonDuration <= Milliseconds(diff))
                {
                    Unsummon();
                    return;
                }
                _summonDuration -= Milliseconds(diff);
            }
            else if (_summonDuration != _originalSummonDuration)
                _summonDuration = _originalSummonDuration;
            break;
        case TEMPSUMMON_CORPSE_TIMED_DESPAWN:
            if (m_deathState == CORPSE)
            {
                if (_summonDuration <= Milliseconds(diff))
                {
                    Unsummon();
                    return;
                }
                _summonDuration -= Milliseconds(diff);
            }
            break;
        case TEMPSUMMON_CORPSE_DESPAWN: // Summon despawns on death
            if (m_deathState == CORPSE)
            {
                Unsummon();
                return;
            }
            break;
        case TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN:
            if (m_deathState == CORPSE)
            {
                Unsummon();
                return;
            }

            if (!IsInCombat())
            {
                if (_summonDuration <= Milliseconds(diff))
                {
                    Unsummon();
                    return;
                }
                _summonDuration -= Milliseconds(diff);
            }
            else if (_summonDuration != _originalSummonDuration)
                _summonDuration = _originalSummonDuration;
            break;
        case TEMPSUMMON_TIMED_OR_DEAD_DESPAWN:
            if (!IsInCombat() && IsAlive())
            {
                if (_summonDuration <= Milliseconds(diff))
                {
                    Unsummon();
                    return;
                }
                _summonDuration -= Milliseconds(diff);
            }
            else if (_summonDuration != _originalSummonDuration)
                _summonDuration = _originalSummonDuration;
            break;
        case TEMPSUMMON_DIE_UPON_EXPIRE:
            if (IsAlive() && _summonDuration <= Milliseconds(diff))
            {
                KillSelf();
                Unsummon(SummonExpirationCorpseDespawnTime);
                return;
            }
            _summonDuration -= Milliseconds(diff);
            break;
        default:
            TC_LOG_ERROR("entities.unit", "TempoarySummon::Update: Summon (entry: %u) uses an invalid TempSummonType (%u). Unsummoning it.", GetEntry(), _summonType);
            Unsummon();
            break;
    }
}

void NewTempoarySummon::HandlePreSummonActions(uint8 creatureLevel)
{
    if (_summonProperties)
    {
        if (_summonProperties->Faction != 0)
            SetFaction(_summonProperties->Faction);

        if (!_summonProperties->GetFlags().HasFlag(SummonPropertiesFlags::UseCreatureLevel) && creatureLevel > 0)
            SetLevel(creatureLevel);

        Unit* summoner = GetSummoner();

        if (summoner && summoner->IsPlayer())
        {
            switch (SummonPropertiesSlot(_summonProperties->Slot))
            {
                case SummonPropertiesSlot::Totem1:
                case SummonPropertiesSlot::Totem2:
                case SummonPropertiesSlot::Totem3:
                case SummonPropertiesSlot::Totem4:
                {
                    // SMSG_TOTEM_CREATED must be sent to the client before adding the summon to world and destroying other totems
                    WorldPackets::Totem::TotemCreated totemCreated;
                    totemCreated.Duration = int32(_summonDuration.count());
                    totemCreated.Slot = _summonProperties->Slot - AsUnderlyingType(SummonPropertiesSlot::Totem1);
                    totemCreated.SpellID = GetUInt32Value(UNIT_CREATED_BY_SPELL);
                    totemCreated.Totem = GetGUID();
                    summoner->ToPlayer()->SendDirectMessage(totemCreated.Write());

                    // There are some creatures which also go into totem slot but are no real totems. In this case we do not want to override the display Id
                    if (uint32 totemModel = summoner->GetModelForTotem(PlayerTotemType(_summonProperties->ID)))
                        SetDisplayId(totemModel);
                    break;
                }
                default:
                    break;
            }
        }
    }
}

void NewTempoarySummon::HandlePostSummonActions()
{
    if (Unit* summoner = GetSummoner())
    {
        if (summoner->IsCreature() && summoner->IsAIEnabled())
            if (CreatureAI* ai = summoner->ToCreature()->AI())
                ai->JustSummoned(this);

        if (IsAIEnabled())
            AI()->IsSummonedBy(summoner);

        if (_summonProperties)
        {
            if (_summonProperties->GetFlags().HasFlag(SummonPropertiesFlags::AttackSummoner))
                EngageWithTarget(summoner);

            if (_summonProperties->GetFlags().HasFlag(SummonPropertiesFlags::HelpWhenSummonedInCombat))
                if (summoner->IsInCombat())
                    if (Unit* victim = summoner->GetThreatManager().GetCurrentVictim())
                        EngageWithTarget(victim);
        }
    }
}

void NewTempoarySummon::Unsummon(Milliseconds timeUntilDespawn /*= 0ms*/)
{
    if (timeUntilDespawn > 0ms)
    {
        m_Events.AddEventAtOffset([&]() { Unsummon(); }, timeUntilDespawn);
        return;
    }

    if (Unit* summoner = GetSummoner())
        if (summoner->IsCreature() && summoner->IsAIEnabled())
            if (CreatureAI* ai = summoner->ToCreature()->AI())
                ai->SummonedCreatureDespawn(this);

    AddObjectToRemoveList();
}

Unit* NewTempoarySummon::GetSummoner() const
{
    if (_internalSummonerGUID.IsEmpty())
        return nullptr;

    return ObjectAccessor::GetUnit(*this, _internalSummonerGUID);
}

bool NewTempoarySummon::ShouldDespawnOnSummonerDeath() const
{
    if (!_summonProperties)
        return false;

    // All summons which have SummonPropertiesFlags::DespawnOnSummonerDeath will be unsummoned
    if (_summonProperties->GetFlags().HasFlag(SummonPropertiesFlags::DespawnOnSummonerDeath))
        return true;

    // All summons which have been registered in a slot will be unsummoned
    return SummonPropertiesSlot(_summonProperties->Slot) != SummonPropertiesSlot::None;
}

bool NewTempoarySummon::ShouldDieUponExpiration() const
{
    // This is for maintaining old scripts compatability
    if (!_summonProperties)
        return false;

    if (_summonProperties->GetFlags().HasFlag(SummonPropertiesFlags::DespawnWhenExpired))
        return false;

    switch (SummonPropertiesSlot(_summonProperties->Slot))
    {
        case SummonPropertiesSlot::None:
        case SummonPropertiesSlot::Quest:
            return true;
        default:
            // This here is a very experimental case. So far we know that player totems should despawn immediately. However, in how far does this apply to all totem slot summons?
            return false;
    }

    return true;
}
