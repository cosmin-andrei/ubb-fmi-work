function J = jacobian_sistem(x)
    J = [
        18*x(1), 72*x(2), 8*x(3);
        2*x(1), -4*x(2), -20;
        2*x(1), -2*x(2), 2*x(3)
    ];
end
