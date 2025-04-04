USE MagazinulNaturii
GO

DROP TABLE if exists TestRunTables
DROP TABLE if exists TestRunViews
DROP TABLE if exists TestRuns
DROP TABLE if exists TestTables
DROP TABLE if exists Tables
DROP TABLE if exists TestViews
DROP TABLE if exists Views
DROP TABLE if exists Tests
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunTables_Tables]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestRunTables] DROP CONSTRAINT FK_TestRunTables_Tables
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestTables_Tables]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestTables] DROP CONSTRAINT FK_TestTables_Tables
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunTables_TestRuns]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestRunTables] DROP CONSTRAINT FK_TestRunTables_TestRuns
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunViews_TestRuns]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestRunViews] DROP CONSTRAINT FK_TestRunViews_TestRuns
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestTables_Tests]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestTables] DROP CONSTRAINT FK_TestTables_Tests
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestViews_Tests]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestViews] DROP CONSTRAINT FK_TestViews_Tests
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunViews_Views]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestRunViews] DROP CONSTRAINT FK_TestRunViews_Views
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestViews_Views]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestViews] DROP CONSTRAINT FK_TestViews_Views
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[Tables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [Tables]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[TestRunTables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestRunTables]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[TestRunViews]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestRunViews]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[TestRuns]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestRuns]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[TestTables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestTables]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[TestViews]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestViews]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[Tests]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [Tests]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[Views]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [Views]
GO

CREATE TABLE [Tables] (
	[TableID] [int] IDENTITY (1, 1) NOT NULL ,
	[Name] [nvarchar] (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [TestRunTables] (
	[TestRunID] [int] NOT NULL ,
	[TableID] [int] NOT NULL ,
	[StartAt] [datetime] NOT NULL ,
	[EndAt] [datetime] NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [TestRunViews] (
	[TestRunID] [int] NOT NULL ,
	[ViewID] [int] NOT NULL ,
	[StartAt] [datetime] NOT NULL ,
	[EndAt] [datetime] NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [TestRuns] (
	[TestRunID] [int] IDENTITY (1, 1) NOT NULL ,
	[Description] [nvarchar] (2000) COLLATE SQL_Latin1_General_CP1_CI_AS NULL ,
	[StartAt] [datetime] NULL ,
	[EndAt] [datetime] NULL 
) ON [PRIMARY]
GO

CREATE TABLE [TestTables] (
	[TestID] [int] NOT NULL ,
	[TableID] [int] NOT NULL ,
	[NoOfRows] [int] NOT NULL ,
	[Position] [int] NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [TestViews] (
	[TestID] [int] NOT NULL ,
	[ViewID] [int] NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [Tests] (
	[TestID] [int] IDENTITY (1, 1) NOT NULL ,
	[Name] [nvarchar] (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [Views] (
	[ViewID] [int] IDENTITY (1, 1) NOT NULL ,
	[Name] [nvarchar] (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL 
) ON [PRIMARY]
GO

ALTER TABLE [Tables] WITH NOCHECK ADD 
	CONSTRAINT [PK_Tables] PRIMARY KEY  CLUSTERED 
	(
		[TableID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [TestRunTables] WITH NOCHECK ADD 
	CONSTRAINT [PK_TestRunTables] PRIMARY KEY  CLUSTERED 
	(
		[TestRunID],
		[TableID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [TestRunViews] WITH NOCHECK ADD 
	CONSTRAINT [PK_TestRunViews] PRIMARY KEY  CLUSTERED 
	(
		[TestRunID],
		[ViewID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [TestRuns] WITH NOCHECK ADD 
	CONSTRAINT [PK_TestRuns] PRIMARY KEY  CLUSTERED 
	(
		[TestRunID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [TestTables] WITH NOCHECK ADD 
	CONSTRAINT [PK_TestTables] PRIMARY KEY  CLUSTERED 
	(
		[TestID],
		[TableID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [TestViews] WITH NOCHECK ADD 
	CONSTRAINT [PK_TestViews] PRIMARY KEY  CLUSTERED 
	(
		[TestID],
		[ViewID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [Tests] WITH NOCHECK ADD 
	CONSTRAINT [PK_Tests] PRIMARY KEY  CLUSTERED 
	(
		[TestID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [Views] WITH NOCHECK ADD 
	CONSTRAINT [PK_Views] PRIMARY KEY  CLUSTERED 
	(
		[ViewID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [TestRunTables] ADD 
	CONSTRAINT [FK_TestRunTables_Tables] FOREIGN KEY 
	(
		[TableID]
	) REFERENCES [Tables] (
		[TableID]
	) ON DELETE CASCADE  ON UPDATE CASCADE ,
	CONSTRAINT [FK_TestRunTables_TestRuns] FOREIGN KEY 
	(
		[TestRunID]
	) REFERENCES [TestRuns] (
		[TestRunID]
	) ON DELETE CASCADE  ON UPDATE CASCADE 
GO

ALTER TABLE [TestRunViews] ADD 
	CONSTRAINT [FK_TestRunViews_TestRuns] FOREIGN KEY 
	(
		[TestRunID]
	) REFERENCES [TestRuns] (
		[TestRunID]
	) ON DELETE CASCADE  ON UPDATE CASCADE ,
	CONSTRAINT [FK_TestRunViews_Views] FOREIGN KEY 
	(
		[ViewID]
	) REFERENCES [Views] (
		[ViewID]
	) ON DELETE CASCADE  ON UPDATE CASCADE 
GO

ALTER TABLE [TestTables] ADD 
	CONSTRAINT [FK_TestTables_Tables] FOREIGN KEY 
	(
		[TableID]
	) REFERENCES [Tables] (
		[TableID]
	) ON DELETE CASCADE  ON UPDATE CASCADE ,
	CONSTRAINT [FK_TestTables_Tests] FOREIGN KEY 
	(
		[TestID]
	) REFERENCES [Tests] (
		[TestID]
	) ON DELETE CASCADE  ON UPDATE CASCADE 
GO

ALTER TABLE [TestViews] ADD 
	CONSTRAINT [FK_TestViews_Tests] FOREIGN KEY 
	(
		[TestID]
	) REFERENCES [Tests] (
		[TestID]
	),
	CONSTRAINT [FK_TestViews_Views] FOREIGN KEY 
	(
		[ViewID]
	) REFERENCES [Views] (
		[ViewID]
	)
GO


DROP PROCEDURE IF EXISTS addToViews
DROP PROCEDURE IF EXISTS addToTests
DROP PROCEDURE IF EXISTS addToTables
DROP PROCEDURE IF EXISTS connectTableToTest
DROP PROCEDURE IF EXISTS connectViewToTest
DROP PROCEDURE IF EXISTS runTest
GO

CREATE PROCEDURE addToTables(@tableName VARCHAR(100))
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

CREATE PROCEDURE addToViews(@viewName VARCHAR(100))
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

CREATE PROCEDURE addToTests(@testName VARCHAR(100))
AS
	IF @testName IN (SELECT Name FROM Tests)
	BEGIN
		PRINT 'Acest test exista deja in tabelul Tests'
		RETURN
	END
	INSERT INTO Tests(Name) VALUES (@testName);
GO

CREATE PROCEDURE connectTableToTest(@tableName VARCHAR(100),
	@testName VARCHAR(100),
	@rows INT,
	@pos INT)
AS
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
GO

CREATE PROCEDURE connectViewToTest(@viewName VARCHAR(100),
	@testName VARCHAR(100))
AS
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
GO

CREATE PROCEDURE runTest(@testName VARCHAR(100),
	@description VARCHAR(100))
AS
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
		EXEC('DELETE FROM ' + @table)
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
GO

IF EXISTS(SELECT * FROM INFORMATION_SCHEMA.ROUTINES WHERE ROUTINE_NAME = 'dropExistingProcedure') 
BEGIN
	DROP PROCEDURE dropExistingProcedure
END
GO

IF EXISTS(SELECT * FROM INFORMATION_SCHEMA.ROUTINES WHERE ROUTINE_NAME = 'dropExistingView')
BEGIN
	DROP PROCEDURE dropExistingView
END
GO

CREATE PROCEDURE dropExistingProcedure(@tableName VARCHAR(100))
AS
	IF EXISTS (SELECT * FROM INFORMATION_SCHEMA.ROUTINES WHERE ROUTINE_NAME = @tableName)
	BEGIN
		EXEC ('DROP PROCEDURE ' + @tableName)
	END
GO

CREATE PROCEDURE dropExistingView(@viewName VARCHAR(100))
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
EXEC dropExistingView 'ProdusProducatorView'

CREATE PROCEDURE populateTableCategorie(@rows INT)
AS
	DECLARE @i INT
	SET @i = 0
	WHILE @i < @rows 
	BEGIN
		INSERT INTO Categorie (IdCategorie, Denumire) 
		VALUES (
			@i, 
			'Categorie' + CAST(@i AS VARCHAR(100))
		);
		SET @i = @i + 1
	END
GO

CREATE PROCEDURE populateTableProducator(@rows INT)
AS
	DECLARE @i INT
	SET @i = 0
	WHILE @i < @rows
	BEGIN
		INSERT INTO Producator (IdProducator, NumeProducator, Tara, Website) 
		VALUES (
			@i,
			'Producator' + CAST(@i AS VARCHAR(100)), 
			'Tara' + CAST(@i % 5 + 1 AS VARCHAR(10)), 
			'www.producator' + CAST(@i AS VARCHAR(100)) + '.com'  
		);
		SET @i = @i + 1
	END
GO

CREATE PROCEDURE populateTableProdus(@rows INT)
AS
	DECLARE @i INT 
	SET @i = 0
	DECLARE @idcat INT
	SET @idcat = 0
	DECLARE @catCount INT
	SET @catCount = (SELECT COUNT(*) FROM Categorie)
	DECLARE @idprod INT
	DECLARE @prodCount INT
	SET @prodCount = (SELECT COUNT(*) FROM Producator)
	WHILE @idcat < @catCount AND @i < @rows
	BEGIN
		SET @idprod = 0
		WHILE @idprod < @prodCount AND @i < @rows
		BEGIN
			INSERT INTO Produs (IdProdus, NumeProdus, Pret, DataFabricare, DataExpirare, IdCategorie, IdProducator)
			VALUES (
				@i, 
				'Produs' + CAST(@i AS VARCHAR(100)), 
				CAST((RAND() * 100) AS INT) + 1,                 
				DATEADD(DAY, -(@i % 365), GETDATE()),                   
				DATEADD(DAY, (@i % 365), GETDATE()),                    
				@idcat,            
				@idprod
			);
			SET @i = @i + 1
			SET @idprod = @idprod + 1
		END
		SET @idcat = @idcat + 1
	END
GO

CREATE PROCEDURE populateTableFurnizor(@rows INT)
AS
	DECLARE @i INT
	SET @i = 0
	WHILE @i < @rows
	BEGIN
		INSERT INTO Furnizor(IdFurnizor, NumeFurnizor, StatusF, ContBancar, TipFurnizor)
		VALUES (
			@i,
			'Furnizor' + CAST(@i AS VARCHAR(100)),
			CASE WHEN @i % 2 = 0 THEN 'Activ' ELSE 'Inactiv' END, 
            'RO' + RIGHT('00000000000000000000' + CAST(@i AS VARCHAR(20)), 20), 
            CASE (@i % 3)                                      
                WHEN 0 THEN 'Local'
                WHEN 1 THEN 'International'
                ELSE 'Regional'
            END
		);
		SET @i = @i + 1
	END
GO

CREATE PROCEDURE populateTableProducatorFurnizor(@rows INT)
AS
	DECLARE @prodId INT
	SET @prodId = 0
	DECLARE @prodCount INT
	SET @prodCount = (SELECT COUNT(*) FROM Producator)
	DECLARE @furnizorId INT
	SET @furnizorId = 0
	DECLARE @furnizorCount INT
	SET @furnizorCount = (SELECT COUNT(*) FROM Furnizor)
	WHILE @prodId < @prodCount AND @rows > 0
	BEGIN
		SET @furnizorId  = 0
		WHILE @furnizorId < @furnizorCount AND @rows > 0
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
GO

CREATE VIEW CategorieView
AS
	SELECT 
		* 
	FROM 
		Categorie;
GO

CREATE VIEW CategorieProdusView
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

CREATE VIEW ProdusProducatorView
AS
	SELECT 
		p.NumeProducator, COUNT(pr.IdProdus) AS TotalProduse 
	FROM 
		Produs pr 
	INNER JOIN 
		Producator p 
	ON 
		pr.IdProducator=p.IdProducator
	GROUP BY 
		p.NumeProducator 
GO

IF EXISTS (SELECT * FROM INFORMATION_SCHEMA.ROUTINES WHERE ROUTINE_NAME = 'populateTable') 
BEGIN
	EXEC ('DROP PROCEDURE populateTable')
END
GO

CREATE PROCEDURE populateTable(@tableName VARCHAR(100), 
	@rows INT)
AS
	IF @tableName NOT IN (SELECT Name FROM Tables)
	BEGIN
		PRINT 'Acest tabel nu este in tabelul Tables'
		RETURN
	END
	
	DECLARE @i INT
	SET @i = 0
	PRINT 'Populare tabel ' + @tableName + ' cu ' + CAST(@rows AS VARCHAR(100)) + ' randuri'
	
	DECLARE @columns TABLE( 
		ColumnName VARCHAR(100),
		DataType VARCHAR(100),
		OrdinalPosition INT
	)

	INSERT INTO @columns
	SELECT COLUMN_NAME, DATA_TYPE, ORDINAL_POSITION FROM INFORMATION_SCHEMA.COLUMNS
	WHERE TABLE_NAME = @tableName

	DECLARE @columnsCount INT
	SET @columnsCount = (SELECT COUNT(*) FROM @columns)

	DECLARE @insertStatement VARCHAR(MAX)
	DECLARE @columnIndex INT

	WHILE @rows > 0
	BEGIN
		SET @columnIndex = 1
		SET @insertStatement = 'INSERT INTO ' + @tableName + ' VALUES ('

		WHILE @columnIndex <= @columnsCount 
		BEGIN
			IF (SELECT DataType FROM @columns WHERE OrdinalPosition = @columnIndex) = 'int' 
			BEGIN
				SET @insertStatement = @insertStatement + CAST(@rows AS VARCHAR(100))
			END

			IF (SELECT DataType FROM @columns WHERE OrdinalPosition = @columnIndex) = 'varchar' 
			BEGIN
				SET @insertStatement = @insertStatement + '''' + (SELECT ColumnName FROM @columns WHERE OrdinalPosition = @columnIndex) + CAST(@rows AS VARCHAR(100)) + ''''
			END

			IF (SELECT DataType FROM @columns WHERE OrdinalPosition = @columnIndex) = 'date' 
			BEGIN
				SET @insertStatement = @insertStatement + 'DATEADD(DAY, ' + CAST(@rows AS VARCHAR(100)) + ', GETDATE())'
			END

			IF @columnIndex < @columnsCount
			BEGIN
				SET @insertStatement = @insertStatement + ', '
			END

			SET @columnIndex = @columnIndex + 1
		END
		
		SET @insertStatement = @insertStatement + ')'
		SET @rows = @rows - 1

		EXEC(@insertStatement)
	END	
GO

DELETE FROM ProducatorFurnizor;
DELETE FROM Furnizor;
DELETE FROM Producator;
DELETE FROM Produs;
DELETE FROM Categorie;
GO

EXEC addToTables 'Categorie'
EXEC addToTables 'Producator'
EXEC addToTables 'Produs'
-- EXEC addToTables 'Furnizor'
-- EXEC addToTables 'ProducatorFurnizor'
EXEC addToViews 'CategorieView'
-- EXEC addToViews 'CategorieProdusView'
-- EXEC addToViews 'ProdusProducatorView'

EXEC addToTests 'MainTest1'

EXEC connectTableToTest 'Categorie', 'MainTest1', 10, 1
EXEC connectTableToTest 'Producator', 'MainTest1', 10, 2
EXEC connectTableToTest 'Produs', 'MainTest1', 10, 3
--EXEC connectTableToTest 'Furnizor', 'MainTest', 10, 4
--EXEC connectTableToTest 'ProducatorFurnizor', 'MainTest', 10, 5
EXEC connectViewToTest 'CategorieView', 'MainTest'
--EXEC connectViewToTest 'CategorieProdusView', 'MainTest'
--EXEC connectViewToTest 'ProdusProducatorView', 'MainTest'

EXEC runTest 'MainTest1', 'Test1'
EXEC runTest 'MainTest1', 'Test2'
EXEC runTest 'MainTest1', 'Test3'
EXEC runTest 'MainTest1', 'Test6'
GO

SELECT * FROM TestRunTables

SELECT * FROM Categorie
SELECT * FROM Producator
SELECT * FROM Produs

