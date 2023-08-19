#include "TASK_MPU.hpp"

short gyro[3],accel[3],magnet[3],Temperature;//三轴加速度陀螺仪数据

//初始化MPU9250
//返回值:0,成功
//    其他,错误代码
uint8_t MPU9250_Init(void)
{
	uint8_t res=0;
	
	IIC_Init();     //初始化IIC总线
	MPU_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT1_REG,0X80);//复位MPU9250
	gOS->delay_ms(100);  //延时100ms
	MPU_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT1_REG,0X00);//唤醒MPU9250
	MPU_Set_Gyro_Fsr(1);					        	//陀螺仪传感器,±500dps=±500°/s   ±32768
	MPU_Set_Accel_Fsr(0);					       	 	//加速度传感器,±2g=±2*9.8m/s2    ±32768
	MPU_Set_Rate(50);						       	 	  //设置采样率50Hz
	MPU_Write_Byte(MPU9250_ADDR,MPU_INT_EN_REG,0X00);   //关闭所有中断
	MPU_Write_Byte(MPU9250_ADDR,MPU_USER_CTRL_REG,0X00);//I2C主模式关闭
	MPU_Write_Byte(MPU9250_ADDR,MPU_FIFO_EN_REG,0X00);	//关闭FIFO
	MPU_Write_Byte(MPU9250_ADDR,MPU_INTBP_CFG_REG,0X02);//INT引脚低电平有效，开启bypass模式，可以直接读取磁力计
	res=MPU_Read_Byte(MPU9250_ADDR,MPU_DEVICE_ID_REG);  //读取MPU6500的ID
	//    if(res==MPU6500_ID) //器件ID正确
	//    {
	MPU_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT1_REG,0X01);  	//设置CLKSEL,PLL X轴为参考
	MPU_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT2_REG,0X00);  	//加速度与陀螺仪都工作
	MPU_Set_Rate(50);						       	//设置采样率为50Hz   
	//    }
	//	else return 1;
	res=MPU_Read_Byte(AK8963_ADDR,MAG_WIA);    			//读取AK8963 ID   
	//    if(res==AK8963_ID)
	//    {

	MPU_Write_Byte(AK8963_ADDR,MAG_CNTL1,0X01); //AK8963每次读完以后都需要重新设置为单次测量模式
	//    }
	//	else return 1;
	return 0;
}

//设置MPU9250陀螺仪传感器满量程范围
//fsr:0,±250dps;1,±500dps;2,±1000dps;3,±2000dps
//返回值:0,设置成功
//    其他,设置失败 
uint8_t MPU_Set_Gyro_Fsr(uint8_t fsr)
{
	return MPU_Write_Byte(MPU9250_ADDR,MPU_GYRO_CFG_REG,fsr<<3);//设置陀螺仪满量程范围  
}
//设置MPU9250加速度传感器满量程范围
//fsr:0,±2g;1,±4g;2,±8g;3,±16g
//返回值:0,设置成功
//    其他,设置失败 
uint8_t MPU_Set_Accel_Fsr(uint8_t fsr)
{
	return MPU_Write_Byte(MPU9250_ADDR,MPU_ACCEL_CFG_REG,fsr<<3);//设置加速度传感器满量程范围  
}

//设置MPU9250的数字低通滤波器
//lpf:数字低通滤波频率(Hz)
//返回值:0,设置成功
//    其他,设置失败 
uint8_t MPU_Set_LPF(uint16_t lpf)
{
	uint8_t data=0;
	if(lpf>=188)data=1;
	else if(lpf>=98)data=2;
	else if(lpf>=42)data=3;
	else if(lpf>=20)data=4;
	else if(lpf>=10)data=5;
	else data=6; 
	return MPU_Write_Byte(MPU9250_ADDR,MPU_CFG_REG,data);//设置数字低通滤波器  
}

//设置MPU9250的采样率(假定Fs=1KHz)
//rate:4~1000(Hz)
//返回值:0,设置成功
//    其他,设置失败 
uint8_t MPU_Set_Rate(uint16_t rate)
{
	uint8_t data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data=1000/rate-1;
	data=MPU_Write_Byte(MPU9250_ADDR,MPU_SAMPLE_RATE_REG,data);	//设置数字低通滤波器
 	return MPU_Set_LPF(rate/2);	//自动设置LPF为采样率的一半
}

//得到温度值
//返回值:温度值(扩大了100倍)
void MPU_Get_Temperature(void)
{
    uint8_t buf[2]; 
    short raw;
	float temp;
	MPU_Read_Len(MPU9250_ADDR,MPU_TEMP_OUTH_REG,2,buf); 
    raw=((uint16_t)buf[0]<<8)|buf[1];  
    temp=21+((double)raw)/333.87;  
    Temperature = temp*100;
}
//得到陀螺仪值(原始值)
//gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)
//返回值:0,成功
//    其他,错误代码
void MPU_Get_Gyroscope(void)
{
	uint8_t buf[6]; 
	
	buf[0]=Single_Read(MPU9250_ADDR,MPU_GYRO_XOUTH_REG); 
	buf[1]=Single_Read(MPU9250_ADDR,MPU_GYRO_XOUTL_REG);

	buf[2]=Single_Read(MPU9250_ADDR,MPU_GYRO_YOUTH_REG);
	buf[3]=Single_Read(MPU9250_ADDR,MPU_GYRO_YOUTL_REG);

	buf[4]=Single_Read(MPU9250_ADDR,MPU_GYRO_ZOUTH_REG);
	buf[5]=Single_Read(MPU9250_ADDR,MPU_GYRO_ZOUTL_REG);
	
	gyro[0] =(((uint16_t)buf[0]<<8)|buf[1]);  
	gyro[1] =(((uint16_t)buf[2]<<8)|buf[3]);  
	gyro[2]= (((uint16_t)buf[4]<<8)|buf[5]);
}
//得到加速度值(原始值)
//gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)
//返回值:0,成功
//    其他,错误代码
void MPU_Get_Accelerometer(void)
{
	uint8_t buf[6];

	buf[0]=Single_Read(MPU9250_ADDR,MPU_ACCEL_XOUTH_REG); 
	buf[1]=Single_Read(MPU9250_ADDR,MPU_ACCEL_XOUTL_REG);

	buf[2]=Single_Read(MPU9250_ADDR,MPU_ACCEL_YOUTH_REG);
	buf[3]=Single_Read(MPU9250_ADDR,MPU_ACCEL_YOUTL_REG);

	buf[4]=Single_Read(MPU9250_ADDR,MPU_ACCEL_ZOUTH_REG);
	buf[5]=Single_Read(MPU9250_ADDR,MPU_ACCEL_ZOUTL_REG);
	
	accel[0] =((uint16_t)buf[0]<<8)|buf[1];  
	accel[1] =((uint16_t)buf[2]<<8)|buf[3];  
	accel[2] =((uint16_t)buf[4]<<8)|buf[5];	
}

//得到磁力计值(原始值)
//mx,my,mz:磁力计x,y,z轴的原始读数(带符号)
//返回值:0,成功
//    其他,错误代码
void MPU_Get_Magnetometer(void)
{
  uint8_t buf[6],res;  
	
		
	MPU_Write_Byte(MPU9250_ADDR,MPU_INTBP_CFG_REG,0X02);//INT引脚低电平有效，开启bypass模式，可以直接读取磁力计
	gOS->delay_ms(10);
	MPU_Write_Byte(AK8963_ADDR,MAG_CNTL1,0X11); //AK8963每次读完以后都需要重新设置为单次测量模式
	gOS->delay_ms(10);
	buf[1]=Single_Read(AK8963_ADDR,MAG_XOUT_L);
	buf[0]=Single_Read(AK8963_ADDR,MAG_XOUT_H); 


	buf[3]=Single_Read(AK8963_ADDR,MAG_YOUT_L);
	buf[2]=Single_Read(AK8963_ADDR,MAG_YOUT_H);


	buf[5]=Single_Read(AK8963_ADDR,MAG_ZOUT_L);
	buf[4]=Single_Read(AK8963_ADDR,MAG_ZOUT_H);

	magnet[0] =((uint16_t)buf[0]<<8)|buf[1];  
	magnet[1] =((uint16_t)buf[2]<<8)|buf[3];  
	magnet[2] =((uint16_t)buf[4]<<8)|buf[5];	

}

//IIC连续写
//addr:器件地址 
//reg:寄存器地址
//len:写入长度
//buf:数据区
//返回值:0,正常
//    其他,错误代码
uint8_t MPU_Write_Len(uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf)
{
    uint8_t i;
    IIC_Start();
    IIC_SendByte((addr<<1)|0); //发送器件地址+写命令
    if(IIC_WaitAck())          //等待应答
    {
        IIC_Stop();
        return 1;
    }
    IIC_SendByte(reg);         //写寄存器地址
    IIC_WaitAck();             //等待应答
    for(i=0;i<len;i++)
    {
        IIC_SendByte(buf[i]);  //发送数据
        if(IIC_WaitAck())      //等待ACK
        {
            IIC_Stop();
            return 1;
        }
    }
    IIC_Stop();
    return 0;
} 

//IIC连续读
//addr:器件地址
//reg:要读取的寄存器地址
//len:要读取的长度
//buf:读取到的数据存储区
//返回值:0,正常
//    其他,错误代码
uint8_t MPU_Read_Len(uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf)
{ 
    IIC_Start();
    IIC_SendByte((addr<<1)|0); //发送器件地址+写命令
    if(IIC_WaitAck())          //等待应答
    {
        IIC_Stop();
        return 1;
    }
    IIC_SendByte(reg);         //写寄存器地址
    IIC_WaitAck();             //等待应答
	IIC_Start();                
    IIC_SendByte((addr<<1)|1); //发送器件地址+读命令
    IIC_WaitAck();             //等待应答
    while(len)
    {
        if(len==1)*buf=IIC_ReadByte();//读数据,发送nACK 
		else *buf=IIC_ReadByte();		//读数据,发送ACK  
		len--;
		buf++;  
    }
    IIC_Stop();                 //产生一个停止条件
    return 0;       
}

//IIC写一个字节 
//devaddr:器件IIC地址
//reg:寄存器地址
//data:数据
//返回值:0,正常
//    其他,错误代码
uint8_t MPU_Write_Byte(uint8_t addr,uint8_t reg,uint8_t data)
{
    IIC_Start();
    IIC_SendByte((addr<<1)|0); //发送器件地址+写命令
    if(IIC_WaitAck())          //等待应答
    {
        IIC_Stop();
        return 1;
    }
    IIC_SendByte(reg);         //写寄存器地址
    IIC_WaitAck();             //等待应答
    IIC_SendByte(data);        //发送数据
    if(IIC_WaitAck())          //等待ACK
    {
        IIC_Stop();
        return 1;
    }
    IIC_Stop();
    return 0;
}

//IIC读一个字节 
//reg:寄存器地址 
//返回值:读到的数据
uint8_t MPU_Read_Byte(uint8_t addr,uint8_t reg)
{
    uint8_t res;
	
    IIC_Start();
    IIC_SendByte((addr<<1)|0); //发送器件地址+写命令
    IIC_WaitAck();             //等待应答
    IIC_SendByte(reg);         //写寄存器地址
    IIC_WaitAck();             //等待应答
	  IIC_Start();                
    IIC_SendByte((addr<<1)|1); //发送器件地址+读命令
    IIC_WaitAck();             //等待应答
		res=IIC_ReadByte();		//读数据,发送nACK  
    IIC_Stop();                 //产生一个停止条件
    return res;  
}

void TASK_MPU::MPU_FUN(void* parameter)
{
	int Voltage;
	int16_t Encoder_Left=0,Encoder_Right=0;
	uint8_t t[20]={0};
	
	MPU9250_Init();
//  Init_MPU9250();		     //初始化MPU9250
	for(;;)
	{
		MPU_Get_Gyroscope();
		MPU_Get_Accelerometer();
		MPU_Get_Magnetometer();
		
				
				Encoder_Left = gBSP->TIM2_LENCODER->ReadCnt();
				Encoder_Right = gBSP->TIM3_RENCODER->ReadCnt();
				Voltage=gBSP->ADC0_VOL->VOLIN4_BAT;

			 	t[0] = accel[0]>>8;
				t[1] = accel[0];
				t[2] = accel[1]>>8;
				t[3] = accel[1];
				t[4] = accel[2]>>8;
				t[5] = accel[2];
			  t[6] = gyro[0]>>8;
				t[7] = gyro[0];
				t[8] = gyro[1]>>8;
				t[9] = gyro[1];
				t[10] = gyro[2]>>8;
				t[11] = gyro[2];
//				t[12] = magnet[0]>>8;
//				t[13] = magnet[0];
//				t[14] = magnet[1]>>8;
//				t[15] = magnet[1];
//				t[16] = magnet[2]>>8;
//				t[17] = magnet[2];
				t[12] = Temperature>>8;
				t[13] = Temperature;
//				t[14] = BUF[0];
//				t[15] = BUF[1];
//				t[16] = BUF[2];
//				t[17] = BUF[3];
//				t[18] = BUF[4];
//				t[19] = BUF[5];
//				t[14] = Encoder_Left>>8;
//				t[15] = Encoder_Left;
//				t[16] = Encoder_Right>>8;
//				t[17] = Encoder_Right;
//				t[18] = Voltage>>8;
//				t[19] = Voltage;
				
		gBSP->UART0_DEBUG->Write(t,20);
		gOS->delay_ms(200);
	}
	
}

TASK_MPU::TASK_MPU()
{
	func = (mainFun_t)MPU_FUN;
	stackSize = 1024;
	name = "TASK_MPU";
	thread_prioroty = 1;
}
