Ts=1/48000;
max = minimums(1, :);
frequncy = minimums(2, :);
cycles = minimums(3,:);
padded_sinusoids = zeros(22, 400);
for n = 1:1:22;
    for m = 1:1:cycles
    f = frequncy(n);
    count = floor(400/max(n));
    x = [0:1:(count*max(n)-1) zeros(1, 400-count*max(n))];
    z = cos(2*pi*f*Ts*x);
    padded_sinusoids(n, :) = z;
    end
end

Ts=1/48000;
max = minimums(1, :);
frequncy = minimums(2, :);
cycles = minimums(3,:);
uneven_sinusoids = zeros(22, 400);
for n = 1:1:22;
    for m = 1:1:cycles
    f = frequncy(n);
    x = 0:1:399;
    z = cos(2*pi*f*Ts*x);
    uneven_sinusoids(n, :) = z;
    end
end

Ts=1/48000;
max = minimums(1, :);
frequncy = minimums(2, :);
cycles = minimums(3,:);
extended_sinusoids = zeros(22, 24000);
for n = 1:1:22;
    for m = 1:1:cycles
    f = frequncy(n);
    count = floor(24000/max(n));
    x = 0:1:(count*max(n)-1);
    z = cos(2*pi*f*Ts*x);
    extended_sinusoids(n, :) = z;
    end
end