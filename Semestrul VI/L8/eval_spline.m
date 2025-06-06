function z=eval_spline(x,c,t)
    n=length(x);
    x=x(:); t=t(:); 
    k = ones(size(t));
    
    %cauta un interval pt t in nodurile spline-ului
    for j = 2:n-1
        k(x(j) <= t) = j;
    end

    % interpolant eval.
    s = t - x(k); 
    %z = d(k) + s.*(c(k) + s.*(b(k) + s.*a(k)));
    z = c(k,4) + s.*(c(k,3) + s.*(c(k,2) + s.*c(k,1)));
