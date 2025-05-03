%Realizati un script folosind MATLAB in care sa aproximati functiile sinus si cosinus cu reducere de argument. 
% Aproximarea se va face intr-un punct x (dat ca parametru).

function [sin_aprox, cos_aprox] = l2(x)

    % reducere argument [0, pi/2]
    x = mod(x, 2*pi);

    %aici retin semnele
    Ssin = 1;
    Scos = 1;

    if x >= pi/2 && x < pi %cadran II
        x = pi - x;
        Scos = -1;
    elseif x >= pi && x < 3*pi/2 %cadran III
        x = x - pi;
        Ssin = -1;
        Scos = -1;
    elseif x >= 3*pi/2 %cadran IV
        x = 2*pi - x;
        Ssin = -1;
    end

    % Taylor sin(x)= x - x^3/3! + x^5/5! - ...
    sinV = 0;
    x_p = x; %x^1
    fact = 1;
    for i = 1:10
        sinV = sinV + x_p / fact;
        x_p = -x_p * x^2;
        fact = fact * (2*i) * (2*i + 1);
    end

    % Taylor cos(x)= 1 - x^2/2! + x^4/4! - ...
    cosV = 0;
    x_p = 1;
    fact = 1;
    for i = 1:10
        cosV = cosV + x_p / fact;
        x_p = -x_p * x^2;
        fact = fact * (2*i) * (2*i - 1);
    end

    %semne in functie de cadran
    sin_aprox = Ssin * sinV;
    cos_aprox = Scos * cosV;

    fprintf('sin(x) aproximat  = %.10f\n', sin_aprox);
    fprintf('sin(x) real       = %.10f\n', sin(x));


    fprintf('cos(x) aproximat  = %.10f\n', cos_aprox);
    fprintf('cos(x) real       = %.10f\n', cos(x));


end




