;postordine

(defun postordine (l)
	(cond
	( (null l) nil )
	( t (append (postordine (cadr l)) (postordine (caddr l)) (list (car l)) ) )
	)
)

(print (postordine '(A (B) (C (D) (E)))))