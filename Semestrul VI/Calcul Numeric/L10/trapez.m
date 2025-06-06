function I = trapez(f, a, b, n)
    h = (b - a) / n;
    I = 0.5 * (f(a) + f(b));
    for k = 1:n-1
        xk = a + k * h;
        I = I + f(xk);
    end
    I = I * h;
end
