;5. Sa se intoarca adancimea la care se afla un nod intr-un arbore de tipul (1).

; As an example, the tree
;   A
;  / \
; B   C
;    / \
;   D   E
; is represented as follows:
; (A 2 B 0 C 2 D 0 E 0) (1)

(defun parcurgere_st (l n m)
	(cond
		((null l) nil)
		((= n (+ 1 m)) nil)
		(t (cons (car l) (cons (cadr l) (parcurgere_st (cddr l) (+ 1 n) (+ (cadr l) m)))))
	)
)

(defun stanga (l)
	(parcurgere_st (cddr l) 0 0)
)

(defun parcurgere_dr (l n m)
	(cond
		((null l) nil)
		((= n (+ 1 m)) l)
		(t (parcurgere_dr (cddr l) (+ 1 n) (+ (cadr l) m)))
	)
)


(defun dreapta (l)
	(parcurgere_dr (cddr l) 0 0)
)

(defun verific_ex (l el)
	(cond
		((null l) nil)
		((equal (car l) el) t)
		(t (exista (cdr l) el))
	)
)


(defun verific_ex_st (l el)
	(verific_ex (stanga l) el)
)


(defun verific_ex_dr (l el)
	(verific_ex (dreapta l) el)
)

(defun ad_el (l e ad)
	(cond
		((null l) nil)
		((equal (car l) e) ad)
		((verific_ex_st l e) (ad_el (stanga l) e (+ 1 ad)))
		((verific_ex_dr l e) (ad_el (dreapta l) e (+ 1 ad)))
	)
)

(print (ad_el '(A 2 B 0 C 2 D 1 I 0 E 0) 'I '0))
