f = @(x) sin(x.^2);       
a = -1; b = 1;           
eps = 1e-7;         

n = 2;                 
err = inf;
rezV = 0;

while err > eps
    [x, w] = gauss(0, n); 
    intN = sum(w .* f(x)); 
    err = abs(intN - rezV);
    rezV = intN;
    n = n + 1;
end

fprintf('Aprox: %.8f\n', intN);
