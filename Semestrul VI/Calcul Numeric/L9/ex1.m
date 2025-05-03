x = 1 : 10;
y = sin(1 : 10);

phi = @(x)[ones(1, length(x)); x; x.^2; x.^3; x.^4; x.^5];

%vect pcte pt aprox
x_approx = x(1) : (x(length(x)) - x(1)) / 100 : x(length(x));

%aprox. val. pt punctele x_approx
y_approx = mcmmp(x, y, phi, x_approx)