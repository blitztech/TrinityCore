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

// This is where scripts' loading functions should be declared:
void AddSC_custom_npc();
void AddSC_monk_spell();
void AddSC_dk_spell();
void AddSC_mage_spell();
void AddSC_paladin_spell();
void AddSC_warrior_spell();
void AddSC_hunter_spell();
void AddSC_warlock_spell();
void AddSC_dh_spell();
void AddSC_priest_spell();
void AddSC_druid_spell();
void AddSC_shaman_spell();


// The name of this function should match:
// void Add${NameOfDirectory}Scripts()
void AddCustomScripts()
{
	AddSC_custom_npc();
	AddSC_monk_spell();
	AddSC_dk_spell();
    AddSC_mage_spell();
    AddSC_paladin_spell();
    AddSC_warrior_spell);
    AddSC_hunter_spell();
    AddSC_warlock_spell);
    AddSC_dh_spell();
    AddSC_priest_spell();
	AddSC_druid_spell();
	AddSC_shaman_spell();
}; 