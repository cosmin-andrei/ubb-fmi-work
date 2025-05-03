function w=omega(A)
    D = diag(diag(A)); %diagonala
    N = D-A; %N=-(L+U)
    T = D\N; %mat iteratie Jacobi D^-1*(L + U)
    e = eig(T); %valorile lui T
    rt = max(abs(e)); %raza spectrala=max val abs a e
    w = 2/(1+sqrt(1-rt^2)); %formula omega