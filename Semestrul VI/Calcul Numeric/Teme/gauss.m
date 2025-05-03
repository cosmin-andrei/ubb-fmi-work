function x = gauss(A, b)
    n = size(A, 1); 
    A = [A, b]; %b ultima coloana
    
    for i = 1:n-1
        [~, p] = max(abs(A(i:n, i))); %cautare pivot col. i
        p = p + i - 1;
     
        if A(p, i) == 0
            error('sist. != sol unica');
        end
        
        %interschimbarea linii
        if p ~= i
            temp = A(i, :);
            A(i, :) = A(p, :);
            A(p, :) = temp;
        end
       
        for j = i+1:n %elim elem sub pivot
            mji = A(j, i) / A(i, i);
            A(j, :) = A(j, :) - mji * A(i, :);
        end
    end

    if A(n, n) == 0
        error('sist. != sol unica');
    end
    
    x = zeros(n, 1); % x- vector solutii
    x(n) = A(n, n+1) / A(n, n);
    for i = n-1:-1:1
        x(i) = (A(i, n+1) - A(i, i+1:n) * x(i+1:n)) / A(i, i);
    end
end
