;(load "D:/ubb-fmi-work/Semestrul III/PLF/LISP/Colocviu/sub3.lisp")


(defun apare (l el niv)
  (cond
    ((and (atom l) (eq l el) (eq (mod niv 2) 0)) t)
    ((and (atom l) (or (not (eq l el)) (not (eq (mod niv 2) 0)))) nil)
    (t (or  (mapcar #'(lambda (v)
                       (apare v el (+ niv 1)))
                   l))
    )
  )
)

(defun main (l el)
  (cond
    ((null l) nil)
    (t (or (mapcar #'(lambda (v)
                       (apare v el 0))
                   l))
    )
  )
)

(print (main '(a (b (g)) (c (d (e)) (f))) 'r))
