CREATE DATABASE Playlist;

USE Playlist;

CREATE TABLE Artist (
	
	id_artist int primary key identity,
	nume varchar(20)
);

CREATE TABLE Melodie (
	id_melodie int primary key identity,
	nume varchar(20),
	id_artist int foreign key references Artist(id_artist)
);

INSERT INTO Artist(nume) VALUES
('Alex Velea'),
('Andra');

SELECT * FROM Artist;

INSERT INTO Melodie(nume, id_artist) VALUES
('Yamasha', 1),
('Discret',1),
('Minim doi',1),
('Va fi bine',2),
('Falava',2);

SELECT * FROM Melodie;


CREATE TABLE ArtistMelodie(
	id int primary key identity,
	id_artist int foreign key references Artist(id_artist),
	id_melodie int foreign key references Melodie(id_melodie)
	);


create index indexMelodie on Melodie(nume);

select nume, id_artist from Melodie order by nume