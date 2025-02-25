;7.
;a) Sa se scrie o functie care testeaza daca o lista este liniara.
(defun test_lista_liniara (l)
	(cond
		((null l) t)
		((listp (car l)) nil)
		(t (test_lista_liniara (cdr l)))
	)
)
(print (test_lista_liniara '(1 2 3 6 9)))

;b) Definiti o functie care substituie prima aparitie a unui element intr-o lista data.
(defun prima_ap (l e1 e2 e)
	(cond
		((null l) nil)
		((and (equal (car l) e1) (equal e 0)) (cons e2 (prima_ap (cdr l) e1 e2 1)))
		(t (cons (car l) (prima_ap (cdr l) e1 e2 e)))
	)
)
(print (prima_ap '(1 2 8 7 2 6 2) '2 '10 '0))

;c) Sa se inlocuiasca fiecare sublista a unei liste cu ultimul ei element. Prin sublista se intelege element de pe primul nivel, care este lista.
;Exemplu: (a (b c) (d (e (f)))) ==> (a c (e (f))) ==> (a c (f)) ==> (a c f) (a (b c) (d ((e) f))) ==> (a c ((e) f)) ==> (a c f)


(defun ultim (l)
	(cond 
		((null l) nil)
		((atom l) l)
		((null (cdr l))
			(cond
				((listp (car l)) (ultim (car l)))
				(t (car l))
			)
		)
		(t (ultim (cdr l)))
	)
)
(print (ultim '(1 2 3)))

(defun inlocuire (l)
	(cond
		((null l) nil)
		((listp (car l)) (cons (ultim (car l)) (inlocuire (cdr l))))
		(t (cons (car l) (inlocuire (cdr l))))
	)
)
(print (inlocuire '(a (b c) (d (e (f))))))


;d) Definiti o functie care interclaseaza fara pastrarea dublurilor doua liste liniare sortate.
(defun interclasare (l1 l2)
	(cond
		((and (null l1) (null l2)) nil)
		((null l1) l2)
		((null l2) l1)
		((< (car l1) (car l2)) (cons (car l1) (interclasare (cdr l1) l2)))
		((< (car l2) (car l1)) (cons (car l2) (interclasare l1 (cdr l2))))
		((= (car l1) (car l2)) (cons (car l1) (interclasare (cdr l1) (cdr l2))))
	)
)

(print (interclasare '(12 21 33 69 70 290) '(31 40 69 70 200)))