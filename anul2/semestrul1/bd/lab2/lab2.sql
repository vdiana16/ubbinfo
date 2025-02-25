USE MagazinulNaturii
GO

--tabele cu relatie m-n : interogariile 1-2
--cel putin 3 tabele: interogariile 3-9
--5 where: interogariile 2,3,4,5,7
--3 group by: interogariile 1,6,8
--2 distinct: interogariile 2,3
--2 having: interogariile 1,6

--1.Afiseaza clienții care au comandat cel putin 3 produse.
SELECT 
    C.NumeClient,
    C.PrenumeClient,
    COUNT(DISTINCT P.IdProdus) AS NumarProduseDistincte
FROM 
    Client C
INNER JOIN 
    Comanda Co ON C.IdClient = Co.IdClient
INNER JOIN 
    Produs P ON Co.IdProdus = P.IdProdus
GROUP BY 
    C.NumeClient, C.PrenumeClient
HAVING 
    COUNT(DISTINCT P.IdProdus) >= 3
ORDER BY 
    NumarProduseDistincte DESC;

--2.Afiseaza lista producătorilor a căror produse sunt distribuite de furnizorii activi
SELECT DISTINCT 
    F.NumeFurnizor,
	NumeProducator
FROM  
    Producator P
INNER JOIN 
    ProducatorFurnizor PF ON P.IdProducator = PF.IdProducator
INNER JOIN 
    Furnizor F ON PF.IdFurnizor = F.IdFurnizor
WHERE 
    F.StatusF = 'Activ';  

--3.Afiseaz numele clientilor care au comandat produse ce au un pret mai mare de 50, precum si adresele lor
SELECT DISTINCT
    C.NumeClient,
    C.PrenumeClient,
    A.Oras
FROM 
    Client C
INNER JOIN 
    Adresa A ON C.IdAdresa = A.IdAdresa
INNER JOIN 
    Comanda Co ON C.IdClient = Co.IdClient
INNER JOIN 
    Produs P ON Co.IdProdus = P.IdProdus
WHERE 
    P.Pret > 50;

--4.Afișează furnizorii care distribuie produsele la care au reduceri de peste 15%.
SELECT 
	F.NumeFurnizor, 
	P.NumeProdus,
	R.ProcentReducere AS Reducere
FROM 
	Furnizor F
INNER JOIN
	ProducatorFurnizor PF ON F.IdFurnizor = PF.IdFurnizor
INNER JOIN 
	Produs P ON PF.IdProducator = P.IdProducator
INNER JOIN 
	Reducere R ON P.IdProdus = R.IdProdus
WHERE 
	R.ProcentReducere > 15;

--5.Afiseaza lista comenzilor unui anumit client impreuna cu statusul facturii
SELECT
	Cl.NumeClient, 
	Cl.PrenumeClient, 
	P.NumeProdus,	
	C.DataComanda, 
	C.StatusComanda, 
	F.StatusFact
FROM 
	Client Cl
INNER JOIN 
	Comanda C ON Cl.IdClient = C.IdClient
INNER JOIN 
	Produs P ON C.IdProdus = P.IdProdus
INNER JOIN 
	Factura F ON C.IdFactura = F.IdFactura
WHERE
	Cl.IdClient = 1;

--6.Afiseaza listă cu produsele care au generat vânzări totale mai mari de 500, împreună cu totalul vânzărilor pentru fiecare produs.
SELECT 
    P.NumeProdus,
    SUM(F.TotalFactura) AS TotalVanzari
FROM 
    Produs P
INNER JOIN 
    Comanda Co ON P.IdProdus = Co.IdProdus
INNER JOIN 
    Factura F ON Co.IdFactura = F.IdFactura
GROUP BY 
    P.NumeProdus
HAVING 
    SUM(F.TotalFactura) > 500;

--7.Afiseaza comenziile livrate in perioada specificata
SELECT 
    c.NumeClient, 
    c.PrenumeClient, 
    p.NumeProdus, 
    co.DataComanda, 
    co.StatusComanda
FROM 
    Comanda co
JOIN 
    Client c ON co.IdClient = c.IdClient
JOIN 
    Produs p ON co.IdProdus = p.IdProdus
WHERE 
    co.DataComanda BETWEEN '2024-10-01' AND '2024-10-31'
    AND co.StatusComanda = 'Livrata';

--8.Afiseaza numele producătorului pentru fiecare produs din fiecare categorie.
SELECT 
    c.Denumire AS Categorie, 
    COUNT(p.IdProdus) AS NumărProduse,
    pr.NumeProducator
FROM 
    Categorie c
LEFT JOIN 
    Produs p ON c.IdCategorie = p.IdCategorie
LEFT JOIN 
    Producator pr ON p.IdProducator = pr.IdProducator
GROUP BY 
    c.Denumire, pr.NumeProducator;

SELECT * FROM Reducere
SELECT * FROM TipReducere
SELECT * FROM Comanda

--9.Afiseaza toate produsele care sunt în continuare la reducere in momentul plasarii comenzii
SELECT 
    p.NumeProdus,
    p.Pret,
    r.ProcentReducere,
    r.DataIncepere,
    r.DataFinalizare,
    c.DataComanda,
	(p.Pret * (1 - r.ProcentReducere / 100)) AS PretReducere
FROM 
    Produs p
INNER JOIN 
    Reducere r ON p.IdProdus = r.IdProdus
INNER JOIN 
    Comanda c ON p.IdProdus = c.IdProdus
WHERE 
    c.DataComanda BETWEEN r.DataIncepere AND r.DataFinalizare
ORDER BY 
    c.DataComanda DESC;

--10.Afiseaza produsele comandate intr-o data specificata
SELECT 
    c.NumeClient AS Nume_Client,
    c.PrenumeClient AS Prenume_Client,
    p.NumeProdus AS Nume_Produs,
    co.DataComanda AS Data_Comanda,
	f.NumarFactura AS NumarFactura,
    f.TotalFactura AS Total_Factura
FROM 
    Comanda co
JOIN 
    Produs p ON co.IdProdus = p.IdProdus
JOIN 
    Client c ON co.IdClient = c.IdClient
JOIN 
    Factura f ON co.IdFactura = f.IdFactura
WHERE 
    co.DataComanda = '2024-10-06'
ORDER BY 
    c.NumeClient, c.PrenumeClient;
