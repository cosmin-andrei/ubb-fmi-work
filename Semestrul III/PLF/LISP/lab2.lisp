;extract(l: list, stg: list, dr: list, k: integer, lim: integer)
;extrage subarborii dintr-o lista in doua liste, corespunzatoare tipului de subarbore (stang/drept)

(defun extract (l stg dr k lim)
  (cond
    ((null l) (list stg dr))
    ((= lim -1) (extract (cddr l) (cons (cadr l) (car l)) dr 0 (cadr l)))
    ((< k lim) (extract (cddr l) (cons (cadr l) (cons (car l) stg)) dr (+ k 1) lim))
    ((= k lim) (extract (cddr l) stg (cons (cadr l) (cons (car l) dr)) k lim))))

(defun INVERS (L)
  (COND
    ((ATOM L) L)
    (T (APPEND (INVERS (CDR L)) (LIST (CAR L))))))


(defun parcurgere (l, x, nivel)
  (cond
    ((null l) nil)
    ((eql (caar lista) x) nivel)
    (t (or (parcurgere (remove-if-not #'listp (cdar lista)) x (1+ nivel))
           (parcurgere (cdr lista) x nivel)))))

; cadr - al doilea elem
; cddr - out primele 2 elem
;(defun main (arbore x)
;   (cond
;	((null arbore) )
;	((= x (car arbore) 0)
;	((= (cadr arbore) 1) parcurgere((cddr arbore) x nivel)
;	(T (progn  
;		(setq stg '())
;		(setq dr '())
;		(extract(cddr(arbore) stg dr 0 -1))
;		(invers stg)
;		(invers dr)
