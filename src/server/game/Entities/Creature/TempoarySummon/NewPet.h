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

#ifndef NewPet_h__
#define NewPet_h__

#include "NewGuardian.h"

class TC_GAME_API NewPet : public NewGuardian
{
public:
    NewPet(SummonPropertiesEntry const* properties, Unit* owner, bool isWorldObject, bool isClassPet);

    void AddToWorld() override;
    void RemoveFromWorld() override;

    void HandlePreSummonActions(uint8 creatureLevel) override;
    void HandlePostSummonActions() override;

    bool IsClassPet() const { return _isClassPet; }
private:
    bool _isClassPet;
};

#endif // NewPet_h__
