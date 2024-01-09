; parcurgere in preordine

(defun preordine(l)
	(cond
	( (null l) nil)
	(t (cons (car l) (append (preordine (cadr l)) (preordine (caddr l)))))
	)
)

(print (preordine '(A (B) (C (D) (E)))))