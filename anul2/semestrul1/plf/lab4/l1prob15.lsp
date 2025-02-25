;15.
;a) Sa se scrie o functie care intoarce reuniunea a doua multimi.
(defun apare (l e)
	(cond
		((null l) nil)
		((equal (car l) e) t)
		(t (apare (cdr l) e))
	)
)

(defun sterge (l e)
	(cond 
		((null l) nil)
		((equal e (car l)) (sterge (cdr l) e))
		(t (cons (car l) (sterge (cdr l) e)))
	)
)

(defun reuniune (a b)
	(cond
		((null a) b)
		((apare b (car a)) (cons (car a) (reuniune (cdr a) (sterge b (car a)))))
		(t (cons (car a) (reuniune (cdr a) b)))
	)
)

(print (reuniune '(1 2 3 10) '(15 10 1 2)))

;b) Sa se construiasca o functie care intoarce produsul atomilor numerici dintr-o lista, de la orice nivel.
(defun produs_atomi (l)
	(cond
		((null l) 1)
		((numberp (car l)) (* (car l) (produs_atomi (cdr l))))
		((listp (car l)) (* (produs_atomi (car l)) (suma_atomi (cdr l))))
		(t (produs_atomi (cdr l)))
	)
)

(print (produs_atomi '(1 2 (6 A b) C 2 (1 3 (2)) 10)))

;c) Definiti o functie care sorteaza cu pastrarea dublurilor o lista liniara.
(defun my_merge (l m)
	(cond
		((null l) m)
		((null m) l)
		((< (car l) (car m)) (cons (car l) (my_merge (cdr l) m)))
		((< (car m) (car l)) (cons (car m) (my_merge l (cdr m))))
		(t (cons (car l) (my_merge (cdr l) m)))
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

;d) Definiti o functie care construiește o listă cu pozițiile elementului minim dintr-o listă liniară numerică
(defun minim_lista (l min)
	(cond
		((null l) min)
		((and (numberp (car l)) (< (car l) min)) (minim_lista (cdr l) (car l)))
		(t (minim_lista (cdr l) min))
	)
)

(defun poz_min (l mini poz)
	(cond
		((null l) nil)
		((equal (car l) mini) (cons poz (poz_min (cdr l) mini (+ 1 poz))))
		(t (poz_min (cdr l) mini (+ 1 poz)))
	)
) 

(defun main (l)
	(poz_min l (minim_lista l '1000) '1)
)

(print (main '(2 21 11 10 9 2 2)))