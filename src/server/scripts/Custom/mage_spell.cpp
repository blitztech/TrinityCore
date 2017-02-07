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

enum GlyphOfIllusion
{
	MAGE_GLYPH_OF_ILLUSION_ACTIVE = 131784
};

class spell_mage_glyph_of_illusion : public SpellScriptLoader
{
public:
	spell_mage_glyph_of_illusion() : SpellScriptLoader("spell_mage_glyph_of_illusion") { }

	class spell_mage_glyph_of_illusion_AuraScript : public AuraScript
	{
		PrepareAuraScript(spell_mage_glyph_of_illusion_AuraScript);

		void HandleEffectApply(AuraEffect const * /*aurEff*/, AuraEffectHandleModes /*mode*/)
		{
			GetCaster()->ToPlayer()->LearnSpell(MAGE_GLYPH_OF_ILLUSION_ACTIVE, false);
		}

		void HandleEffectRemove(AuraEffect const * /*aurEff*/, AuraEffectHandleModes /*mode*/)
		{
			GetCaster()->ToPlayer()->RemoveSpell(MAGE_GLYPH_OF_ILLUSION_ACTIVE);
		}

		void Register() override
		{
			AfterEffectApply += AuraEffectApplyFn(spell_mage_glyph_of_illusion_AuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
			AfterEffectRemove += AuraEffectRemoveFn(spell_mage_glyph_of_illusion_AuraScript::HandleEffectRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
		}
	};

	AuraScript* GetAuraScript() const override
	{
		return new spell_mage_glyph_of_illusion_AuraScript();
	}
};

enum GlyphOfConjureFamiliar
{
	MAGE_GLYPH_OF_CONJURE_FAMILIAR_ACTIVE = 126578
};

class spell_mage_glyph_of_conjure_familiar : public SpellScriptLoader
{
public:
	spell_mage_glyph_of_conjure_familiar() : SpellScriptLoader("spell_mage_glyph_of_conjure_familiar") { }

	class spell_mage_glyph_of_conjure_familiar_AuraScript : public AuraScript
	{
		PrepareAuraScript(spell_mage_glyph_of_conjure_familiar_AuraScript);

		void HandleEffectApply(AuraEffect const * /*aurEff*/, AuraEffectHandleModes /*mode*/)
		{
			GetCaster()->ToPlayer()->LearnSpell(MAGE_GLYPH_OF_CONJURE_FAMILIAR_ACTIVE, false);
		}

		void HandleEffectRemove(AuraEffect const * /*aurEff*/, AuraEffectHandleModes /*mode*/)
		{
			GetCaster()->ToPlayer()->RemoveSpell(MAGE_GLYPH_OF_CONJURE_FAMILIAR_ACTIVE);
		}

		void Register() override
		{
			AfterEffectApply += AuraEffectApplyFn(spell_mage_glyph_of_conjure_familiar_AuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
			AfterEffectRemove += AuraEffectRemoveFn(spell_mage_glyph_of_conjure_familiar_AuraScript::HandleEffectRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
		}
	};

	AuraScript* GetAuraScript() const override
	{
		return new spell_mage_glyph_of_conjure_familiar_AuraScript();
	}
};

void AddSC_mage_spell()
{
	new spell_mage_glyph_of_illusion();
	new spell_mage_glyph_of_conjure_familiar()
}