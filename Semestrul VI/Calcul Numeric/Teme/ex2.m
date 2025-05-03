% Realizati un script folosind MATLAB in care sa determinati aproximarea Pade de grad (m,n) (dati ca parametri) pentru o functie f (data ca parametru). 
% Aveti in vedere faptul ca termenii polinomului de la numitor se calculeaza folosind solverul pentru sisteme liniare.

function [N, D] = ex2(f, m, n)
    syms x;
    
    %MacLaurin
    P = 0;
    for i = 0:(m+n)
        df_i = subs(diff(f, x, i), x, 0) / factorial(i);
        P = P + df_i * x^i;
    end
    
    factors1 = sym2poly(P); % convert P into an factors array (descendent dupa putere)
    factors2 = fliplr(factors1); %inversez ordinea
    factors = factors2(1:(m+n+1)); % primii m+n+1 termeni

    A = zeros(n, n); % mat. nxn pt coeficienti
    b = -factors(m+2:end)'; % coeficientii din dezvoltarea maclaurin (de la m+1)
    
    
    for i = 1:n
        startI = (m + i);
        endI   = (m + i - (n - 1));
        A(i, :) = factors(startI : -1 : endI); % pun coeficientii in matrice
    end
    
    d = [1; A\b]; % factors of D(x)
   
    % N(x) - m+1 factors
    Ncoefs = sym(zeros(m+1, 1));
    for k = 0:m
        s = sym(0);
        for j = 0 : min(k, n)
            s = s + d(j+1)*factors(k-j+1);
        end
        Ncoefs(k+1) = s;
    end

    N = poly2sym(flip(Ncoefs), x);
    D = poly2sym(flip(d), x);
   
    fprintf('N(x) = %s\n', N);
    fprintf('D(x) = %s\n', D);
end
