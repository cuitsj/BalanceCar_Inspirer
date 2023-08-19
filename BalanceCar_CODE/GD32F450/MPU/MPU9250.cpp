#include "MPU9250.hpp"
#include "main.h"

short gyro[3],accel[3],magnet[3],Temperature;//������ٶ�����������

float Pitch,Roll; 


//����MPU9250�����Ǵ����������̷�Χ
//fsr:0,��250dps;1,��500dps;2,��1000dps;3,��2000dps
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
uint8_t MPU_Set_Gyro_Fsr(uint8_t fsr)
{
	return MPU_Write_Byte(MPU9250_ADDR,MPU_GYRO_CFG_REG,fsr<<3);//���������������̷�Χ  
}
//����MPU9250���ٶȴ����������̷�Χ
//fsr:0,��2g;1,��4g;2,��8g;3,��16g
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
uint8_t MPU_Set_Accel_Fsr(uint8_t fsr)
{
	return MPU_Write_Byte(MPU9250_ADDR,MPU_ACCEL_CFG_REG,fsr<<3);//���ü��ٶȴ����������̷�Χ  
}

//����MPU9250�����ֵ�ͨ�˲���
//lpf:���ֵ�ͨ�˲�Ƶ��(Hz)
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
uint8_t MPU_Set_LPF(uint16_t lpf)
{
	uint8_t data=0;
	if(lpf>=188)data=1;
	else if(lpf>=98)data=2;
	else if(lpf>=42)data=3;
	else if(lpf>=20)data=4;
	else if(lpf>=10)data=5;
	else data=6; 
	return MPU_Write_Byte(MPU9250_ADDR,MPU_CFG_REG,data);//�������ֵ�ͨ�˲���  
}

//����MPU9250�Ĳ�����(�ٶ�Fs=1KHz)
//rate:4~1000(Hz)
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
uint8_t MPU_Set_Rate(uint16_t rate)
{
	uint8_t data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data=1000/rate-1;
	data=MPU_Write_Byte(MPU9250_ADDR,MPU_SAMPLE_RATE_REG,data);	//�������ֵ�ͨ�˲���
 	return MPU_Set_LPF(rate/2);	//�Զ�����LPFΪ�����ʵ�һ��
}

//�õ��¶�ֵ
//����ֵ:�¶�ֵ(������100��)
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
//�õ�������ֵ(ԭʼֵ)
//gx,gy,gz:������x,y,z���ԭʼ����(������)
//����ֵ:0,�ɹ�
//    ����,�������
void MPU_Get_Gyroscope(void)
{
	uint8_t buf[6]; 
	
	buf[0]=MPU_Read_Byte(MPU9250_ADDR,MPU_GYRO_XOUTH_REG); 
	buf[1]=MPU_Read_Byte(MPU9250_ADDR,MPU_GYRO_XOUTL_REG);

	buf[2]=MPU_Read_Byte(MPU9250_ADDR,MPU_GYRO_YOUTH_REG);
	buf[3]=MPU_Read_Byte(MPU9250_ADDR,MPU_GYRO_YOUTL_REG);

	buf[4]=MPU_Read_Byte(MPU9250_ADDR,MPU_GYRO_ZOUTH_REG);
	buf[5]=MPU_Read_Byte(MPU9250_ADDR,MPU_GYRO_ZOUTL_REG);
	
	gyro[0] =(((uint16_t)buf[0]<<8)|buf[1]);  
	gyro[1] =(((uint16_t)buf[2]<<8)|buf[3]);  
	gyro[2]= (((uint16_t)buf[4]<<8)|buf[5]);
}
//�õ����ٶ�ֵ(ԭʼֵ)
//gx,gy,gz:������x,y,z���ԭʼ����(������)
//����ֵ:0,�ɹ�
//    ����,�������
void MPU_Get_Accelerometer(void)
{
	uint8_t buf[6];

	buf[0]=MPU_Read_Byte(MPU9250_ADDR,MPU_ACCEL_XOUTH_REG); 
	buf[1]=MPU_Read_Byte(MPU9250_ADDR,MPU_ACCEL_XOUTL_REG);

	buf[2]=MPU_Read_Byte(MPU9250_ADDR,MPU_ACCEL_YOUTH_REG);
	buf[3]=MPU_Read_Byte(MPU9250_ADDR,MPU_ACCEL_YOUTL_REG);

	buf[4]=MPU_Read_Byte(MPU9250_ADDR,MPU_ACCEL_ZOUTH_REG);
	buf[5]=MPU_Read_Byte(MPU9250_ADDR,MPU_ACCEL_ZOUTL_REG);
	
	accel[0] =((uint16_t)buf[0]<<8)|buf[1];  
	accel[1] =((uint16_t)buf[2]<<8)|buf[3];  
	accel[2] =((uint16_t)buf[4]<<8)|buf[5];	
}

//�õ�������ֵ(ԭʼֵ)
//mx,my,mz:������x,y,z���ԭʼ����(������)
//����ֵ:0,�ɹ�
//    ����,�������
void MPU_Get_Magnetometer(void)
{
  uint8_t buf[6],res;  
	
		
	MPU_Write_Byte(MPU9250_ADDR,MPU_INTBP_CFG_REG,0X02);//INT���ŵ͵�ƽ��Ч������bypassģʽ������ֱ�Ӷ�ȡ������
	gOS->delay_ms(10);
	MPU_Write_Byte(AK8963_ADDR,MAG_CNTL1,0X11); //AK8963ÿ�ζ����Ժ���Ҫ��������Ϊ���β���ģʽ
	gOS->delay_ms(10);
	buf[1]=MPU_Read_Byte(AK8963_ADDR,MAG_XOUT_L);
	buf[0]=MPU_Read_Byte(AK8963_ADDR,MAG_XOUT_H); 


	buf[3]=MPU_Read_Byte(AK8963_ADDR,MAG_YOUT_L);
	buf[2]=MPU_Read_Byte(AK8963_ADDR,MAG_YOUT_H);


	buf[5]=MPU_Read_Byte(AK8963_ADDR,MAG_ZOUT_L);
	buf[4]=MPU_Read_Byte(AK8963_ADDR,MAG_ZOUT_H);

	magnet[0] =((uint16_t)buf[0]<<8)|buf[1];  
	magnet[1] =((uint16_t)buf[2]<<8)|buf[3];  
	magnet[2] =((uint16_t)buf[4]<<8)|buf[5];	

}

//��ʼ��MPU9250
//����ֵ:0,�ɹ�
//    ����,�������
uint8_t MPU9250_Init(void)
{
	uint8_t res=0;
	
//	IIC_Init();     //��ʼ��IIC����
	MPU_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT1_REG,0X80);//��λMPU9250
	gOS->delay_ms(100);  //��ʱ100ms
	MPU_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT1_REG,0X00);//����MPU9250
	MPU_Set_Gyro_Fsr(3);					        	//�����Ǵ�����,��500dps=��500��/s   ��32768
	MPU_Set_Accel_Fsr(0);					       	 	//���ٶȴ�����,��2g=��2*9.8m/s2    ��32768
	MPU_Set_Rate(200);						       	 	  //���ò�����50Hz
//	MPU_Write_Byte(MPU9250_ADDR,MPU_INT_EN_REG,0X00);   //�ر������ж�
//	MPU_Write_Byte(MPU9250_ADDR,MPU_USER_CTRL_REG,0X00);//I2C��ģʽ�ر�
//	MPU_Write_Byte(MPU9250_ADDR,MPU_FIFO_EN_REG,0X00);	//�ر�FIFO
//	MPU_Write_Byte(MPU9250_ADDR,MPU_INTBP_CFG_REG,0X02);//INT���ŵ͵�ƽ��Ч������bypassģʽ������ֱ�Ӷ�ȡ������
//	res=MPU_Read_Byte(MPU9250_ADDR,MPU_DEVICE_ID_REG);  //��ȡMPU6500��ID
	//    if(res==MPU6500_ID) //����ID��ȷ
	//    {
	MPU_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT1_REG,0X01);  	//����CLKSEL,PLL X��Ϊ�ο�
	MPU_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT2_REG,0X00);  	//���ٶ��������Ƕ�����
	MPU_Set_Rate(200);						       	//���ò�����Ϊ50Hz   
	//    }
	//	else return 1;
//	res=MPU_Read_Byte(AK8963_ADDR,MAG_WIA);    			//��ȡAK8963 ID   
	//    if(res==AK8963_ID)
	//    {

//	MPU_Write_Byte(AK8963_ADDR,MAG_CNTL1,0X01); //AK8963ÿ�ζ����Ժ���Ҫ��������Ϊ���β���ģʽ
	//    }
	//	else return 1;
	return 0;
}

#define PRINT_ACCEL     (0x01)
#define PRINT_GYRO      (0x02)
#define PRINT_QUAT      (0x04)
#define ACCEL_ON        (0x01)
#define GYRO_ON         (0x02)
#define MOTION          (0)
#define NO_MOTION       (1)
#define DEFAULT_MPU_HZ  (200)
#define FLASH_SIZE      (512)
#define FLASH_MEM_START ((void*)0x1800)
#define q30  1073741824.0f
short sensors;

float q0=1.0f,q1=0.0f,q2=0.0f,q3=0.0f;
static signed char gyro_orientation[9] = {-1, 0, 0,
                                           0,-1, 0,
                                           0, 0, 1};

static  unsigned short inv_row_2_scale(const signed char *row)
{
    unsigned short b;

    if (row[0] > 0)
        b = 0;
    else if (row[0] < 0)
        b = 4;
    else if (row[1] > 0)
        b = 1;
    else if (row[1] < 0)
        b = 5;
    else if (row[2] > 0)
        b = 2;
    else if (row[2] < 0)
        b = 6;
    else
        b = 7;      // error
    return b;
}

static  unsigned short inv_orientation_matrix_to_scalar(const signed char *mtx)
{
    unsigned short scalar;
    scalar = inv_row_2_scale(mtx);
    scalar |= inv_row_2_scale(mtx + 3) << 3;
    scalar |= inv_row_2_scale(mtx + 6) << 6;
    return scalar;
}

static void run_self_test(void)
{
    int result;
    long gyro[3], accel[3];

    result = mpu_run_self_test(gyro, accel);
    if (result == 0x7) {
        /* Test passed. We can trust the gyro data here, so let's push it down
         * to the DMP.
         */
        float sens;
        unsigned short accel_sens;
        mpu_get_gyro_sens(&sens);
        gyro[0] = (long)(gyro[0] * sens);
        gyro[1] = (long)(gyro[1] * sens);
        gyro[2] = (long)(gyro[2] * sens);
        dmp_set_gyro_bias(gyro);
        mpu_get_accel_sens(&accel_sens);
        accel[0] *= accel_sens;
        accel[1] *= accel_sens;
        accel[2] *= accel_sens;
        dmp_set_accel_bias(accel);
		//printf("setting bias succesfully ......\r\n");
    }
}

/**************************************************************************
�������ܣ�MPU6050����DMP�ĳ�ʼ��
��ڲ�������
����  ֵ����
��    �ߣ�ƽ��С��֮��
**************************************************************************/
void DMP_Init(void)
{ 
//   uint8_t temp[1]={0};
//   MPU_Read_Len(0xD0,0x75,1,temp);
//	 //printf("mpu_set_sensor complete ......\r\n");
//	if(temp[0]!=0x68)NVIC_SystemReset();
	if(!mpu_init())
  {
	  if(!mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL));
	  	 //printf("mpu_set_sensor complete ......\r\n");
	  if(!mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL));
	  	 //printf("mpu_configure_fifo complete ......\r\n");
	  if(!mpu_set_sample_rate(200));
	  	 //printf("mpu_set_sample_rate complete ......\r\n");
	  if(!dmp_load_motion_driver_firmware());
	  	//printf("dmp_load_motion_driver_firmware complete ......\r\n");
	  if(!dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_orientation)));
	  	 //printf("dmp_set_orientation complete ......\r\n");
	  if(!dmp_enable_feature(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_TAP |
	        DMP_FEATURE_ANDROID_ORIENT | DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_SEND_CAL_GYRO |
	        DMP_FEATURE_GYRO_CAL));
	  	 //printf("dmp_enable_feature complete ......\r\n");
	  if(!dmp_set_fifo_rate(200));
	  	 //printf("dmp_set_fifo_rate complete ......\r\n");
	  run_self_test();
	  if(!mpu_set_dmp_state(1));
	  	 //printf("mpu_set_dmp_state complete ......\r\n");
  }
}

/**************************************************************************
�������ܣ���ȡMPU6050����DMP����̬��Ϣ
��ڲ�������
����  ֵ����
��    �ߣ�ƽ��С��֮��
**************************************************************************/
void Read_DMP(void)
{	
	  unsigned long sensor_timestamp;
		unsigned char more;
		long quat[4];

				dmp_read_fifo(gyro, accel, quat, &sensor_timestamp, &sensors, &more);		
				if (sensors & INV_WXYZ_QUAT )
				{    
					 q0=quat[0] / q30;
					 q1=quat[1] / q30;
					 q2=quat[2] / q30;
					 q3=quat[3] / q30;
					 Pitch = asin(-2 * q1 * q3 + 2 * q0* q2)* 57.3; 	
					 Roll= atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1)* 57.3; // roll
				}

}
