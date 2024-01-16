;(load "D:/ubb-fmi-work/Semestrul III/PLF/LISP/Colocviu/sub7.lisp")


(defun nivele(l k niv)
	(cond
	( (and (atom l) (eq k niv)) 1)
	( (and (atom l) (not (eq k niv))) 0)
	( t (apply #'+ (mapcar (lambda (v)
				(nivele v k (+ 1 niv)))
			l )))
	)
)


(defun main(l k)
	(cond
	( (and (listp l) (null l)) nil)
	( t (apply #'+ (mapcar (lambda (v)
			(nivele v k 0))
			l )))
	)
)

(print (main '(a (b (g)) (c (d (e)) (f))) 2))