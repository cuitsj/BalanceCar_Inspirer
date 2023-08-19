function callback(scom,event,handles)
global ax ay az gx gy gz temp L_encoder R_encoder vol roll pitch

%% 读取数据
original_data = fread(scom,[1 4],'uint8');

%% 数据格式转换
roll1=typecast(uint16(original_data(1)*256+original_data(2)),'int16');
pitch1=typecast(uint16(original_data(3)*256+original_data(4)),'int16');

% ax=typecast(uint16(original_data(1)*256+original_data(2)),'int16');
% ay=typecast(uint16(original_data(3)*256+original_data(4)),'int16');
% az=typecast(uint16(original_data(5)*256+original_data(6)),'int16');
% gx=typecast(uint16(original_data(7)*256+original_data(8)),'int16');
% gy=typecast(uint16(original_data(9)*256+original_data(10)),'int16');
% gz=typecast(uint16(original_data(11)*256+original_data(12)),'int16');
% temp=typecast(uint16(original_data(13)*256+original_data(14)),'int16');
% L_encoder=typecast(uint16(original_data(15)*256+original_data(16)),'int16');
% R_encoder=typecast(uint16(original_data(17)*256+original_data(18)),'int16');
% vol=typecast(uint16(original_data(19)*256+original_data(20)),'int16');
% 
% %% 计算实际值
% vol=double(vol)/100;
% temp=double(temp)/340+36.53;
% 
% %% 互补滤波
% ax1=double(ax);
% ay1=double(ay);
% az1=double(az)-16384;
% gx1=double(gx)*0.001064;
% gy1=double(gy)*0.001064;
% gz1=double(gz)*0.001064;
% 
%% 加速度计算角度
% roll1 = atan(ay1 / sqrt(ax1^2 + az1^2));
% pitch1 = atan(-ax1 / sqrt(ay1^2 + az1^2));

gyro=[gx1 gy1 gz1]';
persistent r p

if isempty(r)
    r=0;
end

if isempty(p)
    p=0;
end

trans =[ 1, (sin(p)*sin(r))/cos(p), (cos(r)*sin(p))/cos(p);
               0,                 cos(r),                -sin(r);
               0,          sin(r)/cos(p),          cos(r)/cos(p)];
pals=trans*gyro;
r=(r+pals(1,1)*0.01)*0.7+roll1*0.3;
p=(p+pals(2,1)*0.01)*0.7+pitch1*0.3;

 roll = rad2deg(r);
 pitch = rad2deg(p);

%   roll = rad2deg(roll1);
%  pitch = rad2deg(pitch1);


fprintf('%d %d %d %d %d %d %d %d %d %d\n',ax,ay,az,gx,gy,gz,temp,L_encoder,R_encoder,vol); 

end
