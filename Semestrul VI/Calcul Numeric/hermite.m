function val = hermite(x, r, f_deriv, t)

    % numar total noduri
    n = sum(r);  
    % noduri extinse
    z = zeros(n, 1);
    % mat de diferente
    Q = zeros(n, n);

    index = 1;

    % mat de diferente
    for k = 1:length(x)
        for j = 1:r(k)
            z(index) = x(k);
            Q(index,1) = f_deriv{k}{j};
            index = index + 1;
        end
    end

    
