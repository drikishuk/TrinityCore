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

#ifndef AchievementPackets_h__
#define AchievementPackets_h__

#include "PacketsBase.h"

namespace Battlenet
{
    namespace Achievement
    {
        enum Opcode
        {
            CMSG_LISTEN_REQUEST             = 0x0,  // 'Lstn' Not implemented
            CMSG_CRITERIA_FLUSH_REQUEST     = 0x3,  // 'CrFl' Not implemented
            CMSG_CHANGE_TROPHY_CASE_REQUEST = 0x5,  // 'Rph' Not implemented

            SMSG_DATA                       = 0x2,  // 'Data' Not implemented
            SMSG_CRITERIA_FLUSH_RESPONSE    = 0x3,  // 'CrFl' Not implemented
            SMSG_ACHIEVEMENT_HANDLE_UPDATE  = 0x4,  // 'Updt' Not implemented
            SMSG_CHANGE_TROPHY_CASE_RESULT  = 0x6   // 'TrpR' Not implemented
        };
    }
}

#endif // AchievementPackets_h__
