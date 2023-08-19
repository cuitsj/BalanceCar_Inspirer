function varargout = cargui2(varargin)

% CARGUI2 MATLAB code for cargui2.fig
%      CARGUI2, by itself, creates a new CARGUI2 or raises the existing
%      singleton*.
%
%      H = CARGUI2 returns the handle to a new CARGUI2 or the handle to
%      the existing singleton*.
%
%      CARGUI2('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in CARGUI2.M with the given input arguments.
%
%      CARGUI2('Property','Value',...) creates a new CARGUI2 or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before cargui2_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to cargui2_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help cargui2

% Last Modified by GUIDE v2.5 09-Jul-2021 10:32:26

% Begin initialization code - DO NOT EDIT
gui_Singleton = 0;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @cargui2_OpeningFcn, ...
                   'gui_OutputFcn',  @cargui2_OutputFcn, ...
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


% --- Executes just before cargui2 is made visible.
function cargui2_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to cargui2 (see VARARGIN)

% Choose default command line output for cargui2
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes cargui2 wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = cargui2_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in dakaichuankou.
function dakaichuankou_Callback(hObject, eventdata, handles)
% hObject    handle to dakaichuankou (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global scom loop_flag ax ay az gx gy gz temp L_encoder R_encoder vol roll pitch comnumber baudrate
    
    if isempty(comnumber)
        comnumber='COM4';%默认串口4
    end
    if isempty(baudrate)
        baudrate=115200;%默认波特率115200
    end
    if strcmp(comnumber,'COM4')
        set(handles.comnum,'Value',4);
    end
    if baudrate==115200
        set(handles.botelv,'Value',2);
    end
    delete(instrfindall) %%关闭没用的，这句很重要 
    scom = serial(comnumber);
    scom.InputBufferSize =512;
    scom.OutputBufferSize =512;
    scom.ReadAsyncMode='continuous';
    scom.BaudRate =baudrate;
    scom.Parity ='none';
    scom.StopBits =1;
    scom.DataBits =8;
    scom.Terminator ='CR';
    scom.FlowControl ='none';
    scom.timeout =1;
    scom.BytesAvailableFcnMode = 'byte';
    scom.BytesAvailableFcnCount = 20;    
    scom.BytesAvailableFcn = {@callback,handles};

    try
        fopen(scom);
        fprintf(1,'串口打开成功\n'); 
    catch
         fprintf(1,'串口打开失败\n'); 
         msgbox('串口打开失败!','Error','error');
    end
    
    loop_flag=1;
    v = [1,1.5,1;-1,1.5,1;-1,-1.5,1;1,-1.5,1;
        1,1.5,-1;-1,1.5,-1;-1,-1.5,-1; 1,-1.5,-1];%长方体的8个顶点
    f = [1,2,3,4;5,6,7,8;1,4,8,5;1,2,6,5;3,2,6,7;3,4,8,7];%将8个点按照长方体连接起来
    col=[0 0 1;0 1 0;1 0 0;1 0 1;1 1 0;0 1 1];

    persistent aa
    
    if isempty(aa)
        aa=patch('Faces',f,'Vertices',v,'FaceVertexCData',col,'FaceColor','flat');%绘制立方体
        delete(aa);
    end

    view(3);%设置默认的方位角和仰角或者三维空间中的点来指定视点
    axis([-3,3,-3,3,-3,3]);%坐标系范围
    gca_h=gca;
    set(gca_h, 'XGrid', 'on');
    set(gca_h, 'YGrid', 'on');
    set(gca_h, 'ZGrid', 'on');
    %% 细小的网格
%     set(gca_h, 'XMinorGrid', 'on');
%     set(gca_h, 'YMinorGrid', 'on');
%     set(gca_h, 'ZMinorGrid', 'on');
    xlabel('X-axis');
    ylabel('Y-axis');
    zlabel('Z-axis');
    
    
while(loop_flag)
    %% 显示个各项参数
    set(handles.vol,'String',num2str(vol,'%2.2f'));
    set(handles.temp,'String',num2str(temp,'%2.2f'));
    set(handles.gyrx,'String',num2str(gx));
    set(handles.gyry,'String',num2str(gy));
    set(handles.gyrz,'String',num2str(gz));
    set(handles.accx,'String',num2str(ax));
    set(handles.accy,'String',num2str(ay));
    set(handles.accz,'String',num2str(az));
    set(handles.encoder_left,'String',num2str(L_encoder));
    set(handles.encoder_right,'String',num2str(R_encoder));
    title(['Pitch = ',num2str(pitch,'%.1f'),',  Roll = ',num2str(roll,'%.1f'),' (degree)']);

    %% 立方体旋转
    Rx = rotx(roll);%得到绕X轴旋转的旋转矩阵
    Ry = roty(pitch);
    V = Ry*Rx*v';

    delete(aa);
    aa=patch('Faces',f,'Vertices',V','FaceVertexCData',col,'FaceColor','flat');%绘制立方体
    drawnow;
end


% --- Executes on button press in togglebutton1.
function togglebutton1_Callback(hObject, eventdata, handles)
% hObject    handle to togglebutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of togglebutton1


% --- Executes on selection change in comnum.
function comnum_Callback(hObject, eventdata, handles)
% hObject    handle to comnum (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns comnum contents as cell array
%        contents{get(hObject,'Value')} returns selected item from comnum
global comnumber
num = get(handles.comnum,'Value');
switch num
    case 1
        comnumber='COM1';
    case 2
        comnumber='COM2';
    case  3
        comnumber='COM3';
    case  4
        comnumber='COM4';
    case  5
        comnumber='COM5';
    case  6
        comnumber='COM6';
    case  7
        comnumber='COM7';
    case  8
        comnumber='COM8';
    case  9
        comnumber='COM9';
    case  10
        comnumber='COM10';
    otherwise
        comnumber='COM4';
end


% --- Executes during object creation, after setting all properties.
function comnum_CreateFcn(hObject, eventdata, handles)
% hObject    handle to comnum (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in radiobutton1.
function radiobutton1_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of radiobutton1


% --- Executes on slider movement.
function slider2_Callback(hObject, eventdata, handles)
% hObject    handle to slider2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function slider2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on selection change in botelv.
function botelv_Callback(hObject, eventdata, handles)
% hObject    handle to botelv (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns botelv contents as cell array
%        contents{get(hObject,'Value')} returns selected item from botelv
global baudrate
num = get(handles.botelv,'Value');
if num==1
    baudrate=9600;
elseif num==2
    baudrate=115200;
else
    baudrate=115200;
end

% --- Executes during object creation, after setting all properties.
function botelv_CreateFcn(hObject, eventdata, handles)
% hObject    handle to botelv (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function vol_Callback(hObject, eventdata, handles)
% hObject    handle to vol (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of vol as text
%        str2double(get(hObject,'String')) returns contents of vol as a double



% --- Executes during object creation, after setting all properties.
function vol_CreateFcn(hObject, eventdata, handles)
% hObject    handle to vol (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function temp_Callback(hObject, eventdata, handles)
% hObject    handle to temp (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of temp as text
%        str2double(get(hObject,'String')) returns contents of temp as a double


% --- Executes during object creation, after setting all properties.
function temp_CreateFcn(hObject, eventdata, handles)
% hObject    handle to temp (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function gyrx_Callback(hObject, eventdata, handles)
% hObject    handle to gyrx (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of gyrx as text
%        str2double(get(hObject,'String')) returns contents of gyrx as a double


% --- Executes during object creation, after setting all properties.
function gyrx_CreateFcn(hObject, eventdata, handles)
% hObject    handle to gyrx (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function gyry_Callback(hObject, eventdata, handles)
% hObject    handle to gyry (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of gyry as text
%        str2double(get(hObject,'String')) returns contents of gyry as a double


% --- Executes during object creation, after setting all properties.
function gyry_CreateFcn(hObject, eventdata, handles)
% hObject    handle to gyry (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function gyrz_Callback(hObject, eventdata, handles)
% hObject    handle to gyrz (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of gyrz as text
%        str2double(get(hObject,'String')) returns contents of gyrz as a double


% --- Executes during object creation, after setting all properties.
function gyrz_CreateFcn(hObject, eventdata, handles)
% hObject    handle to gyrz (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function accx_Callback(hObject, eventdata, handles)
% hObject    handle to accx (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of accx as text
%        str2double(get(hObject,'String')) returns contents of accx as a double


% --- Executes during object creation, after setting all properties.
function accx_CreateFcn(hObject, eventdata, handles)
% hObject    handle to accx (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function accy_Callback(hObject, eventdata, handles)
% hObject    handle to accy (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of accy as text
%        str2double(get(hObject,'String')) returns contents of accy as a double


% --- Executes during object creation, after setting all properties.
function accy_CreateFcn(hObject, eventdata, handles)
% hObject    handle to accy (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function accz_Callback(hObject, eventdata, handles)
% hObject    handle to accz (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of accz as text
%        str2double(get(hObject,'String')) returns contents of accz as a double


% --- Executes during object creation, after setting all properties.
function accz_CreateFcn(hObject, eventdata, handles)
% hObject    handle to accz (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in qianjin.
function qianjin_Callback(hObject, eventdata, handles)
% hObject    handle to qianjin (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global scom
fwrite(scom,hex2dec('41')); % 以二进制形式向串口对象写入数据A

% --- Executes on button press in zuozhuan.
function zuozhuan_Callback(hObject, eventdata, handles)
% hObject    handle to zuozhuan (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global scom
fwrite(scom,hex2dec('46')); % 以二进制形式向串口对象写入数据A

% --- Executes on button press in tingzhi.
function tingzhi_Callback(hObject, eventdata, handles)
% hObject    handle to tingzhi (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global scom
fwrite(scom,hex2dec('5a')); % 以二进制形式向串口对象写入数据A

% --- Executes on button press in youzhuan.
function youzhuan_Callback(hObject, eventdata, handles)
% hObject    handle to youzhuan (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global scom
fwrite(scom,hex2dec('42')); % 以二进制形式向串口对象写入数据A

% --- Executes on button press in houtui.
function houtui_Callback(hObject, eventdata, handles)
% hObject    handle to houtui (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global scom
fwrite(scom,hex2dec('45')); % 以二进制形式向串口对象写入数据A

% --- Executes on button press in gaosu.
function gaosu_Callback(hObject, eventdata, handles)
% hObject    handle to gaosu (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global scom
fwrite(scom,hex2dec('58')); % 以二进制形式向串口对象写入数据A

% --- Executes on button press in disu.
function disu_Callback(hObject, eventdata, handles)
% hObject    handle to disu (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global scom
fwrite(scom,hex2dec('59')); % 以二进制形式向串口对象写入数据A

% --- Executes during object creation, after setting all properties.
function axes1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to axes1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called


% --- Executes on button press in guanbichuankou.
function guanbichuankou_Callback(hObject, eventdata, handles)
% hObject    handle to guanbichuankou (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global loop_flag
delete(instrfindall); 
loop_flag=0;



function encoder_left_Callback(hObject, eventdata, handles)
% hObject    handle to encoder_left (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of encoder_left as text
%        str2double(get(hObject,'String')) returns contents of encoder_left as a double


% --- Executes during object creation, after setting all properties.
function encoder_left_CreateFcn(hObject, eventdata, handles)
% hObject    handle to encoder_left (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function encoder_right_Callback(hObject, eventdata, handles)
% hObject    handle to encoder_right (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of encoder_right as text
%        str2double(get(hObject,'String')) returns contents of encoder_right as a double


% --- Executes during object creation, after setting all properties.
function encoder_right_CreateFcn(hObject, eventdata, handles)
% hObject    handle to encoder_right (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
