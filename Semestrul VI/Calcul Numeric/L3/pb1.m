A = [10  7  8  7;
     7  5  6  5;
     8  6 10  9;
     7  5  9 10];

x = [32; 23; 33; 31];

x_t = [32.1; 22.9; 33.1; 30.9];

sol1 = A\x;

fprintf('%.6f', sol1);

x_sol = A \ x_t;
fprintf('\n');

fprintf('%.6f', x_sol);

fprintf('\n');

delta_x = norm(x_t-x) / norm(x);
fprintf('Delta x: %e\n', delta_x);

delta_A = norm(x_sol - sol1) / norm(sol1);
fprintf('Delta A %e\n', delta_A);

raport = delta_A / delta_x;
fprintf('Raport %e\n', raport);

cond_A = norm(A,2) * norm(inv(A),2);
fprintf('cond A %e\n', cond_A);

A_perturbat = [10  7  8.1  7.2;
     7.08  5.04  6  5;
     8  5.98 9.89  9;
     6.99  4.99  9 9.98];

x0 = A\x;
x_perturbat = A_perturbat\x;

delta_A = norm(A_perturbat - A) / norm(A);
delta_x = norm(x_perturbat - x0) / norm(x0);

fprintf('Eroarea intrare: %e\n', delta_A);
fprintf('Eroarea iesire: %e\n', delta_x);

eroare = eroare_input / eroare_output;
fprintf('Raport: %e\n', eroare);

%2.


