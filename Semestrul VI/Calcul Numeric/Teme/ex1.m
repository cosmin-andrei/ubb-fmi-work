% Realizati un script folosind MATLAB in care sa determinati polinomul lui MacLaurin de grad n 
% (dat ca parametru) pentru o functie f (data ca parametru).

function P = ex1(f, n)
    syms x;
    P = 0;
    for i = 0:n
        coef = subs(diff(f, x, i), x, 0) / factorial(i); % evaluez derivata in 0 / factorial
        P = P + coef * x^i; % construiesc polinomul
    end
    
    fprintf('P(x) = %s', P);
end
