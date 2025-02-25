;4. Sa se converteasca un arbore de tipul (2) la un arbore de tipul (1).

; As an example, the tree
;   A
;  / \
; B   C
;    / \
;   D   E
; is represented as follows:
; (A 2 B 0 C 2 D 0 E 0) (1)
; (A (B) (C (D) (E))) (2)

(defun nr_subliste (l)
	(cond 
		((null l) 0)
		((listp (car l)) (+ 1 (nr_subliste (cdr l))))
		(t (nr_subliste (cdr l)))
	)
)

(defun tr_2_1 (l)
	(cond
		((null l) nil)
		((atom (car l)) (append (list (car l) (nr_subliste (cdr l))) (tr_2_1 (cdr l))))
		((listp (car l)) (append (tr_2_1 (car l)) (tr_2_1 (cdr l))))
	)
)

(print (tr_2_1 '(A (B) (C (D) (E)))))