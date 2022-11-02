CREATE DATABASE test;

CREATE TABLE test_table(
	test_id int NOT NULL,
	PRIMARY KEY(test_id)
);

INSERT INTO test_table(test_id)
VALUES (1);
