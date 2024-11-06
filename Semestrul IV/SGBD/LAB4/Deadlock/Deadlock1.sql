USE Organizatie;

SELECT * FROM Donator;
SELECT * FROM Donatie;

SET DEADLOCK_PRIORITY HIGH
-- SET DEADLOCK_PRIORITY LOW

BEGIN TRANSACTION
	update Donator set email_donator = 'aaaaaaa@aaaaa.com'
	where nume_donator = 'George Pop';

	WAITFOR DELAY '00:00:07';

	update Donatie set suma_donatie=1000
	where id_donatie = 19;

COMMIT TRAN;

SELECT * FROM Donator;
SELECT * FROM Donatie;

update Donatie set suma_donatie=1001111110
where id_donatie = 19;

update Donator set email_donator = 'george@org.ro'
where nume_donator = 'George Pop';