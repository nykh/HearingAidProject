channel1 = abs(channel1);
channel2 = abs(channel2);
channel3 = abs(channel3);
channel4 = abs(channel4);
channel5 = abs(channel5);
channel6 = abs(channel6);
channel7 = abs(channel7);
channel8 = abs(channel8);
channel9 = abs(channel9);
channel10 = abs(channel10);
channel11 = abs(channel11);
channel12 = abs(channel12);
channel13 = abs(channel13);
channel14 = abs(channel14);
channel15 = abs(channel15);
channel16 = abs(channel16);
channel17 = abs(channel17);
channel18 = abs(channel18);
channel19 = abs(channel19);
channel20 = abs(channel20);
channel21 = abs(channel21);
channel22 = abs(channel22);
max = length(channel1) - 1;
playback = zeros(length(channel1)/48, size(sinusoids, 2));
x = zeros(1, 96);
for m = 0:48:max
for n = 1:8:48
    
    runningsum1 = sum(channel1(1, n+m:n+m+7));
    runningsum2 = sum(channel2(1, n+m:n+m+7));
    runningsum3 = sum(channel3(1, n+m:n+m+7));
    runningsum4 = sum(channel4(1, n+m:n+m+7));
    runningsum5 = sum(channel5(1, n+m:n+m+7));
    runningsum6 = sum(channel6(1, n+m:n+m+7));
    runningsum7 = sum(channel7(1, n+m:n+m+7));
    runningsum8 = sum(channel8(1, n+m:n+m+7));
    runningsum9 = sum(channel9(1, n+m:n+m+7));
    runningsum10 = sum(channel10(1, n+m:n+m+7));
    runningsum11 = sum(channel11(1, n+m:n+m+7));
    runningsum12 = sum(channel12(1, n+m:n+m+7));
    runningsum13 = sum(channel13(1, n+m:n+m+7));
    runningsum14 = sum(channel14(1, n+m:n+m+7));
    runningsum15 = sum(channel15(1, n+m:n+m+7));
    runningsum16 = sum(channel16(1, n+m:n+m+7));
    runningsum17 = sum(channel17(1, n+m:n+m+7));
    runningsum18 = sum(channel18(1, n+m:n+m+7));
    runningsum19 = sum(channel19(1, n+m:n+m+7));
    runningsum20 = sum(channel20(1, n+m:n+m+7));
    runningsum21 = sum(channel21(1, n+m:n+m+7));
    runningsum22 = sum(channel22(1, n+m:n+m+7));
    
   sumatrix =[runningsum1 runningsum2 runningsum3 runningsum4 runningsum5 runningsum6 runningsum7 
        runningsum8 runningsum9 runningsum10 runningsum11 runningsum12 runningsum13 
        runningsum14 runningsum15 runningsum16 runningsum17 runningsum18 runningsum19 
        runningsum20 runningsum21 runningsum22];
    shit = (n-1)/8;
    x(shit) = [find(sumatrix==max(sumatrix)) max(sumatrix)];
    
end

  sound1 = x(2)*sinusoids(x(1), :);
  sound2 = x(4)*sinusoids(x(3), :);
  sound3 = x(6)*sinusoids(x(5), :);
  sound4 = x(8)*sinusoids(x(7), :);
  sound5 = x(10)*sinusoids(x(9), :);
  sound6 = x(12)*sinusoids(x(11), :);  

  currentsample = sound1 + sound2 + sound3 + sound4 + sound5 + sound6;
  playback(m, :) = currentsample;
  end

