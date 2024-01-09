;nivelul pe care apare un nod x in arbore. rad-0

(defun nivel(l x depth)
	(cond
	( (null l) -1 )
	( (eq x (car l)) depth )
	( t (max (nivel (cadr l) x (+ depth 1)) (nivel (caddr l) x (+ depth 1))) )
	)
)

(print (nivel '(A (B) (C (D) (E))) 'D 0 ))