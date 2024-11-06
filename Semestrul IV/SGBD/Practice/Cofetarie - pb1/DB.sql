USE Cofetarie;

CREATE TABLE Laborator(
	id_laborator int primary key identity,
	nume varchar(20)
	);

CREATE TABLE Briosa(
	id_briosa int primary key identity,
	nume varchar(20),
	id_laborator int foreign key references Laborator(id_laborator)
	);

INSERT INTO Laborator(nume) VALUES
('Meri'),
('Pralina');

SELECT * FROM Laborator;

INSERT INTO Briosa(nume, id_laborator) VALUES
('Amandina', 1),
('Briosa', 1),
('Savarina',1),
('Kranz',2);

SELECT * FROM Briosa;