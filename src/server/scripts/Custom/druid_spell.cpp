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

// Spell 105737 Might of Ursoc Guardian Druid.
class spell_dru_might_of_ursoc : public SpellScriptLoader
{
public:
	spell_dru_might_of_ursoc() : SpellScriptLoader("spell_dru_might_of_ursoc") { }

	class spell_dru_might_of_ursoc_AuraScript : public AuraScript
	{
		PrepareAuraScript(spell_dru_might_of_ursoc_AuraScript);

		void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
		{
			amount = GetUnitOwner()->CountPctFromMaxHealth(amount);
		}

		void Register() override
		{
			DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dru_might_of_ursoc_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_MOD_INCREASE_HEALTH_2);
		}
	};

	AuraScript* GetAuraScript() const override
	{
		return new spell_dru_might_of_ursoc_AuraScript();
	}
};

void AddSC_druid_spell()
{
	new spell_dru_might_of_ursoc();
}