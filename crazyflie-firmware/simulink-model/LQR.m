clear
clc

Q = eye(8);
R = eye(4);
load('lqr.mat');
A = lqr.A;
B = lqr.B;
clear lqr;
[K,S,e] = lqr(A,B,Q,R);