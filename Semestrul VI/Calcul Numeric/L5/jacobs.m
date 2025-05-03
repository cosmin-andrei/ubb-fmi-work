function PB1 = jacobs(A,b)
    
    [m,n]=size(A);
    x0 = zeros(size(b)); %val init vect solutie


    M = diag(diag(A));
    N = M - A;
    T = inv(M)*N; 
    c = inv(M)*b; 
    alfa = norm(T,inf); %norma
    x=x0(:); %x col

    xAnterior = x;

    while iter < 10
        x = T * x_prev + c;
        err = norm(x - xAnterior, inf);
       
        xAnterior = x;
        iter = iter + 1;
    end
    PB1 = x;
end