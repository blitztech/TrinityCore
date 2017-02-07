DELETE FROM `spell_script_names` WHERE `ScriptName` IN ('spell_monk_renewing_mist', 'spell_monk_renewing_mist_periodic_heal', 'spell_monk_renewing_mist_target_selector');
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(115151,'spell_monk_renewing_mist'),
(119611,'spell_monk_renewing_mist_periodic_heal'),
(119607,'spell_monk_renewing_mist_target_selector');

DELETE FROM `spell_script_names` WHERE `ScriptName` = 'spell_monk_fortifying_brew';
INSERT INTO spell_script_names (spell_id,ScriptName) VALUES
(115203,'spell_monk_fortifying_brew');

DELETE FROM `spell_script_names` WHERE `ScriptName` = 'spell_monk_expel_harm';
INSERT INTO spell_script_names (spell_id,ScriptName) VALUES
(115129,'spell_monk_expel_harm');

DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_monk_roll' AND `spell_id`= 109132;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(109132,'spell_monk_roll');

DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_monk_ring_of_peace_dummy' AND `spell_id`= 140023;
DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_monk_ring_of_peace' AND `spell_id`= 116844;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(140023,'spell_monk_ring_of_peace_dummy'),
(116844,'spell_monk_ring_of_peace');


DELETE FROM `spell_script_names` WHERE `ScriptName` = 'spell_dru_might_of_ursoc';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(105737,'spell_dru_might_of_ursoc');

DELETE FROM `spell_script_names` WHERE `spell_id`=17877 AND `ScriptName`='spell_warl_shadowburn_damage';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (17877, 'spell_warl_shadowburn_damage');

DELETE FROM `spell_script_names` WHERE `spell_id`=147707 AND `ScriptName`='spell_sha_glyph_rain_of_frogs';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (147707, 'spell_sha_glyph_rain_of_frogs');

DELETE FROM spell_script_names WHERE ScriptName = 'spell_mage_glyph_of_conjure_familiar';
DELETE FROM spell_script_names WHERE ScriptName = 'spell_mage_glyph_of_illusion';
INSERT INTO spell_script_names (spell_id, ScriptName) VALUES
(126748, 'spell_mage_glyph_of_conjure_familiar'),
(63092, 'spell_mage_glyph_of_illusion');

