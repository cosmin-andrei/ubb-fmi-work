n = 5;
H = hilb(n);
b = sum(H, 2);

disp(H)
disp('b =');
disp(b)

fprintf('\n elim gauss \n')
x_gauss = gauss(H, b);
disp(x_gauss)

fprintf('\n descompunere LUP \n')
x_lup = lup(H, b);
disp(x_lup)

fprintf('\n descompunere Cholesky \n')
R = cholesky(H);
y = R' \ b; % R' * y = b
x_cholesky = R \ y; % R * x = y
disp(x_cholesky)