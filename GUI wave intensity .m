function varargout = gui(varargin)
%GUI MATLAB code file for gui.fig
% Last Modified by GUIDE v2.5 10-Apr-2021 18:35:16

gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @gui_OpeningFcn, ...
                   'gui_OutputFcn',  @gui_OutputFcn, ...
                   'gui_LayoutFcn',  [], ...
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


% --- Executes just before gui is made visible.
function gui_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   unrecognized PropertyName/PropertyValue pairs from the
%            command line (see VARARGIN)

% Choose default command line output for gui
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes gui wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = gui_OutputFcn(hObject, eventdata, handles)
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in load.
function load_Callback(hObject, eventdata, handles)
% hObject    handle to load (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

[handles.filename,handles.pathname,handles.filterindex]=uigetfile('.txt');
Z=importdata(handles.filename);
axes(handles.graphA);
    for i=1:size(Z)
        pressure(i,1)=Z(i,1)/1000;
        velocity(i,1)=Z(i,2);
    end
K=zeros(126,1);
    for i=1:size(K)
        t=1/200/126;
        time(i)=t*i;
    end
[hAx,hLine1,hLine2]=plotyy(time,pressure,time,velocity);
grid on;
grid minor;
xlabel('Time [s]');
ylabel(hAx(1),'Pressure [kPa]');
ylabel(hAx(2), 'Velocity [m/s]');
guidata(hObject,handles);

% --- Executes on selection change in list.
function list_Callback(hObject, eventdata, handles)
% hObject    handle to list (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns list contents as cell array
%        contents{get(hObject,'Value')} returns selected item from list
speed=handles.speed;
pressure=handles.pressure;
velocity=handles.velocity;
I_net=handles.I_net;
P_forward=handles.P_forward;
P_backward=handles.P_backward;
U_forward=handles.U_forward;
U_backward=handles.U_backward;

switch get(handles.list,'Value')
    case 1
        plot(pressure,velocity);
        xlabel('Velocity [m/s]');
        ylabel('Pressure [Pa]');
        set(handles.speed_value,'String',speed);
    case 2
        plot(I_net);
        ylabel('Net Wave Intensity');
        set(handles.speed_value,'String',speed);
    case 3
        plot(P_forward);
        hold on;
        plot(P_backward,'g');
        hold off;
        ylabel('Pressure [Pa]');
        set(handles.speed_value,'String',speed);
    case 4
        plot(U_forward);
        hold on;
        plot(U_backward,'g');
        hold off;
        ylabel('Velocity [m/s]');
        axis([0,140,-1,1]);
        set(handles.speed_value,'String',speed);
end

% --- Executes during object creation, after setting all properties.
function list_CreateFcn(hObject, eventdata, handles)
% hObject    handle to list (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in waveanalysis.
function waveanalysis_Callback(hObject, eventdata, handles)
% hObject    handle to waveanalysis (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

Z=importdata(handles.filename);
axes(handles.graphB);
    for i=1:size(Z)
        pressure(i,1)=Z(i,1);
        velocity(i,1)=Z(i,2);
    end
handles.pressure=pressure;
handles.velocity=velocity;
plot(pressure,velocity);
[x,y]=ginput(2);
slope=diff(x)./diff(y);
rho=1050;
speed=slope/rho;
handles.speed=speed;
set(handles.speed_value,'String',num2str(speed));

    for i=1:size(Z)-1
        dp(i,1)=Z(i+1,1)-Z(i,1);
        du(i,1)=Z(i+1,2)-Z(i,2);
        H=[dp,du];
    end
    for i=1:size(H)
        dp_forward(i,1)=0.5*(H(i,1)+(rho*speed*H(i,2)));
        dp_backward(i,1)=0.5*(H(i,1)-(rho*speed*H(i,2)));
        du_forward(i,1)=0.5*(H(i,2)+(H(i,1)/(rho*speed)));
        du_backward(i,1)=0.5*(H(i,2)-(H(i,1)/(rho*speed)));
        J=[dp_forward,dp_backward,du_forward,du_backward];
    end
    for i=1:size(J)
        I_forward(i,1)=J(i,1)*J(i,3);
        I_backward(i,1)=J(i,2)*J(i,4);
    end
 I_net=I_forward+I_backward;
 handles.I_net=I_net;
 P0=15.8456;
    for i=1:size(dp_forward)
        P_forward(i,1)=P0+sum(dp_forward(1:i));
    end
    for i=1:size(dp_backward)
        P_backward(i,1)=sum(dp_backward(1:i));
    end
handles.P_forward=P_forward;
handles.P_backward=P_backward;
U0=0.0028;
    for i=1:size(du_forward)
        U_forward(i,1)=U0+sum(du_forward(1:i));
    end
    for i=1:size(du_backward)
        U_backward(i,1)=sum(du_backward(1:i));
    end
handles.U_forward=U_forward;
handles.U_backward=U_backward;
set(handles.list,'String');

 guidata(hObject,handles); 
        
function speed_value_Callback(hObject, eventdata, handles)
% hObject    handle to speed_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)



% Hints: get(hObject,'String') returns contents of speed_value as text
%        str2double(get(hObject,'String')) returns contents of speed_value as a double

% --- Executes during object creation, after setting all properties.
function speed_value_CreateFcn(hObject, eventdata, handles)
% hObject    handle to speed_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
