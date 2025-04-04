;1. Se da un arbore de tipul (1). Sa se afiseze calea de la radacina pana la un nod x dat.
; As an example, the tree
;     A
;    / \
;   B   C
;      / \
;     D   E
; is represented as follows:
; (A 2 B 0 C 2 D 0 E 0) (1)

(defun parcurg_st (l n m)
	(cond
		((null l) nil)
		((= n (+ 1 m)) nil)
		(t (cons (car l) (cons (cadr l) (parcurg_st (cddr l) (+ 1 n) (+ (cadr l) m)))))
	)
)

(defun stanga (l)
	(parcurg_st (cddr l) 0 0)
)


(defun parcurg_dr (l n m)
	(cond
		((null l) nil)
		((= n (+ 1 m)) l)
		(t (parcurg_dr (cddr l) (+ 1 n) (+ (cadr l) m)))
	)
)

(defun dreapta (l)
	(parcurg_dr (cddr l) 0 0)
)

(defun verific_ex (l el)
	(cond
		((null l) nil)
		((equal (car l) el) t)
		(t (verific_ex (cdr l) el))
	)
)

(defun verific_ex_st (l el)
	(verific_ex (stanga l) el)
)


(defun verific_ex_dr (l el)
	(verific_ex (dreapta l) el)
)

(defun cale (l el)
	(cond
		((null l) nil)
		((equal (car l) el) (list el))
		((verific_ex_dr l el) (cons (car l) (cale (dreapta l) el)))
		((verific_ex_st l el) (cons (car l) (cale (stanga l) el)))
	)	
)

(print (cale '(A 2 B 0 C 2 D 0 E 0) 'B))