;calea de la radacina pana la un nod x dat

(defun cauta(l x)
	(cond
	( (null l) nil )
	( (eq (car l) x) t )
	( (listp (car l)) (or (cauta (car l) x) (cauta (cdr l) x)) )
	( t (cauta (cdr l) x) )
	)
)

(defun parcurgere(l x)
	(cond
	( (null l) l )
	( (eq x (car l)) (list x))
	( (cauta (cadr l) x) (append (list (car l)) (parcurgere (cadr l) x)) )
	( (cauta (caddr l) x) (append (list (car l)) (parcurgere (caddr l) x)) )
	( t nil )
	)
)

(print (parcurgere '(A (B) (C (D) (E))) 'F))