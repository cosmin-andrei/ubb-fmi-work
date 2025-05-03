function [L,U,P]=lup_algoritm(A)

[m,n] = size(A);
P = zeros(m,n);

piv = (1:m)'; 

for i=1:m-1
    [maxim,ppoz] = max(abs(A(i:m,i))); %val max si poz pt pivotare
    ppoz = ppoz+i-1; % pozitie pivot
    
    if i~=ppoz
        A([i,ppoz],:) = A([ppoz,i],:);
        piv([i,ppoz]) = piv([ppoz,i]);
    end
    
    %Schur
    row = i+1:m;
    A(row,i) = A(row,i)/A(i,i);
    A(row,row) = A(row,row)-A(row,i)*A(i,row);
end

for i=1:m
    P(i,piv(i)) = 1;
end

U = triu(A);
L = tril(A,-1);
L = L+eye(m); 
end