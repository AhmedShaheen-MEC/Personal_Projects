function varargout = Test(varargin)
% TEST MATLAB code for Test.fig
%      TEST, by itself, creates a new TEST or raises the existing
%      singleton*.
%
%      H = TEST returns the handle to a new TEsST or the handle to
%      the existing singleton*.
%
%      TEST('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in TEST.M with the given input arguments.
%
%      TEST('Property','Value',...) creates a new TEST or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before Test_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to Test_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help Test

% Last Modified by GUIDE v2.5 12-May-2018 00:06:57

% Begin initialization code - DO NOT EDIT

gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @Test_OpeningFcn, ...
                   'gui_OutputFcn',  @Test_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before Test is made visible.
function Test_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to Test (see VARARGIN)

% Choose default command line output for Test
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes Test wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = Test_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;





function VaLUE1_Callback(hObject, eventdata, handles)
% hObject    handle to VaLUE1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of VaLUE1 as text
%        str2double(get(hObject,'String')) returns contents of VaLUE1 as a double



% --- Executes during object creation, after setting all properties.
function VaLUE1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to VaLUE1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function OP_Callback(hObject, eventdata, handles)
% hObject    handle to OP (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of OP as text
%        str2double(get(hObject,'String')) returns contents of OP as a double
 


% --- Executes during object creation, after setting all properties.
function OP_CreateFcn(hObject, eventdata, handles)
% hObject    handle to OP (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton1.
function pushbutton1_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
P=str2double(get(handles.Inputpower,'string'));
%%GEARS 
Module_AB=str2double(get(handles.M_AB,'string'));       %%Input  Module = Velocity Ratio
Module_CD=str2double(get(handles.M_CD,'string'));  
%%INPUT
N_A=str2double(get(handles.shaft_speed,'string'));
%%Speeds
N_B= N_A/Module_AB;
N_D= N_B/Module_CD;
Speed_D=num2str(N_D);
N_C=N_B;
set(handles.Speed_Dd,'string',Speed_D);
%%Teeth 
Teeth_A= str2double(get(handles.Teeth_A,'string'));
D_A=Teeth_A*Module_AB;
Teeth_B= Module_AB*Teeth_A;
Diameter_GA=num2str(D_A);
set(handles.shaft_D_A,'string',Diameter_GA);
D_B=Module_AB*Teeth_B;
Teeth_C=ceil((Module_AB*(Teeth_A+Teeth_B))/(Module_CD*(1+Module_CD)));
Teeth_D= Module_CD*Teeth_C;
D_C=Module_CD*Teeth_C;
D_D=Module_CD*Teeth_D;
%%%GUI INFO
Diameter_GA=num2str(D_A);
set(handles.Diameter_GA,'string',Diameter_GA);
Teeth_GA=num2str(Teeth_A);
set(handles.Teeth_GA,'string',Teeth_GA);


Diameter_GB=num2str(D_B);
set(handles.Diameter_GB,'string',Diameter_GB);
Teeth_GB=num2str(Teeth_B);
set(handles.Teeth_GB,'string',Teeth_GB);

Diameter_GC=num2str(D_C);
set(handles.Diameter_GC,'string',Diameter_GC);
Teeth_GC=num2str(Teeth_C);
set(handles.Teeth_GC,'string',Teeth_GC);

Diameter_GD=num2str(D_D);
set(handles.Diameter_GD,'string',Diameter_GD);
Teeth_GD=num2str(Teeth_D);
set(handles.Teeth_GD,'string',Teeth_GD);


%%%%%%Shaft design
Taw=str2double(get(handles.Taaw,'string'));
Kb=str2double(get(handles.Kb,'string'));
Kt=str2double(get(handles.Kt,'string'));


d1=str2double(get(handles.d1,'string'));
d2=str2double(get(handles.d2,'string'));
d3=str2double(get(handles.d3,'string'));
N=str2double(get(handles.shaft_speed,'string'));
T=(P*1000)/(2*pi*N_A);
%%Shaft _A
%%D_A
dist(1)=str2double(get(handles.dist_A,'string'));
Ft= (2*P*1000)/(2*pi*N*D_A);
M_h= Ft*(dist(1)/2);
Frr= Ft*tan(20*pi/180);
M_v= Frr*(dist(1)/2);
Mb= sqrt((M_v)^2+(M_h)^2);
Fr= sqrt((Ft/2)^2+(Frr/2)^2);
d_A=num2str(((16/(pi*Taw))*sqrt((Kb*Mb)^2+(Kt*T)^2))^(1/3));
set(handles.shaft_D_A,'string',d_A);

V_AB=2*pi*N_A*(D_A/2);
%%Shaft BC
Ft_CD= Ft*(D_B/D_C);
Fr_CD= Ft_CD*tan(20*pi/180);

%%Vertical m@B
Rc_H=abs(((Ft_CD*(d2+d3))-Ft*d1)/(d1+d2+d3));
Rb_H= abs(Ft_CD-Rc_H-Ft);

%%Horizontal m@B
Rc_V=abs(((Fr_CD*(d2+d3))+(Frr*d3))/(d1+d2+d3));
Rb_V= abs(Fr_CD+Frr-Rc_V);

R_B=sqrt(Rb_V^2+Rb_H^2);
R_C=sqrt(Rc_V^2+Rc_H^2);
Mx=Rc_H*d1;
My=Rb_H*d3;
if (R_B> R_C)
    R_BC = R_B;
else 
    R_BC=R_C;
end

Mxv=Rc_V*d3;
Myv=Rb_V*d1;

M_X=sqrt(Mxv^2+Mx^2);
M_Y=sqrt(Myv^2+My^2);

if (M_X > M_Y) 
    M_max=M_X;
else 
    M_max= M_Y;
end 

%%%%%%%D_B=     %%%%%%%
T_BC= Ft*(D_B/2);
d_BC=num2str(((16/(pi*Taw))*sqrt((Kb*M_max)^2+(Kt*T_BC)^2))^(1/3));
set(handles.shaft_D_BC,'string',d_BC);

%%Shaft D
Rd_H=Ft_CD/2;
Rd_V=Fr_CD/2;
R_D= sqrt(Rd_V^2+Rd_H^2);
Lenght_D=str2double(get(handles.d_D,'string')); %Lenght

%%%%%%%D_D= %%%%%%%
Mmax= sqrt((Rd_H*(Lenght_D/2))^2+(Rd_V*(Lenght_D/2))^2);  %% Torque 
T_D= Ft_CD*(D_D/2);
V_CD=pi*(N_D*(D_D));
Shaft_D=num2str(((16/(pi*Taw))*sqrt((Kb*Mmax)^2+(Kt*T_D)^2))^(1/3));
set(handles.shaft_D_D,'string',Shaft_D);

%%%%Gear Design-----------
Segma_FP=str2double(get(handles.Segma_FP,'string'));   %%Input
Yn=str2double(get(handles.Yn,'string')); 
Ytheta=str2double(get(handles.Ytheta,'string')); 
R_G=str2double(get(handles.R_G,'string')); 
if (R_G>0.5 && R_G<0.99)
    Yz=0.658-(0.0759*log(1-R_G));
else 
    Yz=0.5-(0.109*log(1-R_G));
end 


F_S=str2double(get(handles.F_S,'string')); 

Segma_All_A= (Segma_FP *Yn)/(Ytheta*Yz*F_S);
Segma_All_B=(Segma_FP *Yn)/(Ytheta*Yz*F_S);
Segma_All_C=(Segma_FP *Yn)/(Ytheta*Yz*F_S);
Segma_All_D=(Segma_FP *Yn)/(Ytheta*Yz*F_S);




Yj_A=str2double(get(handles.Yj_A,'string')); 
%%Yj_B=str2double(get(handles.Yj_B,'string')); 
%Yj_C=str2double(get(handles.Yj_C,'string')); 
Yj_D=str2double(get(handles.Yj_D,'string')); 

K0=str2double(get(handles.K0,'string')); 
KH_AD=str2double(get(handles.KH_AB,'string')); 
%%KH_BC=str2double(get(handles.KH_CD,'string')); 
Kv_AB=(6.1+V_AB)/6.1;
Kv_CD=(6.1+V_CD)/6.1;

C=Ft*Kv_AB*K0*KH_AD;
D=Segma_All_A*Module_AB*Yj_A;
Face_Width_A= (D*1000\C);
%%Face_Width_B=Segma_All_B*Module_AB*Yj_B-(Ft*Kv_AB*k0*KH_BC);
%%Face_Width_C=Segma_All_C*Module_CD*Yj_C-(Ft_CD*Kv_CD*k0*KH_BC);
Face_Width_D=(Segma_All_D*Module_CD*Yj_D*1000\(Ft_CD*Kv_CD*K0*KH_AD));

B_A=num2str(Face_Width_A);
B_B=num2str(Face_Width_A);
B_D=num2str(Face_Width_D);
B_C=num2str(Face_Width_D);

set(handles.B_A,'string',B_A)
set(handles.B_B,'string',B_B)
set(handles.B_C,'string',B_C)
set(handles.B_D,'string',B_D)

%%Bearings
Fs=str2double(get(handles.OP,'string'));

C0=num2str(Fr*Fs/1000);  %%AA
C0_BC=num2str(R_BC*Fs/1000);  %%B OR C
C0_D=num2str(R_D*Fs/1000);   %%D

set(handles.C0,'string',C0);
set(handles.C0_BC,'string',C0_BC);
set(handles.C0_D,'string',C0_D);

X=str2double(get(handles.dynamic_load_factor,'string'));
%P=(Fr*X);
Ks=str2double(get(handles.bearing_service_factor,'string'));
H=str2double(get(handles.bearing_working_hours,'string'));
aD=str2double(get(handles.reliability_factor,'string'));
L=(H*N*3600)/10^6;

C=num2str(((Ks*Fr*X/aD)*(L)^(1/3))/1000);  %%AA
C_BC=num2str(((Ks*R_BC*X/aD)*(L)^(1/3))/1000);   %%B OR C
C_D=num2str(((Ks*R_D*X/aD)*(L)^(1/3))/1000);   %%DDD

set(handles.C_dynamic,'string',C);
set(handles.C_dynamic_C,'string',C_BC);
set(handles.C_dynamic_D,'string',C_D);




function shaft_D_A_Callback(hObject, eventdata, handles)
% hObject    handle to shaft_D_A (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of shaft_D_A as text
%        str2double(get(hObject,'String')) returns contents of shaft_D_A as a double


% --- Executes during object creation, after setting all properties.
function shaft_D_A_CreateFcn(hObject, eventdata, handles)
% hObject    handle to shaft_D_A (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function C0_Callback(hObject, eventdata, handles)
% hObject    handle to C0 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of C0 as text
%        str2double(get(hObject,'String')) returns contents of C0 as a double


% --- Executes during object creation, after setting all properties.
function C0_CreateFcn(hObject, eventdata, handles)
% hObject    handle to C0 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function C_dynamic_Callback(hObject, eventdata, handles)
% hObject    handle to C_dynamic (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of C_dynamic as text
%        str2double(get(hObject,'String')) returns contents of C_dynamic as a double


% --- Executes during object creation, after setting all properties.
function C_dynamic_CreateFcn(hObject, eventdata, handles)
% hObject    handle to C_dynamic (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton2.
function pushbutton2_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)



function rotation_factor_Callback(hObject, eventdata, handles)
% hObject    handle to rotation_factor (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of rotation_factor as text
%        str2double(get(hObject,'String')) returns contents of rotation_factor as a double


% --- Executes during object creation, after setting all properties.
function rotation_factor_CreateFcn(hObject, eventdata, handles)
% hObject    handle to rotation_factor (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function dynamic_load_factor_Callback(hObject, eventdata, handles)
% hObject    handle to dynamic_load_factor (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of dynamic_load_factor as text
%        str2double(get(hObject,'String')) returns contents of dynamic_load_factor as a double


% --- Executes during object creation, after setting all properties.
function dynamic_load_factor_CreateFcn(hObject, eventdata, handles)
% hObject    handle to dynamic_load_factor (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function bearing_service_factor_Callback(hObject, eventdata, handles)
% hObject    handle to bearing_service_factor (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of bearing_service_factor as text
%        str2double(get(hObject,'String')) returns contents of bearing_service_factor as a double


% --- Executes during object creation, after setting all properties.
function bearing_service_factor_CreateFcn(hObject, eventdata, handles)
% hObject    handle to bearing_service_factor (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function reliability_factor_Callback(hObject, eventdata, handles)
% hObject    handle to reliability_factor (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of reliability_factor as text
%        str2double(get(hObject,'String')) returns contents of reliability_factor as a double


% --- Executes during object creation, after setting all properties.
function reliability_factor_CreateFcn(hObject, eventdata, handles)
% hObject    handle to reliability_factor (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function bearing_working_hours_Callback(hObject, eventdata, handles)
% hObject    handle to bearing_working_hours (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of bearing_working_hours as text
%        str2double(get(hObject,'String')) returns contents of bearing_working_hours as a double


% --- Executes during object creation, after setting all properties.
function bearing_working_hours_CreateFcn(hObject, eventdata, handles)
% hObject    handle to bearing_working_hours (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function shaft_speed_Callback(hObject, eventdata, handles)
% hObject    handle to shaft_speed (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of shaft_speed as text
%        str2double(get(hObject,'String')) returns contents of shaft_speed as a double


% --- Executes during object creation, after setting all properties.
function shaft_speed_CreateFcn(hObject, eventdata, handles)
% hObject    handle to shaft_speed (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Inputpower_Callback(hObject, eventdata, handles)
% hObject    handle to Inputpower (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Inputpower as text
%        str2double(get(hObject,'String')) returns contents of Inputpower as a double


% --- Executes during object creation, after setting all properties.
function Inputpower_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Inputpower (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function max_T_Callback(hObject, eventdata, handles)
% hObject    handle to max_T (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of max_T as text
%        str2double(get(hObject,'String')) returns contents of max_T as a double


% --- Executes during object creation, after setting all properties.
function max_T_CreateFcn(hObject, eventdata, handles)
% hObject    handle to max_T (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function max_Bending_Callback(hObject, eventdata, handles)
% hObject    handle to max_Bending (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of max_Bending as text
%        str2double(get(hObject,'String')) returns contents of max_Bending as a double


% --- Executes during object creation, after setting all properties.
function max_Bending_CreateFcn(hObject, eventdata, handles)
% hObject    handle to max_Bending (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Kb_Callback(hObject, eventdata, handles)
% hObject    handle to Kb (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Kb as text
%        str2double(get(hObject,'String')) returns contents of Kb as a double


% --- Executes during object creation, after setting all properties.
function Kb_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Kb (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Kt_Callback(hObject, eventdata, handles)
% hObject    handle to Kt (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Kt as text
%        str2double(get(hObject,'String')) returns contents of Kt as a double


% --- Executes during object creation, after setting all properties.
function Kt_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Kt (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in popupmenu1.
function popupmenu1_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu1 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu1


% --- Executes during object creation, after setting all properties.
function popupmenu1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in popupmenu2.
function popupmenu2_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu2 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu2


% --- Executes during object creation, after setting all properties.
function popupmenu2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function horizontal_force_Callback(hObject, eventdata, handles)
% hObject    handle to horizontal_force (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of horizontal_force as text
%        str2double(get(hObject,'String')) returns contents of horizontal_force as a double


% --- Executes during object creation, after setting all properties.
function horizontal_force_CreateFcn(hObject, eventdata, handles)
% hObject    handle to horizontal_force (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function vertical_force_Callback(hObject, eventdata, handles)
% hObject    handle to vertical_force (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of vertical_force as text
%        str2double(get(hObject,'String')) returns contents of vertical_force as a double


% --- Executes during object creation, after setting all properties.
function vertical_force_CreateFcn(hObject, eventdata, handles)
% hObject    handle to vertical_force (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function b_Vertical_Callback(hObject, eventdata, handles)
% hObject    handle to b_Vertical (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of b_Vertical as text
%        str2double(get(hObject,'String')) returns contents of b_Vertical as a double


% --- Executes during object creation, after setting all properties.
function b_Vertical_CreateFcn(hObject, eventdata, handles)
% hObject    handle to b_Vertical (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function b_horizontal_Callback(hObject, eventdata, handles)
% hObject    handle to b_horizontal (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of b_horizontal as text
%        str2double(get(hObject,'String')) returns contents of b_horizontal as a double


% --- Executes during object creation, after setting all properties.
function b_horizontal_CreateFcn(hObject, eventdata, handles)
% hObject    handle to b_horizontal (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function d3_Callback(hObject, eventdata, handles)
% hObject    handle to d3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of d3 as text
%        str2double(get(hObject,'String')) returns contents of d3 as a double


% --- Executes during object creation, after setting all properties.
function d3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to d3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function d_D_Callback(hObject, eventdata, handles)
% hObject    handle to d_D (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of d_D as text
%        str2double(get(hObject,'String')) returns contents of d_D as a double


% --- Executes during object creation, after setting all properties.
function d_D_CreateFcn(hObject, eventdata, handles)
% hObject    handle to d_D (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function dist_A_Callback(hObject, eventdata, handles)
% hObject    handle to dist_A (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of dist_A as text
%        str2double(get(hObject,'String')) returns contents of dist_A as a double


% --- Executes during object creation, after setting all properties.
function dist_A_CreateFcn(hObject, eventdata, handles)
% hObject    handle to dist_A (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function D_gear_A_Callback(hObject, eventdata, handles)
% hObject    handle to D_gear_A (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of D_gear_A as text
%        str2double(get(hObject,'String')) returns contents of D_gear_A as a double


% --- Executes during object creation, after setting all properties.
function D_gear_A_CreateFcn(hObject, eventdata, handles)
% hObject    handle to D_gear_A (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function D_gear_D_Callback(hObject, eventdata, handles)
% hObject    handle to D_gear_D (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of D_gear_D as text
%        str2double(get(hObject,'String')) returns contents of D_gear_D as a double


% --- Executes during object creation, after setting all properties.
function D_gear_D_CreateFcn(hObject, eventdata, handles)
% hObject    handle to D_gear_D (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Taaw_Callback(hObject, eventdata, handles)
% hObject    handle to Taaw (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Taaw as text
%        str2double(get(hObject,'String')) returns contents of Taaw as a double


% --- Executes during object creation, after setting all properties.
function Taaw_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Taaw (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function shaft_D_D_Callback(hObject, eventdata, handles)
% hObject    handle to shaft_D_D (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of shaft_D_D as text
%        str2double(get(hObject,'String')) returns contents of shaft_D_D as a double


% --- Executes during object creation, after setting all properties.
function shaft_D_D_CreateFcn(hObject, eventdata, handles)
% hObject    handle to shaft_D_D (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function shaft_D_BC_Callback(hObject, eventdata, handles)
% hObject    handle to shaft_D_BC (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of shaft_D_BC as text
%        str2double(get(hObject,'String')) returns contents of shaft_D_BC as a double


% --- Executes during object creation, after setting all properties.
function shaft_D_BC_CreateFcn(hObject, eventdata, handles)
% hObject    handle to shaft_D_BC (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function D_gear_B_Callback(hObject, eventdata, handles)
% hObject    handle to D_gear_B (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of D_gear_B as text
%        str2double(get(hObject,'String')) returns contents of D_gear_B as a double


% --- Executes during object creation, after setting all properties.
function D_gear_B_CreateFcn(hObject, eventdata, handles)
% hObject    handle to D_gear_B (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function D_gear_C_Callback(hObject, eventdata, handles)
% hObject    handle to D_gear_C (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of D_gear_C as text
%        str2double(get(hObject,'String')) returns contents of D_gear_C as a double


% --- Executes during object creation, after setting all properties.
function D_gear_C_CreateFcn(hObject, eventdata, handles)
% hObject    handle to D_gear_C (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function d2_Callback(hObject, eventdata, handles)
% hObject    handle to d2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of d2 as text
%        str2double(get(hObject,'String')) returns contents of d2 as a double


% --- Executes during object creation, after setting all properties.
function d2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to d2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function d1_Callback(hObject, eventdata, handles)
% hObject    handle to d1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of d1 as text
%        str2double(get(hObject,'String')) returns contents of d1 as a double


% --- Executes during object creation, after setting all properties.
function d1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to d1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes during object deletion, before destroying properties.
function text39_DeleteFcn(hObject, eventdata, handles)
% hObject    handle to text39 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)




% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu3 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu3

    


% --- Executes during object creation, after setting all properties.
function popupmenu3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function C0_BC_Callback(hObject, eventdata, handles)
% hObject    handle to C0_BC (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of C0_BC as text
%        str2double(get(hObject,'String')) returns contents of C0_BC as a double


% --- Executes during object creation, after setting all properties.
function C0_BC_CreateFcn(hObject, eventdata, handles)
% hObject    handle to C0_BC (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function C0_D_Callback(hObject, eventdata, handles)
% hObject    handle to C0_D (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of C0_D as text
%        str2double(get(hObject,'String')) returns contents of C0_D as a double


% --- Executes during object creation, after setting all properties.
function C0_D_CreateFcn(hObject, eventdata, handles)
% hObject    handle to C0_D (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function C_dynamic_BC_Callback(hObject, eventdata, handles)
% hObject    handle to C_dynamic_BC (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of C_dynamic_BC as text
%        str2double(get(hObject,'String')) returns contents of C_dynamic_BC as a double


% --- Executes during object creation, after setting all properties.
function C_dynamic_BC_CreateFcn(hObject, eventdata, handles)
% hObject    handle to C_dynamic_BC (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function C_dynamic_D_Callback(hObject, eventdata, handles)
% hObject    handle to c_dynamic_d (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of c_dynamic_d as text
%        str2double(get(hObject,'String')) returns contents of c_dynamic_d as a double


% --- Executes during object creation, after setting all properties.
function C_dynamic_D_CreateFcn(hObject, eventdata, handles)
% hObject    handle to c_dynamic_d (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function C_Dynamic_D_Callback(hObject, eventdata, handles)
% hObject    handle to C_dynamic_D (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of C_dynamic_D as text
%        str2double(get(hObject,'String')) returns contents of C_dynamic_D as a double


% --- Executes during object creation, after setting all properties.
function C_Dynamic_D_CreateFcn(hObject, eventdata, handles)
% hObject    handle to C_dynamic_D (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function dynamic_D_Callback(hObject, eventdata, handles)
% hObject    handle to dynamic_D (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of dynamic_D as text
%        str2double(get(hObject,'String')) returns contents of dynamic_D as a double


% --- Executes during object creation, after setting all properties.
function dynamic_D_CreateFcn(hObject, eventdata, handles)
% hObject    handle to dynamic_D (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes during object creation, after setting all properties.
function axes3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to axes3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: place code in OpeningFcn to populate axes3



function Diameter_GA_Callback(hObject, eventdata, handles)
% hObject    handle to Diameter_GA (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Diameter_GA as text
%        str2double(get(hObject,'String')) returns contents of Diameter_GA as a double


% --- Executes during object creation, after setting all properties.
function Diameter_GA_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Diameter_GA (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Teeth_GA_Callback(hObject, eventdata, handles)
% hObject    handle to Teeth_GA (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Teeth_GA as text
%        str2double(get(hObject,'String')) returns contents of Teeth_GA as a double


% --- Executes during object creation, after setting all properties.
function Teeth_GA_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Teeth_GA (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Diameter_GB_Callback(hObject, eventdata, handles)
% hObject    handle to Diameter_GB (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Diameter_GB as text
%        str2double(get(hObject,'String')) returns contents of Diameter_GB as a double


% --- Executes during object creation, after setting all properties.
function Diameter_GB_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Diameter_GB (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Teeth_GB_Callback(hObject, eventdata, handles)
% hObject    handle to Teeth_GB (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Teeth_GB as text
%        str2double(get(hObject,'String')) returns contents of Teeth_GB as a double


% --- Executes during object creation, after setting all properties.
function Teeth_GB_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Teeth_GB (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Diameter_GC_Callback(hObject, eventdata, handles)
% hObject    handle to Diameter_GC (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Diameter_GC as text
%        str2double(get(hObject,'String')) returns contents of Diameter_GC as a double


% --- Executes during object creation, after setting all properties.
function Diameter_GC_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Diameter_GC (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Teeth_GC_Callback(hObject, eventdata, handles)
% hObject    handle to Teeth_GC (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Teeth_GC as text
%        str2double(get(hObject,'String')) returns contents of Teeth_GC as a double


% --- Executes during object creation, after setting all properties.
function Teeth_GC_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Teeth_GC (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Diameter_GD_Callback(hObject, eventdata, handles)
% hObject    handle to Diameter_GD (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Diameter_GD as text
%        str2double(get(hObject,'String')) returns contents of Diameter_GD as a double


% --- Executes during object creation, after setting all properties.
function Diameter_GD_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Diameter_GD (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Teeth_GD_Callback(hObject, eventdata, handles)
% hObject    handle to Teeth_GD (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Teeth_GD as text
%        str2double(get(hObject,'String')) returns contents of Teeth_GD as a double


% --- Executes during object creation, after setting all properties.
function Teeth_GD_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Teeth_GD (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function M_AB_Callback(hObject, eventdata, handles)
% hObject    handle to M_AB (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of M_AB as text
%        str2double(get(hObject,'String')) returns contents of M_AB as a double


% --- Executes during object creation, after setting all properties.
function M_AB_CreateFcn(hObject, eventdata, handles)
% hObject    handle to M_AB (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function M_CD_Callback(hObject, eventdata, handles)
% hObject    handle to M_CD (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of M_CD as text
%        str2double(get(hObject,'String')) returns contents of M_CD as a double


% --- Executes during object creation, after setting all properties.
function M_CD_CreateFcn(hObject, eventdata, handles)
% hObject    handle to M_CD (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Teeth_A_Callback(hObject, eventdata, handles)
% hObject    handle to Teeth_A (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Teeth_A as text
%        str2double(get(hObject,'String')) returns contents of Teeth_A as a double


% --- Executes during object creation, after setting all properties.
function Teeth_A_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Teeth_A (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes during object creation, after setting all properties.
function text58_CreateFcn(hObject, eventdata, handles)
% hObject    handle to text58 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called










% --- Executes during object creation, after setting all properties.
function popupmenu4_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit81_Callback(hObject, eventdata, handles)
% hObject    handle to edit81 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit81 as text
%        str2double(get(hObject,'String')) returns contents of edit81 as a double


% --- Executes during object creation, after setting all properties.
function edit81_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit81 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit80_Callback(hObject, eventdata, handles)
% hObject    handle to edit80 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit80 as text
%        str2double(get(hObject,'String')) returns contents of edit80 as a double


% --- Executes during object creation, after setting all properties.
function edit80_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit80 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit79_Callback(hObject, eventdata, handles)
% hObject    handle to C_dynamic (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of C_dynamic as text
%        str2double(get(hObject,'String')) returns contents of C_dynamic as a double


% --- Executes during object creation, after setting all properties.
function edit79_CreateFcn(hObject, eventdata, handles)
% hObject    handle to C_dynamic (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit78_Callback(hObject, eventdata, handles)
% hObject    handle to edit78 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit78 as text
%        str2double(get(hObject,'String')) returns contents of edit78 as a double


% --- Executes during object creation, after setting all properties.
function edit78_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit78 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit77_Callback(hObject, eventdata, handles)
% hObject    handle to edit77 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit77 as text
%        str2double(get(hObject,'String')) returns contents of edit77 as a double


% --- Executes during object creation, after setting all properties.
function edit77_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit77 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit76_Callback(hObject, eventdata, handles)
% hObject    handle to edit76 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit76 as text
%        str2double(get(hObject,'String')) returns contents of edit76 as a double


% --- Executes during object creation, after setting all properties.
function edit76_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit76 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit75_Callback(hObject, eventdata, handles)
% hObject    handle to edit75 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit75 as text
%        str2double(get(hObject,'String')) returns contents of edit75 as a double


% --- Executes during object creation, after setting all properties.
function edit75_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit75 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton3.
function pushbutton3_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)



function edit74_Callback(hObject, eventdata, handles)
% hObject    handle to C0 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of C0 as text
%        str2double(get(hObject,'String')) returns contents of C0 as a double


% --- Executes during object creation, after setting all properties.
function edit74_CreateFcn(hObject, eventdata, handles)
% hObject    handle to C0 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit73_Callback(hObject, eventdata, handles)
% hObject    handle to shaft_D_A (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of shaft_D_A as text
%        str2double(get(hObject,'String')) returns contents of shaft_D_A as a double


% --- Executes during object creation, after setting all properties.
function edit73_CreateFcn(hObject, eventdata, handles)
% hObject    handle to shaft_D_A (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Segma_FP_Callback(hObject, eventdata, handles)
% hObject    handle to Segma_FP (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Segma_FP as text
%        str2double(get(hObject,'String')) returns contents of Segma_FP as a double


% --- Executes during object creation, after setting all properties.
function Segma_FP_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Segma_FP (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Yn_Callback(hObject, eventdata, handles)
% hObject    handle to Yn (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Yn as text
%        str2double(get(hObject,'String')) returns contents of Yn as a double


% --- Executes during object creation, after setting all properties.
function Yn_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Yn (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Ytheta_Callback(hObject, eventdata, handles)
% hObject    handle to Ytheta (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Ytheta as text
%        str2double(get(hObject,'String')) returns contents of Ytheta as a double


% --- Executes during object creation, after setting all properties.
function Ytheta_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Ytheta (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function R_G_Callback(hObject, eventdata, handles)
% hObject    handle to R_G (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of R_G as text
%        str2double(get(hObject,'String')) returns contents of R_G as a double


% --- Executes during object creation, after setting all properties.
function R_G_CreateFcn(hObject, eventdata, handles)
% hObject    handle to R_G (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function KH_AB_Callback(hObject, eventdata, handles)
% hObject    handle to KH_AB (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of KH_AB as text
%        str2double(get(hObject,'String')) returns contents of KH_AB as a double


% --- Executes during object creation, after setting all properties.
function KH_AB_CreateFcn(hObject, eventdata, handles)
% hObject    handle to KH_AB (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function KH_CD_Callback(hObject, eventdata, handles)
% hObject    handle to KH_CD (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of KH_CD as text
%        str2double(get(hObject,'String')) returns contents of KH_CD as a double


% --- Executes during object creation, after setting all properties.
function KH_CD_CreateFcn(hObject, eventdata, handles)
% hObject    handle to KH_CD (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function K0_Callback(hObject, eventdata, handles)
% hObject    handle to K0 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of K0 as text
%        str2double(get(hObject,'String')) returns contents of K0 as a double


% --- Executes during object creation, after setting all properties.
function K0_CreateFcn(hObject, eventdata, handles)
% hObject    handle to K0 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Yj_A_Callback(hObject, eventdata, handles)
% hObject    handle to Yj_A (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Yj_A as text
%        str2double(get(hObject,'String')) returns contents of Yj_A as a double


% --- Executes during object creation, after setting all properties.
function Yj_A_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Yj_A (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Yj_B_Callback(hObject, eventdata, handles)
% hObject    handle to Yj_B (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Yj_B as text
%        str2double(get(hObject,'String')) returns contents of Yj_B as a double


% --- Executes during object creation, after setting all properties.
function Yj_B_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Yj_B (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Yj_C_Callback(hObject, eventdata, handles)
% hObject    handle to Yj_C (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Yj_C as text
%        str2double(get(hObject,'String')) returns contents of Yj_C as a double


% --- Executes during object creation, after setting all properties.
function Yj_C_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Yj_C (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Yj_D_Callback(hObject, eventdata, handles)
% hObject    handle to Yj_D (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Yj_D as text
%        str2double(get(hObject,'String')) returns contents of Yj_D as a double


% --- Executes during object creation, after setting all properties.
function Yj_D_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Yj_D (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function C_dynamic_C_Callback(hObject, eventdata, handles)
% hObject    handle to C_dynamic_C (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of C_dynamic_C as text
%        str2double(get(hObject,'String')) returns contents of C_dynamic_C as a double


% --- Executes during object creation, after setting all properties.
function C_dynamic_C_CreateFcn(hObject, eventdata, handles)
% hObject    handle to C_dynamic_C (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton8.
function pushbutton8_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton8 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)



function B_B_Callback(hObject, eventdata, handles)
% hObject    handle to B_B (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of B_B as text
%        str2double(get(hObject,'String')) returns contents of B_B as a double


% --- Executes during object creation, after setting all properties.
function B_B_CreateFcn(hObject, eventdata, handles)
% hObject    handle to B_B (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function B_C_Callback(hObject, eventdata, handles)
% hObject    handle to B_C (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of B_C as text
%        str2double(get(hObject,'String')) returns contents of B_C as a double


% --- Executes during object creation, after setting all properties.
function B_C_CreateFcn(hObject, eventdata, handles)
% hObject    handle to B_C (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton7.
function pushbutton7_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)



function B_D_Callback(hObject, eventdata, handles)
% hObject    handle to B_D (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of B_D as text
%        str2double(get(hObject,'String')) returns contents of B_D as a double


% --- Executes during object creation, after setting all properties.
function B_D_CreateFcn(hObject, eventdata, handles)
% hObject    handle to B_D (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function B_A_Callback(hObject, eventdata, handles)
% hObject    handle to B_A (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of B_A as text
%        str2double(get(hObject,'String')) returns contents of B_A as a double


% --- Executes during object creation, after setting all properties.
function B_A_CreateFcn(hObject, eventdata, handles)
% hObject    handle to B_A (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes during object creation, after setting all properties.
function cons_CreateFcn(hObject, eventdata, handles)
% hObject    handle to cons (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called





% --- Executes on selection change in popupmenu6.
function popupmenu6_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


axes(handles.axes11);
popup_sel_index = get(handles.popupmenu6, 'Value');
if  popup_sel_index==1
       I1 = imread('Table.jpg');imshow(I1)
elseif popup_sel_index==2
     I1 = imread('Design.png');imshow(I1)
elseif popup_sel_index==3
     I1 = imread('Sheet.png');imshow(I1)
     elseif popup_sel_index==4
     I1 = imread('Bearing6701.png');imshow(I1)
     elseif popup_sel_index==5
     I1 = imread('Bearing1.png');imshow(I1)
end 



% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu6 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu6


% --- Executes during object creation, after setting all properties.
function popupmenu6_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes during object creation, after setting all properties.
function axes11_CreateFcn(hObject, eventdata, handles)
% hObject    handle to axes11 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: place code in OpeningFcn to populate axes11


% --- Executes during object creation, after setting all properties.
function axes12_CreateFcn(hObject, eventdata, handles)
% hObject    handle to axes12 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
axes(hObject)
I11 = imread('Back.jpg');
imshow(I11)
% Hint: place code in OpeningFcn to populate axes12








function Speed_Dd_Callback(hObject, eventdata, handles)
% hObject    handle to Speed_Dd (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Speed_Dd as text
%        str2double(get(hObject,'String')) returns contents of Speed_Dd as a double


% --- Executes during object creation, after setting all properties.
function Speed_Dd_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Speed_Dd (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function F_S_Callback(hObject, eventdata, handles)
% hObject    handle to F_S (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of F_S as text
%        str2double(get(hObject,'String')) returns contents of F_S as a double


% --- Executes during object creation, after setting all properties.
function F_S_CreateFcn(hObject, eventdata, handles)
% hObject    handle to F_S (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes during object deletion, before destroying properties.
function axes12_DeleteFcn(hObject, eventdata, handles)
% hObject    handle to axes12 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
