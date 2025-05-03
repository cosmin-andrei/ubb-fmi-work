function fi=lagrange1(x, xi, fi_values, epsilon)
     m = length(xi) - 1;

     %sortare
     ai = abs(x - xi);
     [~, sortIndex] = sort(ai);
     xi = xi(sortIndex);
     fi_values = fi_values(sortIndex);

     f = zeros(m+1, m+1); %mat dif
     f(:,1) = fi_values(:); % f(i,1) = f(xi)

      for i = 1:m
        for j = 0:i-1
            yij = xi(i+1) - xi(j+1);
            f(i+1,j+2) = ((x - xi(j+1)) * f(i+1,j+1) - (x - xi(i+1)) * f(j+1,j+1)) / yij;
        end
        
        if abs(f(i+1, i+1) - f(i, i)) <= epsilon
            break;
        end
      end

     
     fi = f(i+1, i+1); %f(i,i)
end
