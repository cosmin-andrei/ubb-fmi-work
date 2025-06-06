function pb1()
    a = 0;
    b = pi;
    n = 10;
    f = @(x) sin(x); % f(x)=sin x

    I_rect = dreptunghiuri(f, a, b, n);
    I_trapez = trapez(f, a, b, n);
    I_simpson = simpson(f, a, b, n);

    fprintf('dreptunghiuri: %.6f\n', I_rect);
    fprintf('trapez: %.6f\n', I_trapez);
    fprintf('simpson: %.6f\n', I_simpson);
end
