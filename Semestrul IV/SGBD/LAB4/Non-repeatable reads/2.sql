-- non-repeatable reads

Use Organizatie;

SET TRANSACTION ISOLATION LEVEL REPEATABLE READ
-- SET TRANSACTION ISOLATION LEVEL READ COMMITTED
BEGIN TRAN
	SELECT * FROM Participant
	WAITFOR DELAY '00:00:10'
	SELECT * FROM Participant
COMMIT TRAN;

select * from Participant;