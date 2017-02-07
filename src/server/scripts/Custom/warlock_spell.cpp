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

class spell_warl_shadowburn_damage : public SpellScriptLoader
{
public:
	spell_warl_shadowburn_damage() : SpellScriptLoader("spell_warl_shadowburn_damage") { }

	class spell_warl_shadowburn_damage_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_warl_shadowburn_damage_SpellScript);

		void HandleOnHit()
		{
			if (Unit* caster = GetCaster())
			{
				int32 damage = GetHitDamage();

				// Mastery: Emberstorm
				if (AuraEffect* aurEff = caster->GetDummyAuraEffect(SPELLFAMILY_WARLOCK, 2129, EFFECT_0))
					AddPct(damage, aurEff->GetAmount());

				SetHitDamage(damage);
			}
		}

		void Register() override
		{
			OnHit += SpellHitFn(spell_warl_shadowburn_damage_SpellScript::HandleOnHit);
		}
	};

	SpellScript* GetSpellScript() const override
	{
		return new spell_warl_shadowburn_damage_SpellScript();
	}
};

void AddSC_warlock_spell()
{
	new spell_warl_shadowburn_damage();
};