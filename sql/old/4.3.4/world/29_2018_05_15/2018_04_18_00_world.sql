-- 
UPDATE `creature` SET `PhaseId`=361 WHERE `guid` BETWEEN 250399 AND 250824;
UPDATE `creature` SET `PhaseId`=0, `PhaseGroup`=551 WHERE `guid` BETWEEN 250825 AND 250875;
UPDATE `creature` SET `PhaseId`=361, `PhaseGroup`=0 WHERE `guid` BETWEEN 250876 AND 250886;
UPDATE `gameobject` SET `PhaseId`=361 WHERE `guid` IN ( 233413,233411,233410,233409,233408,233407,233405);