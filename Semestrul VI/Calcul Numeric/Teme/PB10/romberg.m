function rez = romberg(a, b, f, tol)
    syms x; %var simbolica
    i = 2; %nivel iter
    h = b - a; %lung interval
    %R = (b - a)/2 * [f(a) + f(b)]
    R(1,1) = h/2 * (subs(f,x,a) + subs(f,x,b)); 
    while true
        sum = 0;

        for k = 1:2^(i-2)
            sum = sum + subs(f, x, a + (k - 0.5) * h);
        end

        %R = 1/2 * (R+h*sum(f(x)))
        R(i,1) = 0.5 * (R(i-1,1) + h * sum);

        for j = 2:i
            R(i,j) = (4^(j-1)*R(i,j-1) - R(i-1,j-1)) / (4^(j-1) - 1);
        end

        if abs(R(i,i) - R(i-1,i-1)) < tol
            rez = R(i,i);
            return;
        end

        h = h / 2;
        i = i + 1;
    end
end
