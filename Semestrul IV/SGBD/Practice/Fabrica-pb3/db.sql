CREATE DATABASE Fabrica;

USE Fabrica;

CREATE TABLE Producator (
	id_producator int primary key identity,
	nume_producator varchar(20)
);

CREATE TABLE Biscuite(
	id_biscuite int primary key identity,
	nume_biscuite varchar(20),
	id_producator int foreign key references Producator(id_producator)
	);

INSERT INTO Producator(nume_producator) VALUES
('AAAA'),
('BBBB');

SELECT * FROM Producator;

INSERT INTO Biscuite(nume_biscuite, id_producator) VALUES
('Poienii', 1),
('Clujenii', 1),
('AAA Marca',1),
('BB Merch', 2),
('Aer',2);

SELECT * FROM Biscuite;