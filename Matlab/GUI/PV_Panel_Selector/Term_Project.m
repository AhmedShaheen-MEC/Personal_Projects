function varargout = Term_Project(varargin)
% TERM_PROJECT MATLAB code for Term_Project.fig
%      TERM_PROJECT, by itself, creates a new TERM_PROJECT or raises the existing
%      singleton*.
%
%      H = TERM_PROJECT returns the handle to a new TERM_PROJECT or the handle to
%      the existing singleton*.
%
%      TERM_PROJECT('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in TERM_PROJECT.M with the given input arguments.
%
%      TERM_PROJECT('Property','Value',...) creates a new TERM_PROJECT or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before Term_Project_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to Term_Project_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help Term_Project

% Last Modified by GUIDE v2.5 07-May-2018 13:17:52

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @Term_Project_OpeningFcn, ...
                   'gui_OutputFcn',  @Term_Project_OutputFcn, ...
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


% --- Executes just before Term_Project is made visible.
function Term_Project_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to Term_Project (see VARARGIN)

% Choose default command line output for Term_Project
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes Term_Project wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = Term_Project_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in pushbutton1.
function pushbutton1_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

%%Loads

Total_Power=str2double(get(handles.Watt,'string'));
Total_Cons_Week=str2double(get(handles.KWh,'string'));  %%KWh

Total_Month=num2str(Total_Cons_Week);
set(handles.Monthly,'string',Total_Month);

%%Battery

Sys_Loss=Total_Cons_Week*1.2;
Amp_H_Week=Sys_Loss/12;
Amp_H_T=(Amp_H_Week*1.19*2*2/7);
Battery_Cap=str2double(get(handles.Battery_C,'string'));
N_Battery=ceil(Amp_H_T/Battery_Cap);
N_B=num2str(N_Battery);
set(handles.N_B,'string',N_B);

Unit_Price_B=str2double(get(handles.Battery_Price,'string'));
Total_b_cost=N_Battery*Unit_Price_B;
B_C=num2str(Total_b_cost);
set(handles.B_C,'string',B_C);

%%Controller

Amp_S=(Total_Power*1.2)/12;
Cap=str2double(get(handles.Controller_C,'string'));
N_Con=ceil(Amp_S/Cap);
N_C=num2str(N_Con);
set(handles.N_C,'string',N_C);
Unit_Price=str2double(get(handles.Controller_Price,'string'));
Cost_c=Unit_Price*N_Con;
Total_Cost=num2str(Unit_Price*N_Con);
set(handles.C_C,'string',Total_Cost);

%%Inverter

Inverter_Power=str2double(get(handles.Inverter_C,'string'));
Numb_Inverters=ceil((Total_Power*1.2)/Inverter_Power);
Price=str2double(get(handles.Inverter_Price,'string'));
Inv_Cost=num2str(Numb_Inverters*Price);
I_c=Numb_Inverters*Price;
set(handles.I_C,'string',Inv_Cost);
N_I=num2str(Numb_Inverters);
set(handles.N_I,'string',N_I);

%%Array


Nominal_Rating=str2double(get(handles.Panel_Rating,'string'));

Peak_AMP=str2double(get(handles.Panel_AMPs,'string'));

D_sun_H=str2double(get(handles.Sun_H,'string'));

Unit_PV_price=str2double(get(handles.PV_Price,'string'));

Total_AMP= Amp_S/D_sun_H;

Numb_Of_Array=ceil(Total_AMP/Peak_AMP);
N_A=num2str(Numb_Of_Array);
set(handles.N_A,'string',N_A);

Power_OUT=Nominal_Rating*Numb_Of_Array;

Array_C=Unit_PV_price*Numb_Of_Array;
A_C=num2str(Array_C);
set(handles.A_C,'string',A_C);

Area_Array = str2double(get(handles.Area,'string'));

TOT_A=(Area_Array*Numb_Of_Array);

Area=num2str(TOT_A);
set(handles.TOT_A,'string',11.4);
set(handles.TOT_A,'string',Area);


%%Total
Total=Array_C+I_c+Cost_c+Total_b_cost;
set(handles.T_Cost,'string',Total);




function Monthly_Callback(hObject, eventdata, handles)
% hObject    handle to Monthly (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Monthly as text
%        str2double(get(hObject,'String')) returns contents of Monthly as a double


% --- Executes during object creation, after setting all properties.
function Monthly_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Monthly (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function N_C_Callback(hObject, eventdata, handles)
% hObject    handle to N_C (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of N_C as text
%        str2double(get(hObject,'String')) returns contents of N_C as a double


% --- Executes during object creation, after setting all properties.
function N_C_CreateFcn(hObject, eventdata, handles)
% hObject    handle to N_C (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function C_C_Callback(hObject, eventdata, handles)
% hObject    handle to C_C (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of C_C as text
%        str2double(get(hObject,'String')) returns contents of C_C as a double


% --- Executes during object creation, after setting all properties.
function C_C_CreateFcn(hObject, eventdata, handles)
% hObject    handle to C_C (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function I_C_Callback(hObject, eventdata, handles)
% hObject    handle to I_C (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of I_C as text
%        str2double(get(hObject,'String')) returns contents of I_C as a double


% --- Executes during object creation, after setting all properties.
function I_C_CreateFcn(hObject, eventdata, handles)
% hObject    handle to I_C (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function N_B_Callback(hObject, eventdata, handles)
% hObject    handle to N_B (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of N_B as text
%        str2double(get(hObject,'String')) returns contents of N_B as a double


% --- Executes during object creation, after setting all properties.
function N_B_CreateFcn(hObject, eventdata, handles)
% hObject    handle to N_B (see GCBO)
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



function A_C_Callback(hObject, eventdata, handles)
% hObject    handle to A_C (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of A_C as text
%        str2double(get(hObject,'String')) returns contents of A_C as a double


% --- Executes during object creation, after setting all properties.
function A_C_CreateFcn(hObject, eventdata, handles)
% hObject    handle to A_C (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function T_Cost_Callback(hObject, eventdata, handles)
% hObject    handle to T_Cost (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of T_Cost as text
%        str2double(get(hObject,'String')) returns contents of T_Cost as a double


% --- Executes during object creation, after setting all properties.
function T_Cost_CreateFcn(hObject, eventdata, handles)
% hObject    handle to T_Cost (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit21_Callback(hObject, eventdata, handles)
% hObject    handle to edit21 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit21 as text
%        str2double(get(hObject,'String')) returns contents of edit21 as a double


% --- Executes during object creation, after setting all properties.
function edit21_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit21 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function N_I_Callback(hObject, eventdata, handles)
% hObject    handle to N_I (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of N_I as text
%        str2double(get(hObject,'String')) returns contents of N_I as a double


% --- Executes during object creation, after setting all properties.
function N_I_CreateFcn(hObject, eventdata, handles)
% hObject    handle to N_I (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function N_A_Callback(hObject, eventdata, handles)
% hObject    handle to N_A (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of N_A as text
%        str2double(get(hObject,'String')) returns contents of N_A as a double


% --- Executes during object creation, after setting all properties.
function N_A_CreateFcn(hObject, eventdata, handles)
% hObject    handle to N_A (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Inverter_C_Callback(hObject, eventdata, handles)
% hObject    handle to Inverter_C (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Inverter_C as text
%        str2double(get(hObject,'String')) returns contents of Inverter_C as a double


% --- Executes during object creation, after setting all properties.
function Inverter_C_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Inverter_C (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Inverter_Price_Callback(hObject, eventdata, handles)
% hObject    handle to Inverter_Price (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Inverter_Price as text
%        str2double(get(hObject,'String')) returns contents of Inverter_Price as a double


% --- Executes during object creation, after setting all properties.
function Inverter_Price_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Inverter_Price (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in Controller_Price.
function Controller_Price_Callback(hObject, eventdata, handles)
% hObject    handle to Controller_Price (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of Controller_Price


% --- Executes during object creation, after setting all properties.
function Controller_Price_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Controller_Price (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called



function Controller_C_Callback(hObject, eventdata, handles)
% hObject    handle to Controller_C (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Controller_C as text
%        str2double(get(hObject,'String')) returns contents of Controller_C as a double


% --- Executes during object creation, after setting all properties.
function Controller_C_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Controller_C (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Panel_Rating_Callback(hObject, eventdata, handles)
% hObject    handle to Panel_Rating (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Panel_Rating as text
%        str2double(get(hObject,'String')) returns contents of Panel_Rating as a double


% --- Executes during object creation, after setting all properties.
function Panel_Rating_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Panel_Rating (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Panel_AMPs_Callback(hObject, eventdata, handles)
% hObject    handle to Panel_AMPs (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Panel_AMPs as text
%        str2double(get(hObject,'String')) returns contents of Panel_AMPs as a double


% --- Executes during object creation, after setting all properties.
function Panel_AMPs_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Panel_AMPs (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Sun_H_Callback(hObject, eventdata, handles)
% hObject    handle to Sun_H (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Sun_H as text
%        str2double(get(hObject,'String')) returns contents of Sun_H as a double


% --- Executes during object creation, after setting all properties.
function Sun_H_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Sun_H (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function PV_Price_Callback(hObject, eventdata, handles)
% hObject    handle to PV_Price (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of PV_Price as text
%        str2double(get(hObject,'String')) returns contents of PV_Price as a double


% --- Executes during object creation, after setting all properties.
function PV_Price_CreateFcn(hObject, eventdata, handles)
% hObject    handle to PV_Price (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Watt_Callback(hObject, eventdata, handles)
% hObject    handle to Watt (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Watt as text
%        str2double(get(hObject,'String')) returns contents of Watt as a double


% --- Executes during object creation, after setting all properties.
function Watt_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Watt (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function KWh_Callback(hObject, eventdata, handles)
% hObject    handle to KWh (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of KWh as text
%        str2double(get(hObject,'String')) returns contents of KWh as a double


% --- Executes during object creation, after setting all properties.
function KWh_CreateFcn(hObject, eventdata, handles)
% hObject    handle to KWh (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Battery_Price_Callback(hObject, eventdata, handles)
% hObject    handle to Battery_Price (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Battery_Price as text
%        str2double(get(hObject,'String')) returns contents of Battery_Price as a double


% --- Executes during object creation, after setting all properties.
function Battery_Price_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Battery_Price (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Battery_C_Callback(hObject, eventdata, handles)
% hObject    handle to Battery_C (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Battery_C as text
%        str2double(get(hObject,'String')) returns contents of Battery_C as a double


% --- Executes during object creation, after setting all properties.
function Battery_C_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Battery_C (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes during object creation, after setting all properties.
function axes1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to axes1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: place code in OpeningFcn to populate axes1



% --- Executes during object creation, after setting all properties.
function axes2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to axes2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: place code in OpeningFcn to populate axes2


% --- Executes during object creation, after setting all properties.
function axes3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to axes3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
axes(hObject)
I9 = imread('pic.jpeg');
imshow(I9)

% Hint: place code in OpeningFcn to populate axes3



function TOT_A_Callback(hObject, eventdata, handles)
% hObject    handle to TOT_A (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of TOT_A as text
%        str2double(get(hObject,'String')) returns contents of TOT_A as a double


% --- Executes during object creation, after setting all properties.
function TOT_A_CreateFcn(hObject, eventdata, handles)
% hObject    handle to TOT_A (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Area_Callback(hObject, eventdata, handles)
% hObject    handle to Area (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Area as text
%        str2double(get(hObject,'String')) returns contents of Area as a double


% --- Executes during object creation, after setting all properties.
function Area_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Area (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
