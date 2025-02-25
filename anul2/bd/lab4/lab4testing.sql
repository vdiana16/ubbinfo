USE "MagazinulNaturii"
GO

CREATE OR ALTER PROCEDURE dropExistingProcedure(@tableName VARCHAR(100))
AS
	IF EXISTS (SELECT * FROM INFORMATION_SCHEMA.ROUTINES WHERE ROUTINE_NAME = @tableName)
	BEGIN
		EXEC ('DROP PROCEDURE ' + @tableName)
	END
GO

CREATE OR ALTER PROCEDURE dropExistingView(@viewName VARCHAR(100))
AS
	IF EXISTS (SELECT * FROM INFORMATION_SCHEMA.VIEWS WHERE TABLE_NAME = @viewName)
	BEGIN
		EXEC ('DROP VIEW ' + @viewName)
	END
GO

EXEC dropExistingProcedure 'populateTableCategorie'
EXEC dropExistingProcedure 'populateTableProducator'
EXEC dropExistingProcedure 'populateTableProdus'
EXEC dropExistingProcedure 'populateTableFurnizor'
EXEC dropExistingProcedure 'populateTableProducatorFurnizor'
EXEC dropExistingView 'CategorieView'
EXEC dropExistingView 'CategorieProdusView'
EXEC dropExistingView 'ProducatorFurnizorView'


CREATE OR ALTER PROCEDURE addToTables(@tableName VARCHAR(100))
AS
	IF @tableName NOT IN (SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES)
	BEGIN
		PRINT 'Acest tabel nu exista'
		RETURN
	END
	IF @tableName IN (SELECT Name FROM Tables)
	BEGIN
		PRINT 'Acest tabel exista deja in tabelul Tables'
		RETURN
	END
	INSERT INTO Tables (Name) VALUES (@tableName);
GO

CREATE OR ALTER PROCEDURE addToViews(@viewName VARCHAR(100))
AS
	IF @viewName NOT IN (SELECT TABLE_NAME FROM INFORMATION_SCHEMA.VIEWS)
	BEGIN
		PRINT 'Acest view nu exista'
		RETURN
	END
	IF @viewName IN (SELECT Name FROM Views)
	BEGIN
		PRINT 'Acest view exista deja in tabelul Views'
		RETURN
	END
	INSERT INTO Views (Name) VALUES (@viewName);
GO

CREATE OR ALTER VIEW CategorieView
AS
	SELECT 
		* 
	FROM 
		Categorie;
GO

CREATE OR ALTER VIEW CategorieProdusView
AS
	SELECT 
		c.Denumire, p.NumeProdus, p.Pret 
	FROM	
		Categorie c 
	INNER JOIN	
		Produs p 
	ON
		c.IdCategorie = p.IdCategorie;
GO

CREATE OR ALTER VIEW ProducatorFurnizorView
AS
	SELECT 
		p.IdProducator,
		p.NumeProducator,
		COUNT(DISTINCT f.IdFurnizor) AS TotalFurnizori,
		SUM(pf.Cantitate) AS TotalCantitate
	FROM 
		Producator p
	JOIN 
		ProducatorFurnizor pf ON p.IdProducator = pf.IdProducator
	JOIN 
		Furnizor f ON pf.IdFurnizor = f.IdFurnizor
	GROUP BY 
		p.IdProducator, p.NumeProducator
GO

CREATE OR ALTER PROCEDURE populateTableCategorie(@rows INT)
AS
BEGIN
	SET NOCOUNT ON;

	DECLARE @i INT = 1;
    DECLARE @Denumire NVARCHAR(100);

    WHILE @i <= @rows 
    BEGIN
        -- Creează dinamically Denumire pentru fiecare categorie
        SET @Denumire = CONCAT('Categorie', @i);

        -- Inserează în tabelul Categorie
        INSERT INTO Categorie (IdCategorie, Denumire) 
        VALUES (@i, @Denumire);

        SET @i = @i + 1;
    END

    PRINT CONCAT(@rows, ' randuri au fost inserate.');

	SET NOCOUNT OFF;
END
GO

CREATE OR ALTER PROCEDURE deleteTableCategorie(@rows INT)
AS
BEGIN
	SET NOCOUNT ON;

    -- Variabilă pentru a număra rândurile existente
    DECLARE @totalRows INT;

    -- Determină numărul total de rânduri din tabel
    SELECT @totalRows = COUNT(*) FROM Categorie;

    -- Verifică dacă există suficiente rânduri de șters
    IF @rows > @totalRows
    BEGIN
        PRINT 'Numărul de randuri de sters depaseste totalul randurilor din tabel.';
        RETURN;
    END

	DECLARE @i INT
	DECLARE @id INT
	
	SET @i = @rows
	WHILE @i > 0
	BEGIN
		SELECT TOP 1 @id = C.IdCategorie FROM Categorie C ORDER BY C.IdCategorie DESC
		DELETE FROM Categorie WHERE IdCategorie = @id
		SET @i = @i - 1
	END

    PRINT CONCAT(@rows, ' randuri au fost sterse.');

	SET NOCOUNT OFF;
END
GO

CREATE OR ALTER PROCEDURE populateTableProducator(@rows INT)
AS
BEGIN
	SET NOCOUNT ON;

    DECLARE @i INT = 1;
    DECLARE @NumeProducator NVARCHAR(100);
    DECLARE @Tara NVARCHAR(50);
    DECLARE @Website NVARCHAR(100);

    WHILE @i <= @rows
    BEGIN
        -- Creează variabile pentru fiecare coloană
        SET @NumeProducator = CONCAT('Producator', @i);
        SET @Tara = CONCAT('Tara', @i % 5 + 1);
        SET @Website = CONCAT('www.producator', @i, '.com');

        -- Inserează în tabelul Producator
        INSERT INTO Producator (IdProducator, NumeProducator, Tara, Website) 
        VALUES (@i, @NumeProducator, @Tara, @Website);

        SET @i = @i + 1;
    END

	PRINT CONCAT(@rows, ' randuri au fost inserate.');

	SET NOCOUNT OFF;
END
GO

CREATE OR ALTER PROCEDURE deleteTableProducator(@rows INT)
AS
BEGIN
	SET NOCOUNT ON;

    -- Variabilă pentru a număra rândurile existente
    DECLARE @totalRows INT;

    -- Determină numărul total de rânduri din tabel
    SELECT @totalRows = COUNT(*) FROM Producator;

    -- Verifică dacă există suficiente rânduri de șters
    IF @rows > @totalRows
    BEGIN
        PRINT 'Numărul de randuri de sters depaseste totalul randurilor din tabel.';
        RETURN;
    END

    DECLARE @i INT
	DECLARE @id INT
	
	SET @i = @rows
	WHILE @i > 0
	BEGIN
		SELECT TOP 1 @id = P.IdProducator FROM Producator P ORDER BY P.IdProducator DESC
		DELETE FROM Producator WHERE IdProducator = @id
		SET @i = @i - 1
	END


    PRINT CONCAT(@rows, ' rânduri au fost sterse.');

	SET NOCOUNT OFF;
END
GO

CREATE OR ALTER PROCEDURE populateTableProdus(@rows INT)
AS
BEGIN
    SET NOCOUNT ON;

    DECLARE @i INT = 1;
    DECLARE @fkCategorie INT;
    DECLARE @fkProducator INT;
    DECLARE @NumeProdus NVARCHAR(50);
    DECLARE @Pret DECIMAL(10, 2);
    DECLARE @DataFabricare DATE;
    DECLARE @DataExpirare DATE;

    WHILE @i <= @rows
	BEGIN
        -- Obține aleator un IdCategorie din tabelul Categorie
        SELECT TOP 1 @fkCategorie = IdCategorie
        FROM Categorie
        ORDER BY NEWID();

        -- Obține aleator un IdProducator din tabelul Producator
        SELECT TOP 1 @fkProducator = IdProducator
        FROM Producator
        ORDER BY NEWID();

        -- Generează valori pentru alte coloane
        SET @NumeProdus = CONCAT('Produs_', @i + 1);
        SET @Pret = ROUND((RAND() * 100) + 1, 2); -- Pret între 1 și 100
        SET @DataFabricare = DATEADD(DAY, -1 * (RAND() * 365), GETDATE());
        SET @DataExpirare = DATEADD(DAY, (RAND() * 365), @DataFabricare);

        -- Inserează rândul în tabelul Produs
        INSERT INTO Produs (IdProdus, NumeProdus, Pret, DataFabricare, DataExpirare, IdCategorie, IdProducator)
        VALUES (@i, @NumeProdus, @Pret, @DataFabricare, @DataExpirare, @fkCategorie, @fkProducator);

        -- Incrementarea contorului
        SET @i = @i + 1;
    END

	PRINT CONCAT(@rows, ' randuri au fost inserate.');

    SET NOCOUNT OFF;
END
GO

CREATE OR ALTER PROCEDURE deleteTableProdus(@rows INT)
AS
BEGIN
	SET NOCOUNT ON;

    -- Variabilă pentru a număra rândurile existente
    DECLARE @totalRows INT;

    -- Determină numărul total de rânduri din tabel
    SELECT @totalRows = COUNT(*) FROM Produs;

    -- Verifică dacă există suficiente rânduri de șters
    IF @rows > @totalRows
    BEGIN
        PRINT 'Numarul de randuri de sters depaseste totalul randurilor din tabel.';
        RETURN;
    END

    DECLARE @i INT
	DECLARE @id INT
	
	SET @i = @rows
	WHILE @i > 0
	BEGIN
		SELECT TOP 1 @id = Pro.IdProdus FROM Produs Pro ORDER BY Pro.IdProdus DESC
		DELETE FROM Produs WHERE IdProdus = @id
		SET @i = @i - 1
	END


    PRINT CONCAT(@rows, ' rânduri au fost sterse.');

	SET NOCOUNT OFF;
END
GO

CREATE OR ALTER PROCEDURE populateTableFurnizor(@rows INT)
AS
BEGIN
	SET NOCOUNT ON;

	DECLARE @i INT
    DECLARE @idFurnizor INT
    DECLARE @numeFurnizor VARCHAR(100)
    DECLARE @statusF VARCHAR(10)
    DECLARE @contBancar VARCHAR(20)
    DECLARE @tipFurnizor VARCHAR(20)
    
    SET @i = 1
    WHILE @i <= @rows
    BEGIN
        -- Setăm valorile variabilelor
        SET @idFurnizor = @i
        SET @numeFurnizor = 'Furnizor' + CAST(@i AS VARCHAR(100))
        SET @statusF = CASE WHEN @i % 2 = 0 THEN 'Activ' ELSE 'Inactiv' END
        SET @contBancar = 'RO' + RIGHT('00000000000000000000' + CAST(@i AS VARCHAR(20)), 20)
        SET @tipFurnizor = CASE (@i % 3) 
            WHEN 0 THEN 'Local'
            WHEN 1 THEN 'International'
            ELSE 'Regional'
        END
        
        -- Inserăm valorile în tabel
        INSERT INTO Furnizor(IdFurnizor, NumeFurnizor, StatusF, ContBancar, TipFurnizor)
        VALUES (
            @idFurnizor,
            @numeFurnizor,
            @statusF, 
            @contBancar, 
            @tipFurnizor
        );

        -- Incrementăm @i
        SET @i = @i + 1
    END

	PRINT CONCAT(@rows, ' randuri au fost inserate.');

	SET NOCOUNT OFF;
END
GO

CREATE OR ALTER PROCEDURE deleteTableFurnizor(@rows INT)
AS
BEGIN
    SET NOCOUNT ON;

	-- Variabilă pentru a număra rândurile existente
    DECLARE @totalRows INT;

    -- Determină numărul total de rânduri din tabel
    SELECT @totalRows = COUNT(*) FROM Furnizor;

    -- Verifică dacă există suficiente rânduri de șters
    IF @rows > @totalRows
    BEGIN
        PRINT 'Numarul de randuri de sters depaseste totalul randurilor din tabel.';
        RETURN;
    END

    DECLARE @i INT
	DECLARE @id INT
	
	SET @i = @rows
	WHILE @i > 0
	BEGIN
		SELECT TOP 1 @id = F.IdFurnizor FROM Furnizor F ORDER BY F.IdFurnizor DESC
		DELETE FROM Furnizor WHERE IdFurnizor = @id
		SET @i = @i - 1
	END

    PRINT CONCAT(@rows, ' randuri au fost sterse.');

	SET NOCOUNT OFF;
END
GO

CREATE OR ALTER PROCEDURE populateTableProducatorFurnizor(@rows INT)
AS
BEGIN
	SET NOCOUNT ON;

	DECLARE @prodId INT
	SET @prodId = 1
	DECLARE @prodCount INT
	SET @prodCount = (SELECT COUNT(*) FROM Producator)
	DECLARE @furnizorId INT
	SET @furnizorId = 1
	DECLARE @furnizorCount INT
	SET @furnizorCount = (SELECT COUNT(*) FROM Furnizor)
	DECLARE @rowsCount INT
	SET @rowsCount = @rows

	WHILE @prodId <= @prodCount AND @rows > 0
	BEGIN
		SET @furnizorId  = 1
		WHILE @furnizorId <= @furnizorCount AND @rows > 0
		BEGIN
			INSERT INTO ProducatorFurnizor(IdProducator, IdFurnizor, Cantitate)
			VALUES(
				@prodId,
				@furnizorId,
				CAST((RAND() * 100) AS INT) + 1
			);
			SET @furnizorId = @furnizorId + 1
			SET @rows = @rows - 1
		END
		SET @prodId = @prodId + 1
	END

	
	PRINT CONCAT(@rowsCount, ' randuri au fost inserate.');

	SET NOCOUNT OFF;
END
GO

CREATE OR ALTER PROCEDURE deleteTableProducatorFurnizor(@rows INT)
AS
BEGIN
    SET NOCOUNT ON;

    DECLARE @prodId INT
    SET @prodId = (SELECT MAX(IdProducator) FROM ProducatorFurnizor)  -- Începem de la cel mai mare ID
    DECLARE @prodCount INT
    SET @prodCount = (SELECT COUNT(*) FROM Producator)

    DECLARE @furnizorId INT
    SET @furnizorId = (SELECT MAX(IdFurnizor) FROM ProducatorFurnizor)  -- Începem de la cel mai mare ID
    DECLARE @furnizorCount INT
    SET @furnizorCount = (SELECT COUNT(*) FROM Furnizor)
	
	DECLARE @rowsCount INT
	SET @rowsCount = @rows

    WHILE @prodId >= 1 AND @rows > 0
    BEGIN
        SET @furnizorId = (SELECT MAX(IdFurnizor) FROM Furnizor)  -- Începem de la cel mai mare furnizor
        WHILE @furnizorId >= 1 AND @rows > 0
        BEGIN
            DELETE FROM ProducatorFurnizor
            WHERE IdProducator = @prodId AND IdFurnizor = @furnizorId;

            -- Actualizăm numărul de rânduri rămase
            SET @rows = @rows - 1

            -- Decrementăm furnizorul
            SET @furnizorId = @furnizorId - 1
        END
        
        -- Decrementăm producătorul
        SET @prodId = @prodId - 1
    END

    PRINT CONCAT(@rowsCount, ' randuri au fost sterse.');

    SET NOCOUNT OFF;
END
GO

CREATE OR ALTER PROCEDURE populateTable(@name VARCHAR(50), @rows INT)
AS
BEGIN
	IF @name = 'Categorie'
	BEGIN
		EXEC populateTableCategorie @rows
	END
	ELSE IF @name = 'Produs'
    BEGIN
        EXEC populateTableProducator @rows
        EXEC populateTableProdus @rows
    END
    ELSE IF @name = 'ProducatorFurnizor'
    BEGIN
        EXEC populateTableFurnizor @rows
        EXEC populateTableProducatorFurnizor @rows
    END
    ELSE
    BEGIN
        PRINT 'Tabelul nu exista'
    END
END
GO

CREATE OR ALTER PROCEDURE deleteTable(@name VARCHAR(50))
AS
BEGIN
    IF @name = 'Categorie'
    BEGIN
        DELETE FROM Categorie;
    END
    ELSE IF @name = 'Produs'
    BEGIN
        DELETE FROM Produs;
		DELETE FROM Producator;
    END
    ELSE IF @name = 'ProducatorFurnizor'
    BEGIN
		DELETE FROM ProducatorFurnizor;
		DELETE FROM Furnizor;
    END
    ELSE
    BEGIN
        PRINT 'Tabelul nu exista'
	END
END
GO

CREATE OR ALTER PROCEDURE selectView(@name VARCHAR(50))
AS
BEGIN
	IF @name = 'CategorieView'
		SELECT * FROM CategorieView
	IF @name = 'CategorieProdusView'
		SELECT * FROM CategorieProdusView
	IF @name = 'ProdusProducatorView'
		SELECT * FROM ProdusProducatorView
	ELSE
		PRINT 'Acest view nu exista'
END
GO

CREATE OR ALTER PROCEDURE addToTests(@testName VARCHAR(100))
AS
BEGIN
	IF @testName IN (SELECT Name FROM Tests)
	BEGIN
		PRINT 'Acest test exista deja in tabelul Tests'
		RETURN
	END
	INSERT INTO Tests(Name) VALUES (@testName);
END
GO

CREATE OR ALTER PROCEDURE connectTableToTest(@tableName VARCHAR(100),
	@testName VARCHAR(100),
	@rows INT,
	@pos INT)
AS
BEGIN
	IF @tableName NOT IN (SELECT Name FROM Tables)
	BEGIN
		PRINT 'Acest tabel nu este in tabela Tables'
		RETURN
	END
	IF @testName NOT IN (SELECT Name FROM Tests)
	BEGIN
		PRINT 'Acest test nu este in tabela Tests'
		RETURN
	END
	DECLARE @tableId INT
	DECLARE @testId INT
	SET @tableId = (SELECT TableID FROM Tables WHERE Name=@tableName)
	SET @testId = (SELECT TestID FROM Tests WHERE Name=@testName)
	IF EXISTS(SELECT * FROM TestTables WHERE TestID=@testId AND TableID=@tableId)
	BEGIN
		PRINT 'Conexiunea TestTable exista deja'
	END
	INSERT INTO TestTables VALUES(@testId, @tableId, @rows, @pos);
END
GO

CREATE OR ALTER PROCEDURE connectViewToTest(@viewName VARCHAR(100),
	@testName VARCHAR(100))
AS
BEGIN
	IF @viewName NOT IN(SELECT Name FROM Views)
	BEGIN
		PRINT 'Acest view nu este in tabela Views'
		RETURN
	END
	IF @testName NOT IN(SELECT Name FROM Tests)
	BEGIN
		PRINT 'Acest test nu este in tabela Tests'
		RETURN
	END
	DECLARE @viewId INT
	DECLARE @testId INT
	SET @viewId = (SELECT ViewID FROM Views WHERE Name=@viewName)
	SET @testId = (SELECT TestID FROM Tests WHERE Name=@testName)
	IF EXISTS(SELECT * FROM TestViews WHERE TestId=@testId AND ViewID=@viewId)
	BEGIN
		PRINT 'Conexiunea TestView exista deja'
	END
	INSERT INTO TestViews VALUES(@testId, @viewId);
END
GO

CREATE OR ALTER PROCEDURE runTest(@testName VARCHAR(100),
	@description VARCHAR(100))
AS
BEGIN
	IF @testName NOT IN (SELECT Name FROM TESTS)
	BEGIN
		PRINT 'Acest test nu este in tabelul Tests'
		RETURN
	END

	DECLARE @testStartTime DATETIME
	DECLARE @testRunId INT
	DECLARE @tableId INT
	DECLARE @table VARCHAR(100)
	DECLARE @rows INT
	DECLARE @pos INT
	DECLARE @command VARCHAR(100)
	DECLARE @command2 VARCHAR(100)
	DECLARE @tableInsertStartTime DATETIME
	DECLARE @tableInsertEndTime DATETIME
	DECLARE @testId INT
	DECLARE @view VARCHAR(100)
	DECLARE @viewId INT
	DECLARE @viewStartTime DATETIME
	DECLARE @viewEndTime DATETIME

	SET @testId = (SELECT TestId FROM Tests T WHERE T.Name = @testName)

	DECLARE tableCursor CURSOR SCROLL FOR 
	SELECT Tb.Name, Tb.TableId, Ttb.NoOfRows, Ttb.Position
	FROM Tables Tb INNER JOIN TestTables Ttb ON Tb.TableID = Ttb.TableID
	WHERE Ttb.TestID = @testId
	ORDER BY Ttb.Position ASC

	DECLARE viewCursor CURSOR SCROLL FOR
	SELECT V.Name, V.ViewId
	FROM Views V INNER JOIN TestViews Tv ON V.ViewID = Tv.ViewID
	WHERE Tv.TestID = @testId

	SET @testStartTime = SYSDATETIME()
	INSERT INTO TestRuns(Description, StartAt, EndAt) VALUES (@description, @testStartTime, @testStartTime)
	SET @testRunId = SCOPE_IDENTITY()

	OPEN tableCursor
	FETCH FIRST FROM tableCursor INTO @table, @tableId, @rows, @pos

	WHILE @@FETCH_STATUS = 0 
	BEGIN
		SET @command2 = 'deleteTable'
		EXEC('DELETE FROM ' + @table)
		EXEC(@command2 + ' ''' + @table + '''')
		FETCH tableCursor INTO @table, @tableId, @rows, @pos
	END

	FETCH LAST FROM tableCursor INTO @table, @tableId, @rows, @pos

	WHILE @@FETCH_STATUS = 0
	BEGIN
		SET @command = 'populateTable'
		IF @rows > 0 AND @command NOT IN (SELECT ROUTINE_NAME FROM INFORMATION_SCHEMA.ROUTINES)
		BEGIN
			PRINT @command + 'nu exista'
			RETURN
		END
		SET @tableInsertStartTime = SYSDATETIME()
		IF @rows > 0
		BEGIN
			EXEC(@command + ' ''' + @table + ''', ' + @rows)
		END
		SET @tableInsertEndTime = SYSDATETIME()
		INSERT INTO TestRunTables VALUES(@testRunId, @tableId, @tableInsertStartTime, @tableInsertEndTime)
		FETCH PRIOR FROM tableCursor INTO @table, @tableId, @rows, @pos
	END
	CLOSE tableCursor
	DEALLOCATE tableCursor

	OPEN viewCursor
	FETCH viewCursor INTO @view, @viewId

	WHILE @@FETCH_STATUS = 0 
	BEGIN
		SET @viewStartTime = SYSDATETIME()
		EXEC ('SELECT * FROM ' + @view)
		SET @viewEndTime = SYSDATETIME()
		INSERT INTO TestRunViews
		VALUES(@testRunId, @viewId, @viewStartTime, @viewEndTime)
		FETCH ViewCursor INTO @view, @viewId
	END
	CLOSE viewCursor
	DEALLOCATE viewCursor
	UPDATE TestRuns SET EndAt = SYSDATETIME() WHERE TestRunID = @testRunId;
END
GO

SELECT * FROM Tests;

EXEC addToTests 'MainTest1'
EXEC addToTests 'MainTest2'
EXEC addToTests 'MainTest3'
EXEC addToTests 'MainTest4'

EXEC addToTables 'Categorie'
EXEC addToTables 'Produs'
EXEC addToTables 'ProducatorFurnizor'

EXEC addToViews 'CategorieView'
EXEC addToViews 'CategorieProdusView'
EXEC addToViews 'ProducatorFurnizorView'

EXEC connectTableToTest 'ProducatorFurnizor', 'MainTest1', 10, 1
EXEC connectTableToTest 'Produs', 'MainTest1', 10, 2
EXEC connectTableToTest 'Categorie', 'MainTest1', 10, 3
EXEC connectViewToTest 'CategorieView', 'MainTest1'
EXEC connectViewToTest 'CategorieProdusView', 'MainTest1'
EXEC connectViewToTest 'ProducatorFurnizorView', 'MainTest1'


EXEC connectTableToTest 'ProducatorFurnizor', 'MainTest2', 10, 1
EXEC connectTableToTest 'Produs', 'MainTest2', 10, 2
EXEC connectTableToTest 'Categorie', 'MainTest2', 10, 3
EXEC connectViewToTest 'CategorieView', 'MainTest2'
EXEC connectViewToTest 'CategorieProdusView', 'MainTest2'
EXEC connectViewToTest 'ProducatorFurnizorView', 'MainTest2'

EXEC connectTableToTest 'ProducatorFurnizor', 'MainTest3', 100, 1
EXEC connectTableToTest 'Produs', 'MainTest3', 100, 2
EXEC connectTableToTest 'Categorie', 'MainTest3', 100, 3
EXEC connectViewToTest 'CategorieView', 'MainTest3'
EXEC connectViewToTest 'CategorieProdusView', 'MainTest3'
EXEC connectViewToTest 'ProducatorFurnizorView', 'MainTest3'

EXEC connectTableToTest 'ProducatorFurnizor', 'MainTest4', 100, 4
EXEC connectTableToTest 'Produs', 'MainTest4', 100, 5
EXEC connectTableToTest 'Categorie', 'MainTest4', 100, 6
EXEC connectViewToTest 'CategorieView', 'MainTest4'
EXEC connectViewToTest 'CategorieProdusView', 'MainTest4'
EXEC connectViewToTest 'ProducatorFurnizorView', 'MainTest4'

EXEC runTest 'MainTest1', 'Test1'

EXEC runTest 'MainTest2', 'Test2'


DELETE FROM ProducatorFurnizor;
DELETE FROM Furnizor;
DELETE FROM Produs;
DELETE FROM Producator;
DELETE FROM Categorie;

EXEC runTest 'MainTest3', 'Test3'

EXEC runTest 'MainTest4', 'Test4'
