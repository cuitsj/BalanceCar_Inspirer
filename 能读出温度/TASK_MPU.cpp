#include "TASK_MPU.hpp"

uint16_t gyro[3],accel[3],magnet[3],Temperature;


//初始化MPU9250，根据需要请参考pdf进行修改************************
void Init_MPU9250(void)
{
/*
   Single_Write(GYRO_ADDRESS,PWR_M, 0x80);   //
   Single_Write(GYRO_ADDRESS,SMPL, 0x07);    //
   Single_Write(GYRO_ADDRESS,DLPF, 0x1E);    //±2000°
   Single_Write(GYRO_ADDRESS,INT_C, 0x00 );  //
   Single_Write(GYRO_ADDRESS,PWR_M, 0x00);   //
*/
  Single_Write(GYRO_ADDRESS,PWR_MGMT_1, 0x00);	//解除休眠状态
	Single_Write(GYRO_ADDRESS,SMPLRT_DIV, 0x07);
	Single_Write(GYRO_ADDRESS,CONFIG, 0x06);
	Single_Write(GYRO_ADDRESS,GYRO_CONFIG, 0x18);
	Single_Write(GYRO_ADDRESS,ACCEL_CONFIG, 0x01);
	gOS->delay_ms(100);
  //----------------
//	Single_Write(GYRO_ADDRESS,0x6A,0x00);//close Master Mode	

}
	
//******读取MPU9250数据****************************************
void READ_MPU9250_ACCEL(void)
{ 
	uint8_t buf[6];
	
	buf[0]=Single_Read(ACCEL_ADDRESS,ACCEL_XOUT_H); 
	buf[1]=Single_Read(ACCEL_ADDRESS,ACCEL_XOUT_L);

	buf[2]=Single_Read(ACCEL_ADDRESS,ACCEL_YOUT_H);
	buf[3]=Single_Read(ACCEL_ADDRESS,ACCEL_YOUT_L);

	buf[4]=Single_Read(ACCEL_ADDRESS,ACCEL_ZOUT_H);
	buf[5]=Single_Read(ACCEL_ADDRESS,ACCEL_ZOUT_L);
	
	accel[0] =(((uint16_t)buf[0]<<8)|buf[1]);  
	accel[1] =(((uint16_t)buf[2]<<8)|buf[3]);  
	accel[2]= (((uint16_t)buf[4]<<8)|buf[5]);
}

void READ_MPU9250_GYRO(void)
{ 
	uint8_t buf[6];
	
	buf[0]=Single_Read(GYRO_ADDRESS,GYRO_XOUT_H); 
	buf[1]=Single_Read(GYRO_ADDRESS,GYRO_XOUT_L);

	buf[2]=Single_Read(GYRO_ADDRESS,GYRO_YOUT_H);
	buf[3]=Single_Read(GYRO_ADDRESS,GYRO_YOUT_L);

	buf[4]=Single_Read(GYRO_ADDRESS,GYRO_ZOUT_H);
	buf[5]=Single_Read(GYRO_ADDRESS,GYRO_ZOUT_L);
	
	gyro[0] =(((uint16_t)buf[0]<<8)|buf[1]);  
	gyro[1] =(((uint16_t)buf[2]<<8)|buf[3]);  
	gyro[2]= (((uint16_t)buf[4]<<8)|buf[5]);


	buf[0]=Single_Read(GYRO_ADDRESS,TEMP_OUT_H); 
	buf[1]=Single_Read(GYRO_ADDRESS,TEMP_OUT_L);
	
	Temperature =(((uint16_t)buf[0]<<8)|buf[1]);  
}


void READ_MPU9250_MAG(void)
{ 
	uint8_t buf[6];
	
	Single_Write(GYRO_ADDRESS,0x37,0x02);//turn on Bypass Mode 
	gOS->delay_ms(100);
	Single_Write(MAG_ADDRESS,0x0A,0x01);
	gOS->delay_ms(100);
	buf[0]=Single_Read (MAG_ADDRESS,MAG_XOUT_H);
	buf[1]=Single_Read (MAG_ADDRESS,MAG_XOUT_L);


	buf[2]=Single_Read(MAG_ADDRESS,MAG_YOUT_H);
	buf[3]=Single_Read(MAG_ADDRESS,MAG_YOUT_L);


	buf[4]=Single_Read(MAG_ADDRESS,MAG_ZOUT_H);
	buf[5]=Single_Read(MAG_ADDRESS,MAG_ZOUT_L);
	
	magnet[0] =((uint16_t)buf[0]<<8)|buf[1];  
	magnet[1] =((uint16_t)buf[2]<<8)|buf[3];  
	magnet[2] =((uint16_t)buf[4]<<8)|buf[5];	
}



/*************结束***************/

void TASK_MPU::MPU_FUN(void* parameter)
{
	int Voltage;
	int16_t Encoder_Left=0,Encoder_Right=0;
	uint8_t t[20]={0};
	
  Init_MPU9250();		     //初始化MPU9250
	for(;;)
	{
		READ_MPU9250_ACCEL();  //加速度 
		READ_MPU9250_GYRO();      //陀螺
//		READ_MPU9250_MAG();	      //磁场
		
		Encoder_Left = gBSP->TIM2_LENCODER->ReadCnt();
		Encoder_Right = gBSP->TIM3_RENCODER->ReadCnt();
		Voltage=gBSP->ADC0_VOL->VOLIN4_BAT;

//			 	t[0] = accel[0]>>8;
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
				t[12] = Temperature>>8;
				t[13] = Temperature;
				t[14] = Encoder_Left>>8;
				t[15] = Encoder_Left;
				t[16] = Encoder_Right>>8;
				t[17] = Encoder_Right;
				t[18] = Voltage>>8;
				t[19] = Voltage;
				
		gBSP->UART0_DEBUG->Write(t,20);
		gOS->delay_ms(50);
	}
	
}

TASK_MPU::TASK_MPU()
{
	func = (mainFun_t)MPU_FUN;
	stackSize = 1024;
	name = "TASK_MPU";
	thread_prioroty = 1;
}
