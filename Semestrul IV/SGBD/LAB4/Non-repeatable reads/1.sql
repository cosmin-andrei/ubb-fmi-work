-- non-repeatable reads

Use Playlist;

INSERT INTO Melodie(nume, id_artist) values ('Avioane de hartie', 2);

BEGIN TRANSACTION
	WAITFOR DELAY '00:00:07'
	UPDATE Melodie SET nume = 'Avioane hartiuta'
	WHERE  nume = 'Avioane de hartie'
COMMIT TRAN;

select * from Melodie;

delete from Melodie where nume = 'Avioane de hartie';
delete from Melodie where nume = 'Avioane hartiuta';