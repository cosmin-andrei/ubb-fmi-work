%f-functia
%x- punctele unde stim f
%p - pct aprox f
%n - grad
function val = l9(f, x, p, n)
    y = f(x);

    m=length(x);

    % n+1 x m
     phi = zeros(n + 1, m);
    for k = 0:n
        phi(k + 1, :) = x.^k;
    end

    phi_approx = p.^(0:n)'; % coloana

    A = zeros(n + 1);
    B = zeros(n + 1, 1);
    for i = 1:n+1
        for j = 1:n+1
            A(i, j) = phi(i, :) * phi(j, :)'; % produs scalar 
        end
        B(i) = phi(i, :) * y'; % produs scalar 
    end
    
    a = linsolve(A, B); %A * a =B
    val = a' * phi_approx; %aprox

    fprintf('%.6f', val);
end
