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

#ifndef TempoarySummon_h__
#define TempoarySummon_h__

#include "Creature.h"

struct SummonPropertiesEntry;

// This time sepcifies when a summon will despawn after dying from expiration
static constexpr Milliseconds SummonExpirationCorpseDespawnTime = 15s;

class TC_GAME_API NewTempoarySummon : public Creature
{
public:
    explicit NewTempoarySummon(SummonPropertiesEntry const* properties, Unit* summoner, bool isWorldObject);
    virtual ~NewTempoarySummon() { }

    // Overriden methods of Creature class
    void AddToWorld() override;
    void RemoveFromWorld() override;
    void Update(uint32 diff) override;

    virtual void HandlePreSummonActions(uint8 creatureLevel);
    virtual void HandlePostSummonActions();

    void SetSummonDuration(Milliseconds duration) { _summonDuration = duration; _originalSummonDuration = duration; }
    void SetSummonType(TempSummonType type) { _summonType = type; }
    uint32 GetRemainingSummonDuration() const { return _summonDuration.count(); }
    void Unsummon(Milliseconds timeUntilDespawn = 0ms);

    Unit* GetSummoner() const;
    // Returns the internally stored ObjectGuid of the summoner. Unrelated to UNIT_FIELD_SUMMONEDBY
    ObjectGuid GetInternalSummonerGUID() const { return _internalSummonerGUID; }
    bool ShouldDespawnOnSummonerDeath() const;
    bool ShouldDieUponExpiration() const;

protected:
    SummonPropertiesEntry const* _summonProperties;
    ObjectGuid _internalSummonerGUID;
    Milliseconds _summonDuration;
    Milliseconds _originalSummonDuration;
    TempSummonType _summonType;
};

#endif // PhasingHandler_h__
