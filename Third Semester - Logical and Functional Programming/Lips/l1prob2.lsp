;2.
;a) Definiti o functie care selecteaza al n-lea element al unei liste, sau  NIL, daca nu exista.

(defun selecteazan (l n)
	(cond
		((null l) nil)
		((= n 1) (car l))
		(t (selecteazan (cdr l) (- n 1)))
	)
)

(print (selecteazan '(1 2 (3 5) 6) 5))  ;=>nil

(defun liniarizare (l col)
	(cond
		((null l) col)
		((listp (car l)) (liniarizare (cdr l) (append col (liniarizare (car l) nil))))
		(t (liniarizare (cdr l) (append col (list (car l)))))
	)
)
(print (liniarizare '(1 2 (3 5) 6) '()))  

(defun selecteaza_n_lista_neliniara (l n)
	(selecteazan (liniarizare l nil) n)
)
(print (selecteaza_n_lista_neliniara '(1 2 (3 5) 6) 5))

;b) Sa se construiasca o functie care verifica daca un atom e membru al unei liste nu neaparat liniara.

(defun verific_ap (l a)
	(cond
		((null l) nil)
		((equal (car l) a) t)
		((listp (car l)) (or (verific_ap (cdr l) a) (verific_ap (car l) a)))
		(t (verific_ap (cdr l) a))
	)
)

(print (verific_ap '(1 2 A 3 (B 8 a (9))) '90))

;c) Sa se construiasca lista tuturor sublistelor unei liste. Prin sublista se intelege fie lista insasi, fie un element de pe orice nivel, care este 
;lista. Exemplu: (1 2 (3 (4 5) (6 7)) 8 (9 10)) => ( (1 2 (3 (4 5) (6 7)) 8 (9 10)) (3 (4 5) (6 7)) (4 5) (6 7) (9 10) ).
(defun subliste (l col)
	(cond 
		((null l) col)
		((listp (car l)) (subliste (cdr l) (append (list (car l)) (subliste (car l) col))))
		(t (subliste (cdr l) col))
	)
)
(defun subliste_princip (l)
	(subliste l (list l))
)

;apply 'append combina toate listele intr-o singura lista
;mapcar aplica functia pe fiecare element al listei, generand recursiv toate sublistele
(defun all_sublists(l)
    (
        cond
            ((atom l) nil)
            (T (apply 'append (list l) (mapcar 'all_sublists l)))
    )
)

(print (subliste_princip '(1 2 (3 (4 5) (6 7)) 8 (9 10))))
(print (all_sublists '(1 2 (3 (4 5) (6 7)) 8 (9 10))))


;d) Sa se scrie o functie care transforma o lista liniara intr-o multime.
(defun lista_multime (l col)
	(cond
		((null l) col)
		((verific_ap col (car l)) (lista_multime (cdr l) col))
		(t (lista_multime (cdr l) (append col (list (car l)))))
	)
)

(defun lista_multime_princip (l)
	(lista_multime l nil)
)

(print (lista_multime_princip '(1 2 3 1 5 7)))