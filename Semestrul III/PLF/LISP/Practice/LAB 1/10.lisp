;b multime toate perechile

(defun creareP (l elem)
	(cond
	( (null l) l )
	( t  (cons (list elem (car l)) (creareP (cdr l) elem) ) )
	)
)

;(print ( creareP '(2 3 4) '1 ))

(defun multimeP (l)
	(cond
	( (null l)  l)
	( t (append (creareP (cdr l) (car l)) (multimeP (cdr l))) )
	)
)

(print (multimeP '(a b c d)))

;c rez unei expr arit mem in preordine pe o stiva