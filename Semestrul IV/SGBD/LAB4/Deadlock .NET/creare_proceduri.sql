
CREATE OR ALTER PROCEDURE Donator_Donatie_Deadlock
AS
BEGIN
    SET DEADLOCK_PRIORITY HIGH;
    BEGIN TRANSACTION;
    UPDATE Donator
    SET email_donator = 'aaaaaaa@aaaaa.com'
    WHERE nume_donator = 'George Pop';

    WAITFOR DELAY '00:00:07';

    UPDATE Donatie
    SET suma_donatie = 1000
    WHERE id_donatie = 19;

    COMMIT TRANSACTION;
END;
GO


CREATE OR ALTER PROCEDURE Donatie_Donator_Deadlock
AS
BEGIN
    SET DEADLOCK_PRIORITY LOW;
    BEGIN TRANSACTION;
    UPDATE Donatie
    SET suma_donatie = 1001111110
    WHERE id_donatie = 19;

    WAITFOR DELAY '00:00:07';

    UPDATE Donator
    SET email_donator = 'george@org.ro'
    WHERE nume_donator = 'George Pop';

    COMMIT TRANSACTION;
END;
GO
