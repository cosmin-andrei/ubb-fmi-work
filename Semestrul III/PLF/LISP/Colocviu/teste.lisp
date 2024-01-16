;(load "D:/ubb-fmi-work/Semestrul III/PLF/LISP/Colocviu/teste.lisp")

(DEFUN Fct (F L)
  (COND
    ((NULL L) NIL)
    (t (LAMBDA (v)
         (COND
           (v (CONS v (Fct F (CDR L))))
           (t NIL)))
       (FUNCALL F (CAR L)))))

(print (Fct 5 '(1 2 3 4 5)))