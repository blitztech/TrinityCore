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
	MAGE_GLYPH_OF_ILLUSION_ACTIVE			= 131784,
	SPELL_MAGE_CAUTERIZE					= 86949,
	SPELL_MAGE_CHILLED						= 205708,
	SPELL_MAGE_CONE_OF_COLD					= 212792,
	SPELL_MAGE_BLAZING_BARRIER_TRIGGERED	= 235314
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

// 235313 - Blazing Barrier [7.1.5]
class spell_mage_blazing_barrier : public SpellScriptLoader
{
public:
	spell_mage_blazing_barrier() : SpellScriptLoader("spell_mage_blazing_barrier") { }

	class spell_mage_blazing_barrier_AuraScript : public AuraScript
	{
		PrepareAuraScript(spell_mage_blazing_barrier_AuraScript);

		void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& canBeRecalculated)
		{
			canBeRecalculated = false;

			if (Unit* caster = GetCaster())
				amount = int32(caster->SpellBaseDamageBonusDone(GetSpellInfo()->GetSchoolMask()) * 7.0f);
		}

		void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
		{
			PreventDefaultAction();

			Unit* caster = eventInfo.GetDamageInfo()->GetAttacker();
			Unit* target = eventInfo.GetDamageInfo()->GetVictim();
			if (!caster || !target)
				return;

			caster->CastSpell(target, SPELL_MAGE_BLAZING_BARRIER_TRIGGERED, true);
		}

		void Register() override
		{
			DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_mage_blazing_barrier_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
			OnEffectProc += AuraEffectProcFn(spell_mage_blazing_barrier_AuraScript::HandleProc, EFFECT_1, SPELL_AURA_PROC_TRIGGER_SPELL);
		}
	};

	AuraScript* GetAuraScript() const override
	{
		return new spell_mage_blazing_barrier_AuraScript();
	}
};

// 11426 - Ice Barrier [7.1.5]
class spell_mage_ice_barrier : public SpellScriptLoader
{
public:
	spell_mage_ice_barrier() : SpellScriptLoader("spell_mage_ice_barrier") { }

	class spell_mage_ice_barrier_AuraScript : public AuraScript
	{
		PrepareAuraScript(spell_mage_ice_barrier_AuraScript);

		bool Validate(SpellInfo const* /*spell*/) override
		{
			if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_CHILLED))
				return false;
			return true;
		}

		void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& canBeRecalculated)
		{
			canBeRecalculated = false;
			if (Unit* caster = GetCaster())
				amount += int32(10.0f * caster->SpellBaseHealingBonusDone(GetSpellInfo()->GetSchoolMask()));
		}

		void HandleHit(AuraEffect* /*aurEff*/, DamageInfo& dmgInfo, uint32 & /*absorbAmount*/)
		{
			if (Unit* target = dmgInfo.GetAttacker())
				GetCaster()->CastSpell(target, SPELL_MAGE_CHILLED, true);
		}

		void Register() override
		{
			DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_mage_ice_barrier_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
			AfterEffectAbsorb += AuraEffectAbsorbFn(spell_mage_ice_barrier_AuraScript::HandleHit, EFFECT_0);
		}
	};

	AuraScript* GetAuraScript() const override
	{
		return new spell_mage_ice_barrier_AuraScript();
	}
};

// 120 - Cone of Cold [7.1.5]
class spell_mage_cone_of_cold : public SpellScriptLoader
{
public:
	spell_mage_cone_of_cold() : SpellScriptLoader("spell_mage_cone_of_cold") { }

	class spell_mage_cone_of_cold_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_mage_cone_of_cold_SpellScript);

		bool Validate(SpellInfo const* /*spellInfo*/) override
		{
			if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_CONE_OF_COLD))
				return false;
			return true;
		}

		void HandleHit(SpellEffIndex /*effIndex*/)
		{
			Unit* caster = GetCaster();
			Unit* target = GetHitUnit();
			if (caster && target)
				caster->CastSpell(target, SPELL_MAGE_CONE_OF_COLD, true);
		}

		void Register() override
		{
			OnEffectHitTarget += SpellEffectFn(spell_mage_cone_of_cold_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
		}
	};

	SpellScript* GetSpellScript() const override
	{
		return new spell_mage_cone_of_cold_SpellScript();
	}
};

void AddSC_mage_spell()
{
	new spell_mage_glyph_of_illusion();
	new spell_mage_glyph_of_conjure_familiar();
	new spell_mage_blazing_barrier();
	new spell_mage_ice_barrier();
	new spell_mage_cone_of_cold();
}