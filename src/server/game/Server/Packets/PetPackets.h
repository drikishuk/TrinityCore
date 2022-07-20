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

#ifndef PetPackets_h__
#define PetPackets_h__

#include "Packet.h"
#include "ObjectGuid.h"
#include "Position.h"

namespace WorldPackets
{
    namespace Pet
    {
        class PetDismissSound final : public ServerPacket
        {
        public:
            PetDismissSound() : ServerPacket(SMSG_PET_DISMISS_SOUND, 4 + 4 + 4 + 4) { }

            WorldPacket const* Write() override;

            int32 ModelID = 0;
            TaggedPosition<Position::XYZ> ModelPosition;
        };

        class PetGuids final : public ServerPacket
        {
        public:
            PetGuids() : ServerPacket(SMSG_PET_GUIDS, 1) { }

            WorldPacket const* Write() override;

            std::vector<ObjectGuid> PetGUIDs;
        };

        class SPetMode final : public ServerPacket
        {
        public:
            SPetMode() : ServerPacket(SMSG_PET_MODE, 8 + 4) { }

            WorldPacket const* Write() override;

            ObjectGuid PetGUID;
            uint32 PetMode = 0;
        };

        class PetActionFeedback final : public ServerPacket
        {
        public:
            PetActionFeedback() : ServerPacket(SMSG_PET_ACTION_FEEDBACK, 1) { }

            WorldPacket const* Write() override;

            int32 SpellID = 0;
            uint8 Response = 0;
        };

        class PetActionSound final : public ServerPacket
        {
        public:
            PetActionSound() : ServerPacket(SMSG_PET_ACTION_SOUND, 8 + 4) { }

            WorldPacket const* Write() override;

            ObjectGuid UnitGUID;
            int32 Action = 0;
        };

        class PetAdded final : public ServerPacket
        {
        public:
            PetAdded() : ServerPacket(SMSG_PET_ADDED, 4 + 4 + 1 + 4 + 4) { }

            WorldPacket const* Write() override;

            std::string Name;
            int32 CreatureID = 0;
            int32 Level = 0;
            int32 PetSlot = 0;
            uint32 PetNumber = 0;
            uint8 Flags = 0;
        };

        struct PetSpellCooldown
        {
            int32 SpellID = 0;
            int32 Duration = 0;
            int32 CategoryDuration = 0;
            uint16 Category = 0;
        };

        struct PetSpells
        {
            ObjectGuid PetGUID;
            uint16 CreatureFamily = 0;
            uint16 Specialization = 0;
            uint32 TimeLimit = 0;
            uint32 PetModeAndOrders = 0;
            std::vector<uint32> Actions;
            std::vector<PetSpellCooldown> Cooldowns;
            std::array<uint32, 10> ActionButtons = { };
        };

        class PetSpellsMessage final : public ServerPacket
        {
        public:
            PetSpellsMessage() : ServerPacket(SMSG_PET_SPELLS) { }

            WorldPacket const* Write() override;

            PetSpells Spells;
        };

        class PetAction final : public ClientPacket
        {
        public:
            PetAction(WorldPacket&& packet) : ClientPacket(CMSG_PET_ACTION, std::move(packet)) { }

            void Read() override;

            ObjectGuid PetGUID;
            ObjectGuid TargetGUID;
            TaggedPosition<Position::XYZ> ActionPosition;
            uint32 Action = 0;
        };
    }
}

#endif // PetPackets_h__
