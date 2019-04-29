clear
clc

Q = eye(8);
R = eye(4);
load('lqr.mat');
T = 0.01;
Ac = lqr.A;
Bc = lqr.B;
Cc = lqr.C;
SYS = ss(Ac,Bc,Cc,0);
KUNG = c2d(SYS,T);

Ad = KUNG.A;
Bd = KUNG.B;
Cd = KUNG.C;
Dd = KUNG.D;
clear lqr;
[KLQR,S,e] = dlqr(KUNG.A,KUNG.B,Q,R);