function [x, k] = aprox_vector(f, J, x0, eps, Nmax)
    J0_inv = inv(J(x0));
    phi = @(x) x - J0_inv * f(x);
    for k = 1:Nmax
        x1 = phi(x0);
        if norm(x1 - x0) < eps
            x = x1;
            return;
        end
        x0 = x1;
    end
    error('not precision');
end
