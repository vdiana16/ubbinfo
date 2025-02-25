;5.
;a) Definiti o functie care interclaseaza cu pastrarea dublurilor doua liste liniare sortate.
(defun interclasare (a b)
	(cond
		((null a) b)
		((null b) a)
		((<= (car a) (car b)) (cons (car a) (interclasare (cdr a) b)))
		(t (cons (car b) (interclasare a (cdr b))))
	)
)

(print (interclasare '(1 6 9) '(1 2 7)))

;b) Definiti o functie care substituie un element E prin elementele unei liste L1 la toate nivelurile unei liste date L.
(defun substituie (l e l1)
	(cond
		((null l) nil)
		((listp (car l)) (append (list (substituie (car l) e l1)) (substituie (cdr l) e l1)))
		((equal e (car l)) (append l1 (substituie (cdr l) e l1)))
		(t (cons (car l) (substituie (cdr l) e l1))) 
	)
)

(print (substituie '(1 2 (10 9 8) 10 (11 22)) '10 '(11 21 23)))

;c) Definiti o functie care determina suma a doua numere in reprezentare de lista si calculeaza numarul zecimal corespunzator sumei.
;calculeaza cifra rezultata dintr-o pozitie de adunarea l-cifra din primul numar, k cifra din al doilea numar, c transportul
(defun cifra (l k c)
	(cond
		((null l) (mod (+ k c) 10))
		((null k) (mod (+ l c) 10))
		(t (mod (+ l k c) 10))
	)
)

;calculeaza transportul pentru urmatoarea pozitie
(defun carry (l k c)
	(cond
		((null l) (floor (+ k c) 10))
		((null k) (floor (+ l c) 10))
		(t (floor (+ l k c) 10))
	)
)

;aduna doua liste de cifre recursive tinand cont de transportul
(defun suma_liste (l k c)
	(cond
		((and (null l) (null k)) 
			(cond
				((= 1 c) (list 1))
				(t nil)
			)
		)
		(t (append (suma_liste (cdr l) (cdr k) (carry (car l) (car k) c)) (list (cifra (car l) (car k) c))))
	)
)

(defun invers (l col)
	(cond 
		((null l) col)
		(t (invers (cdr l) (cons (car l) col)))
	)
)

(defun calc_suma (l1 l2)
	(suma_liste (invers l1 ()) (invers l2()) 0)
)

(print (calc_suma '(1 2 3) '(1 9 9)))

;d) Definiti o functie care intoarce cel mai mare divizor comun al numerelor dintr-o lista liniara.
(defun cmmdc (a b)
	(cond 
		((= a 0) b)
		((= b 0) a)
		(t (cmmdc b (mod a b)))
	)
)

(defun cmmdc_lista (l)
	(cond 
		((null l) 0)
		(t (cmmdc (car l) (cmmdc_lista (cdr l))))
	)
)

(print (cmmdc_lista '(12 16 18 20 10)))