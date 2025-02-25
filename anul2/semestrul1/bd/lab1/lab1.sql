DROP DATABASE MagazinulNaturii;

CREATE DATABASE MagazinulNaturii;
GO

USE MagazinulNaturii;
GO

CREATE TABLE Categorie(
	IdCategorie INT PRIMARY KEY,
	Denumire VARCHAR(50) NOT NULL UNIQUE
);

CREATE TABLE Producator(
	IdProducator INT PRIMARY KEY,
	NumeProducator VARCHAR(50) NOT NULL,
	Tara VARCHAR(50),
	Website VARCHAR(50) NOT NULL UNIQUE
);

CREATE TABLE Produs(
	IdProdus INT PRIMARY KEY,
	NumeProdus VARCHAR(100) NOT NULL,
	Pret DECIMAL(10,2) CHECK (Pret>0),
	DataFabricare DATE,
	DataExpirare DATE,
	IdCategorie INT FOREIGN KEY REFERENCES Categorie(IdCategorie),
	IdProducator INT FOREIGN KEY REFERENCES Producator(IdProducator)
);

CREATE TABLE Furnizor(
	IdFurnizor INT PRIMARY KEY,
	NumeFurnizor VARCHAR(50) NOT NULL,
	StatusF VARCHAR(50) NOT NULL,
	ContBancar VARCHAR(24),
	TipFurnizor VARCHAR(50)
);

CREATE TABLE FurnizorContact(
	IdContactFurnizor INT FOREIGN KEY REFERENCES Furnizor(IdFurnizor),
	NumarTelefon VARCHAR(20) NOT NULL,
	TipContact VARCHAR(50) DEFAULT 'Telefon',
	CONSTRAINT pk_Furnizor PRIMARY KEY(IdContactFurnizor)
);

CREATE TABLE ProducatorFurnizor(
	IdProducator INT FOREIGN KEY REFERENCES Producator(IdProducator),
	IdFurnizor INT FOREIGN KEY REFERENCES Furnizor(IdFurnizor),
	Cantitate INT DEFAULT 5 CHECK (Cantitate >= 0),
	CONSTRAINT pk_Producator_Furnizor PRIMARY KEY(IdProducator, IdFurnizor)
);

CREATE TABLE Adresa(
	IdAdresa INT PRIMARY KEY IDENTITY,
	Oras VARCHAR(100) NOT NULL,
	Strada VARCHAR(100),
	NumarStrada VARCHAR(10),
	CodPostal INT
);

CREATE TABLE Client(
	IdClient INT PRIMARY KEY,
	NumeClient VARCHAR(50) NOT NULL,
	PrenumeClient VARCHAR(50),
	IdAdresa INT FOREIGN KEY REFERENCES Adresa(IdAdresa)
);

CREATE TABLE Factura(
	IdFactura INT PRIMARY KEY,
	TotalFactura DECIMAL(10,2) CHECK (TotalFactura >= 0),
	StatusFact VARCHAR(50) NOT NULL
);

CREATE TABLE Comanda(
	IdProdus INT FOREIGN KEY REFERENCES Produs(IdProdus),
	IdClient INT FOREIGN KEY REFERENCES Client(IdClient),
	IdFactura INT FOREIGN KEY REFERENCES Factura(IdFactura),
	Cantitate INT,
	DataComanda DATE,
	StatusComanda VARCHAR(50) NOT NULL,
	CONSTRAINT pk_Comand PRIMARY KEY(IdProdus, IdClient, IdFactura)
);

CREATE TABLE Reducere(
	IdReducere INT PRIMARY KEY IDENTITY,
	IdProdus INT UNIQUE FOREIGN KEY REFERENCES Produs(IdProdus),
	DataIncepere DATE,
	DataFinalizare DATE,
	ProcentReducere INT CHECK (ProcentReducere >= 0 AND ProcentReducere <= 100)
);

CREATE TABLE TipReducere(
	IdTipReducere INT PRIMARY KEY IDENTITY,
 	IdReducere INT FOREIGN KEY REFERENCES Reducere(IdReducere),
	DenumireReducere VARCHAR(50) NOT NULL
);


-- Relatii:
--one-to-many: Categorie-Produs, Factura-Comanda, Client-Adresa, Producator-Produse
--many-to-many: Client-Produs, Producator-Furnizor
--one-to-one: Produse-Reducere, Reducere-TipReducere, Furnizor-DateContactFurnizor
