USE Organizatie
go

BEGIN TRANSACTION
	WAITFOR DELAY '00:00:07'
	INSERT INTO Donator(nume_donator, email_donator, telefon_donator) VALUES
	('ANDREEEEEEEE', 'andreee@gmail.com', '03727585');
COMMIT TRAN;

select * from Donator;
delete from Donator where nume_donator = 'ANDREEEEEEEE';