-- 1 CREATE TABLES
CREATE TABLE Pacient
(idPacient INT PRIMARY KEY IDENTITY,
nume_pacient varchar(50),
prenume_pacient varchar(50),
adresa_pacient varchar(50))

CREATE TABLE Specializare
(idSpecializare INT PRIMARY KEY IDENTITY,
denumire_specializare varchar(20))

CREATE TABLE Diagnostic
(idDiagnostic INT PRIMARY KEY IDENTITY,
denumire_diagnostic varchar(50),
descriere_diagnostic varchar(50))

CREATE TABLE Medic
(idMedic INT PRIMARY KEY IDENTITY,
nume_medic varchar(50),
prenume_medic varchar(50),
idSpecializare  INT FOREIGN KEY REFERENCES Specializare(idSpecializare))

CREATE TABLE Consult
(idConsult INT PRIMARY KEY IDENTITY,
idPacient INT FOREIGN KEY REFERENCES Pacient(idPacient),
idMedic INT FOREIGN KEY REFERENCES Medic(idMedic),
idDiagnostic INT FOREIGN KEY REFERENCES Diagnostic(idDiagnostic),
data_consult DATE NOT NULL,
ora_consult TIME NOT NULL CHECK(DATEPART(MINUTE, ora_consult) = 0 or DATEPART(MINUTE,ora_consult) = 30),
observatii varchar(50)
)

-- INSERT VALUES
INSERT INTO Pacient(nume_pacient, prenume_pacient, adresa_pacient) VALUES
('Andrei', 'Cosmin', 'Galati'),
('Popescu', 'Ion', 'Cluj'),
('Ion', 'Maria', 'Timisoara'),
('Bordea', 'Denisa', 'Iasi');

SELECT * FROM Pacient;

INSERT INTO Specializare(denumire_specializare) VALUES
('Ortopedie'),
('ORL'),
('ATI'),
('Neurologie'),
('Oftalmologie');

SELECT * FROM Specializare;

INSERT INTO Diagnostic(denumire_diagnostic, descriere_diagnostic) VALUES
('Cancer', 'descriere cancer'),
('Oopejfop', 'ochi umflat'),
('Otita', 'ureche umflata'),
('Entorsa', 'dupa cazatura'),
('Tumoare', 'durere de cap');

SELECT * FROM Diagnostic;

INSERT INTO Medic(nume_medic, prenume_medic, idSpecializare) VALUES
('Popescu', 'Mariana', 1),
('Bordeanu', 'Darius', 1),
('Filip', 'Sebastian', 1),
('Nedelcu', 'Maria', 2),
('Andrei', 'Maricica', 2),
('Stas', 'Marian', 3),
('State', 'Miruna',4),
('Dragus', 'Elisabeta', 4),
('Marian', 'Ionut', 4),
('Nicodim', 'Melisa', 4),
('Tirim', 'Rodica', 5),
('Mehedinti', 'Andrei', 5);

SELECT * FROM Medic;

INSERT INTO Consult(idPacient, idMedic, idDiagnostic, data_consult, ora_consult, observatii) VALUES
(1, 1, 2, '2024-01-06', '15:00', 'aa'),
(1, 1, 2, '2024-01-10', '15:00', 'aa'),
(1, 1, 2, '2024-02-06', '15:30', 'aa'),
(1, 1, 2, '2024-03-06', '16:00', 'aa'),
(1, 1, 2, '2024-04-06', '15:00', 'aa'),
(1, 1, 2, '2024-04-20', '18:00', 'aa'),
(1, 1, 2, '2024-04-25', '15:00', 'aa'),
(2, 1, 2, '2023-01-06', '10:00', 'aa'),
(2, 1, 2, '2023-02-06', '10:00', 'aa'),
(2, 1, 2, '2023-03-06', '10:00', 'aa'),
(2, 1, 2, '2023-04-06', '10:00', 'aa'),
(2, 1, 2, '2023-05-06', '10:00', 'aa'),
(2, 1, 2, '2023-06-06', '10:00', 'aa'),
(2, 1, 2, '2023-07-06', '10:00', 'aa'),
(2, 1, 2, '2023-08-06', '10:00', 'aa'),
(2, 1, 2, '2023-09-06', '10:00', 'aa'),
(2, 1, 2, '2023-10-06', '10:00', 'aa'),
(2, 1, 2, '2023-11-06', '10:00', 'aa'),
(2, 1, 2, '2023-12-06', '10:00', 'aa'),
(3, 2, 2, '2023-05-06', '10:00', 'aa');

SELECT * FROM Consult;

-- CREATE PROCEDURE --
CREATE OR ALTER PROCEDURE add_consult
	@idPacient int,
	@idMedic int,
	@idDiagnostic int,
	@data_consult DATE,
	@ora_consult TIME,
	@observatii varchar(50)

AS
BEGIN
	if EXISTS(
		SELECT C.idPacient, C.idMedic, C.data_consult from Consult as C
		INNER JOIN Pacient on Pacient.idPacient = C.idPacient
		INNER JOIN Medic on Medic.idMedic = C.idMedic
		WHERE C.data_consult = @data_consult
			AND C.idMedic = @idMedic
			AND C.idPacient = @idPacient)

	BEGIN
		UPDATE Consult
		SET idDiagnostic = @idDiagnostic,
			ora_consult = @ora_consult,
			observatii = @observatii
		WHERE idMedic = @idMedic 
			AND idPacient = @idPacient
			AND data_consult = @data_consult;
	END

	else
		BEGIN
			INSERT INTO Consult
			VALUES (@idPacient, @idMedic, @idDiagnostic, @data_consult, @ora_consult, @observatii);
		END
END
GO

-- teste procedure --
EXEC add_consult 1,1,1,'2024-12-02', '05:00','de refacut analize';
EXEC add_consult 1,1,2,'2024-12-02', '05:30','de refacut analize';

SELECT * FROM Consult;

-- create view --
CREATE OR ALTER VIEW View_Medici 
AS
	SELECT M.nume_medic, prenume_medic from Medic as M
	INNER JOIN Consult as C
	on C.idMedic = M.idMedic
	group by M.nume_medic, M.prenume_medic
	having COUNT(*) >=20;

GO

SELECT * FROM View_Medici;