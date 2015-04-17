clc
clear all
close all


Fs = 44100;                    % sampling rate
T = 1/Fs;                      % sampling period
t = [0:T:0.25];                % time vector 0:T:0.25
t_orig = t;  
phi = 2 * pi * 0.25;           % 1/4 cycle phase offset
x1 = cos(2*pi*5*t + phi);      % sinusoidal signal, amplitude = 1
x2 = cos(2*pi*5*t);            % sinusoidal signal, amplitude = 1/3
signal = transpose(x1);

% [signal,Fs] = audioread('sample4.mp3');  % read sound from the file
% t = 1/Fs : 1/Fs: length(signal)/Fs;

x_min = min(abs(signal));
x_max = max(abs(signal));

MCL = 0.6;  % comfortable level measured in micro amps
THR = 0.02; %Threshold level

p = 0.5;    % p < 1
A = (MCL - THR) / ((x_max^p) - (x_min^p));
B = THR - (A*((x_min)^p));


for i=1:size(signal)
    
    if angle(signal(i,1)) ~= 0 
    
        signal_new(i,1) = abs((A.*((signal(i,1)).^p))) + B;
        signal_new(i,1) = -signal_new(i,1);
    
    else
        signal_new(i,1) = abs((A.*((signal(i,1)).^p))) + B;
    end
end



figure
plot(t,signal)
figure
plot(t,signal_new,'--')

% sound(signal_new,Fs)