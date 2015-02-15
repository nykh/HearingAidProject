

n = 1;
pos = [1 1 1 1];
neg = [-1 -1 -1 -1];
[x, y] = size(A);
Channel1 = int16.empty(1,0);
Channel2 = int16.empty(1,0);
Channel3 = int16.empty(1,0);
Channel4 = int16.empty(1,0);
Channel5 = int16.empty(1,0);
Channel6 = int16.empty(1,0);
Channel7 = int16.empty(1,0);
Channel8 = int16.empty(1,0);
Channel9 = int16.empty(1,0);
Channel10 = int16.empty(1,0);
Channel11 = int16.empty(1,0);
Channel12 = int16.empty(1,0);
Channel13 = int16.empty(1,0);
Channel14 = int16.empty(1,0);
Channel15 = int16.empty(1,0);
Channel16 = int16.empty(1,0);
Channel17 = int16.empty(1,0);
Channel18 = int16.empty(1,0);
Channel19 = int16.empty(1,0);
Channel20 = int16.empty(1,0);
Channel21 = int16.empty(1,0);
Channel22 = int16.empty(1,0);

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
    Channel4 = [Channel2, zeros([1, 48])];
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