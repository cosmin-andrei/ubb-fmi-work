USE Organizatie
go

--SET TRANSACTION ISOLATION LEVEL TO REPEATABLE READ
SET TRANSACTION ISOLATION LEVEL SERIALIZABLE --PROBLEM: LEVEL REPEATABLE READ
BEGIN TRAN
	SELECT * FROM Donator
	WAITFOR DELAY '00:00:10'
	SELECT * FROM Donator
COMMIT TRAN;

select * from Donator;