/*
 * Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
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

/*
<--------------------------------------------------------------------------->
 - Developer(s): Ghostcrawler336
 - Complete: %100
 - ScriptName: 'Buff Master' 
 - Comment: untested.
<--------------------------------------------------------------------------->
*/
#include "ScriptPCH.h"
 #include "Creature.h"
 #include "Define.h"
 #include "EventProcessor.h"
 #include "Player.h"
 #include "ScriptMgr.h"
 #include "SharedDefines.h"
 #include "ScriptedGossip.h"
 
 
 class DelayedWhisper : public BasicEvent
 {
	 public:    DelayedWhisper(Player* player) : BasicEvent(), player(player)    
	 {
		 player->m_Events.AddEvent(this, player->m_Events.CalculateTime(2500));    
	 }
				bool Execute(uint64, uint32) override    
	 {
		 if (Creature* creature = player->FindNearestCreature(85000, 25.0f))
	 {
		 creature->Whisper("PSSST Hey you!..Yes You! Come to me!", LANG_UNIVERSAL, player);        
		 }

		 return true;
				}    Player* player;
 };
class FirstLogin : public PlayerScript
{
	public:    FirstLogin() : PlayerScript("FirstLogin") 
	{
	}    
			   void OnLogin(Player* player, bool firstLogin) override    
			   {        
				   if (!firstLogin)            
					   return;
				   new DelayedWhisper(player);    
			   }
};
 
enum spells 
{
/* 	POWER_WORD_FORTITUDE = 48162,
	PRAYER_OF_SPRITE = 48074,
	SHADOW_BUFF = 48170,
	KINGS_BUFF = 43223,
	ARCANE_BUFF = 36880, */
	JUMP_TO_SKYHOLD = 192084,
	TELEPORT_VAULTH_OF_WARDEN = 205395
};
     
class warrior_classhall_to_skyhold : public CreatureScript
{
        public:
                warrior_classhall_to_skyhold() : CreatureScript("warrior_classhall_to_skyhold"){}
     
				bool OnGossipHello(Player* player, Creature* creature)
                {
						AddGossipItemFor(player, 4, "Send Me Now!", GOSSIP_SENDER_MAIN, 1);
						AddGossipItemFor(player, 4, "Never mind", GOSSIP_SENDER_MAIN, 100);
						player->PlayerTalkClass->SendGossipMenu(9425, creature->GetGUID());
									
                        return true;
                }
     
                bool OnGossipSelect(Player * player, Creature * creature, uint32 /*uiSender*/, uint32 uiAction)
                {
					player->PlayerTalkClass->ClearMenus();
					
					    switch(player->getClass())
                        {
                                case CLASS_WARRIOR:
									{
                                        player->CastSpell(player, JUMP_TO_SKYHOLD, true);
                                    }break;

								/*case CLASS_PALADIN:
									{
										 pPlayer->CastSpell(pPlayer, POWER_WORD_FORTITUDE, true);
										 pPlayer->CastSpell(pPlayer, KINGS_BUFF, true);
										 pPlayer->CastSpell(pPlayer, MARK_OF_THE_WILD, true);
										 pPlayer->CastSpell(pPlayer, PRAYER_OF_SPRITE, true);
										 pPlayer->CastSpell(pPlayer, ARCANE_BUFF, true);
										 pPlayer->CastSpell(pPlayer, SHADOW_BUFF, true);
										 pCreature->MonsterWhisper("You are now buffed!", pPlayer->GetGUID(), true);
									}break;

								case CLASS_HUNTER:
										{

										}break;

								case CLASS_ROGUE:
									{

									}break;

								case CLASS_PRIEST:
									{

									}break;

								case CLASS_DEATH_KNIGHT:
									{

									}break;

								case CLASS_SHAMAN:
									{

									}break;

								case CLASS_MAGE:
									{

									}break;

								case CLASS_WARLOCK:
									{
	
									}break;

								case CLASS_DRUID:
									{

									}break; */

								case 100:
								{
									CloseGossipMenuFor(player);
								}break;
                                     
						}
                        return true;
                }
};

// npc 99260 Kor'vas Bloodthorn
class demonhunter_teleport_vault_of_Warden : public CreatureScript
{
public:
	demonhunter_teleport_vault_of_Warden() : CreatureScript("demonhunter_teleport_vault_of_Warden") {}

		bool OnGossipHello(Player* player, Creature* creature)
	{
		AddGossipItemFor(player, 4, "Teleport To Vault of Warden!", GOSSIP_SENDER_MAIN, 1);
		AddGossipItemFor(player, 4, "Exit", GOSSIP_SENDER_MAIN, 100);
		player->PlayerTalkClass->SendGossipMenu(9425, creature->GetGUID());

		return true;
	}

	bool OnGossipSelect(Player* player, Creature * creature, uint32 /*uiSender*/, uint32 uiAction)
	{
		player->PlayerTalkClass->ClearMenus();

		switch (player->getClass())
		{
			case CLASS_DEMON_HUNTER:
			{
				player->CastSpell(player, TELEPORT_VAULTH_OF_WARDEN, true);
			}break;

			case 100:
			{
				CloseGossipMenuFor(player);
			}break;

		}
		return true;
	}
};
void AddSC_custom_npc()
{
        new warrior_classhall_to_skyhold();
		new FirstLogin();
		new demonhunter_teleport_vault_of_Warden();
}