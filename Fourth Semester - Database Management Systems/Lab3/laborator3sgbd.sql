USE MagazinulNaturii;

--sistem de logare
CREATE TABLE LogTable
(
	LogTableId INT PRIMARY KEY IDENTITY(1, 1),
	TypeOperation VARCHAR(50),
	TableName VARCHAR(50),
	ExecutionTime DATETIME
);

--functii de validare

CREATE OR ALTER FUNCTION ValidareData(@Data VARCHAR(10))
RETURNS BIT
AS
BEGIN
	DECLARE @DataValida BIT = 0;
	
	IF ISDATE(@Data) = 1
		SET @DataValida = 1;

	RETURN @DataValida;
END
GO

CREATE OR ALTER FUNCTION ValidareValoare(@Valoare INT)
RETURNS BIT
AS
BEGIN
	DECLARE @ValoareValida BIT = 0;
	
	IF @Valoare >= 0
		SET @ValoareValida = 1;

	RETURN @ValoareValida;
END
GO

CREATE OR ALTER FUNCTION ValidareValoareReala(@Valoare FLOAT)
RETURNS BIT
AS
BEGIN
	DECLARE @ValoareValida BIT = 0;
	
	IF @Valoare >= 0
		SET @ValoareValida = 1;

	RETURN @ValoareValida;
END
GO

CREATE OR ALTER FUNCTION ValidareText(@Text VARCHAR(200))
RETURNS BIT
AS
BEGIN
	DECLARE @TextValid BIT = 0;
	
	IF @Text IS NOT NULL AND @Text <> ''
		SET @TextValid = 1;

	RETURN @TextValid;
END
GO

CREATE OR ALTER FUNCTION ValidareDataFabricareExpirare(@DataFabricare DATE, @DataExpirare DATE)
RETURNS BIT
AS
BEGIN
	DECLARE @ProdusValid BIT = 0;
	IF (@DataExpirare IS NOT NULL AND @DataFabricare IS NOT NULL)
	BEGIN
		IF (@DataFabricare < @DataExpirare AND @DataExpirare > GETDATE())
			SET @ProdusValid = 1;
	END
	RETURN @ProdusValid ;
END

CREATE OR ALTER FUNCTION ValidareDataComanda(@DataComanda DATE)
RETURNS BIT
AS
BEGIN
	DECLARE @ComandaValida BIT = 0;
	IF (@DataComanda <= GETDATE())
	BEGIN
		SET @ComandaValida = 1;
	END
	RETURN @ComandaValida
END

CREATE OR ALTER FUNCTION ValidareStatusComanda(@Status VARCHAR(50))
RETURNS BIT
AS
BEGIN
	DECLARE @StatusValid BIT = 0;
	IF (@Status IN ('In curs de procesare', 'Preluata', 'Livrata'))
	BEGIN	
		SET @StatusValid = 1;
	END
	RETURN @StatusValid
END

--Validare parametrii tabele
CREATE OR ALTER FUNCTION ValidareParamProdus(@NumeProdus VARCHAR(50), @Pret FLOAT, @DataFabricare DATE, @DataExpirare DATE, @IdProducator INT)
RETURNS VARCHAR(150)
AS
BEGIN
	DECLARE @errorMess VARCHAR(150) = '';

	IF (dbo.ValidareText(@NumeProdus) = 0)
		SET @errorMess = @errorMess + 'Numele Produsului este nul!' + CHAR(13) + CHAR(10);

	IF (dbo.ValidareValoareReala(@Pret) = 0)
		SET @errorMess = @errorMess + 'Pretul este nul!' + CHAR(13) + CHAR(10);

	IF (dbo.ValidareData(@DataExpirare) = 0)
		SET @errorMess = @errorMess + 'Data Expirarii este nula!' + CHAR(13) + CHAR(10);

	IF (dbo.ValidareData(@DataFabricare) = 0)
		SET @errorMess = @errorMess + 'Data Fabricarii este nula!' + CHAR(13) + CHAR(10);

	IF (dbo.ValidareDataFabricareExpirare(@DataFabricare, @DataExpirare) = 0)
		SET @errorMess = @errorMess + 'Data Fabricarii sau Data Expirarii nu sunt corecte!' + CHAR(13) + CHAR(10);

	IF (NOT EXISTS(SELECT IdProducator FROM Producator WHERE IdProducator = @IdProducator))
		SET @errorMess = @errorMess + 'Producatorul nu este corect!' + CHAR(13) + CHAR(10);
	RETURN @errorMess;
END

CREATE OR ALTER FUNCTION ValidareParamClient(@NumeClient VARCHAR(50), @PrenumeClient VARCHAR(50), @IdAdresa INT)
RETURNS VARCHAR(150)
AS
BEGIN
	DECLARE @errorMess VARCHAR(150) = ''

	IF (dbo.ValidareText(@NumeClient) = 0)
		SET @errorMess = @errorMess + 'Numele Clientului este nul!' + CHAR(13) + CHAR(10);

	IF (dbo.ValidareText(@PrenumeClient) = 0)
		SET @errorMess = @errorMess + 'Prenumele Clientului este nul!' + CHAR(13) + CHAR(10);

	IF (NOT EXISTS(SELECT IdAdresa FROM Adresa WHERE IdAdresa = @IdAdresa))
		SET @errorMess = @errorMess + 'Adresa nu este corecta!' + CHAR(13) + CHAR(10);
	RETURN @errorMess;
END

CREATE OR ALTER FUNCTION ValidareParamComanda(@IdProdus INT, @IdClient INT, @Cantitate INT, @DataComanda DATE, @Status VARCHAR(50))
RETURNS VARCHAR(150)
AS
BEGIN
	DECLARE @errorMess VARCHAR(150) = '';
	IF (dbo.ValidareValoare(@Cantitate) = 0)
		SET @errorMess = @errorMess + 'Cantitatea nu este corecta!' + CHAR(13) + CHAR(10);

	IF (dbo.ValidareData(@DataComanda) = 0)
		SET @errorMess = @errorMess + 'Data comenzii este nula!' + CHAR(13) + CHAR(10);

	IF (dbo.ValidareDataComanda(@DataComanda) = 0)
		SET @errorMess = @errorMess + 'Data comenzii nu este corecta!' + CHAR(13) + CHAR(10);
	
	IF (dbo.ValidareStatusComanda(@Status) = 0)
		SET @errorMess = @errorMess + 'Statusul comenzii nu este corect!' + CHAR(13) + CHAR(10);

	IF (NOT EXISTS(SELECT IdProdus FROM Produs WHERE IdProdus = @IdProdus))
		SET @errorMess = @errorMess + 'Produsul nu este corect!' + CHAR(13) + CHAR(10);

	IF (NOT EXISTS(SELECT IdClient FROM Client WHERE IdClient = @IdClient))
		SET @errorMess = @errorMess + 'Clientul nu este corect!' + CHAR(13) + CHAR(10);

	IF (EXISTS (SELECT IdProdus, IdClient FROM Comanda WHERE IdProdus = @IdProdus AND IdClient = @IdClient))
		SET @errorMess = @errorMess + 'Comanda nu este corecta, pentru ca aceasta exista deja!' + CHAR(13) + CHAR(10);
	RETURN @errorMess;
END

DELETE FROM Comanda
DELETE FROM Produs
DELETE FROM Client

CREATE OR ALTER PROCEDURE InsertIntoTables
(
	@NumeProdus VARCHAR(100),
	@Pret FLOAT,
	@DataFabricare DATE,
	@DataExpirare DATE, 
	@IdProducator INT,
	@NumeClient VARCHAR(50),
	@PrenumeClient VARCHAR(50),
	@IdAdresa INT,
	@Cantitate INT,
	@DataComanda DATE,
	@Status VARCHAR(50)
)
AS 
BEGIN
	BEGIN TRAN
	BEGIN TRY

		DECLARE @errorMess VARCHAR(150) = ''

		SET @errorMess = dbo.ValidareParamProdus(@NumeProdus, @Pret, @DataFabricare, @DataExpirare, @IdProducator)
		IF (@errorMess != '')
		BEGIN
			PRINT 'Eroare parametrii Produs' + @errorMess
			RAISERROR(@errorMess, 14, 1)
		END

		INSERT INTO Produs(NumeProdus, Pret, DataFabricare, DataExpirare, IdProducator) VALUES (@NumeProdus, @Pret, @DataFabricare, @DataExpirare, @IdProducator)
		INSERT INTO LogTable(TypeOperation, TableName, ExecutionTime) VALUES ('INSERT', 'Produs', CURRENT_TIMESTAMP)

		SET @errorMess = dbo.ValidareParamClient(@NumeClient, @PrenumeClient, @IdAdresa)
		IF (@errorMess != '')
		BEGIN
			PRINT 'Eroare parametrii Client' + @errorMess
			RAISERROR(@errorMess, 14, 1)
		END

		INSERT INTO Client(NumeClient, PrenumeClient, IdAdresa) VALUES (@NumeClient, @PrenumeClient, @IdAdresa)
		INSERT INTO LogTable(TypeOperation, TableName, ExecutionTime) VALUES ('INSERT', 'Client', CURRENT_TIMESTAMP)

		DECLARE @IdProdus INT;
		DECLARE @IdClient INT;
		SET @IdProdus = (SELECT MAX(IdProdus) FROM Produs)
		SET @IdClient = (SELECT MAX(IdClient) FROM Client)
		SET @errorMess = dbo.ValidareParamComanda(@IdProdus, @IdClient, @Cantitate, @DataComanda, @Status)
		IF (@errorMess != '')
		BEGIN
			PRINT 'Eroare parametrii Comanda' + @errorMess
			RAISERROR(@errorMess, 14, 1)
		END

		INSERT INTO Comanda(IdProdus, IdClient, Cantitate, DataComanda, StatusComanda) VALUES (@IdProdus, @IdClient, @Cantitate, @DataComanda, @Status)
		INSERT INTO LogTable(TypeOperation, TableName, ExecutionTime) VALUES ('INSERT', 'Comanda', CURRENT_TIMESTAMP)

	COMMIT TRAN
		
		INSERT INTO LogTable(TypeOperation, TableName, ExecutionTime) VALUES ('TRANSACTION COMMITED', 'Tables', CURRENT_TIMESTAMP)
	SELECT 'Transaction committed'

	END TRY
	
	BEGIN CATCH
		ROLLBACK TRAN
			INSERT INTO LogTable(TypeOperation, TableName, ExecutionTime) VALUES ('TRANSACTION ROLLBACKED', 'Tables', CURRENT_TIMESTAMP)
		SELECT 'Transaction rollbacked'
	END CATCH
END
GO

--Teste cu succes
EXEC InsertIntoTables
	@NumeProdus = 'CeaideLavanda',
	@Pret = 15.50,
	@DataFabricare = '2025-03-20', 
	@DataExpirare = '2027-03-01',
	@IdProducator = 1,
	@NumeClient = 'Iasca', 
	@PrenumeClient = 'Irina',
	@IdAdresa = 1, 
	@Cantitate = 16, 
	@DataComanda = '2025-04-28', 
	@Status = 'In curs de procesare'
	
SELECT * FROM Produs
SELECT * FROM Client
SELECT * FROM Comanda

--Teste cu eroare
EXEC InsertIntoTables
	@NumeProdus = 'CeaideLavanda',
	@Pret = 15.50,
	@DataFabricare = '2025-03-20', 
	@DataExpirare = '2027-03-01',
	@IdProducator = 1,
	@NumeClient = 'Iasca', 
	@PrenumeClient = 'Irina',
	@IdAdresa = 1, 
	@Cantitate = 16, 
	@DataComanda = '2026-04-28',  --gresit
	@Status = 'In curs de procesare'
	
SELECT * FROM Produs
SELECT * FROM Client
SELECT * FROM Comanda

CREATE OR ALTER PROCEDURE InsertIntoTablesWithPossibleDataStorage
(
	@NumeProdus VARCHAR(100),
	@Pret FLOAT,
	@DataFabricare DATE,
	@DataExpirare DATE, 
	@IdProducator INT,
	@NumeClient VARCHAR(50),
	@PrenumeClient VARCHAR(50),
	@IdAdresa INT,
	@Cantitate INT,
	@DataComanda DATE,
	@Status VARCHAR(50)
)
AS 
BEGIN
	DECLARE @error INT = 0;

	BEGIN TRAN
	BEGIN TRY
		DECLARE @errorMess VARCHAR(150) = ''
		SET @errorMess = dbo.ValidareParamProdus(@NumeProdus, @Pret, @DataFabricare, @DataExpirare, @IdProducator)
		IF (@errorMess != '')
		BEGIN
			PRINT 'Eroare parametrii Produs' + @errorMess
			RAISERROR(@errorMess, 14, 1)
		END

		INSERT INTO Produs(NumeProdus, Pret, DataFabricare, DataExpirare, IdProducator) VALUES (@NumeProdus, @Pret, @DataFabricare, @DataExpirare, @IdProducator)
		INSERT INTO LogTable(TypeOperation, TableName, ExecutionTime) VALUES ('INSERT', 'Produs', CURRENT_TIMESTAMP)

	COMMIT TRAN 
		SELECT 'Transaction committed for table Produs'
		INSERT INTO LogTable(TypeOperation, TableName, ExecutionTime) VALUES ('TRANSACTION COMMITED', 'Produs', CURRENT_TIMESTAMP)
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		SELECT 'Transaction rollbacked for table Produs'
		SET @error = 1
		INSERT INTO LogTable(TypeOperation, TableName, ExecutionTime) VALUES ('TRANSACTION ROLLBACKED', 'Produs', CURRENT_TIMESTAMP)
	END CATCH
	
	BEGIN TRAN
	BEGIN TRY
		SET @errorMess = dbo.ValidareParamClient(@NumeClient, @PrenumeClient, @IdAdresa)
		IF (@errorMess != '')
		BEGIN
			PRINT 'Eroare parametrii Client' + @errorMess
			RAISERROR(@errorMess, 14, 1)
		END

		INSERT INTO Client(NumeClient, PrenumeClient, IdAdresa) VALUES (@NumeClient, @PrenumeClient, @IdAdresa)
		INSERT INTO LogTable(TypeOperation, TableName, ExecutionTime) VALUES ('INSERT', 'Client', CURRENT_TIMESTAMP)

	COMMIT TRAN 
		SELECT 'Transaction committed for table Client'
		INSERT INTO LogTable(TypeOperation, TableName, ExecutionTime) VALUES ('TRANSACTION COMMITED', 'Client', CURRENT_TIMESTAMP)
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		SELECT 'Transaction rollbacked for table Client'
		SET @error = 1
		INSERT INTO LogTable(TypeOperation, TableName, ExecutionTime) VALUES ('TRANSACTION ROLLBACKED', 'Client', CURRENT_TIMESTAMP)
	END CATCH

	IF (@error != 0)
		RETURN

	BEGIN TRAN
	BEGIN TRY
		DECLARE @IdProdus INT;
		DECLARE @IdClient INT;
		SET @IdProdus = (SELECT MAX(IdProdus) FROM Produs)
		SET @IdClient = (SELECT MAX(IdClient) FROM Client)
		SET @errorMess = dbo.ValidareParamComanda(@IdProdus, @IdClient, @Cantitate, @DataComanda, @Status)
		IF (@errorMess != '')
		BEGIN
			PRINT 'Eroare parametrii Comanda' + @errorMess
			RAISERROR(@errorMess, 14, 1)
		END

		INSERT INTO Comanda(IdProdus, IdClient, Cantitate, DataComanda, StatusComanda) VALUES (@IdProdus, @IdClient, @Cantitate, @DataComanda, @Status)
		INSERT INTO LogTable(TypeOperation, TableName, ExecutionTime) VALUES ('INSERT', 'Comanda', CURRENT_TIMESTAMP)

	COMMIT TRAN
		INSERT INTO LogTable(TypeOperation, TableName, ExecutionTime) VALUES ('TRANSACTION COMMITED', 'Comanda', CURRENT_TIMESTAMP)
	SELECT 'Transaction committed for table Comanda'

	END TRY
	
	BEGIN CATCH
		ROLLBACK TRAN
			INSERT INTO LogTable(TypeOperation, TableName, ExecutionTime) VALUES ('TRANSACTION ROLLBACKED', 'Comanda', CURRENT_TIMESTAMP)
		SELECT 'Transaction rollbacked for table Comanda'
		SET @error = 1
	END CATCH
END
GO

--Teste cu succes
EXEC InsertIntoTablesWithPossibleDataStorage
	@NumeProdus = 'Unt de cocos',
	@Pret = 15.50,
	@DataFabricare = '2025-03-16', 
	@DataExpirare = '2029-03-01',
	@IdProducator = 1,
	@NumeClient = 'Morar', 
	@PrenumeClient = 'Mara',
	@IdAdresa = 1, 
	@Cantitate = 20, 
	@DataComanda = '2025-04-23', 
	@Status = 'Livrata'
	
SELECT * FROM Produs
SELECT * FROM Client
SELECT * FROM Comanda

--Teste cu eroare
EXEC InsertIntoTablesWithPossibleDataStorage
	@NumeProdus = 'Unt de cocos',
	@Pret = 15.50,
	@DataFabricare = '2025-03-16', 
	@DataExpirare = '2029-03-01',
	@IdProducator = 1,
	@NumeClient = 'Morar', 
	@PrenumeClient = 'Mara',
	@IdAdresa = 1, 
	@Cantitate = 20, 
	@DataComanda = '2029-04-23', 
	@Status = 'Livrata'
	
SELECT * FROM Produs
SELECT * FROM Client
SELECT * FROM Comanda