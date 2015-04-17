clc
clear all
close all



%{



Ts=1/48000;                 % time interval between samples
x = 1:10000;

 n =8;
    f = 100 * 10^((n-.5)/(11.56));
    signal = transpose(sin(2*pi*f*Ts*x));


   
    
    
% Saqib's code: Output is the original signal and a 2xn vector which
% contains the average and the channel # corresponding to that channel 
% in variable z
if 1

if 1 % Loads all the filters
load('filter1.mat')
load('filter2.mat')
load('filter3.mat')
load('filter4.mat')
load('filter5.mat')
load('filter6.mat')
load('filter7.mat')
load('filter8.mat')
load('filter9.mat')
load('filter10.mat')
load('filter11.mat')
load('filter12.mat')
load('filter13.mat')
load('filter14.mat')
load('filter15.mat')
load('filter16.mat')
load('filter17.mat')
load('filter18.mat')
load('filter19.mat')
load('filter20.mat')
load('filter21.mat')
load('filter22.mat')
end 

% Fs = 48000;                    % sampling rate
% T = 1/Fs;                      % sampling period
% t_new = [0:T:0.25];                % time vector 0:T:0.25
% phi = 2 * pi * 0.25;           % 1/4 cycle phase offset
% signal = cos(2*pi*101*t_new + phi);      % sinusoidal signal, amplitude = 1
% %y = cos(2*pi*5*t);            % sinusoidal signal, amplitude = 1/3
% signal = transpose(signal);
% 
% clear phi T 
% 
% plot(signal)
% hold on


% Fs = 44100;                    % sampling rate
% T = 1/Fs;                      % sampling period
% t = [0:T:0.25];                % time vector 0:T:0.25
% t_orig = t;  
% phi = 2 * pi * 0.25;           % 1/4 cycle phase offset
% x1 = cos(2*pi*500*t + phi);      % sinusoidal signal, amplitude = 1
% x2 = cos(2*pi*5*t);            % sinusoidal signal, amplitude = 1/3
% signal = transpose(x1);

% [signal,Fs] = audioread('sample4.mp3');  % read sound from the file
% t_new = 1/Fs : 1/Fs: length(signal)/Fs;


i = 1;
d = [];
w = [];
z = [];



    
y1=filter(Hd1, y);
y2=filter(Hd2, y);
y3=filter(Hd3, y);
y4=filter(Hd4, y);
y5=filter(Hd5, y);
y6=filter(Hd6, y);
y7=filter(Hd7, y);
y8=filter(Hd8, y);
y9=filter(Hd9, y);
y10=filter(Hd10, y);
y11=filter(Hd11, y);
y12=filter(Hd12, y);
y13=filter(Hd13, y);
y14=filter(Hd14, y);
y15=filter(Hd15, y);
y16=filter(Hd16, y);
y17=filter(Hd17, y);
y18=filter(Hd18, y);
y19=filter(Hd19, y);
y20=filter(Hd20, y);
y21=filter(Hd21, y);
y22=filter(Hd22, y);




while i<length(signal)
    
    if((i+100) > length(signal))
        y = signal(i:length(signal),1);
    
    else
        y = signal(i:i+99,1);
    end
    

    
y = [y1 y2 y3 y4 y5 y6 y7 y8 y9 y10 y11 y12 y13 y14 y15 y16 y17 y18 y19 y20 y21 y22];


x = [mean(y1) mean(y2) mean(y3) mean(y4) mean(y5) mean(y6) mean(y7) mean(y8) mean(y9) mean(y10) mean(y11) mean(y12) mean(y13) mean(y14) mean(y15) mean(y16) mean(y17) mean(y18) mean(y19) mean(y20) mean(y21) mean(y22)];

c = 1:1:22;
b = [x ; c];

    counter = 22;
    for j=1:(counter-6) %this number alters the # of channels activated
        [val,idx] =  min(abs(x(1,:)));
        c(idx) = [];
        x(idx) = [];

        b(:,idx) = [];
        y (:,idx) = [];

    end
    
    f = y(:,1) + y(:,2) + y(:,3) + y(:,4) + y(:,5) + y(:,6);% + y(:,7) + y(:,8);
    %f = f + y(:,9) + y(:,10) + y(:,11) + y(:,12) + y(:,13) + y(:,14) + y(:,15);
    %f = f + y(:,16) + y(:,17) + y(:,18) + y(:,19) + y(:,20) + y(:,21) + y(:,22);
    % f = f.*4; % varies the gain of the signal
    
    g = [y(:,1),y(:,2),y(:,3),y(:,4),y(:,5),y(:,6)];% ,y(:,7),y(:,8)];
    
 
    
    l = [x ; c];
    w = [w , l];
    d = [d ; f];
    i = i + 100;
    z = [z , l];
    
    clear f g val idx c x T b counter j phi t_orig t x1 x2 l
end


A = z;
clearvars -except signal l z A


end


C1 = 0;
C2 = 0;
C3 = 0;
C4 = 0;
C5 = 0;
C6 = 0;
C7 = 0;
C8 = 0;
C9 = 0;
C10 = 0;
C11 = 0;
C12 = 0;
C13 = 0;
C14 = 0;
C15 = 0;
C16 = 0;
C17 = 0;
C18 = 0;
C19 = 0;
C20 = 0;
C21 = 0;
C22 = 0;


x = size(A(2,:));
x = x(1,2);


for i=1:x
       if(A(2,i) == 1)
           C1 = C1 + 1;
            elseif (A(2,i) == 2)
       C2 = C2 + 1;
           elseif (A(2,i) == 3)
       C3 = C3 + 1;
           elseif (A(2,i) == 4)
       C4 = C4 + 1;
           elseif (A(2,i) == 5)
       C5 = C5+1;
            elseif (A(2,i) == 6)
       C6 = C6 + 1;
           elseif (A(2,i) == 7)
       C7 = C7 + 1;
           elseif (A(2,i) == 8)
       C8 = C8 + 1;
           elseif (A(2,i) == 9)
       C9 = C9 + 1;
           elseif (A(2,i) == 10)
       C10 = C10 + 1;
           elseif (A(2,i) == 11)
       C11 = C11 + 1;
           elseif (A(2,i) == 12)
       C12 = C12 + 1;
           elseif (A(2,i) == 13)
       C13 = C13 + 1;
           elseif (A(2,i) == 15)
       C15 = C15 + 1;
           elseif (A(2,i) == 14)
       C14 = C14 + 1;
           elseif (A(2,i) == 16)
       C16 = C16 + 1;
           elseif (A(2,i) == 17)
       C17 = C17 + 1;
           elseif (A(2,i) == 18)
       C18 = C18 + 1;
       elseif (A(2,i) == 19)
       C19 = C19 + 1;
       elseif (A(2,i) == 20)
       C20 = C20 + 1;
       elseif (A(2,i) == 21)
       C21 = C21 + 1;
       else
       C22 = C22 + 1;
       
       end
           
end
    









% Katelyn's code
if 1
    
n = 1;
pos = [1 1 1 1];
neg = [-1 -1 -1 -1];
[x, y] = size(A);

% create an array of zeros of size 8*size(A)

% Channel1 = int16.empty(1,0);
% Channel2 = int16.empty(1,0);
% Channel3 = int16.empty(1,0);
% Channel4 = int16.empty(1,0);
% Channel5 = int16.empty(1,0);
% Channel6 = int16.empty(1,0);
% Channel7 = int16.empty(1,0);
% Channel8 = int16.empty(1,0);
% Channel9 = int16.empty(1,0);
% Channel10 = int16.empty(1,0);
% Channel11 = int16.empty(1,0);
% Channel12 = int16.empty(1,0);
% Channel13 = int16.empty(1,0);
% Channel14 = int16.empty(1,0);
% Channel15 = int16.empty(1,0);
% Channel16 = int16.empty(1,0);
% Channel17 = int16.empty(1,0);
% Channel18 = int16.empty(1,0);
% Channel19 = int16.empty(1,0);
% Channel20 = int16.empty(1,0);
% Channel21 = int16.empty(1,0);
% Channel22 = int16.empty(1,0);


Channel1 = [];
Channel2 = [];
Channel3 = [];
Channel4 = [];
Channel5 = [];
Channel6 = [];
Channel7 = [];
Channel8 = [];
Channel9 = [];
Channel10 = [];
Channel11 = [];
Channel12 = [];
Channel13 = [];
Channel14 = [];
Channel15 = [];
Channel16 = [];
Channel17 = [];
Channel18 = [];
Channel19 = [];
Channel20 = [];
Channel21 = [];
Channel22 = [];

CreatePulse1 = [pos, neg, zeros([1,40])];
CreatePulse2 = [zeros([1,8]), pos, neg, zeros([1,32])];
CreatePulse3 = [zeros([1,16]), pos, neg, zeros([1,24])];
CreatePulse4 = [zeros([1,24]), pos, neg, zeros([1,16])];
CreatePulse5 = [zeros([1,32]), pos, neg, zeros([1,8])];
CreatePulse6 = [zeros([1,40]), pos, neg];

while(n < y)
    
C1 = A(2,n);
C2 = A(2,(n+1));
C3 = A(2,(n+2));
C4 = A(2,(n+3));
C5 = A(2,(n+4));
C6 = A(2,(n+5));

Pulse1 = A(1,n);
Pulse2 = A(1,(n+1));
Pulse3 = A(1,(n+2));
Pulse4 = A(1,(n+3));
Pulse5 = A(1,(n+4));
Pulse6 = A(1,(n+5));

Pulses1 = CreatePulse1*Pulse1;
Pulses2 = CreatePulse2*Pulse3;
Pulses3 = CreatePulse3*Pulse5;
Pulses4 = CreatePulse4*Pulse2;
Pulses5 = CreatePulse5*Pulse4;
Pulses6 = CreatePulse6*Pulse6;

if C1 == 1
    Channel1 = [Channel1, Pulses1];
elseif( C2 == 1 )
    Channel1 = [Channel1, Pulses4];
elseif( C3 == 1 )
    Channel1 = [Channel1, Pulses2];
elseif ( C4 == 1 )
    Channel1 = [Channel1, Pulses5];
elseif( C5 == 1 )
    Channel1 = [Channel1, Pulses3];
elseif( C6 == 1 )
    Channel1 = [Channel1, Pulses6];
else
    Channel1 = [Channel1, zeros([1, 48])];
end
                    
if C1 == 2
    Channel2 = [Channel2, Pulses1];
elseif( C2 == 2 )
    Channel2 = [Channel2, Pulses4];
elseif( C3 == 2 )
    Channel2 = [Channel2, Pulses2];
elseif ( C4 == 2 )
    Channel2 = [Channel2, Pulses5];
elseif( C5 == 2 )
    Channel2 = [Channel2, Pulses3];
elseif( C6 == 2 )
    Channel2 = [Channel2, Pulses6];
else
    Channel2 = [Channel2, zeros([1, 48])];
end  

if C1 == 3
    Channel3 = [Channel3, Pulses1];
elseif( C2 == 3 )
    Channel3 = [Channel3, Pulses4];
elseif( C3 == 3 )
    Channel3 = [Channel3, Pulses2];
elseif ( C4 == 3 )
    Channel3 = [Channel3, Pulses5];
elseif( C5 == 3 )
    Channel3 = [Channel3, Pulses3];
elseif( C6 == 3 )
    Channel3 = [Channel3, Pulses6];
else
    Channel3 = [Channel3, zeros([1, 48])];
end 


if C1 == 4
    Channel4 = [Channel4, Pulses1];
elseif( C2 == 4 )
    Channel4 = [Channel4, Pulses4];
elseif( C3 == 4 )
    Channel4 = [Channel4, Pulses2];
elseif ( C4 == 4 )
    Channel4 = [Channel4, Pulses5];
elseif( C5 == 4 )
    Channel4 = [Channel4, Pulses3];
elseif( C6 == 4 )
    Channel4 = [Channel4, Pulses6];
else
    Channel4 = [Channel4, zeros([1, 48])];
end 


if C1 == 5
    Channel5 = [Channel5, Pulses1];
elseif( C2 == 5 )
    Channel5 = [Channel5, Pulses4];
elseif( C3 == 5 )
    Channel5 = [Channel5, Pulses2];
elseif ( C4 == 5 )
    Channel5 = [Channel5, Pulses5];
elseif( C5 == 5 )
    Channel5 = [Channel5, Pulses3];
elseif( C6 == 5 )
    Channel5 = [Channel5, Pulses6];
else
    Channel5 = [Channel5, zeros([1, 48])];
end 


if C1 == 6
    Channel6 = [Channel6, Pulses1];
elseif( C2 == 6 )
    Channel6 = [Channel6, Pulses4];
elseif( C3 == 6 )
    Channel6 = [Channel6, Pulses2];
elseif ( C4 == 6 )
    Channel6 = [Channel6, Pulses5];
elseif( C5 == 6 )
    Channel6 = [Channel6, Pulses3];
elseif( C6 == 6 )
    Channel6 = [Channel6, Pulses6];
else
    Channel6 = [Channel6, zeros([1, 48])];
end 


if C1 == 7
    Channel7 = [Channel7, Pulses1];
elseif( C2 == 7 )
    Channel7 = [Channel7, Pulses4];
elseif( C3 == 7 )
    Channel7 = [Channel7, Pulses2];
elseif ( C4 == 7 )
    Channel7 = [Channel7, Pulses5];
elseif( C5 == 7 )
    Channel7 = [Channel7, Pulses3];
elseif( C6 == 7 )
    Channel7 = [Channel7, Pulses6];
else
    Channel7 = [Channel7, zeros([1, 48])];
end 


if C1 == 8
    Channel8 = [Channel8, Pulses1];
elseif( C2 == 8 )
    Channel8 = [Channel8, Pulses4];
elseif( C3 == 8 )
    Channel8 = [Channel8, Pulses2];
elseif ( C4 == 8 )
    Channel8 = [Channel8, Pulses5];
elseif( C5 == 8 )
    Channel8 = [Channel8, Pulses3];
elseif( C6 == 8 )
    Channel8 = [Channel8, Pulses6];
else
    Channel8 = [Channel8, zeros([1, 48])];
end 


if C1 == 9
    Channel9 = [Channel9, Pulses1];
elseif( C2 == 9 )
    Channel9 = [Channel9, Pulses4];
elseif( C3 == 9 )
    Channel9 = [Channel9, Pulses2];
elseif ( C4 == 9 )
    Channel9 = [Channel9, Pulses5];
elseif( C5 == 9 )
    Channel9 = [Channel9, Pulses3];
elseif( C6 == 9 )
    Channel9 = [Channel9, Pulses6];
else
    Channel9 = [Channel9, zeros([1, 48])];
end 


if C1 == 10
    Channel10 = [Channel10, Pulses1];
elseif( C2 == 10 )
    Channel10 = [Channel10, Pulses4];
elseif( C3 == 10 )
    Channel10 = [Channel10, Pulses2];
elseif ( C4 == 10 )
    Channel10 = [Channel10, Pulses5];
elseif( C5 == 10 )
    Channel10 = [Channel10, Pulses3];
elseif( C6 == 10 )
    Channel10 = [Channel10, Pulses6];
else
    Channel10 = [Channel10, zeros([1, 48])];
end 


if C1 == 11
    Channel11 = [Channel11, Pulses1];
elseif( C2 == 11 )
    Channel11 = [Channel11, Pulses4];
elseif( C3 == 11 )
    Channel11 = [Channel11, Pulses2];
elseif ( C4 == 11 )
    Channel11 = [Channel11, Pulses5];
elseif( C5 == 11 )
    Channel11 = [Channel11, Pulses3];
elseif( C6 == 11 )
    Channel11 = [Channel11, Pulses6];
else
    Channel11 = [Channel11, zeros([1, 48])];
end 


if C1 == 12
    Channel12 = [Channel12, Pulses1];
elseif( C2 == 12 )
    Channel12 = [Channel12, Pulses4];
elseif( C3 == 12 )
    Channel12 = [Channel12, Pulses2];
elseif ( C4 == 12 )
    Channel12 = [Channel12, Pulses5];
elseif( C5 == 12 )
    Channel12 = [Channel12, Pulses3];
elseif( C6 == 12 )
    Channel12 = [Channel12, Pulses6];
else
    Channel12 = [Channel12, zeros([1, 48])];
end 


if C1 == 13
    Channel13 = [Channel13, Pulses1];
elseif( C2 == 13 )
    Channel13 = [Channel13, Pulses4];
elseif( C3 == 13 )
    Channel13 = [Channel13, Pulses2];
elseif ( C4 == 13 )
    Channel13 = [Channel13, Pulses5];
elseif( C5 == 13 )
    Channel13 = [Channel13, Pulses3];
elseif( C6 == 13 )
    Channel13 = [Channel13, Pulses6];
else
    Channel13 = [Channel13, zeros([1, 48])];
end 


if C1 == 14
    Channel14 = [Channel14, Pulses1];
elseif( C2 == 14 )
    Channel14 = [Channel14, Pulses4];
elseif( C3 == 14 )
    Channel14 = [Channel14, Pulses2];
elseif ( C4 == 14 )
    Channel14 = [Channel14, Pulses5];
elseif( C5 == 14 )
    Channel14 = [Channel14, Pulses3];
elseif( C6 == 14 )
    Channel14 = [Channel14, Pulses6];
else
    Channel14 = [Channel14, zeros([1, 48])];
end 


if C1 == 15
    Channel15 = [Channel15, Pulses1];
elseif( C2 == 15 )
    Channel15 = [Channel15, Pulses4];
elseif( C3 == 15 )
    Channel15 = [Channel15, Pulses2];
elseif ( C4 == 15 )
    Channel15 = [Channel15, Pulses5];
elseif( C5 == 15 )
    Channel15 = [Channel15, Pulses3];
elseif( C6 == 15 )
    Channel15 = [Channel15, Pulses6];
else
    Channel15 = [Channel15, zeros([1, 48])];
end 


if C1 == 16
    Channel16 = [Channel16, Pulses1];
elseif( C2 == 16 )
    Channel16 = [Channel16, Pulses4];
elseif( C3 == 16 )
    Channel16 = [Channel16, Pulses2];
elseif ( C4 == 16 )
    Channel16 = [Channel16, Pulses5];
elseif( C5 == 16 )
    Channel16 = [Channel16, Pulses3];
elseif( C6 == 16 )
    Channel16 = [Channel16, Pulses6];
else
    Channel16 = [Channel16, zeros([1, 48])];
end 


if C1 == 17
    Channel17 = [Channel17, Pulses1];
elseif( C2 == 17 )
    Channel17 = [Channel17, Pulses4];
elseif( C3 == 17 )
    Channel17 = [Channel17, Pulses2];
elseif ( C4 == 17 )
    Channel17 = [Channel17, Pulses5];
elseif( C5 == 17 )
    Channel17 = [Channel17, Pulses3];
elseif( C6 == 17 )
    Channel17 = [Channel17, Pulses6];
else
    Channel17 = [Channel17, zeros([1, 48])];
end 


if C1 == 18
    Channel18 = [Channel18, Pulses1];
elseif( C2 == 18 )
    Channel18 = [Channel18, Pulses4];
elseif( C3 == 18 )
    Channel18 = [Channel18, Pulses2];
elseif ( C4 == 18 )
    Channel18 = [Channel18, Pulses5];
elseif( C5 == 18 )
    Channel18 = [Channel18, Pulses3];
elseif( C6 == 18 )
    Channel18 = [Channel18, Pulses6];
else
    Channel18 = [Channel18, zeros([1, 48])];
end 


if C1 == 19
    Channel19 = [Channel19, Pulses1];
elseif( C2 == 19 )
    Channel19 = [Channel19, Pulses4];
elseif( C3 == 19 )
    Channel19 = [Channel19, Pulses2];
elseif ( C4 == 19 )
    Channel19 = [Channel19, Pulses5];
elseif( C5 == 19 )
    Channel19 = [Channel19, Pulses3];
elseif( C6 == 19 )
    Channel19 = [Channel19, Pulses6];
else
    Channel19 = [Channel19, zeros([1, 48])];
end 


if C1 == 20
    Channel20 = [Channel20, Pulses1];
elseif( C2 == 20 )
    Channel20 = [Channel20, Pulses4];
elseif( C3 == 20 )
    Channel20 = [Channel20, Pulses2];
elseif ( C4 == 20 )
    Channel20 = [Channel20, Pulses5];
elseif( C5 == 20 )
    Channel20 = [Channel20, Pulses3];
elseif( C6 == 20 )
    Channel20 = [Channel20, Pulses6];
else
    Channel20 = [Channel20, zeros([1, 48])];
end 


if C1 == 21
    Channel21 = [Channel21, Pulses1];
elseif( C2 == 21 )
    Channel21 = [Channel21, Pulses4];
elseif( C3 == 21 )
    Channel21 = [Channel21, Pulses2];
elseif ( C4 == 21 )
    Channel21 = [Channel21, Pulses5];
elseif( C5 == 21 )
    Channel21 = [Channel21, Pulses3];
elseif( C6 == 21 )
    Channel21 = [Channel21, Pulses6];
else
    Channel21 = [Channel21, zeros([1, 48])];
end 
 

if C1 == 22
    Channel22 = [Channel22, Pulses1];
elseif( C2 == 22 )
    Channel22 = [Channel22, Pulses4];
elseif( C3 == 22 )
    Channel22 = [Channel22, Pulses2];
elseif ( C4 == 22 )
    Channel22 = [Channel22, Pulses5];
elseif( C5 == 22 )
    Channel22 = [Channel22, Pulses3];
elseif( C6 == 22 )
    Channel22 = [Channel22, Pulses6];
else
    Channel22 = [Channel22, zeros([1, 48])];
end 

    
  n = n + 6;  
    
    
end
end


 %}
% % Kaitlyn's code
% if 0
%     

Ts=1/48000;                 % time interval between samples
pulses_per_sample = 480;
x = 1:pulses_per_sample;
ss=1;
sinusoids= zeros(22, pulses_per_sample);
while ss <= 22
    frequency = 100 * 10^((ss-.5)/(11.56));
    sines = sin(2*pi*frequency*Ts*x);
    sinusoids(ss, :) = sines;
    ss = ss + 1;
end

%     
% channel1 = abs(Channel1);
% channel2 = abs(Channel2);
% channel3 = abs(Channel3);
% channel4 = abs(Channel4);
% channel5 = abs(Channel5);
% channel6 = abs(Channel6);
% channel7 = abs(Channel7);
% channel8 = abs(Channel8);
% channel9 = abs(Channel9);
% channel10 = abs(Channel10);
% channel11 = abs(Channel11);
% channel12 = abs(Channel12);
% channel13 = abs(Channel13);
% channel14 = abs(Channel14);
% channel15 = abs(Channel15);
% channel16 = abs(Channel16);
% channel17 = abs(Channel17);
% channel18 = abs(Channel18);
% channel19 = abs(Channel19);
% channel20 = abs(Channel20);
% channel21 = abs(Channel21);
% channel22 = abs(Channel22);
% max = length(channel1) - 1;
% playback = zeros(length(channel1)/48, size(sinusoids, 2));
% x = zeros(1, 96);
% for m = 0:48:max
% for n = 1:8:48
%     
%     runningsum1 = sum(channel1(1, n+m:n+m+7))/8;
%     runningsum2 = sum(channel2(1, n+m:n+m+7))/8;
%     runningsum3 = sum(channel3(1, n+m:n+m+7))/8;
%     runningsum4 = sum(channel4(1, n+m:n+m+7))/8;
%     runningsum5 = sum(channel5(1, n+m:n+m+7))/8;
%     runningsum6 = sum(channel6(1, n+m:n+m+7))/8;
%     runningsum7 = sum(channel7(1, n+m:n+m+7))/8;
%     runningsum8 = sum(channel8(1, n+m:n+m+7))/8;
%     runningsum9 = sum(channel9(1, n+m:n+m+7))/8;
%     runningsum10 = sum(channel10(1, n+m:n+m+7))/8;
%     runningsum11 = sum(channel11(1, n+m:n+m+7))/8;
%     runningsum12 = sum(channel12(1, n+m:n+m+7))/8;
%     runningsum13 = sum(channel13(1, n+m:n+m+7))/8;
%     runningsum14 = sum(channel14(1, n+m:n+m+7))/8;
%     runningsum15 = sum(channel15(1, n+m:n+m+7))/8;
%     runningsum16 = sum(channel16(1, n+m:n+m+7))/8;
%     runningsum17 = sum(channel17(1, n+m:n+m+7))/8;
%     runningsum18 = sum(channel18(1, n+m:n+m+7))/8;
%     runningsum19 = sum(channel19(1, n+m:n+m+7))/8;
%     runningsum20 = sum(channel20(1, n+m:n+m+7))/8;
%     runningsum21 = sum(channel21(1, n+m:n+m+7))/8;
%     runningsum22 = sum(channel22(1, n+m:n+m+7))/8;
%     
%    sumatrix =[runningsum1 runningsum2 runningsum3 runningsum4 runningsum5 runningsum6 runningsum7 
%         runningsum8 runningsum9 runningsum10 runningsum11 runningsum12 runningsum13 
%         runningsum14 runningsum15 runningsum16 runningsum17 runningsum18 runningsum19 
%         runningsum20 runningsum21 runningsum22];
%     shit = (n-1)/8;
%     x(shit) = [find(sumatrix==max(sumatrix)) max(sumatrix)];
%     
% end
% 
%   sound1 = x(2)*sinusoids(x(1), :);
%   sound2 = x(4)*sinusoids(x(3), :);
%   sound3 = x(6)*sinusoids(x(5), :);
%   sound4 = x(8)*sinusoids(x(7), :);
%   sound5 = x(10)*sinusoids(x(9), :);
%   sound6 = x(12)*sinusoids(x(11), :);  
% 
%   currentsample = sound1 + sound2 + sound3 + sound4 + sound5 + sound6;
%   playback(m, :) = currentsample;
%   end
%   
%     
%     
%     
% end
% 
% 
figure 
hold on
for i=1:22
    plot(sinusoids(i,:))
end