
L(1)=Link('d', 0, 'a', .12, 'alpha',0);  
L(2)=Link('d', 0, 'a', .18, 'alpha', 0); % a2=432 mm
BB.gravity=[0;9.81;0]
%Define Links geometry:
%Link 1 
BB.links(1).m=0.001*[181.36]              %Link mass
BB.links(1).r=0.001*[93;2.3;25]               %Link center of mass
BB.links(1).I=10^-6*[72780.56  29859.58  1122.98; 29859.58 868146.88 361.83; 1122.98 361.83 864863.32]               %Link inertia 'Matrix'  , How to calc I matrix?
BB.links(1).Jm=0             %Motor inertia
BB.links(1).Tc=  0            %columb firction
BB.links(1).G= 0              %Gearing ratio
BB.links(1).Bm= 0             %%Visc friction


%Link 2 
BB.links(2).m=[0.001]
BB.links(2).r=0.001*[95.01;2.2;15]
BB.links(2).I=10^-6*[15731.90 3219.93 1014.07; 3219.93 319227.53 363.17; 1014.07 363.17 319950.15]
BB.links(2).Jm=0
BB.links(2).Tc=0
BB.links(2).G=0
BB.links(2).Bm=0

BB.Tool=
BB=SerialLink(L, 'name', 'BB')     %% if you want to change the base or the tool write the following:
          
%% BB.base or tool = [  ;  ;  ;  ;] and so on

t= [0:0.1:2] %Define a time vector

%-------------------------------------------------------------------------------------------
% Simple Trajectory planing code
pause(10) 
qi= [0 0]
T=BB.fkine(qi)
BB.plot(qi)
pause 
qf= [pi/4  pi/4]

T=BB.fkine(qf)
BB.plot(qf)
pause(10)

q=jtraj(qi,qf,t)
pause(10)

BB.plot(q)
%-------------------------------------------------------------------------------------------

%%Work Space code
%-------------------------------------------------------------------------------------------
qi_w=[pi/2 pi/2]
T=BB.fkine(qi_w)

plot3(T(1,4),T(2,4),T(3,4),'.', 'MarkerSize',15)
hold

for Trial=0:1000

q1 = (160+160)*rand()-160;
q2 = (225+45)*rand()-45;


pose=[q1 q2];

BB.plot(pose);

T=BB.fkine(pose);

plot3(T(1,4),T(2,4),T(3,4),'.', 'MarkerSize',15)

end
%-------------------------------------------------------------------------------------------

%Jacobian

T0=p560.fkine(qn)

% the value of 1 means that the rotational speed of 

BB.jacob0(q)
det
rank
singu
maniplty

plot.ellipse(J*J') % to show  the limts of  the speeds 'just a representation' jacobian in x , y ,z

%%%%%COMENT%%%% Most probably we will not use the jacob but will use the %%%%%inverse 

%-------------------------------------------------------------------------------------------

%Singularity and velocity and acc calculations:


% set the first pose
T1=transl(0.5, 0.3, 0.44)*troty(pi/2)

% set the second pose
T2=transl(0.5, -0.3, 0.44)*troty(pi/2)

% generate a number of intermediate poses between the two poses
Ts=ctraj(T1, T2, length(t))

% find the inverse kinematics trajectory for the joints to achieve these
% intermediate poses.
qc =BB.ikine(Ts , [0 0],[1 1 0 0 0 0])  %using mask (Try and error method)

%plot the joint angles against time.
qplot(t,qc) %Will plot (q1 and q2 changer vs time)
hold on
pause

% start a new figure
figure

% do a joint space trajectory betweent the two poses
q1=BB.ikine(T1 , [0 0],[1 1 0 0 0 0])
q2=BB.ikine(T2 , [0 0],[1 1 0 0 0 0])
[qj qjd qjdd]=jtraj(q1,q2,length(t))

% plot the set of joint angles against time.
qplot(t,qj)
pause(20)
close
qplot(t,qjd)
pause(20)
close
qplot(t,qjdd)
pause(20)
close
%Scalling the velocity and acc to find the actual values

%Dynamics
%-------------------------------------------------------------------------------------------

%Calculating all the torques 

Fg=BB.gravload.(q)
BB.payload(mass ,[X , Y ,Z]) %(%mass ,[X , Y ,Z]) Add payload at the tool 
F_ALL=BB.rne(q,qd,qdd) 

%Path planing code: Main Code 
%%First Path
Xi  ;Xf 
Yi  ;Yf
%-----------------------
TPi=transl(Xi,Yi,0)*troty(pi)
TPf=transl(Xf,Yf,0)*troty(pi)
Ts1=ctraj(TPi,TPf,length(t))
qs1=BB.ikine(Ts1 , [0 0],[1 1 0 0 0 0])
figure
BB.plot(qs1)
hold on
p11=transl(Ts1)
plot3(p11(1,1),p11(1,2),p11(1,3),'.', 'MarkerSize',10)



%%Second  Path
Xi  ;Xf 
Yi  ;Yf
%-----------------------
TPi2=transl(Xi,Yi,0)*troty(pi)
TPf=transl(Xf,Yf,0)*troty(pi)
Ts2=ctraj(TPi2,TPf,length(t))
qs2=BB.ikine(Ts2 , [0 0],[1 1 0 0 0 0])
figure
BB.plot(qs2)
hold on
p2=transl(Ts3)
plot3(p2(1,1),p2(1,2),p2(1,3),'.', 'MarkerSize',10)






%%Third Path
Xi  ;Xf 
Yi  ;Yf
%-----------------------
TPi3=transl(Xi,Yi,0)*troty(pi)
TPf3=transl(Xf,Yf,0)*troty(pi)
Ts3=ctraj(TPi3,TPf3,length(t))
qs3=BB.ikine(Ts3 , [0 0],[1 1 0 0 0 0])
figure
for 1:length(t)
x=1;
qs_3=[(1,x),(1,x)]    
BB.plot(qs_3)
hold on
Ts_3=[(1,x),(1,x),(1,x)] 
p33=transl(Ts_3)
plot3(p33(1,1),p33(1,2),p33(1,3),'.', 'MarkerSize',10)
x++;
end
%----------------------