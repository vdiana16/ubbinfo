;13.
;a) Sa se intercaleze un element pe pozitia a n-a a unei liste liniare.
(defun poz_n (l n e)
	(cond
		((null l) nil)
		((equal n 1) (append (list e (car l)) (cdr l)))
		(t (cons (car l) (poz_n (cdr l) (- n 1) e)))
	)
)

(print (poz_n '(1 2 3 6 81) '3 '1902))

;b) Sa se construiasca o functie care intoarce suma atomilor numerici dintr-o lista, de la orice nivel.
(defun suma_atomi (l)
	(cond
		((null l) 0)
		((numberp (car l)) (+ (car l) (suma_atomi (cdr l))))
		((listp (car l)) (+ (suma_atomi (car l)) (suma_atomi (cdr l))))
		(t (suma_atomi (cdr l)))
	)
)

(print (suma_atomi '(1 2 (6 A b) C 2 (1 3 (2)) 10)))

;c) Sa se scrie o functie care intoarce multimea tuturor sublistelor unei liste date. Ex: Ptr. lista ((1 2 3) ((4 5) 6)) => ((1 2 3) (4 5) ((4 5) 6))
(defun liste (l)
	(cond
		((null l) nil)
		((listp (car l)) (append (list (car l)) (liste (car l)) (liste (cdr l))))
		(t (liste (cdr l)))
	)
)
(print (liste '((1 2 3) ((4 5) 6))))


;d) Sa se scrie o functie care testeaza egalitatea a doua multimi, fara sa se faca apel la diferenta a doua multimi.
(defun my_merge (l k)
	(cond 
		((null l) k)
		((null k) l)
		((<= (car l) (car k)) (cons (car l) (my_merge (cdr l) k)))
		((> (car l) (car k)) (cons (car k) (my_merge l (cdr k))))
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
		(t ((lambda (X) (my_merge (merge_sort (car X)) (merge_sort (cadr X)))) (divide l nil)))
	)
)

(defun egalitate (a b)
	(cond
		((and (null a) (null b)) t)
		((not (equal (length a) (length b))) nil)
		((= (car a) (car b)) (egalitate (cdr a) (cdr b)))
		(t nil)
	)
)

(defun main (a b)
	(egalitate (merge_sort a) (merge_sort b))
)

(print (main '(1 2 10 9 7) '(7 10 1 2 9)))