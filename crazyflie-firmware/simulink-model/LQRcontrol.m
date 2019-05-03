% State vector = [a1 a2 v1 v2 v3 w1 w2 w3]
clear all; clc;

A = [ 0     0     1     0     0
     0     0     0     1     0
     0     0     0     0     0
     0     0     0     0     0
     0     0     0     0     0];

B = [0	0	0	0
	 0	0	0	0
	-0.02094	-0.02094	0.02094     0.02094
    -0.02034	0.02034     0.02034     -0.02034
	-15.03      15.03       -15.03      15.03];
   
% C =    [57.2958   0          0         0         0
%          0   57.2958         0         0         0
%          0         0   57.2958         0         0
%          0         0         0   57.2958         0
%          0         0         0         0   57.2958];
C =    [1   0    0   0   0
         0   1   0   0   0
         0   0   1   0   0
         0   0   0   1   0
         0   0   0   0   1];
     
D = [0     0     0     0
     0     0     0     0
     0     0     0     0
     0     0     0     0
     0     0     0     0];
 


Ai = [A zeros(size(A,1),3); -C([1 2 5],:) zeros(3)];
Bi = [B; zeros(3,size(B,2))];
Ci = [C zeros(size(C,1),3)];
Di = zeros(size(Ci,1),4);

sysc = ss(Ai,Bi,Ci,Di);

%Discretize system
Ts = 0.01;
sysd = c2d(sysc,Ts);

% Calculate LQR Control Gain
% Set LQR weighting matrices.
Q = diag([100 100 1 1 1 40 40 40]);
R = 0.0001*eye(4);

% Calculate control gain using LQR optimization.
KLQR = dlqr(sysd.A,sysd.B,Q,R);
