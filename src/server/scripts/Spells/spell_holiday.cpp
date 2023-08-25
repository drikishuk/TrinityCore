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

/*
 * Spells used in holidays/game events that do not fit any other category.
 * Ordered alphabetically using scriptname.
 * Scriptnames in this file should be prefixed with "spell_#holidayname_".
 */

#include "ScriptMgr.h"
#include "CellImpl.h"
#include "CreatureAIImpl.h"
#include "GridNotifiersImpl.h"
#include "Player.h"
#include "ScriptedCreature.h"
#include "SpellAuraEffects.h"
#include "SpellScript.h"
#include "TemporarySummon.h"
#include "Vehicle.h"
#include "World.h"

enum RibbonPoleData
{
    SPELL_HAS_FULL_MIDSUMMER_SET        = 58933,
    SPELL_BURNING_HOT_POLE_DANCE        = 58934,
    SPELL_RIBBON_DANCE_COSMETIC         = 29726,
    SPELL_RIBBON_DANCE                  = 29175,
    GO_RIBBON_POLE                      = 181605,
};

class spell_gen_ribbon_pole_dancer_check : public SpellScriptLoader
{
    public:
        spell_gen_ribbon_pole_dancer_check() : SpellScriptLoader("spell_gen_ribbon_pole_dancer_check") { }

        class spell_gen_ribbon_pole_dancer_check_AuraScript : public AuraScript
        {
            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                return ValidateSpellInfo(
                {
                    SPELL_RIBBON_DANCE_COSMETIC,
                    SPELL_BURNING_HOT_POLE_DANCE,
                    SPELL_HAS_FULL_MIDSUMMER_SET,
                    SPELL_RIBBON_DANCE
                });
            }

            void PeriodicTick(AuraEffect const* /*aurEff*/)
            {
                Unit* target = GetTarget();

                // check if aura needs to be removed
                if (!target->FindNearestGameObject(GO_RIBBON_POLE, 8.0f) || !target->HasUnitState(UNIT_STATE_CASTING))
                {
                    target->InterruptNonMeleeSpells(false);
                    target->RemoveAurasDueToSpell(GetId());
                    target->RemoveAura(SPELL_RIBBON_DANCE_COSMETIC);
                    return;
                }

                // set xp buff duration
                if (Aura* aur = target->GetAura(SPELL_RIBBON_DANCE))
                {
                    aur->SetMaxDuration(std::min(3600000, aur->GetMaxDuration() + 180000));
                    aur->RefreshDuration();

                    // reward achievement criteria
                    if (aur->GetMaxDuration() == 3600000 && target->HasAura(SPELL_HAS_FULL_MIDSUMMER_SET))
                        target->CastSpell(target, SPELL_BURNING_HOT_POLE_DANCE, true);
                }
                else
                    target->AddAura(SPELL_RIBBON_DANCE, target);
            }

            void Register() override
            {
                OnEffectPeriodic.Register(&spell_gen_ribbon_pole_dancer_check_AuraScript::PeriodicTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_gen_ribbon_pole_dancer_check_AuraScript();
        }
};

enum DarkmoonDeathmatch
{
    AREA_ID_DARKMOON_DEATHMATCH = 5877,

    SPELL_ENTER_DEATHMATCH_1    = 108919,
    SPELL_ENTER_DEATHMATCH_2    = 113212,
    SPELL_ENTER_DEATHMATCH_3    = 113213,
    SPELL_ENTER_DEATHMATCH_4    = 113216,
    SPELL_ENTER_DEATHMATCH_5    = 113219,
    SPELL_ENTER_DEATHMATCH_6    = 113224,
    SPELL_ENTER_DEATHMATCH_7    = 113227,
    SPELL_ENTER_DEATHMATCH_8    = 113228,
    SPELL_EXIT_DEATHMATCH       = 108923,

};

uint32 enterDeathMatchSpells[] =
{
    SPELL_ENTER_DEATHMATCH_1,
    SPELL_ENTER_DEATHMATCH_2,
    SPELL_ENTER_DEATHMATCH_3,
    SPELL_ENTER_DEATHMATCH_4,
    SPELL_ENTER_DEATHMATCH_5,
    SPELL_ENTER_DEATHMATCH_6,
    SPELL_ENTER_DEATHMATCH_7,
    SPELL_ENTER_DEATHMATCH_8
};

class spell_darkmoon_island_deathmatch : public SpellScriptLoader
{
public:
    spell_darkmoon_island_deathmatch() : SpellScriptLoader("spell_darkmoon_island_deathmatch") { }

    class spell_darkmoon_island_deathmatch_SpellScript : public SpellScript
    {
        bool Validate(SpellInfo const* /*spell*/) override
        {
            return ValidateSpellInfo(
                {
                    SPELL_ENTER_DEATHMATCH_1,
                    SPELL_ENTER_DEATHMATCH_2,
                    SPELL_ENTER_DEATHMATCH_3,
                    SPELL_ENTER_DEATHMATCH_4,
                    SPELL_ENTER_DEATHMATCH_5,
                    SPELL_ENTER_DEATHMATCH_6,
                    SPELL_ENTER_DEATHMATCH_7,
                    SPELL_ENTER_DEATHMATCH_8,
                    SPELL_EXIT_DEATHMATCH
                });
        }

        void HandleScript(SpellEffIndex /*effIndex*/)
        {
            Unit* target = GetHitUnit();
            if (target->GetAreaId() == AREA_ID_DARKMOON_DEATHMATCH)
                target->CastSpell(target, SPELL_EXIT_DEATHMATCH);
            else
            {
                uint8 i = urand(0, 7);
                target->CastSpell(target, enterDeathMatchSpells[i]);
            }
        }

        void Register() override
        {
            OnEffectHitTarget.Register(&spell_darkmoon_island_deathmatch_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_darkmoon_island_deathmatch_SpellScript();
    }
};

enum RingToss
{
    SPELL_RING_TOSS_HIT     = 101699,
    SPELL_RING_TOSS_MISS    = 101698,
    SPELL_RING_TOSS_AURA    = 102058
};

class spell_darkmoon_island_ring_toss : public SpellScriptLoader
{
public:
    spell_darkmoon_island_ring_toss() : SpellScriptLoader("spell_darkmoon_island_ring_toss") { }

    class spell_darkmoon_island_ring_toss_SpellScript : public SpellScript
    {
        bool Validate(SpellInfo const* /*spell*/) override
        {
            return ValidateSpellInfo(
                {
                    SPELL_RING_TOSS_HIT,
                    SPELL_RING_TOSS_MISS,
                    SPELL_RING_TOSS_AURA
                });
        }

        bool Load() override
        {
            _hasHit = false;
            return true;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            Unit* target = GetHitUnit();
            Position destination = GetExplTargetDest()->GetPosition();

            if (target->GetExactDist2d(destination) <= 1.0f)
                caster->CastSpell(target, SPELL_RING_TOSS_HIT, true);
            else
                caster->CastSpell({ destination.GetPositionX(), destination.GetPositionY(), destination.GetPositionZ() }, SPELL_RING_TOSS_MISS, true);
            _hasHit = true;
        }

        void HandleAfterCast()
        {
            Unit* caster = GetCaster();

            if (!_hasHit)
            {
                Position destination = GetExplTargetDest()->GetPosition();
                caster->CastSpell({ destination.GetPositionX(), destination.GetPositionY(), destination.GetPositionZ() }, SPELL_RING_TOSS_MISS, true);
            }

            if (!caster->GetPower(POWER_ALTERNATE_POWER))
                caster->RemoveAurasDueToSpell(SPELL_RING_TOSS_AURA);
        }

        void Register() override
        {
            OnEffectHitTarget.Register(&spell_darkmoon_island_ring_toss_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            AfterCast.Register(&spell_darkmoon_island_ring_toss_SpellScript::HandleAfterCast);
        }

    private:
        bool _hasHit;
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_darkmoon_island_ring_toss_SpellScript();
    }
};

enum WhackAGnoll
{
    // Creature
    NPC_DARMOON_FAIRE_WHACK_A_GNOLL_BUNNY               = 58570,
    NPC_MOLA                                            = 54601,

    // Spellls
    SPELL_WHACK_SUMMON_NORMAL                           = 102036,
    SPELL_WHACK_SUMMON_BABY                             = 102043,
    SPELL_WHACK_SUMMON_BONUS                            = 102044,
    SPELL_GNOLL_AURA_OKAY_TO_HIT                        = 101996,
    SPELL_WHACK_A_GNOLL_ACTION_BAR_REMOVED              = 102137,
    SPELL_WHACK_A_GNOLL_ACTION_BAR                      = 110230,
    SPELL_WHACK_TRIGGERED                               = 102022,
    SPELL_WHACK_ROOT                                    = 101829,
    SPELL_STAY_OUT_DARKMOON_FAIRE_WHACK_A_GNOLL_BUNNY   = 110966,
    SPELL_STAY_OUT_MOLA                                 = 109977
};

class spell_darkmoon_island_whack_summon_aura : public SpellScriptLoader
{
public:
    spell_darkmoon_island_whack_summon_aura() : SpellScriptLoader("spell_darkmoon_island_whack_summon_aura") { }

    class spell_darkmoon_island_whack_summon_aura_AuraScript : public AuraScript
    {
        bool Validate(SpellInfo const* /*spell*/) override
        {
            return ValidateSpellInfo({ SPELL_GNOLL_AURA_OKAY_TO_HIT });
        }

        void OnPeriodic(AuraEffect const* aurEff)
        {
            GetTarget()->CastSpell(GetTarget(), SPELL_GNOLL_AURA_OKAY_TO_HIT, aurEff);
        }

        void Register() override
        {
            OnEffectPeriodic.Register(&spell_darkmoon_island_whack_summon_aura_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_darkmoon_island_whack_summon_aura_AuraScript();
    }
};

class GnollHolderTargetSelector
{
    public:
        GnollHolderTargetSelector(Unit* caster) : _caster(caster) { }

        bool operator() (WorldObject* target)
        {
            if (target->GetTypeId() != TYPEID_UNIT)
                return true;

            if (TempSummon* summon = target->ToUnit()->ToTempSummon())
                if (summon->GetSummoner() == _caster)
                    return false;

            return true;
        }

    private:
        Unit* _caster;
};

class spell_darkmoon_island_gnoll_aura_okay_to_hit : public SpellScriptLoader
{
public:
    spell_darkmoon_island_gnoll_aura_okay_to_hit() : SpellScriptLoader("spell_darkmoon_island_gnoll_aura_okay_to_hit") { }

    class spell_darkmoon_island_gnoll_aura_okay_to_hit_SpellScript : public SpellScript
    {
        bool Validate(SpellInfo const* /*spell*/) override
        {
            return ValidateSpellInfo(
                {
                    SPELL_WHACK_SUMMON_NORMAL,
                    SPELL_WHACK_SUMMON_BABY,
                    SPELL_WHACK_SUMMON_BONUS
                });
        }

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            targets.remove_if(GnollHolderTargetSelector(GetCaster()));

            if (targets.size())
                Trinity::Containers::RandomResize(targets, 1);

        }

        void HandleSummon(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            uint32 summonSpellId = SPELL_WHACK_SUMMON_NORMAL;
            if (roll_chance_i(50))
                summonSpellId = RAND(SPELL_WHACK_SUMMON_BABY, SPELL_WHACK_SUMMON_BONUS);

            caster->CastSpell(GetHitUnit(), summonSpellId, true);
        }

        void Register() override
        {
            OnObjectAreaTargetSelect.Register(&spell_darkmoon_island_gnoll_aura_okay_to_hit_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENTRY);
            OnEffectHitTarget.Register(&spell_darkmoon_island_gnoll_aura_okay_to_hit_SpellScript::HandleSummon, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_darkmoon_island_gnoll_aura_okay_to_hit_SpellScript();
    }
};

class spell_darkmoon_island_whack_dummy : public SpellScriptLoader
{
public:
    spell_darkmoon_island_whack_dummy() : SpellScriptLoader("spell_darkmoon_island_whack_dummy") { }

    class spell_darkmoon_island_whack_dummy_SpellScript : public SpellScript
    {
        bool Validate(SpellInfo const* /*spell*/) override
        {
            return ValidateSpellInfo(
                {
                    SPELL_WHACK_TRIGGERED,
                    SPELL_WHACK_ROOT,
                });
        }

        void HandleDummy()
        {
            Unit* caster = GetCaster();
            caster->CastSpell(caster, SPELL_WHACK_ROOT, true);
            caster->CastSpell(caster, SPELL_WHACK_TRIGGERED);
        }

        void Register() override
        {
            AfterCast.Register(&spell_darkmoon_island_whack_dummy_SpellScript::HandleDummy);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_darkmoon_island_whack_dummy_SpellScript();
    }
};

class spell_darkmoon_island_whack : public SpellScriptLoader
{
public:
    spell_darkmoon_island_whack() : SpellScriptLoader("spell_darkmoon_island_whack") { }

    class spell_darkmoon_island_whack_SpellScript : public SpellScript
    {
        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            targets.remove_if(GnollHolderTargetSelector(GetCaster()));
        }

        void Register() override
        {
            OnObjectAreaTargetSelect.Register(&spell_darkmoon_island_whack_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_CONE_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_darkmoon_island_whack_SpellScript();
    }
};

class spell_darkmoon_island_whack_a_gnoll : public SpellScriptLoader
{
public:
    spell_darkmoon_island_whack_a_gnoll() : SpellScriptLoader("spell_darkmoon_island_whack_a_gnoll") { }

    class spell_darkmoon_island_whack_a_gnoll_AuraScript : public AuraScript
    {
        bool Validate(SpellInfo const* /*spell*/) override
        {
            return ValidateSpellInfo(
                {
                    SPELL_WHACK_A_GNOLL_ACTION_BAR,
                    SPELL_WHACK_A_GNOLL_ACTION_BAR_REMOVED,
                    SPELL_STAY_OUT_DARKMOON_FAIRE_WHACK_A_GNOLL_BUNNY,
                    SPELL_STAY_OUT_MOLA
                });
        }

        void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* target = GetTarget();
            target->RemoveAurasDueToSpell(GetSpellInfo()->Effects[EFFECT_1].TriggerSpell);
            target->RemoveAurasDueToSpell(SPELL_WHACK_A_GNOLL_ACTION_BAR);
            target->CastSpell(target, SPELL_WHACK_A_GNOLL_ACTION_BAR_REMOVED, true);

            if (Creature* bunny = target->FindNearestCreature(NPC_DARMOON_FAIRE_WHACK_A_GNOLL_BUNNY, 20.f))
                bunny->CastSpell(target, SPELL_STAY_OUT_DARKMOON_FAIRE_WHACK_A_GNOLL_BUNNY);

            if (Creature* mola = target->FindNearestCreature(NPC_MOLA, 50.f))
                mola->CastSpell(target, SPELL_STAY_OUT_MOLA);
        }

        void Register() override
        {
            AfterEffectRemove.Register(&spell_darkmoon_island_whack_a_gnoll_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_OVERRIDE_SPELLS, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_darkmoon_island_whack_a_gnoll_AuraScript();
    }
};

class spell_darkmoon_island_whack_a_gnoll_player_action_bar_removed : public SpellScriptLoader
{
public:
    spell_darkmoon_island_whack_a_gnoll_player_action_bar_removed() : SpellScriptLoader("spell_darkmoon_island_whack_a_gnoll_player_action_bar_removed") { }

    class spell_darkmoon_island_whack_a_gnoll_player_action_bar_removed_SpellScript : public SpellScript
    {
        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            targets.remove_if(GnollHolderTargetSelector(GetCaster()));
        }

        void DespawnUnits(SpellEffIndex /*effIndex*/)
        {
            if (Creature* creature = GetHitCreature())
                creature->DespawnOrUnsummon();
        }

        void Register() override
        {
            OnObjectAreaTargetSelect.Register(&spell_darkmoon_island_whack_a_gnoll_player_action_bar_removed_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENTRY);
            OnObjectAreaTargetSelect.Register(&spell_darkmoon_island_whack_a_gnoll_player_action_bar_removed_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_DEST_AREA_ENTRY);
            OnEffectHitTarget.Register(&spell_darkmoon_island_whack_a_gnoll_player_action_bar_removed_SpellScript::DespawnUnits, EFFECT_0, SPELL_EFFECT_DUMMY);
            OnEffectHitTarget.Register(&spell_darkmoon_island_whack_a_gnoll_player_action_bar_removed_SpellScript::DespawnUnits, EFFECT_1, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_darkmoon_island_whack_a_gnoll_player_action_bar_removed_SpellScript();
    }
};

void AddSC_holiday_spell_scripts()
{
    // Midsummer Fire Festival
    new spell_gen_ribbon_pole_dancer_check();
    // Darkmoon Island
    new spell_darkmoon_island_deathmatch();
    new spell_darkmoon_island_ring_toss();
    new spell_darkmoon_island_whack_summon_aura();
    new spell_darkmoon_island_gnoll_aura_okay_to_hit();
    new spell_darkmoon_island_whack_dummy();
    new spell_darkmoon_island_whack();
    new spell_darkmoon_island_whack_a_gnoll();
    new spell_darkmoon_island_whack_a_gnoll_player_action_bar_removed();
}
