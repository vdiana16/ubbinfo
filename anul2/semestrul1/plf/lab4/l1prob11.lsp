;11.
;a) Sa se determine cel mai mic multiplu comun al valorilor numerice dintr-o lista neliniara.
(defun extrage_numere (l)
	(cond
		((null l) nil)
		((numberp (car l)) (cons (car l) (extrage_numere (cdr l))))
		((listp (car l)) (append (extrage_numere (car l)) (extrage_numere (cdr l))))
		(t (extrage_numere (cdr l)))
	)
)

(defun cmmdc (a b)
	(cond
		((equal a 0) b)
		((equal b 0) a)
		(t (cmmdc b (mod a b)))
	)
)

(defun cmmmc (a b)
	(floor (* a b) (cmmdc a b))
)

(defun cmmmc_lista (l mult)
	(cond 
		((null l) mult)
		(t (cmmmc_lista (cdr l) (cmmmc (car l) mult)))
	)
)

(defun main (l)
	(cmmmc_lista (extrage_numere l) 1)
)

(print (main '(1 10 (20 A) 50 b c)))

;b) Sa se scrie o functie care sa testeze daca o lista liniara formata din numere intregi are aspect de "munte"(o secvență se spune ca are aspect de 
;"munte" daca elementele cresc pana la un moment dat, apoi descresc. De ex. 10 18 29 17 11 10).
(defun desc (l)
	(cond 
		((null (cdr l)) t)
		((<= (car l) (cadr l)) nil)
		(t (desc (cdr l)))
	)
)

(defun cresc (l)
	(cond 
		((null (cdr l)) nil)
		((< (car l) (cadr l)) (cresc (cdr l)))
		((> (car l) (cadr l)) (desc (cdr l)))
		(t nil)
	)
)

(defun munte (l)
	(cond 
		((and (>= (length l) 2) (< (car l) (cadr l))) (cresc (cdr l)))
		(t nil)
	)
)

(print (munte '(10 18 29 17 11 10)))

;c) Sa se elimine toate aparitiile elementului numeric maxim dintr-o lista neliniara.
(defun maxim_lista (l max)
	(cond
		((null l) max)
		((and (numberp (car l)) (> (car l) max)) (maxim_lista (cdr l) (car l)))
		((listp (car l)) (maxim_lista (cdr l) (maxim_lista (car l) max)))
		(t (maxim_lista (cdr l) max))
	)
)

(defun sterge_lista_el (l e)
	(cond 
		((null l) nil)
		((equal e (car l)) (sterge_lista_el (cdr l) e))
		((listp (car l)) (cons (sterge_lista_el (car l) e) (sterge_lista_el (cdr l) e))) 
		(t (cons (car l) (sterge_lista_el (cdr l) e)))
	)
)

(defun main_c (l)	
	(sterge_lista_el l (maxim_lista l '-1))
)

(print (main_c '(10 29 a b x (18 (29 A) 29) 17 11 10)))

;d) Sa se construiasca o functie care intoarce produsul atomilor numerici pari dintr-o lista, de la orice nivel.
(defun produs_at_pari (l)
	(cond
		((null l) 1)
		((and (numberp (car l)) (evenp (car l))) (* (car l) (produs_at_pari (cdr l))))
		((listp (car l)) (* (produs_at_pari (car l)) (produs_at_pari (cdr l))))
		(t (produs_at_pari (cdr l)))
	)
)

(print (produs_at_pari '(2 29 a b x (9 (29 A) 29) 17 11 6)))

