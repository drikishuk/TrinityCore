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

#include "ScriptMgr.h"
#include "GameObject.h"
#include "GridNotifiers.h"
#include "MotionMaster.h"
#include "Player.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "ScriptedGossip.h"
#include "SpellInfo.h"

/*######
## npc_clintar_spirit
######*/

struct Waypoint
{
    float X;
    float Y;
    float Z;
    float O;
    uint32 waitTime;
};

Waypoint const Clintar_spirit_WP[41] =
{
    //pos_x   pos_y    pos_z    orien waitTime
   {7465.28f, -3115.46f, 439.327f, 0.83f, 4000},
   {7476.49f, -3101,     443.457f, 0.89f, 0},
   {7486.57f, -3085.59f, 439.478f, 1.07f, 0},
   {7472.19f, -3085.06f, 443.142f, 3.07f, 0},
   {7456.92f, -3085.91f, 438.862f, 3.24f, 0},
   {7446.68f, -3083.43f, 438.245f, 2.40f, 0},
   {7446.17f, -3080.21f, 439.826f, 1.10f, 6000},
   {7452.41f, -3085.8f,  438.984f, 5.78f, 0},
   {7469.11f, -3084.94f, 443.048f, 6.25f, 0},
   {7483.79f, -3085.44f, 439.607f, 6.25f, 0},
   {7491.14f, -3090.96f, 439.983f, 5.44f, 0},
   {7497.62f, -3098.22f, 436.854f, 5.44f, 0},
   {7498.72f, -3113.41f, 434.596f, 4.84f, 0},
   {7500.06f, -3122.51f, 434.749f, 5.17f, 0},
   {7504.96f, -3131.53f, 434.475f, 4.74f, 0},
   {7504.31f, -3133.53f, 435.693f, 3.84f, 6000},
   {7504.55f, -3133.27f, 435.476f, 0.68f, 15000},
   {7501.99f, -3126.01f, 434.93f,  1.83f, 0},
   {7490.76f, -3114.97f, 434.431f, 2.51f, 0},
   {7479.64f, -3105.51f, 431.123f, 1.83f, 0},
   {7474.63f, -3086.59f, 428.994f, 1.83f, 2000},
   {7472.96f, -3074.18f, 427.566f, 1.57f, 0},
   {7472.25f, -3063,     428.268f, 1.55f, 0},
   {7473.46f, -3054.22f, 427.588f, 0.36f, 0},
   {7475.08f, -3053.6f,  428.653f, 0.36f, 6000},
   {7474.66f, -3053.56f, 428.433f, 3.19f, 4000},
   {7471.81f, -3058.84f, 427.073f, 4.29f, 0},
   {7472.16f, -3064.91f, 427.772f, 4.95f, 0},
   {7471.56f, -3085.36f, 428.924f, 4.72f, 0},
   {7473.56f, -3093.48f, 429.294f, 5.04f, 0},
   {7478.94f, -3104.29f, 430.638f, 5.23f, 0},
   {7484.46f, -3109.61f, 432.769f, 5.79f, 0},
   {7490.23f, -3111.08f, 434.431f, 0.02f, 0},
   {7496.29f, -3108,     434.783f, 1.15f, 0},
   {7497.46f, -3100.66f, 436.191f, 1.50f, 0},
   {7495.64f, -3093.39f, 438.349f, 2.10f, 0},
   {7492.44f, -3086.01f, 440.267f, 1.38f, 0},
   {7498.26f, -3076.44f, 440.808f, 0.71f, 0},
   {7506.4f,  -3067.35f, 443.64f,  0.77f, 0},
   {7518.37f, -3057.42f, 445.584f, 0.74f, 0},
   {7517.51f, -3056.3f,  444.568f, 2.49f, 4500}
};

Position const AspectRavenSummon = { 7472.96f, -3074.18f, 427.566f, 0.0f };
Position const ClintarSpiritSummon = { 7459.2275f, -3122.5632f, 438.9842f, 0.8594f };

enum ClintarSpirit
{
    ASPECT_RAVEN = 22915,

    // Texts for JustEngagedWith, the event and the end of the event are missing
    CLINTAR_SPIRIT_SAY_START = 0,
};

class npc_clintar_spirit : public CreatureScript
{
public:
    npc_clintar_spirit() : CreatureScript("npc_clintar_spirit") { }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_clintar_spiritAI(creature);
    }

    struct npc_clintar_spiritAI : public EscortAI
    {
    public:
        npc_clintar_spiritAI(Creature* creature) : EscortAI(creature)
        {
            Initialize();
            PlayerGUID.Clear();
        }

        void Initialize()
        {
            Step = 0;
            CurrWP = 0;
            EventTimer = 0;
            PlayerGUID.Clear();
            checkPlayerTimer = 1000;
            EventOnWait = false;
        }

        uint8 Step;
        uint32 CurrWP;
        uint32 EventTimer;
        uint32 checkPlayerTimer;

        ObjectGuid PlayerGUID;

        bool EventOnWait;

        void Reset() override
        {
            if (!PlayerGUID)
                Initialize();
        }

        void IsSummonedBy(Unit* /*summoner*/) override
        {
            std::list<Player*> playerOnQuestList;
            Trinity::AnyPlayerInObjectRangeCheck checker(me, 5.0f);
            Trinity::PlayerListSearcher searcher(me, playerOnQuestList, checker);
            Cell::VisitWorldObjects(me, searcher, 5.0f);
            for (std::list<Player*>::const_iterator itr = playerOnQuestList.begin(); itr != playerOnQuestList.end(); ++itr)
            {
                // Check if found player target has active quest
                if (Player* player = (*itr))
                {
                    if (player->GetQuestStatus(10965) == QUEST_STATUS_INCOMPLETE)
                    {
                        StartEvent(player);
                        break;
                    }
                }
                else
                    break;
            }
        }

        void JustDied(Unit* /*killer*/) override
        {
            if (!PlayerGUID)
                return;

            Player* player = ObjectAccessor::GetPlayer(*me, PlayerGUID);
            if (player && player->GetQuestStatus(10965) == QUEST_STATUS_INCOMPLETE)
            {
                player->FailQuest(10965);
                PlayerGUID.Clear();
                Reset();
            }
        }

        void EnterEvadeMode(EvadeReason why) override
        {
            Player* player = ObjectAccessor::GetPlayer(*me, PlayerGUID);
            if (player && player->IsInCombat() && player->getAttackerForHelper())
            {
                AttackStart(player->getAttackerForHelper());
                return;
            }
            EscortAI::EnterEvadeMode(why);
        }

        void StartEvent(Player* player)
        {
            if (player && player->GetQuestStatus(10965) == QUEST_STATUS_INCOMPLETE)
            {
                for (uint8 i = 0; i < 41; ++i)
                {
                    AddWaypoint(i, Clintar_spirit_WP[i].X, Clintar_spirit_WP[i].Y, Clintar_spirit_WP[i].Z, Clintar_spirit_WP[i].O, Clintar_spirit_WP[i].waitTime);
                }
                PlayerGUID = player->GetGUID();
                Start(true, false, PlayerGUID);
                me->SetDisplayFromModel(0);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            }
            return;
        }

        void UpdateAI(uint32 diff) override
        {
            EscortAI::UpdateAI(diff);

            if (!PlayerGUID)
            {
                me->setDeathState(JUST_DIED);
                return;
            }

            if (!me->IsInCombat() && !EventOnWait)
            {
                if (checkPlayerTimer <= diff)
                {
                    Player* player = ObjectAccessor::GetPlayer(*me, PlayerGUID);
                    if (player && player->IsInCombat() && player->getAttackerForHelper())
                        AttackStart(player->getAttackerForHelper());
                    checkPlayerTimer = 1000;
                }
                else checkPlayerTimer -= diff;
            }

            if (EventOnWait && EventTimer <= diff)
            {
                Player* player = ObjectAccessor::GetPlayer(*me, PlayerGUID);
                if (!player || player->GetQuestStatus(10965) == QUEST_STATUS_NONE)
                {
                    me->setDeathState(JUST_DIED);
                    return;
                }

                switch (CurrWP)
                {
                case 0:
                    switch (Step)
                    {
                    case 0:
                        Talk(CLINTAR_SPIRIT_SAY_START, player);
                        EventTimer = 8000;
                        Step = 1;
                        break;
                    case 1:
                        EventOnWait = false;
                        break;
                    }
                    break;
                case 6:
                    switch (Step)
                    {
                    case 0:
                        me->HandleEmoteCommand(EMOTE_STATE_USE_STANDING_NO_SHEATHE);
                        EventTimer = 5000;
                        Step = 1;
                        break;
                    case 1:
                        me->HandleEmoteCommand(EMOTE_ONESHOT_NONE);
                        // Needs text
                        EventOnWait = false;
                        break;
                    }
                    break;
                case 15:
                    switch (Step)
                    {
                    case 0:
                        me->HandleEmoteCommand(EMOTE_STATE_USE_STANDING_NO_SHEATHE);
                        EventTimer = 5000;
                        Step = 1;
                        break;
                    case 1:
                        me->HandleEmoteCommand(EMOTE_ONESHOT_NONE);
                        EventOnWait = false;
                        break;
                    }
                    break;
                case 16:
                    switch (Step)
                    {
                    case 0:
                        // Needs text
                        EventTimer = 15000;
                        Step = 1;
                        break;
                    case 1:
                        EventOnWait = false;
                        break;
                    }
                    break;
                case 20:
                    switch (Step)
                    {
                    case 0:
                        if (Creature* mob = me->SummonCreature(ASPECT_RAVEN, AspectRavenSummon, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 2s))
                        {
                            AddThreat(me, 10000.0f, mob);
                            mob->AI()->AttackStart(me);
                        }
                        EventTimer = 2000;
                        Step = 1;
                        break;
                    case 1:
                        EventOnWait = false;
                        break;
                    }
                    break;
                case 24:
                    switch (Step)
                    {
                    case 0:
                        me->HandleEmoteCommand(EMOTE_STATE_USE_STANDING_NO_SHEATHE);
                        EventTimer = 5000;
                        Step = 1;
                        break;
                    case 1:
                        me->HandleEmoteCommand(EMOTE_ONESHOT_NONE);
                        EventOnWait = false;
                        break;
                    }
                    break;
                case 25:
                    switch (Step)
                    {
                    case 0:
                        // Needs text
                        EventTimer = 4000;
                        Step = 1;
                        break;
                    case 1:
                        EventOnWait = false;
                        break;
                    }
                    break;
                case 40:
                    switch (Step)
                    {
                    case 0:
                        me->HandleEmoteCommand(EMOTE_ONESHOT_BOW);
                        // Needs text
                        player->CompleteQuest(10965);
                        EventTimer = 1500;
                        Step = 1;
                        break;
                    case 1:
                        me->HandleEmoteCommand(EMOTE_ONESHOT_NONE);
                        EventTimer = 3000;
                        Step = 2;
                        break;
                    case 2:
                        player->TalkedToCreature(me->GetEntry(), me->GetGUID());
                        PlayerGUID.Clear();
                        Reset();
                        me->setDeathState(JUST_DIED);
                        break;
                    }
                    break;
                default:
                    EventOnWait = false;
                    break;
                }

            }
            else if (EventOnWait) EventTimer -= diff;
        }

        void WaypointReached(uint32 waypointId, uint32 /*pathId*/) override
        {
            CurrWP = waypointId;
            EventTimer = 0;
            Step = 0;
            EventOnWait = true;
        }
    };

};

void AddSC_moonglade()
{
    new npc_clintar_spirit();
}
