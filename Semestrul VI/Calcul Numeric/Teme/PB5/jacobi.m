function x_sol = jacobi(A,b,tol,max_iter)
    %tol-tolenrata
    [m,n]=size(A); %dim A
    x_prev = zeros(size(b)); %val init vector solutie
    if (m~=n) || (n~=length(b))
        error('dimensiune')
    end

    D = diag(diag(A)); % doar diagonala
    N = A - D; % restul elementelor 

    T = inv(D)*N; %T=D^-1 *(L+U)
    c = inv(D)*b; %c=D^-1 *b
    alfa = norm(T,inf); %criteriul de oprire, norma lui T
    x_sol=x_prev(:);%x=x0

    true = 1;
    %xi+1=T*xi+c
    for k = 1:max_iter
        %xi+1 = T*xi+c
        x_prev = x_sol;
        x_sol = T*x_prev+c;
        if norm(x_sol-x_prev,inf)<(1-alfa)/alfa*tol
            true = 0;
            return
        end
    end
    
    fprintf("nu converge");
end