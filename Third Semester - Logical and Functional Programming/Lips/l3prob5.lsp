;5. Definiti o functie care testeaza apartenenta unui nod intr-un arbore n-ar 
;reprezentat sub forma (radacina lista_noduri_subarb1... lista_noduri_ _subarbn) 
;Ex: arborelele este (a (b (c)) (d) (e (f))) si nodul este 'b => adevarat

(defun sau (l)
	(cond
		((null l) nil)
		(t (or (car l) (sau (cdr l))))
	)
)

(defun apare (l e)
	(cond 
		((and (atom l) (equal l e)) t)
		((and (atom l) (not (equal l e))) nil)
		(t (funcall #'sau(mapcar #'(lambda (x)
									(apare x e)
									)
									l
						)
			)
		)
	)
)

(print (apare '(a (b (c)) (d) (e (f))) 'e))
(print (apare '(a (b (c)) (d) (e (f))) 'b))
(print (apare '(a (b (c)) (d) (e (f))) 'i))