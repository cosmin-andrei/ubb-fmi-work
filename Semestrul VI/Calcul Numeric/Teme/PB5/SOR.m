%w-relaxarea
%tol-toleranta (implicit 1e-3)
function x_sol = SOR(A,b,w,tol,max_iter)
    if (w<=0) || (w>=2)
        error('parametrii')
    end
    
    [m,n]=size(A); %dim A
    x_prev=zeros(size(b)); %init vect solutie
    if (m~=n) || (n~=length(b))
        error('dimensiuni')
    end
   
    % M = (1/w) * D + L : D-diag A, L-sub diag A
    D = diag(diag(A));
    L = tril(A, -1);
    M = (1/w) * D + L;
    N = M - A;

    T = M\N; %mat iterativa - inv(M)*N
    c = M\b; %inv(M)*b
    alfa = norm(T,inf); %norma lui T - criteriu oprire
    x_sol = x_prev(:); %init vector solutie
    
    true = 1;
     for iter = 1:max_iter
        x_prev= x_sol;
        x_sol = T * x_prev + c;
        %criteriu de oprire
        if norm(x_sol - x_prev, inf) < (1 - alfa)/alfa * tol
            true = 0;
            return;
        end
    end
    
    fprintf("nu converge");
end