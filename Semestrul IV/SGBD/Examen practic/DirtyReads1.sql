USE S9;

SELECT * FROM InghetatePreferate;

BEGIN TRANSACTION
	UPDATE InghetatePreferate SET
	Categorie='only cioco' WHERE Denumire = 'Tort de ciocolata'
	WAITFOR DELAY '00:00:7'
ROLLBACK TRANSACTION