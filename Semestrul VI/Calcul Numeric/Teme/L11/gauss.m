function [x, w] = gauss(type, n, alpha, beta)
    if nargin < 3, alpha = 0; end
    if nargin < 4, beta = 0; end

    J = zeros(n);         % Matricea Jacobi
    b = zeros(n-1, 1);  

    switch type
        case 0  % Legendre: w(x) = 1, pe [-1, 1]
            for k = 1:n-1
                b(k) = sqrt(k^2 / (4*k^2 - 1));
            end
            beta0 = 2;

        case 1  % Chebyshev de tip I: w(x) = 1/sqrt(1 - x^2)
            b(:) = 0.5;
            b(1) = sqrt(0.5);
            beta0 = pi;

        case 2  % Chebyshev de tip II: w(x) = sqrt(1 - x^2)
            b(:) = 0.5;
            beta0 = pi / 2;

        case 3  % Laguerre: w(x) = x^alpha * exp(-x), pe [0, ∞)
            for k = 1:n-1
                b(k) = sqrt(k * (k + alpha));
            end
            for k = 0:n-1
                J(k+1,k+1) = 2*k + alpha + 1;
            end
            beta0 = gamma(alpha + 1);

        case 4  % Hermite: w(x) = exp(-x^2), pe (-∞, ∞)
            for k = 1:n-1
                b(k) = sqrt(k / 2);
            end
            beta0 = sqrt(pi);

        case 5  % Jacobi: w(x) = (1-x)^alpha * (1+x)^beta, pe [-1,1]
            for k = 1:n
                ab = 2*k + alpha + beta;
                if k == 1
                    a_k = (beta - alpha) / (alpha + beta + 2);
                    b_k = 2^(alpha + beta + 1) * gamma(alpha + 1) * gamma(beta + 1) / ...
                          (gamma(alpha + beta + 2) * (alpha + beta + 1));
                else
                    a_k = (beta^2 - alpha^2) / ((ab - 2)*ab);
                    b_k = 4*(k-1)*(k-1+alpha)*(k-1+beta)*(k-1+alpha+beta) / ...
                          ((ab-1)^2 * (ab-2) * ab);
                    b(k-1) = sqrt(b_k);
                end
                J(k,k) = a_k;
            end
            beta0 = 2^(alpha + beta + 1) * gamma(alpha + 1) * gamma(beta + 1) / ...
                    gamma(alpha + beta + 2);
    end

    J = J + diag(b, 1) + diag(b, -1);

    [V, D] = eig(J);
    x = diag(D);
    [x, idx] = sort(x);       
    V = V(:, idx);            

    w = beta0 * (V(1,:).^2)';

end
