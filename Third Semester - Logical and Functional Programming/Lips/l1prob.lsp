;1.
;a) Sa se insereze intr-o lista liniara un atom a dat dupa al 2-lea, al 4-lea, al 6-lea,....element.
(defun inserpozpar (l p a)
	(cond 
		((null l) nil)
		((= (mod p 2) 0) (cons (car l) (cons a (inserpozpar (cdr l) (+ p 1) a))))
		(t (cons (car l) (inserpozpar (cdr l) (+ p 1) a)))
	)
)

(defun inserpozparprincip (l a)
	(inserpozpar l 1 a)
)

(print (inserpozparprincip '(1 2 3 4 5 6) '2))


;b) Definiti o functie care obtine dintr-o lista data lista tuturor atomilor care apar, pe orice nivel, dar in ordine inversa. De exemplu: (((A B) C) (D E)) --> (E D C B A)
(defun inversare (l col)
	(cond
		((null l) col)
		((listp (car l)) (inversare (cdr l) (inversare (car l) col)))
		(t (inversare (cdr l) (cons (car l) col)))
	)
)

(defun inversareprincip (l)
	(inversare l '())
)

(print (inversareprincip '(((A B) C) (D E))))

;c) Definiti o functie care intoarce cel mai mare divizor comun al numerelor dintr-o lista neliniara.
(defun cmmdc (a b)
	(cond
		((= b 0) a)
		((= a 0) b)
		(t (cmmdc b (mod a b)))
	)
)

;fac pe cazuri pentru ca pot avea si un atom nu numai un numar
(defun cmmdclista (l div)
	(cond 
		((null l) div)
		((numberp (car l)) (cmmdclista (cdr l) (cmmdc (car l) div)))
		((listp (car l)) (cmmdclista (cdr l) (cmmdclista (car l) div)))
		(t (cmmdclista (cdr l) div))
	)
)

(defun cmmdclistap (l)
	(cmmdclista l 0)
)

(print (cmmdclistap '(15 A B (20 35 Y (10)))))

;d) Sa se scrie o functie care determina numarul de aparitii ale unui atom dat intr-o lista neliniara.

;folosesc equal pentru ca lucrez cu atomi
(defun aparitii (l a)
	(cond
		((null l) 0)
		((listp (car l)) (+ (aparitii (cdr l) a) (aparitii (car l) a)))
		((equal (car l) a) (+ 1 (aparitii (cdr l) a)))
		(t (aparitii (cdr l) a))
	)
)

(print (aparitii '(1 2 A 6 (A nw (b)) 5 A) 'A)) 
