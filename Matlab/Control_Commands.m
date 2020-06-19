%%All MATLAB COMMANDS CSTD

%To get system properties: 
damp(G_sc) 
%Responses: 
impules()
step()
initial(Sys,Xnot)
A=[3 5 4;3 2 1;0 5 8]; %to take a part from A Aa=A(r_1:r_final, c_initial:c_final)
B=[0;5;2];
C=[1 2 3];
D=[0];
Sys=ss(A,B,C,D)
G_sc= tf(Sys)
% check observability:
rank(obsv(Sys))
%check controllability:
rank(ctrb(Sys))
%poles: 
[V,L]= eig(A) %where V is the eigen vector and L  values
% to get the minmial model and kalman decomposition: 
[Sysm,T]= minreal(Sys) 
%to get the A,B,C,D matrices form Simulink model
[A,B,C,D]= linmod('file name')
to bulid T.F:
G= tf([cofficients of numerator], [cofficients of Den],gain, Sampling time if Discrete)
G= zpk([zeros locations],[poles location],[gain],sampling time if discrete

%Manual poleplacement: 
p=[new poles]
f=-place (A,B,p)
l= -place(A',C',po)' %Observer new poles
% Design:

ni= size(B,2)
no= size(c,1)
n= size(A,1)
%Augmanted plant:
Aaug=[ A zeros(n,no);-C zeros(no)]
Baug=[B;zeros(no,ni)]
Q=blkdiag(C'*C,eye(no))
R=eye(ni)*K %where K is a tuning gain [Control effort]
F= - lqr(Aaug,Baug,Q,R)

%LQG: 
Q_e=B'*B
R_e= q*eye(no)
L=-lqr(A',C',Q_e,R_e)'

%% Discrete design:
Ts; % Sampling time
Sys_d= c2d(Sys,Ts,'zoh') % OR tustin , default is zoh
G_d= tf(Sys_d)

%Optimal design: 
% controller gain:
f_d= -lqrd(Aaug,Baug,Q,R)
%observer gain:
l_d= -dlqr(Sys_d.A',Sys_d.B',Q_d,R_d) %where Q_d,R_d Are new tuning parameters


%% To Bulid a closed loop model: 

%G_cl= feedback(Sys,feedback T.F, -1)
% If you have a block system in simulink and you want to feedback the
% states:
augstate(Sys) % states now at the output of the plan block

%To simulate a model and get the time, input output: 
sim('File name')

%% Model Order reduction: 
[Sysb,g]=balreal(Sys) %where g is Hankel sigular values 
%ALT: 
g_a= hsvd(Sys)
elim= (g<0.005) % return zeros at the matched values
rsys=modred(Sysb,elim,'matchDC') %or 'Truncate'%

[Gstable,Gunstable] = stabsep(G)




