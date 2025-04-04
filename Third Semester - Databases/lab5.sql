USE MagazinulNaturii
GO

DELETE FROM Produs
DELETE FROM ProducatorFurnizor
DELETE FROM Producator
DELETE FROM Categorie
DELETE FROM Furnizor
DELETE FROM Client
DELETE FROM Adresa

--Not allow empty strings to be inserted
CREATE OR ALTER FUNCTION Validate_Parameter_Is_Not_Null(@sir VARCHAR(50))
	RETURNS INT
AS
BEGIN
	IF @sir IS NOT NULL
	BEGIN
		IF @sir=''
		BEGIN
			RETURN 0
		END
		RETURN 1
	END
	RETURN 0
END

CREATE OR ALTER FUNCTION Validate_Status(@status VARCHAR(50))
	RETURNS VARCHAR(50)
BEGIN
	IF @status IS NOT NULL
	BEGIN
		IF @status='Activ' OR @status='Inactiv' OR @status='Blocat'
		BEGIN
			RETURN @status
		END
		RETURN '0'
	END
	RETURN '0'
END

CREATE OR ALTER FUNCTION Validate_IdProducator(@IdProducator INT)
	RETURNS INT
BEGIN
	IF NOT EXISTS(SELECT * FROM Producator WHERE IdProducator=@IdProducator)
	BEGIN
		RETURN 0
	END
	RETURN @IdProducator
END

CREATE OR ALTER FUNCTION Validate_IdFurnzior(@IdFurnizor INT)
	RETURNS INT
BEGIN
	IF NOT EXISTS(SELECT * FROM Furnizor WHERE IdFurnizor=@IdFurnizor)
	BEGIN
		RETURN 0
	END
	RETURN @IdFurnizor
END

CREATE OR ALTER FUNCTION Validate_IdCategorie(@IdCategorie INT)
	RETURNS INT
BEGIN
	IF NOT EXISTS(SELECT * FROM Categorie WHERE IdCategorie=@IdCategorie)
	BEGIN
		RETURN 0
	END
	RETURN @IdCategorie
END

CREATE OR ALTER FUNCTION Validate_IdAdresa(@IdAdresa INT)
	RETURNS INT
BEGIN
	IF NOT EXISTS(SELECT * FROM Adresa WHERE IdAdresa=@IdAdresa)
	BEGIN
		RETURN 0
	END
	RETURN @IdAdresa
END

CREATE OR ALTER FUNCTION Validate_IdProducatorFurnizor(@IdProducator INT, @IdFurnizor INT)
	RETURNS INT
BEGIN
	IF EXISTS(SELECT * FROM ProducatorFurnizor WHERE (IdProducator=@IdProducator AND IdFurnizor=@IdFurnizor))
	BEGIN
		RETURN 0
	END
	RETURN 1
END

CREATE OR ALTER FUNCTION Validate_CantitateCheck(@Cantitate INT)
	RETURNS INT
BEGIN
	IF @Cantitate BETWEEN 1 AND 100
	BEGIN
		RETURN @Cantitate
	END
	RETURN 0
END

CREATE OR ALTER FUNCTION Validate_Pret(@Pret FLOAT)
	RETURNS INT
BEGIN
	IF @Pret BETWEEN 5 AND 1000
	BEGIN
		RETURN 1
	END
	RETURN 0
END

CREATE OR ALTER FUNCTION Validate_Data(@DataFabricare DATE, @DataExpirare DATE)
	RETURNS INT
BEGIN
	IF @DataFabricare IS NOT NULL AND @DataExpirare IS NOT NULL
		AND @DataFabricare < GETDATE() AND @DataFabricare < @DataExpirare
	BEGIN
		RETURN 1
	END
	RETURN 0
END

--validate Producator--
CREATE OR ALTER PROCEDURE Validate_Producator(@NumeProducator VARCHAR(50), 
									 @Tara VARCHAR(50), 
									 @Website VARCHAR(50))
AS
BEGIN
	--Declare a variable to accumulate error
	DECLARE @ErrorMessages NVARCHAR(MAX) = '';

	--Validating id Producator
	IF dbo.Validate_Parameter_Is_Not_Null(@NumeProducator)=0
	BEGIN
		SET @ErrorMessages +='Numele Producatorului nu poate sa fie vid!' + CHAR(13) + CHAR(10);
	END
	IF dbo.Validate_Parameter_Is_Not_Null(@Tara)=0
	BEGIN
		SET @ErrorMessages +='Tara nu poate sa fie vida!' + CHAR(13) + CHAR(10);
	END
	IF dbo.Validate_Parameter_Is_Not_Null(@Website)=0
	BEGIN
		SET @ErrorMessages +='Website-ul nu poate sa fie vid!' + CHAR(13) + CHAR(10);
	END
	IF @ErrorMessages <> ''
	BEGIN
		RAISERROR(@ErrorMessages, 16, 1);
		RETURN 0;
	END

	--No errors
	RETURN 1; 
END


--validate Furnizor--
CREATE OR ALTER PROCEDURE Validate_Furnizor(@NumeFurnizor VARCHAR(50),
									@StatusFInput VARCHAR(50),
									@ContBancar VARCHAR(50),
									@TipFurnizor VARCHAR(50),
									@StatusF VARCHAR(50) OUTPUT)
AS
BEGIN
	--Declare a variable to accumulate error
	DECLARE @ErrorMessages NVARCHAR(MAX) = '';

	--Validating id Producator
	IF dbo.Validate_Parameter_Is_Not_Null(@NumeFurnizor)=0
	BEGIN
		SET @ErrorMessages +='Numele Furnizorului nu poate sa fie vid!' + CHAR(13) + CHAR(10);
	END
	IF dbo.Validate_Parameter_Is_Not_Null(@ContBancar)=0
	BEGIN
		SET @ErrorMessages +='Contul Bancar al furnizorului nu poate sa fie vid!' + CHAR(13) + CHAR(10);
	END
	IF dbo.Validate_Parameter_Is_Not_Null(@TipFurnizor)=0
	BEGIN
		SET @ErrorMessages +='Tipul furnizorului nu poate sa fie vid!' + CHAR(13) + CHAR(10);
	END
	SET @StatusF = dbo.Validate_Status(@StatusFInput)
	IF @StatusF = '0'
	BEGIN
		SET @ErrorMessages +='Statusul este altul decat {Blocat, Inactiv, Activ}!' + CHAR(13) + CHAR(10);
	END
	IF @ErrorMessages <> ''
	BEGIN
		RAISERROR(@ErrorMessages, 16, 1);
		RETURN 0;
	END

	--No errors
	RETURN 1; 
END

--Validate ProducatorFurnizor
CREATE OR ALTER PROCEDURE Validate_ProducatorFurnizor(@IdProducatorInput INT, 
													  @IdFurnizorInput INT,
													  @CantitateInput INT,
													  @IdProducator INT OUTPUT, 
													  @IdFurnizor INT OUTPUT, 
													  @Cantitate INT OUTPUT)
AS
BEGIN
	DECLARE @ErrorMessages NVARCHAR(MAX) = '';

	--Validate IdProducator
	SET @IdProducator = dbo.Validate_IdProducator(@IdProducatorInput);
	IF @IdProducator = 0
	BEGIN
		SET @ErrorMessages += 'Id Producator este inexistent!' + CHAR(13) + CHAR(10);
	END
	SET @IdFurnizor = dbo.Validate_IdFurnzior(@IdFurnizorInput);
	IF @IdFurnizor = 0
	BEGIN
		SET @ErrorMessages += 'Id Furnizor este inexistent!' + CHAR(13) + CHAR(10);
	END
	IF dbo.Validate_IdProducatorFurnizor(@IdProducator, @IdFurnizor) = 0
	BEGIN 
		SET @ErrorMessages += 'Aceasta pereche de id exista deja!' + CHAR(13) + CHAR(10);
	END
	SET @Cantitate = dbo.Validate_CantitateCheck(@CantitateInput);
	IF @Cantitate = 0
	BEGIN 
		SET @ErrorMessages += 'Cantitate neacceptata!' + CHAR(13) + CHAR(10);
	END

	IF @ErrorMessages <> ''
	BEGIN
		RAISERROR(@ErrorMessages, 16, 1);
		RETURN 0;
	END
	RETURN 1;
END

--Validate Produs
CREATE OR ALTER PROCEDURE Validate_Produs(@NumeProdus VARCHAR(50),
										  @Pret FLOAT, 
										  @DataFabricare DATE,
										  @DataExpirare DATE,
										  @IdCategorieInput INT,
										  @IdProducatorInput INT,
								          @IdCategorie INT OUTPUT,
										  @IdProducator INT OUTPUT)
AS
BEGIN
	--Declare a variable to accumulate error
	DECLARE @ErrorMessages NVARCHAR(MAX) = '';

	--Validating id Producator
	IF dbo.Validate_Parameter_Is_Not_Null(@NumeProdus)=0
	BEGIN
		SET @ErrorMessages +='Numele Produsului nu poate sa fie vid!' + CHAR(13) + CHAR(10);
	END
	IF dbo.Validate_Pret(@Pret)=0
	BEGIN
		SET @ErrorMessages +='Pretul nu este valid!' + CHAR(13) + CHAR(10);
	END
	IF dbo.Validate_Data(@DataFabricare, @DataExpirare)=0
	BEGIN
		SET @ErrorMessages +='Datele nu sunt valide!' + CHAR(13) + CHAR(10);
	END
	SET @IdCategorie = dbo.Validate_IdCategorie(@IdCategorieInput)
	IF @IdCategorie = 0
	BEGIN
		SET @ErrorMessages +='Id Categorie nu este valid!' + CHAR(13) + CHAR(10);
	END
	SET @IdProducator = dbo.Validate_IdProducator(@IdProducatorInput)
	IF @IdProducator = 0
	BEGIN
		SET @ErrorMessages +='Id Producator nu este valid!' + CHAR(13) + CHAR(10);
	END
	IF @ErrorMessages <> ''
	BEGIN
		RAISERROR(@ErrorMessages, 16, 1);
		RETURN 0;
	END

	--No errors
	RETURN 1; 
END

--Validate Client
CREATE OR ALTER PROCEDURE Validate_Client(@NumeClient VARCHAR(50), 
										  @PrenumeClient VARCHAR(50),
										  @IdAdresaInput INT,
										  @IdAdresa INT OUTPUT)
AS
BEGIN
	--Declare a variable to accumulate error
	DECLARE @ErrorMessages NVARCHAR(MAX) = '';

	--Validating id Producator
	IF dbo.Validate_Parameter_Is_Not_Null(@NumeClient)=0
	BEGIN
		SET @ErrorMessages +='Numele Clientului nu poate sa fie vid!' + CHAR(13) + CHAR(10);
	END
	IF dbo.Validate_Parameter_Is_Not_Null(@PrenumeClient)=0
	BEGIN
		SET @ErrorMessages +='Prenumele Clientului nu poate sa fie vid!' + CHAR(13) + CHAR(10);
	END
	SET @IdAdresa = dbo.Validate_IdAdresa(@IdAdresaInput)
	IF @IdAdresa = 0
	BEGIN
		SET @ErrorMessages +='Id Adresa nu este valid!' + CHAR(13) + CHAR(10);
	END
	IF @ErrorMessages <> ''
	BEGIN
		RAISERROR(@ErrorMessages, 16, 1);
		RETURN 0;
	END

	--No errors
	RETURN 1; 
END


--CRUD operations--


---CRUD Producator---
CREATE OR ALTER PROCEDURE CRUD_Producator
	@NumeProducator VARCHAR(100),
	@Tara VARCHAR(100),
	@Website VARCHAR(100),
	@NoOfRows INT
AS
BEGIN
	SET NOCOUNT ON;

	--validate
	BEGIN TRY
	EXEC dbo.Validate_Producator @NumeProducator, @Tara, @Website;

	--insert
	DECLARE @i INT=0;
	WHILE @i<@NoOfRows
		BEGIN
			INSERT INTO Producator VALUES (@NumeProducator, @Tara, @Website);
			SET @i=@i+1;
		END

	--select
	SELECT * FROM Producator
	ORDER BY Producator.NumeProducator

	--update
	UPDATE Producator SET Producator.NumeProducator=@NumeProducator+'_CRUD'
	WHERE Producator.NumeProducator=@NumeProducator;

	--select 
	SELECT * FROM Producator
	ORDER BY Producator.NumeProducator

	--delete
	DELETE FROM Producator WHERE Producator.NumeProducator LIKE @NumeProducator+'_CRUD';

	--select
	SELECT * FROM Producator
	ORDER BY Producator.NumeProducator

	--stop
	PRINT 'Operatiile Crud realizate cu succes!'
	END TRY
BEGIN CATCH
	--Handle error
	PRINT 'A aparut o eroare: ' + ERROR_MESSAGE();
END CATCH
END

SELECT * FROM Producator
EXEC CRUD_Producator 'Sinapis', 'Romania', 'sinapis@gmail.com', 3

--Crud Furnizor
CREATE OR ALTER PROCEDURE CRUD_Furnizor
	@NumeFurnizor VARCHAR(50),
	@StatusFInput VARCHAR(50),
	@ContBancar VARCHAR(50),
	@TipFurnizor VARCHAR(50),
	@NoOfRows INT
AS
BEGIN
	SET NOCOUNT ON;

	DECLARE @StatusF VARCHAR(50);
	--validate
	BEGIN TRY
	EXEC dbo.Validate_Furnizor @NumeFurnizor, @StatusFInput, @ContBancar, @TipFurnizor, @StatusF OUTPUT;

	--insert
	DECLARE @i INT=0;
	WHILE @i<@NoOfRows
		BEGIN
			INSERT INTO Furnizor VALUES (@NumeFurnizor, @StatusF, @ContBancar, @TipFurnizor);
			SET @i=@i+1;
		END

	--select
	SELECT * FROM Furnizor
	ORDER BY Furnizor.NumeFurnizor

	--update
	UPDATE Furnizor SET Furnizor.NumeFurnizor=@NumeFurnizor+'*'
	WHERE Furnizor.StatusF LIKE 'Activ';

	--select 
	SELECT * FROM Furnizor
	ORDER BY Furnizor.NumeFurnizor

	--delete
	DELETE FROM Furnizor WHERE Furnizor.NumeFurnizor LIKE @NumeFurnizor+'*';

	--select
	SELECT * FROM Furnizor
	ORDER BY Furnizor.NumeFurnizor

	--stop
	PRINT 'Operatiile Crud realizate cu succes!'
	END TRY
BEGIN CATCH
	--Handle error
	PRINT 'A aparut o eroare: ' + ERROR_MESSAGE();
END CATCH
END

EXEC CRUD_Furnizor 'Furnizor1', 'Activ', '00001234', 'Regional', 3


--CRUD ProducatorFurnizor
CREATE OR ALTER PROCEDURE CRUD_ProducatorFurnizor(@IdProducatorInput INT, 
												  @IdFurnizorInput INT, 
												  @CantitateInput INT)
AS
BEGIN
	SET NOCOUNT ON;

	--validate
	DECLARE @IdProducator INT, @IdFurnizor INT, @Cantitate INT;
	BEGIN TRY
	EXEC dbo.Validate_ProducatorFurnizor @IdProducatorInput, @IdFurnizorInput, @CantitateInput,
										 @IdProducator OUTPUT, @IdFurnizor OUTPUT, @Cantitate OUTPUT  

	--insert
	INSERT INTO ProducatorFurnizor VALUES(@IdProducator, @IdFurnizor, @Cantitate);

	--select
	SELECT * FROM ProducatorFurnizor
	ORDER BY ProducatorFurnizor.Cantitate DESC

	--update
	UPDATE ProducatorFurnizor SET Cantitate=Cantitate+1
	WHERE ProducatorFurnizor.IdProducator = @IdProducator AND ProducatorFurnizor.IdFurnizor=@IdFurnizor;

	--select
	SELECT * FROM ProducatorFurnizor
	ORDER BY ProducatorFurnizor.Cantitate DESC

	--delete
	DELETE FROM ProducatorFurnizor WHERE ProducatorFurnizor.Cantitate=@Cantitate + 1;

	--select
	SELECT * FROM ProducatorFurnizor
	ORDER BY ProducatorFurnizor.Cantitate DESC

	PRINT 'Operatiile Crud realizate cu succes!'
	END TRY
	
	BEGIN CATCH
		PRINT 'A aparut o eroare' + ERROR_MESSAGE();
	END CATCH
END

INSERT INTO Producator VALUES('Sinapis', 'Romania', 'sinapis@gmail.com')
INSERT INTO Furnizor VALUES('BioFurnizor', 'Activ', '0012536729191', 'regional')

SELECT * FROM Producator
SELECT * FROM Furnizor

EXEC CRUD_ProducatorFurnizor 6, 5, 1

DELETE FROM Producator
DELETE FROM Furnizor

--CRUD ProducatorProdus
CREATE OR ALTER PROCEDURE CRUD_Produs(@NumeProdus VARCHAR(50), 
									  @Pret FLOAT, 
									  @DataFabricare DATE,
									  @DataExpirare DATE,
									  @IdCategorieInput INT,
									  @IdProducatorInput INT,
									  @NoOfRows INT)
AS
BEGIN
	SET NOCOUNT ON;

	--validate
	DECLARE @IdCategorie INT, @IdProducator INT;
	BEGIN TRY
	EXEC dbo.Validate_Produs @NumeProdus, @Pret, @DataFabricare, @DataExpirare, @IdCategorieInput, @IdProducatorInput,
							 @IdCategorie OUTPUT, @IdProducator OUTPUT

	--insert
	DECLARE @i INT=0
	WHILE @i<@NoOfRows
	BEGIN
		INSERT INTO Produs VALUES(@NumeProdus, @Pret, @DataFabricare, @DataExpirare, @IdCategorie, @IdProducator);
		SET @i=@i+1
	END
	--select
	SELECT * FROM Produs
	ORDER BY Produs.NumeProdus ASC

	--update
	UPDATE Produs SET Pret=Pret+15
	WHERE Produs.Pret = @Pret;

	--select
	SELECT * FROM Produs
	ORDER BY Produs.NumeProdus ASC

	--delete
	DELETE FROM Produs WHERE Produs.Pret=@Pret+15;

	--select
	SELECT * FROM Produs
	ORDER BY Produs.NumeProdus ASC

	PRINT 'Operatiile Crud realizate cu succes!'
	END TRY
	
	BEGIN CATCH
		PRINT 'A aparut o eroare' + ERROR_MESSAGE();
	END CATCH
END

INSERT INTO Producator VALUES('Sinapis', 'Romania', 'sinapis@gmail.com')
INSERT INTO Categorie VALUES('ProduseCosmetice');

SELECT * FROM Categorie
SELECT * FROM Producator

EXEC CRUD_Produs 'CremaHidratanta', 100.10, '2024-10-01', '2024-12-20', 2, 7, 10;

DELETE FROM Producator
DELETE FROM Categorie

--CRUD Client
CREATE OR ALTER PROCEDURE CRUD_Client(@NumeClient VARCHAR(50), 
									  @PrenumeClient VARCHAR(50), 
									  @IdAdresaInput INT,
									  @NoOfRows INT)
AS
BEGIN
	SET NOCOUNT ON;

	--validate
	DECLARE @IdAdresa INT;
	BEGIN TRY
	EXEC dbo.Validate_Client @NumeClient, @PrenumeClient, @IdAdresaInput,
							 @IdAdresa OUTPUT

	--insert
	DECLARE @i INT=0
	WHILE @i<@NoOfRows
	BEGIN
		INSERT INTO Client VALUES(@NumeClient, @PrenumeClient, @IdAdresa);
		SET @i=@i+1
	END
	--select
	SELECT * FROM Client
	ORDER BY Client.NumeClient ASC

	--update
	UPDATE Client SET NumeClient=NumeClient+'_CRUD'
	WHERE Client.NumeClient=@NumeClient;

	--select
	SELECT * FROM Client
	ORDER BY Client.NumeClient ASC

	--delete
	DELETE FROM Client WHERE Client.NumeClient LIKE @NumeClient+'_CRUD';

	--select
	SELECT * FROM Client
	ORDER BY Client.NumeClient ASC

	PRINT 'Operatiile Crud realizate cu succes!'
	END TRY
	
	BEGIN CATCH
		PRINT 'A aparut o eroare' + ERROR_MESSAGE();
	END CATCH
END

INSERT INTO Adresa VALUES('Cluj', 'Iernii', '19B', 567889);

SELECT * FROM Adresa

EXEC CRUD_Client 'Udila', 'Paul', 2, 5

DELETE FROM Adresa


--VIEWS

DELETE FROM Produs
INSERT INTO Producator(NumeProducator, Tara, Website) 
VALUES ('DoubleVegan', 'Bulgaria', 'doubleveg@gmail.bg');

INSERT INTO Categorie(Denumire) VALUES ('Vegane');

SELECT * FROM Categorie
SELECT * FROM Producator

INSERT INTO Produs(NumeProdus, Pret, DataFabricare, DataExpirare, IdCategorie, IdProducator)
VALUES ('BranzwaMigdale', 100.10, '2024-12-02', '2024-10-21', 3, 8),
	   ('WoontCaju', 80, '2024-11-11', '2024-10-10', 3, 8),
	   ('IawoortMigdale', 95, '2024-11-19', '2024-10-20', 3, 8),
	   ('BSuperfoodMusli', 60, '2024-09-10', '2024-12-10', 3, 8),
	   ('BStafideAurii', 30.50, '2024-09-09', '2024-12-08', 3, 8);

SELECT * FROM Produs
CREATE OR ALTER VIEW View_Produse 
AS
	SELECT IdProdus FROM Produs WHERE NumeProdus LIKE 'B%'

SELECT * FROM View_Produse

IF EXISTS (SELECT name FROM sys.indexes WHERE name = N'nidx_numeprodus') 
 DROP INDEX nidx_numeprodus ON Produs 
GO 
CREATE NONCLUSTERED INDEX nidx_numeprodus ON Produs(NumeProdus); 
GO

CREATE OR ALTER VIEW View_Client
AS
	SELECT IdClient FROM Client WHERE NumeClient LIKE 'A%'

SELECT * FROM View_Client
IF EXISTS (SELECT name FROM sys.indexes WHERE name = N'nidx_numeclient') 
 DROP INDEX nidx_numeclient ON Client 
GO 
CREATE NONCLUSTERED INDEX nidx_numeclient ON Client(NumeClient); 
GO


CREATE OR ALTER VIEW View_ProdusCategorie AS
SELECT 
    P.IdCategorie
FROM Categorie AS C INNER JOIN Produs AS P
ON C.IdCategorie = P.IdCategorie;

SELECT * FROM View_ProdusCategorie

IF EXISTS (SELECT name FROM sys.indexes WHERE name = N'nidx_idcat') 
 DROP INDEX nidx_idcat ON Produs
GO 
CREATE NONCLUSTERED INDEX nidx_idcat ON Produs(IdCategorie); 
GO
