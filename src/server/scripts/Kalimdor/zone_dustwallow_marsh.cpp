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
#include "Player.h"
#include "SpellInfo.h"
#include "SpellScript.h"

enum OozeZap
{
    SPELL_OOZE_CHANNEL_CREDIT = 42486
};

// 42489 - Cast Ooze Zap When Energized
class spell_ooze_zap : public SpellScriptLoader
{
public:
    spell_ooze_zap() : SpellScriptLoader("spell_ooze_zap") { }

    class spell_ooze_zap_SpellScript : public SpellScript
    {
        SpellCastResult CheckRequirement()
        {
            if (!GetCaster()->HasAura(GetSpellInfo()->Effects[EFFECT_1].CalcValue()))
                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW; // This is actually correct

            if (!GetExplTargetUnit())
                return SPELL_FAILED_BAD_TARGETS;

            return SPELL_CAST_OK;
        }

        void HandleDummy(SpellEffIndex effIndex)
        {
            PreventHitDefaultEffect(effIndex);
            if (GetHitUnit())
                GetCaster()->CastSpell(GetHitUnit(), uint32(GetEffectValue()), true);
        }

        void Register() override
        {
            OnEffectHitTarget.Register(&spell_ooze_zap_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            OnCheckCast.Register(&spell_ooze_zap_SpellScript::CheckRequirement);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_ooze_zap_SpellScript();
    }
};

// 42485 - End of Ooze Channel
class spell_ooze_zap_channel_end : public SpellScriptLoader
{
public:
    spell_ooze_zap_channel_end() : SpellScriptLoader("spell_ooze_zap_channel_end") { }

    class spell_ooze_zap_channel_end_SpellScript : public SpellScript
    {
        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return ValidateSpellInfo({ SPELL_OOZE_CHANNEL_CREDIT });
        }

        void HandleDummy(SpellEffIndex effIndex)
        {
            PreventHitDefaultEffect(effIndex);
            if (Player* player = GetCaster()->ToPlayer())
                player->CastSpell(player, SPELL_OOZE_CHANNEL_CREDIT, true);
            GetHitUnit()->KillSelf();
        }

        void Register() override
        {
            OnEffectHitTarget.Register(&spell_ooze_zap_channel_end_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_ooze_zap_channel_end_SpellScript();
    }
};

// 42492 - Cast Energized
class spell_energize_aoe : public SpellScriptLoader
{
public:
    spell_energize_aoe() : SpellScriptLoader("spell_energize_aoe") { }

    class spell_energize_aoe_SpellScript : public SpellScript
    {
        void FilterTargets(std::list<WorldObject*>& targets)
        {
            for (std::list<WorldObject*>::iterator itr = targets.begin(); itr != targets.end();)
            {
                if ((*itr)->GetTypeId() == TYPEID_PLAYER && (*itr)->ToPlayer()->GetQuestStatus(GetSpellInfo()->Effects[EFFECT_1].CalcValue()) == QUEST_STATUS_INCOMPLETE)
                    ++itr;
                else
                    targets.erase(itr++);
            }
            targets.push_back(GetCaster());
        }

        void HandleScript(SpellEffIndex effIndex)
        {
            PreventHitDefaultEffect(effIndex);
            GetCaster()->CastSpell(GetCaster(), uint32(GetEffectValue()), true);
        }

        void Register() override
        {
            OnEffectHitTarget.Register(&spell_energize_aoe_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            OnObjectAreaTargetSelect.Register(&spell_energize_aoe_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
            OnObjectAreaTargetSelect.Register(&spell_energize_aoe_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_energize_aoe_SpellScript();
    }
};

/*######
## Quest 11140: Recover the Cargo!
######*/

enum RecoverTheCargo
{
    SPELL_SUMMON_LOCKBOX = 42288,
    SPELL_SUMMON_BURROWER = 42289
};

// 42287 - Salvage Wreckage
class spell_dustwallow_marsh_salvage_wreckage : public SpellScriptLoader
{
public:
    spell_dustwallow_marsh_salvage_wreckage() : SpellScriptLoader("spell_dustwallow_marsh_salvage_wreckage") { }

    class spell_dustwallow_marsh_salvage_wreckage_SpellScript : public SpellScript
    {
        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return ValidateSpellInfo({ SPELL_SUMMON_LOCKBOX, SPELL_SUMMON_BURROWER });
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            GetCaster()->CastSpell(GetCaster(), roll_chance_i(50) ? SPELL_SUMMON_LOCKBOX : SPELL_SUMMON_BURROWER);
        }

        void Register() override
        {
            OnEffectHit.Register(&spell_dustwallow_marsh_salvage_wreckage_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_dustwallow_marsh_salvage_wreckage_SpellScript();
    }
};

void AddSC_dustwallow_marsh()
{
    new spell_ooze_zap();
    new spell_ooze_zap_channel_end();
    new spell_energize_aoe();
    new spell_dustwallow_marsh_salvage_wreckage();
}
