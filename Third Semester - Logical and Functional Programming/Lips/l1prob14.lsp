;14.
;a) Dandu-se o lista liniare, se cere sa se elimine elementele din N in N.
(defun sterge (l n poz)
	(cond 
		((null l) nil)
		((zerop (mod poz n)) (sterge (cdr l) n (+ poz 1)))
		(t (cons (car l) (sterge (cdr l) n (+ poz 1))))
	)
)
(print (sterge '(1 2 3 10 7 8) '2 '1))

;b) Sa se scrie o functie care sa testeze daca o lista liniara formata din numere intregi are aspect de "vale"(o secvență se spune ca are aspect de 
;"vale" daca elementele descresc pana la un moment dat, apoi cresc. De ex. 10 8 6 17 19 20).
(defun cresc (l)
	(cond 
		((null (cdr l)) t)
		((>= (car l) (cadr l)) nil)
		(t (cresc (cdr l)))
	)
)

(defun desc (l)
	(cond
		((null (cdr l)) nil)
		((> (car l) (caddr l)) (desc (cdr l)))
		((< (car l) (caddr l)) (cresc (cdr l)))
		(t nil)
	)
)

(defun vale (l)
	(cond
		((and (>= (length l) 2) (> (car l) (cadr l))) (desc l))
		(t nil)
	)
)

(print (vale '(10 8 6 17 19 20)))

;c) Sa se construiasca o functie care intoarce minimul atomilor numerici dintr-o lista, de la orice nivel.
(defun minim_lista (l min)
	(cond
		((null l) min)
		((and (numberp (car l)) (< (car l) min)) (minim_lista (cdr l) (car l)))
		((listp (car l)) (minim_lista (cdr l) (minim_lista (car l) min)))
		(t (minim_lista (cdr l) min))
	)
)


(print (minim_lista '(10 29 a b x (18 (2 (9 A) 29) 17 11 10)) '1000))

;d) Sa se scrie o functie care sterge dintr-o lista liniara toate aparitiile elementului maxim numeric.
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
		(t (cons (car l) (sterge_lista_el (cdr l) e)))
	)
)

(defun main_c (l)	
	(sterge_lista_el l (maxim_lista l '-1))
)

(print (main_c '(10 29 a b x (18 (29 A) 29) 17 11 10)))