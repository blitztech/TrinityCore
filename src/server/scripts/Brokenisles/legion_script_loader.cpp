/*
* Copyright (C) 2016 FreedomCore <https://freedomcore.ru/>
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

void AddSC_legion();

// Maw of Souls
void AddSC_instance_maw_of_souls();
void AddSC_boss_ymiron_maw();
void AddSC_boss_harbaron_maw();
void AddSC_boss_helya_maw();


// Zone Scripts
void AddSC_azsuna();
void AddSC_broken_shore();
void AddSC_dalaran();
void AddSC_highmountain();
void AddSC_stormheim();
void AddSC_suramar();
void AddSC_valsharah();

void AddLegionScripts() {

	AddSC_legion();

	// Maw of Souls
	AddSC_instance_maw_of_souls();
	AddSC_boss_ymiron_maw();
	AddSC_boss_harbaron_maw();
	AddSC_boss_helya_maw();


	// Zone Scripts
	AddSC_azsuna();
	AddSC_broken_shore();
	AddSC_dalaran();
	AddSC_highmountain();
	AddSC_stormheim();
	AddSC_suramar();
	AddSC_valsharah();
}