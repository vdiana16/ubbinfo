;4.
;a) Definiti o functie care intoarce suma a doi vectori.
(defun suma_vectori (a b)
	(cond
		((or (null a) (null b)) nil)
		(t (cons (+ (car a) (car b)) (suma_vectori (cdr a) (cdr b))))
	)
)
(print (suma_vectori '(1 2 3) '(4 5 6)))

;b) Definiti o functie care obtine dintr-o lista data lista tuturor atomilor care apar, pe orice nivel, dar in aceeasi ordine. De exemplu:
;(((A B) C) (D E)) --> (A B C D E)
(defun extrage_atomi (l)
	(cond
		((null l) nil) 
		((atom (car l)) (cons (car l) (extrage_atomi (cdr l))))
		((listp (car l)) (append (extrage_atomi (car l)) (extrage_atomi (cdr l))))
		(t (extrage_atomi (cdr l)))
	)
)

(print (extrage_atomi '(((A B) C) (D E))))

;c) Sa se scrie o functie care plecand de la o lista data ca argument, inverseaza numai secventele continue de atomi. Exemplu:
;(a b c (d (e f) g h i)) ==> (c b a (d (f e) i h g))
(defun inverseaza_liste_cont (l col)
	(cond
		((null l) col)
		((atom (car l)) (inverseaza_liste_cont (cdr l) (cons (car l) col)))
		((listp (car l)) (append col (list (inverseaza_liste_cont (car l) ())) (inverseaza_liste_cont (cdr l) ())))
	)
)

(print (inverseaza_liste_cont '(a b c (d (e f) g h i)) ()))

;d) Sa se construiasca o functie care intoarce maximul atomilor numerici dintr-o lista, de la nivelul superficial.
(defun maxim (l maxi)
	(cond
		((null l) maxi)
		((and (numberp (car l)) (> (car l) maxi)) (maxim (cdr l) (car l)))
		(t (maxim (cdr l) maxi))
	)
)

(defun maxim_princip (l)
	(maxim l '-999)
)

(print (maxim_princip '(1 2 (5 (100) 10) 29 8 1 A)))