;9.
;a) Sa se scrie o functie care intoarce diferenta a doua multimi.
(defun apare (l e)
	(cond
		((null l) nil)
		((equal (car l) e) t)
		(t (apare (cdr l) e))
	)
)

(defun diferenta_multimi (l1 l2)
	(cond
		((null l2) l1)
		((null l1) nil)
		((not (apare l2 (car l1))) (cons (car l1) (diferenta_multimi (cdr l1) l2)))
		(t (diferenta_multimi (cdr l1) l2))
	)
)
(print (diferenta_multimi '(1 2 3 4 5) '(1 3)))

;b) Definiti o functie care inverseaza o lista impreuna cu toate sublistele sale de pe orice nivel.
(defun inverseaza (l)
	(cond
		((null l) nil)
		((atom (car l)) (append (inverseaza (cdr l)) (list (car l))))
		(t (append (inverseaza (cdr l)) (list (inverseaza (car l)))))
	)
)
(print (inverseaza '(1 2 (3 4 5 (9 10) 9 10) 7 8)))

;c) Dandu-se o lista, sa se construiasca lista primelor elemente ale tuturor elementelor lista ce au un numar impar de elemente la nivel superficial.
;Exemplu: (1 2 (3 (4 5) (6 7)) 8 (9 10 11)) => (1 3 9).
(defun prim_element (l)
	(cond
		((null l) nil)
		((atom (car l)) (car l))
		((listp (car l)) (prim_element (car l)))
	)
)

(defun prim_el_impare (l)
	(cond 
		((null l) nil)
		((and (listp (car l)) (oddp (length (car l)))) (cons (prim_element (car l)) (prim_el_impare (cdr l))))
		(t (prim_el_impare (cdr l)))
	)
)

(defun main (l)
	(cond
		((oddp (length l)) (cons (prim_element l) (prim_el_impare (cdr l))))
		(t (prim_el_impare (cdr l)))
	)
)

(print (main '(1 2 ((4 7 5) 9 (6 7)) 8 (9 10 11))))

;d) Sa se construiasca o functie care intoarce suma atomilor numerici dintr-o lista, de la nivelul superficial.
(defun suma_atomi (l)
	(cond
		((null l) 0)
		((numberp (car l)) (+ (car l) (suma_atomi (cdr l))))
		(t (suma_atomi (cdr l)))
	)
)

(print (suma_atomi '(1 2 (6 A b) C 2 (11 30 (9)) 10)))