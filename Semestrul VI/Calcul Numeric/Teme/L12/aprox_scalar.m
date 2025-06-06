function [x, k] = aprox_scalar(x0, eps, Nmax)
    g = @(x) (sin(x) - cos(x)) / 4;

    for k = 1:Nmax
        x1 = g(x0);
        if abs(x1 - x0) < eps
            x = x1;
            return;
        end
        x0 = x1;
    end

    error('not precision');
end
