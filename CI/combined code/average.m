clc
close all
clear all

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

Fs = 48000;                    % sampling rate
T = 1/Fs;                      % sampling period
t_new = [0:T:0.25];                % time vector 0:T:0.25
phi = 2 * pi * 0.25;           % 1/4 cycle phase offset
signal = cos(2*pi*101*t_new + phi);      % sinusoidal signal, amplitude = 1
%y = cos(2*pi*5*t);            % sinusoidal signal, amplitude = 1/3
signal = transpose(signal);

clear phi T 
% 
% plot(signal)
% hold on


% [signal,Fs] = audioread('sample4.mp3');  % read sound from the file
% t_new = 1/Fs : 1/Fs: length(signal)/Fs;


i = 1;
d = [];
w = [];

while i<length(signal)
    
    if(i+1000 > length(signal))
        y = signal(i:length(signal),1);
    
    else
        y = signal(i:i+1000,1);
    end
    
    
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
    
y = [y1 y2 y3 y4 y5 y6 y7 y8 y9 y10 y11 y12 y13 y14 y15 y16 y17 y18 y19 y20 y21 y22];


x = [mean(y1) mean(y2) mean(y3) mean(y4) mean(y5) mean(y6) mean(y7) mean(y8) mean(y9) mean(y10) mean(y11) mean(y12) mean(y13) mean(y14) mean(y15) mean(y16) mean(y17) mean(y18) mean(y19) mean(y20) mean(y21) mean(y22)];

c = 1:1:22;
b = [x ; c];

    counter = 22;
    for j=1:(counter-8) %this number alters the # of channels activated
        [val,idx] =  min(abs(x(1,:)));
        c(idx) = [];
        x(idx) = [];

        b(:,idx) = [];
        y (:,idx) = [];

    end
    
    f = y(:,1) + y(:,2) + y(:,3) + y(:,4) + y(:,5) + y(:,6) + y(:,7) + y(:,8);
    %f = f + y(:,9) + y(:,10) + y(:,11) + y(:,12) + y(:,13) + y(:,14) + y(:,15);
    %f = f + y(:,16) + y(:,17) + y(:,18) + y(:,19) + y(:,20) + y(:,21) + y(:,22);
    % f = f.*4; % varies the gain of the signal
    
    g = [y(:,1),y(:,2),y(:,3),y(:,4),y(:,5),y(:,6),y(:,7),y(:,8)];
    
   
    
    l = [x ; c];
    w = [w , l];
    d = [d ; f];
    i = i + 1000;
    
    clear l g j y counter c val x b f idx val x
end







