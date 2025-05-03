function x = eliminare_gauss(A)

    [n,n] = size(A)
    for i = 1:(n-1)
        p = max(abs(A(i:n, i)))
    end

end