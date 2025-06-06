function I = simpson(f, a, b, n)
    h = (b - a) / n;
    x = a:h:b;
    I = f(x(1)) + f(x(end));
    for k = 2:2:n
        I = I + 4 * f(x(k));
    end
    for k = 3:2:n-1
        I = I + 2 * f(x(k));
    end
    I = I * h / 3;
end
