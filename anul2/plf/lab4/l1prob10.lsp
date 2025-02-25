;10.
;a) Sa se construiasca o functie care intoarce produsul atomilor numerici dintr-o lista, de la nivelul superficial.
(defun produs_atomi (l)
	(cond
		((null l) 1)
		((numberp (car l)) (* (car l) (produs_atomi (cdr l))))
		(t (produs_atomi (cdr l)))
	)
)

(print (produs_atomi '(1 2 (6 A b) C 2 (11 30 (9)) 10)))

;b) Sa se scrie o functie care, primind o lista, intoarce multimea tuturor  perechilor din lista. De exemplu: (a b c d) --> ((a b) (a c) (a d)(b c) (b d) (c d))
;(mapcar func list)

(defun perechi (l)
	(cond
		((null l) nil)
		(t (append 
			(mapcar #'(lambda (x) (list (car l) x)) (cdr l))
			(perechi (cdr l))))
	)
)

(print (perechi '(a b c d)))

;c) Sa se determine rezultatul unei expresii aritmetice memorate in preordine pe o stiva. Exemple:
;(+ 1 3) ==> 4 (1 + 3)
;(+ * 2 4 3) ==> 11 ((2 * 4) + 3)
;(+ * 2 4 - 5 * 2 2) ==> 9 ((2 * 4) + (5 - (2 * 2))

(defun expresie (op a b)
	(cond
		((string= op "+") (+ a b))
		((string= op "-") (- a b))
		((string= op "*") (* a b))
		((string= op "/") (floor a b))
	)
)

(defun expr (l)
	(cond 
		((null l) nil)
		((and (and (numberp (cadr l)) (numberp (caddr l))) (atom (car l))) (cons (expresie (car l) (cadr l) (caddr l)) (expr (cdddr l))))
		(t (cons (car l) (expr (cdr l))))
	)
)

(defun solutie (l)
	(cond
		((null (cdr l)) (car l))
		(t (solutie (expr l)))
	)
)

(print (solutie '(+ 1 3)))
(print (solutie '(+ * 2 4 3)))
(print (solutie '(+ * 2 4 - 5 * 2 2)))

;d) Definiti o functie care, dintr-o lista de atomi, produce o lista de perechi (atom n), unde atom apare in lista initiala de n ori. De ex: 
;(A B A B A C A) --> ((A 4) (B 2) (C 1)).
(defun contor (l e)
	(cond
		((null l) 0)
		((equal e (car l)) (+ 1 (contor (cdr l) e)))
		(t (contor (cdr l) e))
	)
)

(defun sterge (l e)
	(cond 
		((null l) nil)
		((equal e (car l)) (sterge (cdr l) e))
		(t (cons (car l) (sterge (cdr l) e)))
	)
)

(defun contor_atomi (l)
	(cond
		((null l) nil)
		(t (cons (list (car l) (contor l (car l))) (contor_atomi (sterge l (car l)))))
	)
)

(print (contor_atomi '(A B A B A C A)))