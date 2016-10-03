--Core/Spells: Fix up Rogues Stealth--
DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (1784,115191) AND `spell_effect` IN (158185,158188);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES
(1784,158185,2,'Stealth mod'),
(1784,158188,2,'Stealth shapeshift'),
(115191,158185,2,'Stealth mod');