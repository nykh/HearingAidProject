function [padded_sinusoids, padded_length, extended_sinusoids, extendlength] = Sinusoid_Generator(minimums, fulllength)
extendlength = fulllength;
Ts=1/48000;
size = minimums(1, :);
padded_length = max(size);
frequncy = minimums(2, :);
cycles = minimums(3,:);
padded_sinusoids = zeros(22, padded_length);
for n = 1:1:22;
    for m = 1:1:cycles
    f = frequncy(n);
    count = floor(padded_length/size(n));
    x = [0:1:(count*size(n)-1) zeros(1, padded_length-count*size(n))];
    z = cos(2*pi*f*Ts*x);
    padded_sinusoids(n, :) = z;
    end
end


Ts=1/48000;
size = minimums(1, :);
frequncy = minimums(2, :);
cycles = minimums(3,:);
extended_sinusoids = zeros(22, fulllength);
for n = 1:1:22;
    for m = 1:1:cycles
    f = frequncy(n);
    count = floor(fulllength/size(n));
    x = 0:1:(count*size(n)-1);
    z = cos(2*pi*f*Ts*x);
    extended_sinusoids(n, :) = z;
    end
end
end
