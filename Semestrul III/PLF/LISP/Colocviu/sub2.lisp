;(load "D:/ubb-fmi-work/Semestrul III/PLF/LISP/Colocviu/sub2.lisp")


(defun modif (l el niv)
  (cond
    ((and (listp l) (null l)) nil)
    ((and (atom l) (eq (mod niv 2) 1)) el)
    ((and (atom l) (eq (mod niv 2) 0)) l)
    (t (mapcar #'(lambda (v)
                   (modif v el (+ niv 1)))
               l))))

(print (modif '(b (g)) 'h 0))

(defun main (l el)
  (cond
    ((null l) nil)
    ((atom l) (main (cdr l) el))
    (t (cons (modif (car l) el 0) (main (cdr l) el)))))

(print (main '(a (b (g)) (c (d (e)) (f))) 'h))