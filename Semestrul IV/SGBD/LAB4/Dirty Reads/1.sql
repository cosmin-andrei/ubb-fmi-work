-- DIRTY READS

BEGIN TRANSACTION
	UPDATE Donator SET
	email_donator='aaaa@gmail.com' WHERE nume_donator = 'Andrei111'
	WAITFOR DELAY '00:00:7'
ROLLBACK TRANSACTION
