%%
syms wx wy wz phi theta psi real;

angle = [phi theta psi];
w = [wx wy wz]';
Jx = 1.395e-5;
Jy = 1.436e-5;
Jz = 2.173e-5;
J = diag([Jx Jy Jz]');
crossJw = vpa(-cross(w,J*w),5)
crossJwinv = vpa(inv(J)*crossJw,5)

R_x = [1             0              0;
            0 cos(angle(1)) -sin(angle(1));
            0 sin(angle(1)) cos(angle(1))]; 
        
R_y = [cos(angle(2)) 0 sin(angle(2));
        0             1             0;
       -sin(angle(2)) 0 cos(angle(2))];

R_z = [cos(angle(3)) -sin(angle(3)) 0;
        sin(angle(3)) cos(angle(3))  0;
        0             0              1];

R = R_x*R_y*R_z;


%%
d = 0.046;
k = 1e-9;
b = 2.75e-11;

tau_x = d*cos(pi/4)*[-1 -1 1 1];
tau_y = d*sin(pi/4)*[-1 1 1 -1];


tau_z = k/b * [-1 1 -1 1];



tau = [tau_x;tau_y;tau_z];