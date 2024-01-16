;(load "D:/ubb-fmi-work/Semestrul III/PLF/LISP/Colocviu/sub2023-13.lisp")

(defun inloc(l e niv)
	(cond
	( (null l) nil)
	( (and (atom (car l)) (= (mod niv 2) 1)) e)
	( t (mapcar #'inloc l e (+ niv 1)) )
	)
)