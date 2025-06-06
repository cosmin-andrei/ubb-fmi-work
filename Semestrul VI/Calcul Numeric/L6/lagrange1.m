function lagrange1 (x, y, f, x0)

    m = length(x) - 1; %nodes
    w = ones(1, m + 1); 
    for j = 1:m+1
        w(j) = prod(x(j) - x([1:j-1, j+1:end])); %(xj -xk)
    end
    w = 1 ./ w;  % ponderi baricentrice

    % interpolare in x0
    p_val = 0;
    denom = 0;
    gasit = false;
    for j = 1:m+1
        if x0 == x(j) %x0 nod, luam y(j) val
            fx_interp = y(j);
            gasit = true;
            break;
        else
            %termen baricentric
            temp = w(j) / (x0 - x(j));
            p_val = p_val + temp * y(j);
            denom = denom + temp;
        end
    end
    if ~gasit
        fx_interp = p_val / denom; %valinterpolata
    end

    % reprezentare grafica
    xp = linspace(min(x), max(x), 1000);
    yp = zeros(size(xp));
    for i = 1:length(xp)
        xxi = xp(i);
        num = 0;
        den = 0;
        for j = 1:m+1
            if xxi == x(j)
                num = y(j);
                den = 1;
                break;
            else
                temp = w(j) / (xxi - x(j));
                num = num + temp * y(j);
                den = den + temp;
            end
        end
        yp(i) = num / den;
    end

    figure;
    plot(xp, f(xp), 'b-', 'LineWidth', 1.5); hold on;
    plot(xp, yp, 'r--', 'LineWidth', 1.5);
    plot(x, y, 'ko', 'MarkerFaceColor', 'k', 'MarkerSize', 6);
    plot(x0, fx_interp, 'ms', 'MarkerSize', 10, 'MarkerFaceColor', 'm');
    legend('f(x)', 'interpolare', 'noduri', 'valoare', 'location', 'best');
    xlabel('x'); ylabel('y');
    title(sprintf('interpolare baricentrica %.4f, %.6f', x0, fx_interp));
    grid on;
end
