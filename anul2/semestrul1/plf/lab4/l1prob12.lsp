;12.
;a) Definiti o functie care intoarce produsul scalar a doi vectori.
(defun produs_scalar (a b)
	(cond	
		((or (null a) (null b)) 0)
		(t (+ (* (car a) (car b)) (produs_scalar (cdr a) (cdr b))))
	)
)
(print (produs_scalar '(1 2 3) '(4 5 6)))

;b) Sa se construiasca o functie care intoarce maximul atomilor numerici dintr-o lista, de la orice nivel.
(defun maxim_lista (l max)
	(cond
		((null l) max)
		((and (numberp (car l)) (> (car l) max)) (maxim_lista (cdr l) (car l)))
		((listp (car l)) (maxim_lista (cdr l) (maxim_lista (car l) max)))
		(t (maxim_lista (cdr l) max))
	)
)

(defun maxim_lista_p (l)
	(maxim_lista l '-1)
)

(print (maxim_lista_p '(10 29 a b x (18 (29 A) 29) 17 11 10)))

;c) Sa se scrie o functie care intoarce lista permutarilor unei liste date.
(defun elimina (el l)
  (cond
    ((null l) nil)  ; Dacă lista este goală, întoarcem nil
    ((equal el (car l)) (cdr l))  ; Dacă elementul curent este egal cu elementul căutat, îl eliminăm
    (t (cons (car l) (elimina el (cdr l))))))

(defun permutari (l)
	(cond
		((null l) '(()))
		(t (apply 'append (mapcar (lambda (x)
									(mapcar (lambda (y) (cons x y)) (permutari (elimina x l))))
									l)))
	)
)

(print (permutari '(1 2 3)))

;d) Sa se scrie o functie care intoarce T daca o lista are numar par de elemente pe primul nivel si NIL in caz contrar, fara sa se numere elementele listei.
(defun par_pe_primul_nivel (l f)
  (cond
    ((and (= f 1) (null l)) t)  
	((and (= f 0) (null l)) nil)
    ((= f 1) (par_pe_primul_nivel (cdr l) 0))
	((= f 0) (par_pe_primul_nivel (cdr l) 1))
  )
) 
(print (par_pe_primul_nivel '(1 2 3 (8) 9) '1))