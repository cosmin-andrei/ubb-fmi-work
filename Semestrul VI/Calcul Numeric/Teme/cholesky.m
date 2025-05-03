%Cholesky
function R = cholesky(A)
[m,n] = size(A);
for k=1:m
    %pt fiecare rand de sub diag curr aplic o actualizare
    for j=k+1:m
        A(j,j:m)=A(j,j:m)-A(k,j:m)*A(k,j)/A(k,k);
    end
    A(k,k:m)=A(k,k:m)/sqrt(A(k,k)); %normalizez linia k
end
R=triu(A);