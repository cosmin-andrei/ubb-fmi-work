;(load "D:/ubb-fmi-work/Semestrul III/PLF/LISP/Colocviu/sub1.lisp")


(defun elim (l e)
  (cond
    ((null l) nil)
    ((and (atom l) (not (eq e l))) l )
    ((and (atom l) (eq e l)) nil)
    (t (mapcar #'(lambda (v)
                 (elim v e))
               l))
))

(print (elim '(1 (2 A (3 A)) (A)) 'A))
