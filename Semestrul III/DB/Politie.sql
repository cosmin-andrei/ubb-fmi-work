CREATE DATABASE Politie;

-- create tables --
CREATE TABLE Sectie
(idSectie INT PRIMARY KEY IDENTITY,
denumire_sectie varchar(50) not null,
adresa_sectie varchar(50) not null);

CREATE TABLE Grad
(idGrad INT PRIMARY KEY IDENTITY,
denumire_grad varchar(50) not null
);

CREATE TABLE Politist
(idPolitist INT PRIMARY KEY IDENTITY,
nume_politist varchar(50) not null,
prenume_politist varchar(50) not null,
idSectie INT FOREIGN KEY REFERENCES Sectie(idSectie) not null,
idGrad INT FOREIGN KEY REFERENCES Grad(idGrad) not null
);

CREATE TABLE Sector
(idSector INT PRIMARY KEY IDENTITY,
denumire_sector varchar(50) not null
);

CREATE TABLE Programare
(idProgramare INT PRIMARY KEY IDENTITY,
idPolitist INT FOREIGN KEY REFERENCES Politist(idPolitist) not null,
idSector INT FOREIGN KEY REFERENCES Sector(idSector) not null,
data_intrare DATE not null,
ora_intrare TIME not null,
data_iesire DATE not null,
ora_iesire TIME not null
);


-- insert values --

INSERT INTO Sectie(denumire_sectie, adresa_sectie) VALUES
('Sectia 1', 'str. Cringasi'),
('Sectia 2', 'str. Crizantemelor'),
('Sectia 3', 'Str. Iasi'),
('Sectia 4', 'Calea Bucuresti');

SELECT * FROM Sectie;

INSERT INTO Grad(denumire_grad) VALUES
('Gradul1'),
('Gradul2'),
('Gradul3'),
('Gradul4'),
('Gradul5');

SELECT * FROM Grad;

INSERT INTO Politist(nume_politist, prenume_politist, idSectie, idGrad) VALUES
('Popescu', 'Marian', 1, 2),
('Popescu', 'Ionut', 1, 3),
('Andrei', 'Cosmin',1 ,5),
('Balea', 'Larian', 2, 1),
('Mucenic', 'Robert', 2, 1),
('Bordeanu', 'Darius', 3, 5),
('Arahide', 'Peanut', 3, 4),
('Bucuresti', 'Alin', 3, 2),
('Tonea', 'Raly', 4, 1),
('Tonciu', 'Andreea', 4, 2),
('Pop', 'Elena', 4, 5);

SELECT * FROM Politist;

INSERT INTO Sector(denumire_sector) VALUES
('Sector 1'),
('Sector 2'),
('Sector 3'),
('Sector 4');

SELECT * FROM Sector;

INSERT INTO Programare(idPolitist, idSector, data_intrare, ora_intrare, data_iesire, ora_iesire) VALUES
(1, 1, '2023-01-07', '08:00', '2023-01-07', '16:00'),
(1, 1, '2023-01-08', '08:00', '2023-01-08', '16:00'),
(1, 1, '2023-01-09', '08:00', '2023-01-09', '16:00'),
(1, 1, '2023-01-10', '08:00', '2023-01-10', '16:00'),
(1, 1, '2023-01-11', '08:00', '2023-01-11', '16:00'),
(1, 1, '2023-01-12', '08:00', '2023-01-12', '16:00'),
(2, 1, '2023-01-07', '16:00', '2023-01-07', '00:00'),
(2, 1, '2023-01-08', '16:00', '2023-01-08', '00:00'),
(2, 1, '2023-01-09', '16:00', '2023-01-09', '00:00'),
(2, 1, '2023-01-10', '16:00', '2023-01-10', '00:00'),
(2, 1, '2023-01-11', '16:00', '2023-01-11', '00:00'),
(2, 1, '2023-01-12', '16:00', '2023-01-12', '00:00'),
(3, 1, '2023-01-07', '00:00', '2023-01-08', '08:00'),
(3, 1, '2023-01-08', '00:00', '2023-01-09', '08:00'),
(3, 1, '2023-01-09', '00:00', '2023-01-10', '08:00'),
(3, 1, '2023-01-10', '00:00', '2023-01-11', '08:00'),
(3, 1, '2023-01-11', '00:00', '2023-01-12', '08:00'),
(4, 2, '2023-01-11', '00:00', '2023-01-12', '08:00'),
(4, 2, '2023-01-12', '00:00', '2023-01-13', '08:00'),
(5, 2, '2023-01-07', '08:00', '2023-01-07', '16:00'),
(5, 2, '2023-01-08', '08:00', '2023-01-09', '16:00'),
(6, 3, '2023-01-07', '08:00', '2023-01-08', '16:00'),
(6, 3, '2023-01-08', '08:00', '2023-01-09', '16:00'),
(6, 3, '2023-01-09', '08:00', '2023-01-10', '16:00');

SELECT * FROM Programare;


-- create procedure --

CREATE OR ALTER PROCEDURE add_programare
	@idPolitist int,
	@idSector int,
	@data_intrare DATE,
	@ora_intrare TIME,
	@data_iesire DATE,
	@ora_iesire TIME
AS
BEGIN
	if EXISTS(
		SELECT P.idPolitist, P.idSector, P.data_intrare from Programare as P
		INNER JOIN Politist on Politist.idPolitist = P.idPolitist
		INNER JOIN Sector on Sector.idSector = P.idSector
		WHERE P.data_intrare = @data_intrare
			AND P.idPolitist = @idPolitist
			AND P.idSector = @idSector)

	BEGIN
		UPDATE Programare
		SET ora_intrare=@ora_intrare,
			data_iesire = @data_iesire,
			ora_iesire = @ora_iesire
		WHERE idPolitist=@idPolitist
		AND idSector=@idSector
		AND data_intrare=@data_intrare;
	END

	else
		BEGIN
			INSERT INTO Programare
			VALUES (@idPolitist, @idSector, @data_intrare, @ora_intrare, @data_iesire, @ora_iesire);
		END
END
GO
	
EXEC add_programare 10,4,'2024-12-02','09:00','2024-12-02','17:00';

SELECT * FROM Programare;

-- create view --
CREATE OR ALTER VIEW View_Polististi
AS
    SELECT
        S.denumire_sectie,
        P.nume_politist,
        P.prenume_politist,
        COUNT(Pr.idPolitist) * 8 AS ore_lucrate
    FROM 
        Politist AS P
        INNER JOIN Sectie AS S ON S.idSectie = P.idSectie
        INNER JOIN Programare AS Pr ON Pr.idPolitist = P.idPolitist AND Pr.data_intrare BETWEEN '2023-01-01' AND '2023-01-31'
    GROUP BY
        S.denumire_sectie,
        P.nume_politist,
        P.prenume_politist;

GO

SELECT * FROM View_Polististi;

CREATE OR ALTER FUNCTION View_PolitistiProg
(
    @data_intrare DATE,
    @ora_intrare TIME
)
RETURNS TABLE
AS
RETURN
(
    SELECT
        P.nume_politist,
        P.prenume_politist,
        COUNT(Pr.idPolitist) AS nr_prog
    FROM
        Politist AS P
        INNER JOIN Programare AS Pr 
        ON Pr.idPolitist = P.idPolitist AND Pr.data_intrare = @data_intrare AND Pr.ora_intrare = @ora_intrare
    GROUP BY
        P.nume_politist,
        P.prenume_politist
);


SELECT * FROM View_PolitistiProg ('2023-01-07', '08:00');