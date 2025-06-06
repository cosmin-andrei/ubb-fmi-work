function I = dreptunghiuri(f, a, b, n)
    h = (b - a) / n;
    I = 0;
    for k = 1:n
        xk = a + (k - 0.5) * h; % punctul de mijloc
        I = I + f(xk);
    end
    I = I * h;
end
