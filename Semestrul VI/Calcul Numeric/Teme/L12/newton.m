function [x, k] = newton(f, J, x0, eps, Nmax)
    for k = 1:Nmax
        delta = J(x0) \ f(x0);
        x1 = x0 - delta;
        if norm(x1 - x0) < eps
            x = x1;
            return;
        end
        x0 = x1;
    end
    error('not precision');
end
