;construire lista noduri arbore parcurs in inordine

(defun inordine (l)
	(cond
		((null l) nil)
		(t (append (inordine (cadr l)) (list (car l)) (inordine (caddr l))))
	)
)
(print (inordine '(A (B) (C (D) (E)))))