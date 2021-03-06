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

#include "ScriptMgr.h"
#include "ScriptedCreature.h"

enum Spells
{
    SPELL_CONSECRATED_LIGHT = 153006,
    SPELL_HALLOWED_GROUND = 154526,
    SPELL_HOLY_SHIELD = 153480,
    SPELL_SANCTIFIED_GROUND = 153430,
    SPELL_SANCTIFIED_STRIKE = 152954,
};

enum Events
{
    EVENT_CONSECRATED_LIGHT = 1,
    EVENT_HALLOWED_GROUND,
    EVENT_HOLY_SHIELD,
    EVENT_SANCTIFIED_GROUND,
    EVENT_SANCTIFIED_STRIKE,
};

class boss_vigilant_kaathar : public CreatureScript
{
public:
    boss_vigilant_kaathar() : CreatureScript("boss_vigilant_kaathar") { }

    struct boss_vigilant_kaatharAI : public BossAI
    {
        boss_vigilant_kaatharAI(Creature* creature) : BossAI(creature, 75839)
        {
        }

        void Reset() override
        {
            BossAI::Reset();
        }

        void EnterCombat(Unit* victim) override
        {
            BossAI::EnterCombat(victim);
            events.ScheduleEvent(EVENT_CONSECRATED_LIGHT, 4000);
            events.ScheduleEvent(EVENT_HALLOWED_GROUND, 8000);
            events.ScheduleEvent(EVENT_HOLY_SHIELD, 12000);
            events.ScheduleEvent(EVENT_SANCTIFIED_GROUND, 16000);
            events.ScheduleEvent(EVENT_SANCTIFIED_STRIKE, 20000);
        }

        void KilledUnit(Unit * /*victim*/) override
        {
        }

        void JustDied(Unit * /*victim*/) override
        {
            _JustDied();
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CONSECRATED_LIGHT:
                    DoCastAOE(SPELL_CONSECRATED_LIGHT);
                    events.ScheduleEvent(EVENT_CONSECRATED_LIGHT, 4000);
                    break;
                case EVENT_HALLOWED_GROUND:
                    DoCastAOE(SPELL_HALLOWED_GROUND);
                    events.ScheduleEvent(EVENT_HALLOWED_GROUND, 8000);
                    break;
                case EVENT_HOLY_SHIELD:
                    DoCastVictim(SPELL_HOLY_SHIELD);
                    events.ScheduleEvent(EVENT_HOLY_SHIELD, 12000);
                    break;
                case EVENT_SANCTIFIED_GROUND:
                    DoCastAOE(SPELL_SANCTIFIED_GROUND);
                    events.ScheduleEvent(EVENT_SANCTIFIED_GROUND, 16000);
                    break;
                case EVENT_SANCTIFIED_STRIKE:
                    DoCastAOE(SPELL_SANCTIFIED_STRIKE);
                    events.ScheduleEvent(EVENT_SANCTIFIED_STRIKE, 20000);
                    break;
                default:
                    break;
                }
            }
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_vigilant_kaatharAI(creature);
    }
};

void AddSC_boss_vigilant_kaathar()
{
    new boss_vigilant_kaathar();
}
