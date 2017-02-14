/*
* Copyright (C) 2008-2017 TrinityCore <http://www.trinitycore.org/>
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

#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "ScriptMgr.h"
#include "GridNotifiers.h"
#include "SpellScript.h"
#include "Unit.h"

enum WarriorSpells
{
	SPELL_WARRIOR_STORM_BOLT		= 107570,
	SPELL_WARRIOR_STORM_BOLT_STUN	= 132169,
	SPELL_WARRIOR_SHOCKWAVE			= 46968,
	SPELL_WARRIOR_SHOCKWAVE_STUN	= 132168,
};

// 107570 - Storm Bolt
class spell_warr_storm_bolt : public SpellScriptLoader
{
public:
	spell_warr_storm_bolt() : SpellScriptLoader("spell_warr_storm_bolt") { }

	class spell_warr_storm_bolt_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_warr_storm_bolt_SpellScript);

		bool Validate(SpellInfo const* /*spellInfo*/) override
		{
			return ValidateSpellInfo
			({
				SPELL_WARRIOR_STORM_BOLT,
				SPELL_WARRIOR_STORM_BOLT_STUN
			});
		}

		void HandleDamage(SpellEffIndex /*effIndex*/)
		{
			Unit* caster = GetCaster();

			if (Unit* target = GetHitUnit())
				caster->CastSpell(target, SPELL_WARRIOR_STORM_BOLT_STUN, true);
		}

		void Register() override
		{
			OnEffectHitTarget += SpellEffectFn(spell_warr_storm_bolt_SpellScript::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
		}
	};

	SpellScript* GetSpellScript() const override
	{
		return new spell_warr_storm_bolt_SpellScript();
	}
};

// 46968 - Shockwave
class spell_warr_shockwave : public SpellScriptLoader
{
public:
	spell_warr_shockwave() : SpellScriptLoader("spell_warr_shockwave") { }

	class spell_warr_shockwave_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_warr_shockwave_SpellScript);

		bool Validate(SpellInfo const* /*spellInfo*/) override
		{
			return ValidateSpellInfo
			({
				SPELL_WARRIOR_SHOCKWAVE,
				SPELL_WARRIOR_SHOCKWAVE_STUN
			});
		}

		bool Load() override
		{
			return GetCaster()->GetTypeId() == TYPEID_PLAYER;
		}

		void CountTargets(std::list<WorldObject*>& targetList)
		{
			_targetCount = targetList.size();
		}

		void HandleDamage(SpellEffIndex /*effIndex*/)
		{
			Unit* caster = GetCaster();
			Unit* target = GetHitUnit();

			if (target)
			{
				caster->CastSpell(target, SPELL_WARRIOR_SHOCKWAVE_STUN, true);
			}
		}

		// Cooldown reduced by 20 sec if it strikes at least 3 targets.
		void HandleAfterCast()
		{
			if (_targetCount >= uint32(GetSpellInfo()->GetEffect(EFFECT_0)->CalcValue()))
			{
				GetCaster()->ToPlayer()->GetSpellHistory()->ModifyCooldown(SPELL_WARRIOR_SHOCKWAVE, -(GetSpellInfo()->GetEffect(EFFECT_3)->CalcValue() * IN_MILLISECONDS));
			}
		}

		void Register() override
		{
			OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_warr_shockwave_SpellScript::CountTargets, EFFECT_0, TARGET_UNIT_CONE_ENEMY_104);
			OnEffectHitTarget += SpellEffectFn(spell_warr_shockwave_SpellScript::HandleDamage, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
			AfterCast += SpellCastFn(spell_warr_shockwave_SpellScript::HandleAfterCast);
		}

	private:
		uint32 _targetCount = 0;
	};

	SpellScript* GetSpellScript() const override
	{
		return new spell_warr_shockwave_SpellScript();
	}
};
void AddSC_warrior_spell()
{
	new spell_warr_storm_bolt();
	new spell_warr_shockwave();
}