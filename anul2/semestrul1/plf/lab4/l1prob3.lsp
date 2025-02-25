;3.
;a) Definiti o functie care intoarce produsul a doi vectori.
(defun produs_vectori (a b)
	(cond
		((or (null a) (null b)) nil)
		(t (+ (* (car a) (car b)) (produs_vectori (cdr a) (cdr b))))
	)
)
(print (produs_vectori '(1 2 3) '(4 5 6)))

;b) Sa se construiasca o functie care intoarce adancimea unei liste.
(defun adancime_lista (l)
	(cond
		((null l) 0)
		((not (listp l)) 0)
		(t (max (+ 1 (adancime_lista (car l))) (adancime_lista (cdr l))))
	)
)
(print (adancime_lista '(1 2 (6 8) (7 (1 2) 0))))

;c) Definiti o functie care sorteaza fara pastrarea dublurilor o lista liniara.
(defun my_merge (l m)
	(cond
		((null l) m)
		((null m) l)
		((< (car l) (car m)) (cons (car l) (my_merge (cdr l) m)))
		((< (car m) (car l)) (cons (car m) (my_merge l (cdr m))))
		(t (cons (car l) (my_merge (cdr l) (cdr m))))
	)
)

(defun divide (l r)
	(cond
		((null l) r)
		((null (cdr l)) (list (cons (car l) (car r)) (cadr r)))
		(t (divide (cddr l) (list (cons (car l) (car r)) (cons (cadr l) (cadr r)))))
	)
)

(defun merge_sort (l)
	(cond
		((null l) nil)
		((null (cdr l)) l)
		(t ((lambda (X) (my_merge (merge_sort (car X)) (merge_sort (cadr X))))
			 (divide l nil)
		   )
		)
	)
)

(print (merge_sort '(11 2 21 11 10 9 21 9 21)))

;d) Sa se scrie o functie care intoarce intersectia a doua multimi.
(defun apare (l e)
	(cond
		((null l) nil)
		((equal (car l) e) t)
		(t (apare (cdr l) e))
	)
)

(defun intersectie (a b)
	(cond 
		((or (null a) (null b)) nil)
		((apare b (car a)) (cons (car a) (intersectie (cdr a) b)))
		(t (intersectie (cdr a) b))
	)
)

(print (intersectie '(1 2 31) '(1 7 8 0 3 7 12)))
