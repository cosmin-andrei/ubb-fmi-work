function spline_run(f, f_prim, f_d2)
    a = -1; b = 1;
    xN = linspace(a, b, 10);
    yVal = f(xN);

    coef_complet = spline(xN, yVal, 0, [f_prim(a), f_prim(b)]);
    coef_d2      = spline(xN, yVal, 1, [f_d2(a), f_d2(b)]);
    coef_natural = spline(xN, yVal, 2);
    coef_deboor  = spline(xN, yVal, 3);

    x_test = 0.25;

    y_true     = f(x_test);
    y_complet  = eval_spline(xN, coef_complet, x_test);
    y_d2       = eval_spline(xN, coef_d2, x_test);
    y_natural  = eval_spline(xN, coef_natural, x_test);
    y_deboor   = eval_spline(xN, coef_deboor, x_test);

    fprintf('f(x) = %.8f\n', y_true);
    fprintf('Spline complet = %.8f\n', y_complet);
    fprintf('Spline D2 = %.8f\n', y_d2);
    fprintf('Spline natural = %.8f\n', y_natural);
    fprintf('Spline de Boor = %.8f\n', y_deboor);
end
