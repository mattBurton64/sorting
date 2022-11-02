CREATE DATABASE videogame;

DROP TABLE IF EXISTS `server`;
DROP TABLE IF EXISTS `account`;
DROP TABLE IF EXISTS `player`;
DROP TABLE IF EXISTS `profile`;
DROP TABLE IF EXISTS `perk`;
DROP TABLE IF EXISTS `item`;
DROP TABLE IF EXISTS `primary_weapon`;
DROP TABLE IF EXISTS `secondary_weapon`;
DROP TABLE IF EXISTS `utility`;
DROP TABLE IF EXISTS `loadout`;
DROP TABLE IF EXISTS `friendship`;
DROP TABLE IF EXISTS `stat_log`;

CREATE TABLE `server`(
	`server_id` int unsigned NOT NULL auto_increment,
	`server_gamemode` varchar(30),
	`server_max_players` int,
	`server_current_players` int,
	PRIMARY KEY(`server_id`)
) AUTO_INCREMENT = 1;

CREATE TABLE `account`(
	`acc_id` int unsigned NOT NULL auto_increment,
	`acc_username` varchar(30),
	`acc_password` varchar(30),
	PRIMARY KEY(`acc_id`)
) AUTO_INCREMENT = 1;

CREATE TABLE `player`(
	`player_id` int unsigned NOT NULL auto_increment,
	`player_level` int,
	`player_health` int,
	PRIMARY KEY(`player_id`)
) AUTO_INCREMENT = 1;

CREATE TABLE `profile`(
	FOREIGN KEY(`acc_id`) REFERENCES account(`acc_id`) int NOT NULL,
	FOREIGN KEY(`player_id`) REFERENCES player(`player_id`) int NOT NULL,
	`prof_player_name` varchar(30),
	`prof_start_date` DATE,
	PRIMARY KEY(`acc_id`, `player_id`)
);

CREATE TABLE `item`(
	`item_id` int unsigned NOT NULL auto_increment,
	`item_description` varchar(255),
   `item_type` varchar(30),
	PRIMARY KEY(`item_id`)
) AUTO_INCREMENT = 1;

CREATE TABLE `perk`(
	`perk_id` int unsigned NOT NULL auto_increment,
	`perk_description` varchar(255),
	PRIMARY KEY(`perk_id`)
) AUTO_INCREMENT = 1;

CREATE TABLE `primary_weapon`(
	FOREIGN KEY(`primary_id`) REFERENCE item(`item_id`) int NOT NULL,
	`primary_ammo` int,
	`primary_range` int,
	`primary_damage` int,
	PRIMARY KEY(`primary_id`)
);

CREATE TABLE `secondary_weapon`(
	FOREIGN KEY(`secondary_id`) REFERENCE item(`item_id`) int NOT NULL,
	`secondary_ammo` int,
	`secondary_range` int,
	`secondary_damage` int,
	PRIMARY KEY(`secondary_id`)
);

CREATE TABLE `utility`(
	FOREIGN KEY(`utility_id`) REFERENCE item(`item_id`) int NOT NULL,
	`utility_quantity` int,
	PRIMARY KEY(`utility_id`)
);

CREATE TABLE `loadout`(
	`loadout_id` int unsigned NOT NULL auto_increment,
	FOREIGN KEY(`primary_id`) REFERENCE primary_weapon(`primary_id`),
	FOREIGN KEY(`secondary_id`) REFERENCE secondary_weapon(`secondary_id`),
	FOREIGN KEY(`utility_id`) REFERENCE utility(`utility_id`),
	PRIMARY KEY(`loadout_id`)
) AUTO_INCREMENT = 1;
 
CREATE TABLE `friendship`(
	FOREIGN KEY(`player_id`) REFERENCE player(`player_id`) int NOT NULL,
	FOREIGN KEY(`friend_id`) REFERENCE player(`player_id`) int NOT NULL,
	`date_added` DATE,
	`games_played_together` int,
	PRIMARY KEY(`friendship_id`)
);

CREATE TABLE `stat_log`(
	FOREIGN KEY(`player_id`) REFERENCE player(`player_id`) int NOT NULL,
	FOREIGN KEY(`item_id`) REFERENCE item(`item_id`),
	`games_played` int,
	PRIMARY KEY(`player_id`, `item_id`)
);

INSERT INTO `server`(`server_gamemode`, `server_max_players`, `server_current_players`)
VALUES('domination', 24, 12);

INSERT INTO `account`(`acc_username`, `acc_password`)
VALUES ('lagana', 'thisclassissofun');

INSERT INTO	`player`(`player_id`, `player_level`, `player_health`)
VALUES 
	(1, 34, 94),
	(2, 36, 67);

INSERT INTO `profile`(`acc_id`, `player_id`, `prof_player_name`, `prof_start_date`)
VALUES(1, 1, 'lagana', '04-04-2020');

INSERT INTO `perk`(`perk_description`)
VALUES ('super speed');

INSERT INTO `item`(`item_description`, `item_type`)
VALUES('Assault Rifle', 'Gun');

INSERT INTO `primary_weapon`(`primary_id`,`item_id`, `primary_ammo`, `primary_range`, `primary_damage`)
VALUES (1,1,12,24,65);

INSERT INTO `secondary_weapon`(`secondary_id`, `item_id`, `secondary_ammo`, `secondary_range`, `secondary_ammo`)
VALUES (2, 1, 50, 69);

INSERT INTO `utility`(`utility_id`, `utility_quantity`)
VALUES (3, 1, 10);

INSERT INTO `loadout`(`primary_id`, `secondary_id`, `utility_id`)
VALUES (1, 2, 3);

INSERT INTO `friendship`(`player_id`, `friend_id`, `data_added`, `games_played`)
VALUES (1, 1, '08-05-2021', 10);

INSERT INTO `stat_log`(`player_id`, `item_id`, `games_played`)
VALUES(1, 1, 10);

COMMIT;
