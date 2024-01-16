;(load "D:/ubb-fmi-work/Semestrul III/PLF/LISP/Colocviu/sub4.lisp")

(defun elim (l niv)
  (cond
    ((and (numberp l) (eq (mod l 2) 0) (eq (mod niv 2) 1)) nil)
    ((atom l) l)
    (t (mapcar #'(lambda (v) (elim v (+ 1 niv))) l))
))


(defun elimNil (l)
	(cond
	( (null l) nil)
	( (equal (car l) nil) (elimNil (cdr l)) )
	( (listp (car l)) (cons (elimNil (car l)) (elimNil (cdr l))) )
	( t (cons (car l) (elimNil (cdr l))) )
	)
)

(defun elim_wrapper (l)
  (cond
    ((null l) nil)
    (t (mapcar #'(lambda (v) (elim v 1)) l))))

(defun main(l)
	(elimNil (elim_wrapper l))
)

(print (main '(1 (2 A (4 A)) (6))))
