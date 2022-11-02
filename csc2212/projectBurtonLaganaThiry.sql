BEGIN;

DROP TABLE IF EXISTS server;
DROP TABLE IF EXISTS account;
DROP TABLE IF EXISTS player;
DROP TABLE IF EXISTS profile;
DROP TABLE IF EXISTS perk;
DROP TABLE IF EXISTS item;
DROP TABLE IF EXISTS primary_weapon;
DROP TABLE IF EXISTS secondary_weapon;
DROP TABLE IF EXISTS utility;
DROP TABLE IF EXISTS loadout;
DROP TABLE IF EXISTS friendship;
DROP TABLE IF EXISTS stat_log;

CREATE TABLE server(
	server_id int NOT NULL,
	server_gamemode varchar(30),
	server_max_players int,
	server_current_players int,
	PRIMARY KEY(server_id)
);

CREATE TABLE account(
	acc_id int NOT NULL,
	acc_username varchar(30),
	acc_password varchar(30),
	PRIMARY KEY(acc_id)
);

CREATE TABLE player(
	player_id int NOT NULL,
	player_level int,
	player_health int,
	PRIMARY KEY(player_id)
);

CREATE TABLE profile(
	acc_id int NOT NULL,
	FOREIGN KEY(player_id) REFERENCES player(player_id) int NOT NULL,
	prof_player_name varchar(30),
	prof_start_date DATE,
	PRIMARY_KEY(acc_id, player_id)
);

CREATE TABLE item(
	item_id int NOT NULL,
	item_description varchar(255),
	item_type varchar(30),
	PRIMARY KEY(item_id)
);

CREATE TABLE perk(
	perk_id int NOT NULL,
	perk_description varchar(255),
	PRIMARY_KEY(perk_id)
);

CREATE TABLE primary_weapon(
	FOREIGN KEY(primary_id) REFERENCE item(item_id) int NOT NULL,
	primary_ammo int,
	primary_range int,
	primary damage int,
	PRIMARY KEY(primary_id)
);

CREATE TABLE secondary_weapon(
	FOREIGN KEY(secondary_id) REFERENCE item(item_id) int NOT NULL,
	secondary_ammo int,
	secondary_range int,
	secondary_damage int,
	PRIMARY KEY(secondary_id)
);

CREATE TABLE utility(
	FOREIGN KEY(utility_id) REFERENCE item(item_id) int NOT NULL,
	utility_quantity int,
	PRIMARY KEY(utility_id)
);

CREATE TABLE loadout(
	loadout_id int NOT NULL,
	FOREIGN KEY(primary_id) REFERENCE primary_weapon(primary_id),
	FOREIGN KEY(secondary_id) REFERENCE secondary_weapon(secondary_id),
	FOREIGN KEY(utility_id) REFERENCE utility(utility_id),
	PRIMARY KEY(loadout_id)
);
 
CREATE TABLE friendship(
	FOREIGN KEY(player_id) REFERENCE player(player_id) int NOT NULL,
	FOREIGN KEY(friend_id) REFERENCE player(player_id) int NOT NULL,
	date_added DATE,
	games_played_together int,
	PRIMARY KEY(friendship_id)
);

CREATE TABLE stat_log(
	FOREIGN KEY(player_id) REFERENCE player(player_id) int NOT NULL,
	FOREIGN KEY(item_id) REFERENCE item(item_id),
	games_played int,
	PRIMARY_KEY(player_id, item_id)
);

INSERT INTO server(server_id, server_gamemode, server_max_players, server_current_players);
VALUES(1, ‘domination’, 24, 12);

INSERT INTO account(acc_id, acc_username, acc_password);
VALUES (1, ‘lagana’, ‘thisclassissofun’);

INSERT INTO	player(player_id, player_level,player_health);
VALUES 
	(1, 34, 94),
	(2, 36, 67);

INSERT INTO profile(acc_id, player_id, prof_player_name, prof_start_date);
VALUES(1, 1, ‘lagana’, ’04-04-2020’);

INSERT INTO perk(perk_id, perk_description);
VALUES (1, ‘super speed’);

INSERT INTO item(item_id, item_description, item_type);
VALUES(1, ‘Assault Rifle’, ‘Gun’);

INSERT INTO primary_weapon(primary_id,item_id, primary_ammo, primary_range, primary_damage);
VALUES (1,1,12,24,65);

INSERT INTO secondary_weapon(secondary_id, item_id, secondary_ammo, secondary_range, secondary_ammo);
VALUES (1, 1, 50, 69);

INSERT INTO utility(utility_id, utility_quantity);
VALUES (1, 1, 10);

INSERT INTO loadout(loadout_id, primary_id, secondary_id, utility_id);
VALUES (1, 1, 1, 1);

INSERT INTO friendship(player_id, friend_id, data_added, games_played,);
VALUES (1, 1, 1, 1);

INSERT INTO stat_log(player_id, item_id, games_played);
VALUES(1, 1, 10);

COMMIT;
