clc; clear;

n=5;
A = hilb(n);
b = sum(A,2);

disp(A);
disp(b);

tol = 1e-6;
max_iter = 500;

x_jacobi = jacobi(A, b, tol, max_iter);
disp("Sol aproximata JACOBI:");
disp(x_jacobi);

w = omega(A);
fprintf("Omega estimat: %.4f\n", w);
x_sor = SOR(A, b, w, tol, max_iter);
disp("Sol aproximata SOR:");
disp(x_sor);

x_exact = ones(n,1);
fprintf("Solutia exacta\n");
disp(x_exact);
