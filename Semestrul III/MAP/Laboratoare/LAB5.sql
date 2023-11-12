CREATE TABLE users(
id BIGINT PRIMARY KEY,
first_name VARCHAR(50),
last_name VARCHAR(50))

SELECT *
FROM users

INSERT INTO users(id, first_name, last_name) VALUES
(1, 'Ion', 'Popescu'),
(2, 'Cosmin', 'Andrei'),
(3, 'Andreea', 'Pop'),
(4, 'Raly', 'Tonea'),
(5, 'Maria', 'Ionescu')

SELECT *
FROM users