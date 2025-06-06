function rez = trapez(a, b, n, f)
    syms x;
    h = (b - a) / n;
    xi = a:h:b;
    rez = h/2 * (subs(f,x,xi(1)) + 2*sum(subs(f,x,xi(2:end-1))) + subs(f,x,xi(end)));
end

function rez = dreptunghi(a, b, n, f)
    syms x;
    h = (b - a) / n;
    rez = 0;
    for k = 1:n
        rez = rez + subs(f,x, a + (k - 0.5)*h);
    end
    rez = h * rez;
end

function rez = simpson(a, b, n, f)
    syms x;
    if mod(n,2) ~= 0
        n = n + 1;
    end
    h = (b - a) / n;
    xi = a:h:b;
    rez = h/3 * (subs(f,x,xi(1)) + 4*sum(subs(f,x,xi(2:2:end-1))) + 2*sum(subs(f,x,xi(3:2:end-2))) + subs(f,x,xi(end)));
end

function rez = adaptquad_trapez(a, b, f, tol)
    if abs(trapez(a,b,4,f) - trapez(a,b,8,f)) < tol
        rez = trapez(a,b,8,f);
    else
        c = (a + b)/2;
        rez = adaptquad_trapez(a,c,f,tol) + adaptquad_trapez(c,b,f,tol);
    end
end

function rez = adaptquad_dreptunghi(a, b, f, tol)
    if abs(dreptunghi(a,b,4,f) - dreptunghi(a,b,8,f)) < tol
        rez = dreptunghi(a,b,8,f);
    else
        c = (a + b)/2;
        rez = adaptquad_dreptunghi(a,c,f,tol) + adaptquad_dreptunghi(c,b,f,tol);
    end
end

function rez = adaptquad_simpson(a, b, f, tol)
    if abs(simpson(a,b,4,f) - simpson(a,b,8,f)) < tol
        rez = simpson(a,b,8,f);
    else
        c = (a + b)/2;
        rez = adaptquad_simpson(a,c,f,tol) + adaptquad_simpson(c,b,f,tol);
    end
end
