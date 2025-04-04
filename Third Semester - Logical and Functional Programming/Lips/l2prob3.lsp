;3. Se da un arbore de tipul (1). Sa se precizeze numarul de niveluri din arbore.
; As an example, the tree
;   A
;  / \
; B   C
;    / \
;   D   E
; is represented as follows:
; (A 2 B 0 C 2 D 0 E 0) 

(defun skipArbore (l)
	(cond
		((null l) '())
		((equal (cadr l) 0) (cddr l))
		((equal (cadr l) 1) (skipArbore (cddr l)))
		(t (skipArbore (skipArbore (cddr l))))
	)
)

(defun nivele (l)
	(cond
		((null l) 0)
		((equal (cadr l) 0) 1)
		((equal (cadr l) 1) (+ 1 (nivele (cddr l))))
		(t (+ 1 (max (nivele (cddr l)) (nivele (skipArbore (cddr l))))))
	)
)

(print (nivele '(A 2 B 0 C 2 D 0 E 0)))