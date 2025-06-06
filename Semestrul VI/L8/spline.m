%0 complete
%1 cu derivate secunde
%2 natural
%3 deBoor

function [c, rhs]=spline(x,f,type,der)
   
    %NATURAL SPLINE
    if (nargin<4) || (type==2), der=[0,0]; end

    n=length(x);

    %verif cresc
    if any(diff(x)<0)
        [x,ind]=sort(x); 
    else 
        ind = 1:n; 
    end
    
    y=f(ind); %reordonare y, conf x
    x=x(:); y=y(:); %x,y col

    %delta x si dif divizate
    dx=diff(x); %dx(i) = x(i+1) - x(i)
    diff(y');
    diff(y);
    ddiv=diff(y)./dx; % ddiv(i) = (y(i+1) - y(i)) / dx(i)

    ds=dx(1:end-1); %diag sub
    dd=dx(2:end); %diag s
    dp=2*(ds+dd); %dp          
    rhs=3*(dd.*ddiv(1:end-1)+ds.*ddiv(2:end)); %elem p dreapta
    
    
    switch type  
        case 0 %COMPLETE SPLINE                                      
            dp1=1; dpn=1; %capete dp
            vd1=0; vdn=0; %coef exteriori
            md1=der(1); mdn=der(2); %f'(a), f'(b)
       
        case {1,2} %D2 SI NORMAL
            dp1=2; dpn=2; %dp
            vd1=1; vdn=1;%coef
            md1=3*ddiv(1)-0.5*dx(1)*der(1);
            mdn=3*ddiv(end)+0.5*dx(end)*der(2);
    
        case 3 %DEBOOR SPLINE
            x31=x(3)-x(1); %stg
            xn=x(n)-x(n-2); %dr
            dp1=dx(2); dpn=dx(end-1); %dp
            vd1=x31; vdn=xn;
            md1=((dx(1)+2*x31)*dx(2)*ddiv(1)+dx(1)^2*ddiv(2))/x31;
            mdn=(dx(end)^2*ddiv(end-1)+(2*xn+dx(end))*dx(end-1)*ddiv(end))/xn;
    end
    
    %construct. sist.
    dp=[dp1;dp;dpn]; 
    dp1=[0;vd1;dd];
    sub_diag=[ds;vdn;0];
    rhs=[md1;rhs;mdn];

    A=spdiags([sub_diag,dp,dp1],-1:1,n,n); %matrice rara
    m=A\rhs; %sol sist

    %coef spline
    c(:,4)=y(1:end-1);
    c(:,3)=m(1:end-1);
    c(:,1)=(m(2:end)+m(1:end-1)-2*ddiv)./(dx.^2);
    c(:,2)=(ddiv-m(1:end-1))./dx-dx.*c(:,1);

end