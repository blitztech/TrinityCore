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

enum ShamanSpells
{
	SPELL_SHA_RAIN_OF_FROGS = 147709
};

class spell_sha_glyph_rain_of_frogs : public SpellScriptLoader
{
public:
	spell_sha_glyph_rain_of_frogs() : SpellScriptLoader("spell_sha_glyph_rain_of_frogs") { }

	class spell_sha_glyph_rain_of_frogs_AuraScript : public AuraScript
	{
		PrepareAuraScript(spell_sha_glyph_rain_of_frogs_AuraScript);

		void OnApply(AuraEffect const * /*aurEff*/, AuraEffectHandleModes /*mode*/)
		{
			if (Player* _player = GetTarget()->ToPlayer())
				_player->LearnSpell(SPELL_SHA_RAIN_OF_FROGS, false);
		}

		void OnRemove(AuraEffect const * /*aurEff*/, AuraEffectHandleModes /*mode*/)
		{
			if (Player* _player = GetTarget()->ToPlayer())
				if (_player->HasSpell(SPELL_SHA_RAIN_OF_FROGS))
					_player->RemoveSpell(SPELL_SHA_RAIN_OF_FROGS, false, false);
		}

		void Register() override
		{
			OnEffectApply += AuraEffectApplyFn(spell_sha_glyph_rain_of_frogs_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
			OnEffectRemove += AuraEffectRemoveFn(spell_sha_glyph_rain_of_frogs_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
		}
	};

	AuraScript* GetAuraScript() const override
	{
		return new spell_sha_glyph_rain_of_frogs_AuraScript();
	}
};

void AddSC_shaman_spell()
{
	new spell_sha_glyph_rain_of_frogs();
}