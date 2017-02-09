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

enum MonkSpells
{
	SPELL_MONK_RENEWING_MIST = 115151,
	SPELL_MONK_RENEWING_MIST_PERIODIC_HEAL = 119611,
	SPELL_MONK_RENEWING_MIST_TARGET_SELECT = 119607,
	SPELL_MONK_RENEWING_MIST_DUMMY_VISUAL = 119647,
	SPELL_MONK_GLYPH_OF_FORTIFYING_BREW = 124997,
	SPELL_MONK_FORTIFYING_BREW_AURA = 120954,
	SPELL_MONK_EXPEL_HARM_AREA_DMG = 115129,
	SPELL_MONK_ROLL = 109132,
	SPELL_MONK_ROLL_TRIGGER = 107427,
	SPELL_MONK_RING_OF_PEACE_AURA = 140023,
	SPELL_MONK_RING_OF_PEACE_DISARM = 137461,
	SPELL_MONK_RING_OF_PEACE_SILENCE = 137460

};

// 115151 - Renewing Mist
class spell_monk_renewing_mist : public SpellScriptLoader
{
public:
	spell_monk_renewing_mist() : SpellScriptLoader("spell_monk_renewing_mist") { }

	class spell_monk_renewing_mist_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_monk_renewing_mist_SpellScript);

		bool Validate(SpellInfo const* /*spellInfo*/) override
		{
			if (!sSpellMgr->GetSpellInfo(SPELL_MONK_RENEWING_MIST))
				return false;
			if (!sSpellMgr->GetSpellInfo(SPELL_MONK_RENEWING_MIST_PERIODIC_HEAL))
				return false;
			if (!sSpellMgr->GetSpellInfo(SPELL_MONK_RENEWING_MIST_TARGET_SELECT))
				return false;
			if (!sSpellMgr->GetSpellInfo(SPELL_MONK_RENEWING_MIST_DUMMY_VISUAL))
				return false;
			return true;
		}

		void HandleDummy(SpellEffIndex effIndex)
		{
			PreventHitDefaultEffect(effIndex);
			GetCaster()->CastSpell(GetHitUnit(), SPELL_MONK_RENEWING_MIST_PERIODIC_HEAL, true);
		}

		void Register() override
		{
			OnEffectHitTarget += SpellEffectFn(spell_monk_renewing_mist_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
		}
	};

	SpellScript* GetSpellScript() const override
	{
		return new spell_monk_renewing_mist_SpellScript();
	}
};

// 119611 - Renewing Mist Periodic Heal
class spell_monk_renewing_mist_periodic_heal : public SpellScriptLoader
{
public:
	spell_monk_renewing_mist_periodic_heal() : SpellScriptLoader("spell_monk_renewing_mist_periodic_heal") { }

	class spell_monk_renewing_mist_periodic_heal_AuraScript : public AuraScript
	{
		PrepareAuraScript(spell_monk_renewing_mist_periodic_heal_AuraScript);

		bool Validate(SpellInfo const* /*spellInfo*/) override
		{
			if (!sSpellMgr->GetSpellInfo(SPELL_MONK_RENEWING_MIST_PERIODIC_HEAL))
				return false;
			if (!sSpellMgr->GetSpellInfo(SPELL_MONK_RENEWING_MIST_TARGET_SELECT))
				return false;
			if (!sSpellMgr->GetSpellInfo(SPELL_MONK_RENEWING_MIST_DUMMY_VISUAL))
				return false;
			return true;
		}

		void HandlePeriodic(AuraEffect const* aurEff)
		{
			if (aurEff->GetBase()->GetCharges() > 1)
				if (Unit* originCaster = GetCaster())
					originCaster->CastSpell(GetTarget(), SPELL_MONK_RENEWING_MIST_TARGET_SELECT, true);
		}

		void HandleDummy(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
		{
			aurEff->GetBase()->SetCharges(aurEff->GetAmount());
		}

		void Register() override
		{
			OnEffectPeriodic += AuraEffectPeriodicFn(spell_monk_renewing_mist_periodic_heal_AuraScript::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_HEAL);
			OnEffectApply += AuraEffectApplyFn(spell_monk_renewing_mist_periodic_heal_AuraScript::HandleDummy, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
		}
	};

	AuraScript* GetAuraScript() const override
	{
		return new spell_monk_renewing_mist_periodic_heal_AuraScript();
	}
};

// 119607 - Renewing Mist Target Selection
class spell_monk_renewing_mist_target_selector : public SpellScriptLoader
{
public:
	spell_monk_renewing_mist_target_selector() : SpellScriptLoader("spell_monk_renewing_mist_target_selector") { }

	class spell_monk_renewing_mist_target_selector_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_monk_renewing_mist_target_selector_SpellScript);

	public:
		spell_monk_renewing_mist_target_selector_SpellScript() { }

	private:
		bool Validate(SpellInfo const* /*spellInfo*/) override
		{
			if (!sSpellMgr->GetSpellInfo(SPELL_MONK_RENEWING_MIST_PERIODIC_HEAL))
				return false;
			if (!sSpellMgr->GetSpellInfo(SPELL_MONK_RENEWING_MIST_TARGET_SELECT))
				return false;
			if (!sSpellMgr->GetSpellInfo(SPELL_MONK_RENEWING_MIST_DUMMY_VISUAL))
				return false;
			return true;
		}

		void FilterTargets(std::list<WorldObject*>& targets)
		{
			targets.remove(GetExplTargetWorldObject());
			if (targets.empty())
				return;
			targets.sort(Trinity::HealthPctOrderPred());
			targets.resize(1);
		}

		void HandleDummy(SpellEffIndex effIndex)
		{
			PreventHitDefaultEffect(effIndex);
			if (Unit* target = GetHitUnit())
				if (Aura* aura = GetExplTargetUnit()->GetAura(SPELL_MONK_RENEWING_MIST_PERIODIC_HEAL, GetCaster()->GetGUID()))
					if (AuraEffect* effect = aura->GetEffect(EFFECT_1))
					{
						GetExplTargetUnit()->CastSpell(target, SPELL_MONK_RENEWING_MIST_DUMMY_VISUAL, true);
						aura->SetCharges(0);
						int32 bp1 = std::max(0, effect->GetAmount() - 1);
						GetExplTargetUnit()->CastCustomSpell(SPELL_MONK_RENEWING_MIST_PERIODIC_HEAL, SPELLVALUE_BASE_POINT1, bp1, target, true, 0, effect, GetCaster()->GetGUID());
					}
		}

		void Register() override
		{
			OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_monk_renewing_mist_target_selector_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_DEST_AREA_ALLY);
			OnEffectHitTarget += SpellEffectFn(spell_monk_renewing_mist_target_selector_SpellScript::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
		}
	};

	SpellScript* GetSpellScript() const override
	{
		return new spell_monk_renewing_mist_target_selector_SpellScript();
	}
};

class spell_monk_fortifying_brew : public SpellScriptLoader
{
public:
	spell_monk_fortifying_brew() : SpellScriptLoader("spell_monk_fortifying_brew")
	{ }

	class spell_monk_fortifying_brew_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_monk_fortifying_brew_SpellScript);

		bool Validate(SpellInfo const* /*spellInfo*/) override
		{
			if (!sSpellMgr->GetSpellInfo(SPELL_MONK_FORTIFYING_BREW_AURA) || !sSpellMgr->GetSpellInfo(SPELL_MONK_GLYPH_OF_FORTIFYING_BREW))
				return false;
			return true;
		}

		void HandleOnHit(SpellEffIndex /*effIndex*/)
		{
			if (Unit* target = GetHitUnit())
			{
				int32 bp0 = GetEffectValue();
				int32 bp1 = -bp0;

				if (Aura* aura = target->GetAura(SPELL_MONK_GLYPH_OF_FORTIFYING_BREW))
				{
					bp0 -= aura->GetEffect(EFFECT_1)->GetAmount();
					bp1 -= aura->GetEffect(EFFECT_0)->GetAmount();
				}

				bp0 = CalculatePct(target->GetMaxHealth(), bp0);
				target->CastCustomSpell(target, SPELL_MONK_FORTIFYING_BREW_AURA, &bp0, &bp1, NULL, true);
			}
		}

		void Register() override
		{
			OnEffectHitTarget += SpellEffectFn(spell_monk_fortifying_brew_SpellScript::HandleOnHit, EFFECT_0, SPELL_EFFECT_DUMMY);
		}
	};

	SpellScript* GetSpellScript() const override
	{
		return new spell_monk_fortifying_brew_SpellScript();
	}
};

class spell_monk_expel_harm : public SpellScriptLoader
{
public:
	spell_monk_expel_harm() : SpellScriptLoader("spell_monk_expel_harm") { }

	class spell_monk_expel_harm_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_monk_expel_harm_SpellScript);

		void HandleOnHit()
		{
			if (auto caster = GetCaster())
			{
				int32 bp = CalculatePct(GetHitHeal(), 50);
				caster->CastCustomSpell(caster, SPELL_MONK_EXPEL_HARM_AREA_DMG, &bp, NULL, NULL, true);
			}
		}

		void Register() override
		{
			AfterHit += SpellHitFn(spell_monk_expel_harm_SpellScript::HandleOnHit);
		}
	};

	SpellScript* GetSpellScript() const override
	{
		return new spell_monk_expel_harm_SpellScript();
	}
};

class spell_monk_roll : public SpellScriptLoader
{
public:
	spell_monk_roll() : SpellScriptLoader("spell_monk_roll") { }

	class spell_monk_roll_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_monk_roll_SpellScript);

		bool Validate(SpellInfo const* /*spell*/) override
		{
			if (!sSpellMgr->GetSpellInfo(SPELL_MONK_ROLL_TRIGGER))
				return false;
			return true;
		}

		bool Load() override
		{
			return GetCaster()->GetTypeId() == TYPEID_PLAYER;
		}

		void HandleBeforeCast()
		{
			Aura* aura = GetCaster()->AddAura(SPELL_MONK_ROLL_TRIGGER, GetCaster());
			if (!aura)
				return;

			AuraApplication* app = aura->GetApplicationOfTarget(GetCaster()->GetGUID());
			if (!app)
				return;

			app->ClientUpdate();
		}

		void HandleAfterCast()
		{
			Unit* caster = GetCaster();
			caster->CastSpell(caster, SPELL_MONK_ROLL_TRIGGER, true);
		}

		void Register() override
		{
			BeforeCast += SpellCastFn(spell_monk_roll_SpellScript::HandleBeforeCast);
			AfterCast += SpellCastFn(spell_monk_roll_SpellScript::HandleAfterCast);
		}
	};

	SpellScript* GetSpellScript() const override
	{
		return new spell_monk_roll_SpellScript();
	}
};

class spell_monk_ring_of_peace_dummy : public SpellScriptLoader
{
public:
	spell_monk_ring_of_peace_dummy() : SpellScriptLoader("spell_monk_ring_of_peace_dummy") {}

	class spell_monk_ring_of_peace_dummy_AuraScript : public AuraScript
	{
		PrepareAuraScript(spell_monk_ring_of_peace_dummy_AuraScript);

		void OnProc(AuraEffect const* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
		{
			if (Unit* caster = GetCaster())
			{
				if (Unit* target = GetTarget())
				{
					caster->CastSpell(target, SPELL_MONK_RING_OF_PEACE_SILENCE, true);
					caster->CastSpell(target, SPELL_MONK_RING_OF_PEACE_DISARM, true);
				}
			}
		}

		void Register() override
		{
			OnEffectProc += AuraEffectProcFn(spell_monk_ring_of_peace_dummy_AuraScript::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
		}
	};

	AuraScript* GetAuraScript() const override
	{
		return new spell_monk_ring_of_peace_dummy_AuraScript();
	}
};

/*class spell_monk_ring_of_peace : public SpellScriptLoader
{
public:
	spell_monk_ring_of_peace() : SpellScriptLoader("spell_monk_ring_of_peace") { }

	class spell_monk_ring_of_peace_AuraScript : public AuraScript
	{
		PrepareAuraScript(spell_monk_ring_of_peace_AuraScript);

		void OnUpdate(uint32 diff)
		{
			if (Unit* caster = GetCaster())
			{
				if (Unit* target = GetUnitOwner())
				{
					std::list<Unit*> targetList;
					float radius = 8.0f;

					Trinity::NearestAttackableUnitInObjectRangeCheck u_check(target, caster, radius);
					Trinity::UnitListSearcher<Trinity::NearestAttackableUnitInObjectRangeCheck> searcher(target, targetList, u_check);
					target->VisitNearbyObject(radius, searcher);

					for (auto itr : targetList)
						caster->CastSpell(itr, SPELL_MONK_RING_OF_PEACE_AURA, true);
				}
			}
		}

		void Register() override
		{
			OnAuraUpdate += AuraUpdateFn(spell_monk_ring_of_peace_AuraScript::OnUpdate);
		}
	};

	AuraScript* GetAuraScript() const override
	{
		return new spell_monk_ring_of_peace_AuraScript();
	}
};*/

void AddSC_monk_spell()
{
	new spell_monk_renewing_mist();
	new spell_monk_renewing_mist_periodic_heal();
	new spell_monk_renewing_mist_target_selector();
	new spell_monk_fortifying_brew();
	new spell_monk_expel_harm();
	new spell_monk_roll();
	new spell_monk_ring_of_peace_dummy();
	/*new spell_monk_ring_of_peace();*/
}