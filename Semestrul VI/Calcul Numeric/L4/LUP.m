function x = LUP(L, U, b, P, n)

    bP = b * P;
    y = zeros(n, 1);
    for i = 1:n
        syms sum=0;
        for j = 1:(i-1)
            sum = sum + L(i,j)* y(j);
        end
        y(i) = bP(i) - sum;
    end

    x = zeros(n, 1);

    for i = n:-1:1
        x(i)=(y(i)-U(i, i+1:n) * x(i+1:n))/U(i,i);
    end

    fprintf('Solutie %s', x);

end