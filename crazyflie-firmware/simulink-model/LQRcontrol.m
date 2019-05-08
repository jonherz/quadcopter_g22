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
 


% Ai = [A zeros(size(A,1),3); -C([1 2 5],:) zeros(3)];
% Bi = [B; zeros(3,size(B,2))];
% Ci = [C zeros(size(C,1),3)];
% Di = zeros(size(Ci,1),4);

sysc = ss(A,B,C,D);

%Discretize system
Ts = 0.01;
sysd = c2d(sysc,Ts);

% Calculate LQR Control Gain
% Set LQR weighting matrices.
ang_max = 15;
ang12_vel_max = 200;
ang3_vel_max = 180;

Q = diag([10^8/ang_max^2 10^8/ang_max^2 10^(-1)/ang12_vel_max^2 10^(-1)/ang12_vel_max^2 10^8/ang3_vel_max^2]);
R = 0.1*eye(4);

% Calculate control gain using LQR optimization.
KLQR = dlqr(sysd.A,sysd.B,Q,R);
KLQR(:,5) = KLQR(:,5)*10;
