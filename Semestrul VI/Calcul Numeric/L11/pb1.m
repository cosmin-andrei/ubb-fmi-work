function pb1()
   
    f = @(x) x .* exp(-x.^2);
    n = 20;           
    
    aprox = cebyshev_gauss(f, n);
    fprintf('%.10f', aprox);
end

function I = cebyshev_gauss(f, n)
    k = 1:n;
    x_k = cos((2*k - 1) * pi / (2*n));
    
    w_k = pi / n;
    I = w_k * sum(f(x_k));
end
