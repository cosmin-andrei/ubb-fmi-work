CREATE DATABASE GestiuneCase
USE GestiuneCase;

--- create tables ---

CREATE TABLE Proprietar
(idProprietar INT PRIMARY KEY IDENTITY,
nume_proprietar varchar(50) not null,
prenume_proprietar varchar(50) not null,
gen_proprietar varchar(10) not null,
functie_proprietar varchar(50) not null);

SELECT * FROM Proprietar;

CREATE TABLE Chirias
(idChirias INT PRIMARY KEY IDENTITY,
nume_chirias varchar(50) not null,
prenume_chirias varchar(50) not null,
gen_chirias varchar(10) not null,
data_nastare DATE not null,
idProprietar INT FOREIGN KEY REFERENCES Proprietar(idProprietar) not null);

SELECT * FROM Chirias;

CREATE TABLE Casa
(idCasa INT PRIMARY KEY IDENTITY,
strada varchar(50) not null,
numar varchar(50) not null,
localitate varchar(10) not null,
cod_postal INT not null,
idProprietar INT FOREIGN KEY REFERENCES Proprietar(idProprietar) not null);

SELECT * FROM Casa;


CREATE TABLE Mobilier
(idMobilier INT PRIMARY KEY IDENTITY,
denumire varchar(50) not null,
descriere varchar(50) not null,
cantitate INT not null,
pret FLOAT not null);

SELECT * FROM Mobilier;

CREATE TABLE Inventar
(idInventar INT PRIMARY KEY IDENTITY,
idCasa INT FOREIGN KEY REFERENCES Casa(idCasa) not null,
idMobilier INT FOREIGN KEY REFERENCES Mobilier(idMobilier) not null,
data_achizitie DATE not null,
data_livrare DATE not null);

SELECT * FROM Inventar;

--- insert values ---

INSERT INTO Proprietar(nume_proprietar, prenume_proprietar, gen_proprietar, functie_proprietar) VALUES
('Popescu', 'Ion', 'M', 'Student'),
('Andrei', 'Cosmin', 'M', 'Profesor'),
('Stan', 'Ariana', 'F', 'Director economic'),
('Balea', 'Andrei', 'M', 'Asistent manager'),
('Rusu', 'Dana', 'F', 'Medic');

SELECT * FROM Proprietar;

INSERT INTO Chirias(nume_chirias, prenume_chirias, gen_chirias, data_nastare, idProprietar) VALUES
('Ruse', 'Teodor', 'M', '2003-12-02', 1),
('Paun', 'Paula', 'F', '1972-10-02', 2),
('Paun', 'Alex', 'M', '1975-05-01', 2),
('Toader', 'Larisa', 'F', '2009-01-01', 3),
('Trandafir', 'Bogdan', 'M', '2000-09-21', 4),
('Andrei', 'Costel', 'M', '1952-03-16', 4),
('Trandafir', 'Bogdan', 'M', '2000-09-21', 5);

SELECT * FROM Chirias;

INSERT INTO Casa(strada, numar, localitate, cod_postal, idProprietar) VALUES
('Drumul de centura', '152', 'Galati', 800248, 1),
('str. Teleorman', '55', 'ClujNapoca', 900234, 2),
('Bld. Dunarea', '7', 'Galati', 800894, 2),
('Calea Bucuresti', '290A', 'Iasi', 100546, 3),
('Strada Principala', '1C', 'Adam', 500432, 4),
('Bulevardul Galati', '390', 'Braila', 678904, 4),
('Str. Rizer', '1045', 'Timisoara', 445695, 5);

SELECT * FROM Casa;

INSERT INTO Mobilier(denumire, descriere, cantitate, pret) VALUES
('tv', 'blabvl', 2, 678.90),
('laptop', 'pt office', 1, 1950),
('frigider', 'mancare', 1, 6789),
('calorifer', 'caldura', 3, 450),
('dulap', 'haine', 1, 600.50),
('pat', 'pentru dormit', 2, 999.99);

SELECT * FROM Mobilier;

INSERT INTO Inventar(idCasa, idMobilier, data_achizitie, data_livrare) VALUES
(1, 1, '2024-03-29', '2024-04-05'),
(1, 5, '2024-03-29', '2024-04-05'),
(1, 6, '2024-03-29', '2024-04-05'),
(1, 3, '2024-03-29', '2024-04-05'),
(2, 3, '2024-03-29', '2024-04-05'),
(2, 5, '2024-03-29', '2024-04-05'),
(2, 6, '2024-03-29', '2024-04-05'),
(3, 3, '2024-03-29', '2024-04-05'),
(3, 6, '2024-03-29', '2024-04-05'),
(4, 1, '2024-03-29', '2024-04-05'),
(4, 3, '2024-03-29', '2024-04-05'),
(4, 5, '2024-03-29', '2024-04-05'),
(5, 2, '2024-03-29', '2024-04-05');

SELECT * FROM Inventar;

--- create procedure ---

CREATE OR ALTER PROCEDURE add_inventar
	@idCasa int,
	@idMobilier int,
	@data_achizitie DATE,
	@data_livrare DATE

AS
BEGIN
	if EXISTS(
		SELECT I.idCasa, I.idMobilier from Inventar as I
		INNER JOIN Casa on Casa.idCasa = I.idCasa
		INNER JOIN Mobilier on Mobilier.idMobilier = I.idMobilier
		WHERE I.idCasa = @idCasa
			AND I.idMobilier = @idMobilier)

	BEGIN
		UPDATE Inventar
		SET data_achizitie=@data_achizitie,
			data_livrare = @data_livrare
		WHERE idCasa = @idCasa
			AND idMobilier = @idMobilier;
	END

	else
		BEGIN
			INSERT INTO Inventar
			VALUES (@idCasa, @idMobilier, @data_achizitie, @data_livrare);
		END
END
GO

EXEC add_inventar 1,1,'2023-03-29','2023-05-09';
EXEC add_inventar 6,1,'2023-03-29','2023-05-09';
EXEC add_inventar 6,2,'2023-03-29','2023-05-09';
EXEC add_inventar 7,1,'2023-03-29','2023-05-09';

SELECT * FROM Inventar;

--- create view ---
CREATE OR ALTER VIEW View_Mobilier
AS
    SELECT
        M.denumire,
		COUNT(I.idCasa) AS nr_case
    FROM 
        Mobilier AS M
        INNER JOIN Inventar AS I ON M.idMobilier = I.idMobilier
    GROUP BY
        M.denumire
	HAVING
		COUNT(I.idCasa)<4

GO

SELECT * FROM View_Mobilier;