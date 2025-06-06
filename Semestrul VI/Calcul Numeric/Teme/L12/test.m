eps = 1e-6;
Nmax = 100;
x0_vec = [1; 1; 0]; 

% Metoda Newton
[x_newton, k_newton] = newton(@f_sistem, @jacobian_sistem, x0_vec, eps, Nmax);
fprintf('x = %.6f\ny = %.6f\nz = %.6f\n', x_newton(1), x_newton(2), x_newton(3));
fprintf('Iteratii: %d\n', k_newton);

% Aproximatii succesive
[x_aprox, k_aprox] = aprox_succesive(@f_sistem, @jacobian_sistem, x0_vec, eps, Nmax);
fprintf('x = %.6f\ny = %.6f\nz = %.6f\n', x_aprox(1), x_aprox(2), x_aprox(3));
fprintf('Iteratii: %d\n', k_aprox);
