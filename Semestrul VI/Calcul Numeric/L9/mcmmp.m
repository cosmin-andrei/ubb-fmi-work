function res = mcmmp(x, y, f, p)

    phi = f(x); %eval phi
    phi_approx = f(p); %eval phi_approx
    
    n = length(x);
    [n, ~] = size(phi);
    
    %A * a = B
    %A = phi * Z ; B = phi * y
    for i = 1 : n
        for j = 1 : n
            A(i, j) = phi(i, :) * transpose(phi(j, :));
        end
        B(i, 1) = phi(i, :) * transpose(y);
    end
    
    %A * a = B (a)
    a = linsolve(A, B);
    res = transpose(a) * phi_approx;
end