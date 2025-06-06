function hermite(x, f, fd, eval)

    m = length(x);
    z = zeros(1, 2 * m);         
    Q = zeros(2 * m, 2 * m);       

    for i = 1:m
        z(2*i-1) = x(i);
        z(2*i)   = x(i);
        Q(2*i-1, 1) = f(i);
        Q(2*i,   1) = f(i);
        Q(2*i,   2) = fd(i);
        if i ~= 1
            Q(2*i-1, 2) = (Q(2*i-1,1) - Q(2*i-2,1)) / (z(2*i-1) - z(2*i-2));
        end
    end

    for i = 3 : 2*m
        for j = 3 : i
            Q(i,j) = (Q(i,j-1) - Q(i-1,j-1)) / (z(i) - z(i-j+1));
        end
    end

    s = 1;
    p = Q(1,1);
    for i = 2:2*m
        s = s * (eval - z(i-1));
        p = p + Q(i,i) * s;
    end
    fprintf('Val polinom %.4f: %.8f\n', eval, p);

    t = linspace(min(x)-0.2, max(x)+0.2, 500);
    y_interp = zeros(size(t));
    for k = 1:length(t)
        s = 1;
        pval = Q(1,1);
        for i = 2:2*m
            s = s * (t(k) - z(i-1));
            pval = pval + Q(i,i) * s;
        end
        y_interp(k) = pval;
    end

    figure;
    plot(t, y_interp, 'r', 'LineWidth', 2); hold on;
    plot(t, exp(t), 'b--', 'LineWidth', 1.5);
    plot(x, f, 'ko', 'MarkerFaceColor', 'k');
    plot(eval, p, 'ms', 'MarkerSize', 10, 'MarkerFaceColor', 'm'); 
    legend('Hermite', 'f(x) real', 'noduri', 'eval');
    xlabel('x'); ylabel('f(x)');
    grid on;
end
