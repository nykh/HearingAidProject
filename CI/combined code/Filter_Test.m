time=3;                     % length of time
Ts=1/48000;                 % time interval between samples
Fs = 1/Ts;
%x=randn(1,time/Ts);
x = 1:10000;
n=48;
y= zeros(1, 880000);
while n <= 88
    f = 100 * 10^(n/(4*11.56));
    z = sin(2*pi*f*Ts*x);
    q = n*10000+1 : (n+1)*10000;
    y(q) = z;
    n = n + 1;
end
sound(y, 48000);

% y1=filter(Hd1, y);
% sound(y1, 48000);
%
% y2=filter(Hd2, y);
% sound(y2, 48000);
%
% y3=filter(Hd3, y);
% sound(y3, 48000);
% 
% y4=filter(Hd4, y);
% sound(y4, 48000);
% 
% y5=filter(Hd5, y);
% sound(y5, 48000);
% 
% y6=filter(Hd6, y);
% sound(y6, 48000);
% 
% y7=filter(Hd7, y);
% sound(y7, 48000);
% 
% y8=filter(Hd8, y);
% sound(y8, 48000);
% 
% y9=filter(Hd9, y);
% sound(y9, 48000);
% 
% y10=filter(Hd10, y);
% sound(y10, 48000);
% 
% y11=filter(Hd11, y);
% sound(y11, 48000);
% 
% y12=filter(Hd12, y);
% sound(y12, 48000);
% 
% y13=filter(Hd13, y);
% sound(y13, 48000);
% 
% y14=filter(Hd14, y);
% sound(y14, 48000);
% 
% y15=filter(Hd15, y);
% sound(y15, 48000);
% 
% y16=filter(Hd16, y);
% sound(y16, 48000);
% 
% y17=filter(Hd17, y);
% sound(y17, 48000);
% 
% y18=filter(Hd18, y);
% sound(y18, 48000);
% 
% y19=filter(Hd19, y);
% sound(y19, 48000);
% 
% y20=filter(Hd20, y);
% sound(y20, 48000);
% 
% y21=filter(Hd21, y);
% sound(y21, 48000);
% 
% y22=filter(Hd22, y);
% sound(y22, 48000);
