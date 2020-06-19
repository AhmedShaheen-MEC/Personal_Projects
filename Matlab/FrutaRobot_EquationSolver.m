
syms theta1dd theta2dd theta1d theta2d theta1 theta2 tau1 tau2
syms J0 J2 m2 L1 l1 l2 g b1 b2 L2
syms E E0

% thetadd_vect = [theta1dd theta2dd]; % system dynamics 
% Coefficients of the acceleration term: 

dd_coeff = [J0+J2*sin(theta2)^2 m2*L1*l2*cos(theta2);
            m2*L1*l2*cos(theta2) J2];
states_coefficients = dd_coeff\[(m2*L1*l2*sin(theta2)) -J2*sin(2*theta2) -b1 0 0; % system states coefficients 
                        0 0 0 0.5*J2*sin(2*theta2) -b2];
states= [theta2d^2  theta1d*theta2d   theta1d theta1d^2 theta2d]'; % five states   
gravity_term = [0 0;0 -m2*l2*sin(theta2)];  % Input  
tau_vect = [tau1 tau2]';                     % Inputs

gravity_coefficients =(dd_coeff\gravity_term);
tau_coefficients = inv(dd_coeff);

thetadd_vect = states_coefficients*states + gravity_coefficients*[0;g]+ tau_coefficients*tau_vect ; % Non linear equation

% Energy equation:
Ep2 = m2*g*l2*(1 - cos(theta2));
Eke2 = 0.5 * theta1d^2 *(m2*L2^2 + J2*sin(theta2)^2) + 0.5*theta2d^2*(J2) + m2*L1*l2*cos(theta2)*theta1d*theta2d
E = Ep2 + Eke2
pretty(E)
E0 = 0;
diary Results
disp('System states: ')
pretty(states)
disp('Theta_1_dd: ')
disp('States Coefficients: ')
pretty(states_coefficients(1,:))
disp('Gravity Coefficients: ')
pretty(gravity_coefficients(1,:))
disp('Tau1 Coefficients: ')
pretty(tau_coefficients(1,:))

disp('Theta_1_dd Equation: ')
pretty(thetadd_vect(1,:))

disp('Theta_2_dd: ')
disp('States Coefficients: ')
pretty(states_coefficients(2,:))
disp('Gravity Coefficients: ')
pretty(gravity_coefficients(2,:))
disp('Tau1 Coefficients: ')
pretty(tau_coefficients(2,:))

disp('Theta_2_dd Equation: ')
pretty(thetadd_vect(2,:))
diary off
type Results
%%
% %% Linearize the Model about the vetical equilibrium position: Theta1 = 0, Theta2 = pi, Theta_1_dot = 0, Theta_2_dot = 0

theta2 = pi;
% % Refresh the computed symboles.. :
states_coefficients = dd_coeff\[(m2*L1*l2*sin(theta2)) -J2*sin(2*theta2) -b1 0 0; % system states coefficients 
                        0 0 0 0.5*J2*sin(2*theta2) -b2];
gravity_coefficients =(dd_coeff\gravity_term);
tau_coefficients = inv(dd_coeff);
thetadd_vect = states_coefficients*states + gravity_coefficients*[0;g]+ tau_coefficients*tau_vect;
disp('Theta2dd vector Linearized')
pretty(thetadd_vect(1,:))  
pretty(thetadd_vect(2,:))  

%% Numerical Values

g = 9.8
m1= 0.3 %kg
m2= 0.075 %kg
%Mass Location

l1= 0.15 %m
l2= 0.148 %m
b1 = 10^-4 %Nms damping coefficent
b2 = 2.8*(10^-4) %Nms damping coefficent (free joint)

%Motor Parameters
L = 0.005 %Henry
R = 7.8 %ohm
Km = 0.09 %Nm/A
L1 = 0.278 %m
L2 = 0.3 %m

J1= 2.48*(10^-2) %kg/m^2 inertia tensors (moment of inertia in 3D)
J2= 3.86*(10^-3) %kg/m^2 inertia tensors (moment of inertia in 3D)

J1 = J1 + m1*((l1)^2)
J2 = J2 + m2*((l2)^2)
J0 = J1 + m2*((L1)^2)
%%
denm = (J0*J2 - m2^2*L1^2*L2^2);
A31 = 0;
A32 = (g*m2^2*l2^2*L1)/denm ;
A33 = -b1*J2 /denm;
A34 = -b2*m2*l2*L1/ denm;

A41 = 0;
A42 = g*m2*l2*J0/denm;
A43 = -b1*m2*l2*L1 / denm;
A44 = -b2*J0/denm;

A = [0 0 0 1;0 0 1 0; A31 A32 A33 A34; A41 A42 A43 A44];
pretty(A)

B31 = J2 / denm;
B41 = m2*L1*l2 / denm;
B32 = m2*L1*l2 / denm;
B42 = J0/ denm;
B= [0 0;0 0;B31 B32;B41 B42];

Km = 0.09 %Nm/A
Rm = 7.8 %ohm
B = B*(Km/Rm); 
pretty(B)

C = [1 0 0 0;0 1 0 0]
D = 0;

%LQR:

sen1_reg = pi;
sen2_reg = (1*pi)/180;
Qh = [1/sen1_reg 0;0 1/sen2_reg]'
Q = C'*Qh'*Qh*C 
Rh = Rm / Km;
R = B(:,1)'*Rh'* Rh*B(:,1)
A,B,C,D

sys = ss(A,B(:,1),C,D)
K = -lqr(A,B(:,1),Q,R)
K = K(1,:)
    
    
    
    