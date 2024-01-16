;(load "D:/ubb-fmi-work/Semestrul III/PLF/LISP/Colocviu/sub5.lisp")


(defun inloc (l e k niv)
  (cond
   ((and (eq k niv) (atom l)) e)
   ((and (not (eq k niv)) (atom l)) l)
   (t (mapcar #'(lambda (v)
                  (inloc v e k (+ niv 1)))
                l))))

(defun inloc_wrapper (l e k)
	(cond
	((null l) nil)
	( t (mapcar #'(lambda (v) 
			(inloc v e k 0)
			) l))
	)
)

(print (inloc_wrapper '(a (b (g)) (c (d (e)) (f))) 'h 2))