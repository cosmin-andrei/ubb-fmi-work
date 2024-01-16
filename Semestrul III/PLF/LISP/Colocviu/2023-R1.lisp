;(load "D:/ubb-fmi-work/Semestrul III/PLF/LISP/Colocviu/2023-R1.lisp")

(defun inloc (l niv e)
	(cond
	( (and (atom l) (eq (mod niv 2) 1)) e)
	( (atom l) l)
	( t (mapcar #'(lambda (v) (inloc v (+ 1 niv) e)) l) )
	)
)


(defun main (l e)
	(cond
	( (null l) l)
	( t (mapcar #'(lambda (v) (inloc v 0 e))l))
	)
)

(print (main '(a (b (g)) (c (d (e)) (f))) 'h))
