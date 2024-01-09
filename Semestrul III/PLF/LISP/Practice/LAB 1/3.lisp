;; 3.
;; a) Definiti o functie care intoarce produsul a doi vectori.

(defun produs (l1 l2)
  (cond
    ((null l1) l2)
    ((null l2) l1)
    (t (cons (* (car l1) (car l2)) (produs (cdr l1) (cdr l2))))))

(print (produs '(1 2 3) '(4 5 6 7)))

;; b) Sa se construiasca o functie care intoarce adancimea unei liste.

(defun adancime (l k)
  (cond
    ((null l) k)
    ((listp (car l))
     (max (adancime (car l) (+ k 1)) (adancime (cdr l) k)))
    (t (adancime (cdr l) k))))

(defun ad (l)
  (adancime l 1))

(print (ad '(A (B (C E) F) G)))

;; c) Definiti o functie care sorteaza fara pastrarea
;; dublurilor o lista liniara.




		