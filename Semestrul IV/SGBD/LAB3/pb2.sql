USE Organizatie
go


CREATE OR ALTER FUNCTION dbo.validareNume (@nume varchar(30)) RETURNS INT AS
BEGIN
	declare @return INT
	set @return = 1

	if @nume is null or @nume = ''
		set @return=0

	return @return
END
GO

CREATE OR ALTER FUNCTION dbo.validareEmail (@email varchar(30)) RETURNS INT AS
BEGIN
	DECLARE @return INT
	SET @return=1
	
	IF @email IS NULL or @email = ''
        SET @return = 0
    ELSE IF NOT @email LIKE '%_@__%.__%'
        SET @return = 0


	return @return
END
GO

CREATE OR ALTER FUNCTION dbo.validareTelefon(@telefon varchar(30)) RETURNS INT AS
BEGIN
	DECLARE @return INT
	SET @return=1

	IF @telefon is null or ISNUMERIC(@telefon)=0 or LEN(@telefon)<>10
		SET @return = 0

	return @return
END
GO

CREATE OR ALTER FUNCTION dbo.validareSuma(@suma int) RETURNS INT AS
BEGIN
	
	DECLARE @return INT
	SET @return=1

	IF @suma<0 or @suma=0
		SET @return = 0

	return @return
END
GO

CREATE OR ALTER FUNCTION dbo.validareData(@data varchar(30)) RETURNS INT AS
BEGIN

	DECLARE @return INT
	SET @return = 1

	IF @data is null or TRY_CONVERT(date, @data) IS NULL
		set @return = 0

	return @return
END
GO


CREATE OR ALTER PROCEDURE AddDonator
	@nume_donator varchar(30), @email varchar(30), @telefon varchar(30)

AS BEGIN
BEGIN TRAN

BEGIN TRY

	if dbo.validareNume(@nume_donator) <> 1
		begin
			print 'Nume donator'
			raiserror('Nume donator invalid', 14, 1)
		end

	if dbo.validareEmail(@email) <> 1
		begin
			print 'Email donator'
			raiserror('Email invalid', 14, 1)
		end

	if dbo.validareTelefon(@telefon) <> 1
		begin
			print 'Telefon donator'
			raiserror('Telefon donator invalid', 14, 1)
		end


	INSERT INTO Donator(nume_donator, email_donator, telefon_donator) VALUES
	(@nume_donator, @email, @telefon)

	print 'Donator adaugat'

	COMMIT TRAN
	SELECT 'Transaction committed'

END TRY

BEGIN CATCH
	ROLLBACK TRAN
	print ERROR_MESSAGE();
	SELECT 'Transaction rollbacked'
	return 0
END CATCH

	return 1

END
GO



CREATE OR ALTER PROCEDURE AddDonatie
	@suma int, @data_donatie varchar(30)

AS BEGIN
BEGIN TRAN

BEGIN TRY

	if dbo.validareSuma(@suma) <> 1
		begin
			print 'Suma donatie'
			raiserror('Suma donatie invalida', 14, 1)
		end

	if dbo.validareData(@data_donatie) <> 1
		begin
			print 'Data donatie'
			raiserror('Data donatie invalida', 14, 1)
		end

	INSERT INTO Donatie(idONG, id_eveniment, suma_donatie, data_donatie) VALUES
	(1, 1, @suma, @data_donatie)

	print 'Donatie adaugata'

	COMMIT TRAN
	SELECT 'Transaction committed'

END TRY

BEGIN CATCH
	ROLLBACK TRAN
	print ERROR_MESSAGE();
	SELECT 'Transaction rollbacked'
	return 0
END CATCH

	return 1
END
GO


CREATE OR ALTER PROCEDURE AddTranzactie2
	@nume_donator varchar(30), @email varchar(30), @telefon varchar(30),
	@suma int, @data_donatie varchar(30)

AS BEGIN

	DECLARE @donatorStatus int;
	DECLARE @donatieStatus int;

	EXEC @donatorStatus = AddDonator @nume_donator, @email, @telefon;
	EXEC @donatieStatus = AddDonatie @suma, @data_donatie;

	if @donatorStatus <> 1
		BEGIN
			PRINT 'Donator not added'
			return 0
		END

	if @donatieStatus <> 1
		BEGIN
			PRINT 'Donatie not added'
			RETURN 0
		END

	declare @id_donator int;
	declare @id_donatie int;

	SELECT TOP 1 @id_donator = D.id_donator
	FROM dbo.Donator as D
	WHERE D.nume_donator = @nume_donator;

	SELECT TOP 1 @id_donatie = D.id_donatie
	FROM dbo.Donatie as D
	WHERE D.suma_donatie = @suma and D.data_donatie = @data_donatie;

	INSERT INTO Tranzactie VALUES (@id_donator, @id_donatie);

	PRINT 'Tranzactie adaugata'

END
go 

----VARIANTA CORECTA

CREATE OR ALTER PROCEDURE AddTranzactie3
	@nume_donator varchar(30), @email varchar(30), @telefon varchar(30),
	@suma int, @data_donatie varchar(30)

AS BEGIN

	DECLARE @donatorStatus INT
	DECLARE @donatieStatus INT
	SET @donatorStatus=1
	SET @donatieStatus = 1

BEGIN TRY
BEGIN TRAN

	if dbo.validareNume(@nume_donator) <> 1
		begin
			print 'Nume donator'
			raiserror('Nume donator invalid', 14, 1)
		end

	if dbo.validareEmail(@email) <> 1
		begin
			print 'Email donator'
			raiserror('Email invalid', 14, 1)
		end

	if dbo.validareTelefon(@telefon) <> 1
		begin
			print 'Telefon donator'
			raiserror('Telefon donator invalid', 14, 1)
		end


	INSERT INTO Donator(nume_donator, email_donator, telefon_donator) VALUES
	(@nume_donator, @email, @telefon)

	print 'Donator adaugat'

	COMMIT TRAN
	SELECT 'Transaction committed'

END TRY

BEGIN CATCH
	ROLLBACK TRAN
	print ERROR_MESSAGE();
	SELECT 'Transaction rollbacked'
	SET @donatorStatus = 0
END CATCH

BEGIN TRY
BEGIN TRAN

	if dbo.validareSuma(@suma) <> 1
		begin
			print 'Suma donatie'
			raiserror('Suma donatie invalida', 14, 1)
		end

	if dbo.validareData(@data_donatie) <> 1
		begin
			print 'Data donatie'
			raiserror('Data donatie invalida', 14, 1)
		end

	INSERT INTO Donatie(idONG, id_eveniment, suma_donatie, data_donatie) VALUES
	(1, 1, @suma, @data_donatie)

	print 'Donatie adaugata'

	COMMIT TRAN
	SELECT 'Transaction committed'

END TRY

BEGIN CATCH
	ROLLBACK TRAN
	print ERROR_MESSAGE();
	SELECT 'Transaction rollbacked'
	SET @donatieStatus = 0
END CATCH

BEGIN TRY
BEGIN TRAN
	if @donatorStatus <> 1
		BEGIN
			PRINT 'Donator not added'
			return 0
		END

	if @donatieStatus <> 1
		BEGIN
			PRINT 'Donatie not added'
			RETURN 0
		END

    declare @id_donator int;
	declare @id_donatie int;

	SELECT TOP 1 @id_donator = D.id_donator
	FROM dbo.Donator as D
	WHERE D.nume_donator = @nume_donator;

	SELECT TOP 1 @id_donatie = D.id_donatie
	FROM dbo.Donatie as D
	WHERE D.suma_donatie = @suma and D.data_donatie = @data_donatie;

	INSERT INTO Tranzactie VALUES (@id_donator, @id_donatie);

	PRINT 'Tranzactie adaugata'
	COMMIT TRAN
	SELECT 'Transaction committed'

END TRY
BEGIN CATCH
	ROLLBACK TRAN
	print ERROR_MESSAGE();
	SELECT 'Transaction rollbacked'
	RETURN 0
END CATCH

END
GO


SELECT * FROM Tranzactie;
SELECT * FROM Donator;
SELECT * FROM Donatie;

EXEC AddTranzactie3 '', 'aaaaa', 'orpe', '-5', '20 aaa';

SELECT * FROM Tranzactie;
SELECT * FROM Donator;
SELECT * FROM Donatie;

EXEC AddTranzactie3 'Andrei1122222111', 'andrei@onedu.ro','0773704567', '1001111110', '2027-12-20';

SELECT * FROM Tranzactie;
SELECT * FROM Donator;
SELECT * FROM Donatie;

