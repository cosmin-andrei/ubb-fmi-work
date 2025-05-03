function x = lup(A, b)

[L,U,P] = lup_algoritm(A);

y = L\(P*b);
x = U\y; 
end