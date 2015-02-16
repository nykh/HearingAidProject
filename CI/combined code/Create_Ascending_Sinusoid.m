[sineu, stuff] = Frequency_Finder();
 Fs = 48000;                    % sampling rate
 T = 1/Fs;                      % sampling period
 t_new = 0:1:1999;                % time vector 0:T:0.25'
 result = zeros(1, 2000*22);
 for n = 1:1:22
     
   somestuffIadded = cos(2*pi*sineu(2, n)*T*t_new);      % sinusoidal signal, amplitude = 1
 result(1, (2000*(n-1))+1:(2000*n) ) = somestuffIadded;
 end
 wavwrite(result, 48000, 'Test_Sinusoids');