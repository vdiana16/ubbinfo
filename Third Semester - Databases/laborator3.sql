USE MagazinulNaturii;
GO


CREATE TABLE Versiune
(
	IdVersiune INT DEFAULT 0 NOT NULL
);

--Schimb tipul coloanei NumeProdus din tabela Produs din VARCHAR in NVARCHAR pentru ca denumirea unui produs sa poata contine si diacritice
CREATE PROCEDURE modificTipColoana
AS
BEGIN
	ALTER TABLE Produs
	ALTER COLUMN NumeProdus NVARCHAR(100) NOT NULL;
	PRINT 'S-a modificat tipul coloanei NumeProdus din tabela Produs din VARCHAR in NVARCHAR'
END

--Schimb tipul coloanei NumeProdus din tabela Produs din NVARCHAR in VARCHAR
CREATE PROCEDURE undoModificTipColoana
AS
BEGIN
	ALTER TABLE Produs
	ALTER COLUMN NumeProdus VARCHAR(100) NOT NULL;
	PRINT 'S-a modificat tipul coloanei NumeProdus din tabela Produs din NVARCHAR in VARCHAR'
END

--Adaug constrangere de valoare implicita coloanei Cantitate din tabela Comanda
CREATE PROCEDURE adaugDefaultColoana
AS
BEGIN
	ALTER TABLE Comanda
	ADD CONSTRAINT DF_3 DEFAULT 3 FOR Cantitate;
	PRINT 'S-a adaugat constrangerea default pentru campul Cantitate din tabelul Comanda'
END

--Elimin constrangerea de valoare implicita aplicata coloanei Cantitate din tabela Comanda
CREATE PROCEDURE eliminDefaultColoana
AS
BEGIN
	ALTER TABLE Comanda
	DROP CONSTRAINT DF_3;
	PRINT 'S-a adaugat constrangerea default pentru campul Cantitate din tabelul Comanda'
END

--Creez tabela Recenzie pentru a afla parerea clientilor despre o comanda plasata
CREATE PROCEDURE adaugTabela
AS
BEGIN
	CREATE TABLE Recenzie(
		IdRecenzie INT PRIMARY KEY NOT NULL,
		Descriere TEXT NOT NULL,
		Nota INT DEFAULT 0 CHECK (Nota >= 1 AND NOTA <= 10),
		IdClient INT FOREIGN KEY REFERENCES Client(IdClient) ON UPDATE CASCADE ON DELETE CASCADE,
		IdProdus INT
	);
	PRINT 'S-a adaugat tabelul Recenzie'
END

--Sterg tabelul Recenzie
CREATE PROCEDURE stergTabela
AS
BEGIN
	DROP TABLE Recenzie;
	PRINT 'S-a sters tabelul Recenzie'
END


--Adaug campul Gramaj tabelei Produs
CREATE PROCEDURE adaugColoana
AS
BEGIN
	ALTER TABLE Produs 
	ADD Gramaj DECIMAL(10,2);
	PRINT 'S-a adaugat coloana Gramaj in tabelul Produs'
END

--Sterg campul Gramaj din tabela Produs
CREATE PROCEDURE stergColoana
AS
BEGIN
	ALTER TABLE Produs 
	DROP COLUMN Gramaj;
	PRINT 'S-a sters coloana Gramaj din tabelul Produs'
END

--Adaug constrangerea de cheie straina coloanei noi IdComanda in tabela Recenzie
CREATE PROCEDURE adaugCheieStraina
AS
BEGIN
	ALTER TABLE Recenzie
	ADD CONSTRAINT FK_Produs_Recenzie FOREIGN KEY(IdProdus) REFERENCES Produs(IdProdus);  
	PRINT 'S-a adaugat cheia straina IdComanda in tabela Recenzie'
END

--Sterg constrangerea de cheie straina din coloana noua IdComanda din tabela Recenzie
CREATE PROCEDURE stergCheieStraina
AS
BEGIN
	ALTER TABLE Recenzie
	DROP CONSTRAINT FK_Produs_Recenzie
	PRINT 'S-a sters cheia straina IdComanda in tabela Recenzie'
END

--DELETE FROM Versiune
INSERT INTO Versiune (IdVersiune) VALUES(0);

CREATE TABLE proceduraDirecta(
	IdProcDirecta INT PRIMARY KEY,
	NumeProcedura VARCHAR(150)
);

CREATE TABLE proceduraInversa(
	IdProcInversa INT PRIMARY KEY,
	NumeProcedura VARCHAR(150)
);


INSERT INTO proceduraDirecta (IdProcDirecta, NumeProcedura)
VALUES
		(1, 'modificTipColoana'),
		(2, 'adaugDefaultColoana'),
		(3, 'adaugTabela'),
		(4, 'adaugColoana'),
		(5, 'adaugCheieStraina');

INSERT INTO proceduraInversa (IdProcInversa, NumeProcedura)
VALUES
		(1, 'undoModificTipColoana'),
		(2, 'eliminDefaultColoana'),
		(3, 'stergTabela'),
		(4, 'stergColoana'),
		(5, 'stergCheieStraina');


CREATE OR ALTER PROCEDURE main
@VersiuneInput FLOAT

AS
BEGIN
	IF FLOOR(@VersiuneInput) <> CEILING(@VersiuneInput)
		BEGIN
		raiserror('Versiunea bazei de date consta intr-un numar intreg!', 17, 1);
		RETURN; 
		END

	DECLARE @VersiuneCeruta AS INT
	SET @VersiuneCeruta = FLOOR(@VersiuneInput)

	IF @VersiuneCeruta > 5
		BEGIN
			raiserror('Versiune indisponibila', 17, 1);
			RETURN;
		END

	DECLARE @VersiuneCurenta AS INT
	SELECT @VersiuneCurenta = IdVersiune from Versiune;

	PRINT 'Versiunea actuala este: ';
	PRINT @VersiuneCurenta;
	PRINT 'Versiunea ceruta este: ';
	PRINT @VersiuneCeruta;

	DECLARE @Functie AS VARCHAR(50);

	IF @VersiuneCurenta < @VersiuneCeruta
		BEGIN
			WHILE @VersiuneCurenta != @VersiuneCeruta
				BEGIN
					SELECT @Functie = numeProcedura FROM proceduraDirecta WHERE IdProcDirecta = @VersiuneCurenta + 1;
					EXEC @Functie;

					SET @VersiuneCurenta = @VersiuneCurenta + 1;
				END
			UPDATE Versiune
			SET IdVersiune = @VersiuneCurenta
		END
	
	ELSE IF @VersiuneCurenta > @VersiuneCeruta
		BEGIN
			WHILE @VersiuneCurenta != @VersiuneCeruta
				BEGIN
					SELECT @Functie = numeProcedura FROM proceduraInversa WHERE IdProcInversa = @VersiuneCurenta;
					EXEC @Functie;

					SET @VersiuneCurenta = @VersiuneCurenta - 1;
				END
			UPDATE Versiune
			SET IdVersiune = @VersiuneCurenta;
		END

	ELSE IF @VersiuneCurenta = @VersiuneCeruta
		BEGIN
			print 'Baza de date se afla deja in aceasta versiune';
			RETURN;
		END
END;

SELECT * FROM Versiune;
EXEC main @VersiuneInput = 0;
