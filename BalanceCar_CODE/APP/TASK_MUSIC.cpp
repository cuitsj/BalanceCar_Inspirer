#include "TASK_MUSIC.hpp"

#define Bass		0
#define	Alto		1
#define	Teble		2

#define	One_Beat				1
#define	One_TWO_Beat		2
#define	One_FOUR_Beat		4

uint16_t Tone_Index[8][3]={
	{0  ,0  ,0   },
	{262,523,1046},
	{294,587,1175},
	{330,659,1318},
	{349,698,1397},
	{392,784,1568},
	{440,880,1760},
	{494,988,1976}		
};
	
//���� ÿ����65�� һ��920ms
uint16_t Music_Lone_Brave[][3]={
//����Ϣ
	{0,0,920},
	
	//��һС��
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	
	//�ڶ�С��	
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	
	//����С��	
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	
	//����С��	
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	
	//����С��	
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	
	//����С��	
	{3,Alto,One_Beat}		   ,{3,Alto,One_Beat}		  ,{0,Alto,One_Beat}       ,{0,Alto,One_FOUR_Beat} ,
	{1,Alto,One_FOUR_Beat} ,{2,Alto,One_FOUR_Beat},{1,Alto,One_FOUR_Beat}  ,
	
	//����С��
	{3,Alto,One_Beat}      ,{3,Alto,One_Beat}			,{0,Alto,One_TWO_Beat}	 ,{1,Alto,One_FOUR_Beat} ,
	{2,Alto,One_FOUR_Beat} ,{1,Alto,One_FOUR_Beat},{2,Alto,One_FOUR_Beat}  ,{3,Alto,One_FOUR_Beat} ,
	
	//�ڰ�С��
	{6,Bass,One_TWO_Beat}  ,{1,Alto,One_FOUR_Beat},{6,Bass,One_TWO_Beat}	 ,{1,Alto,One_FOUR_Beat} ,
	{6,Bass,One_TWO_Beat}  ,{1,Alto,One_FOUR_Beat},{2,Alto,One_TWO_Beat}   ,{1,Alto,One_TWO_Beat}  ,
	
	//�ھ�С��
	{7,Bass,One_TWO_Beat}  ,{7,Bass,One_FOUR_Beat},{0,Alto,One_TWO_Beat}	 ,{0,Alto,One_FOUR_Beat} ,

	//��ʮС��
	{3,Alto,One_Beat}		   ,{3,Alto,One_Beat}		  ,{0,Alto,One_Beat}       ,{0,Alto,One_FOUR_Beat} ,
	{1,Alto,One_FOUR_Beat} ,{2,Alto,One_FOUR_Beat},{1,Alto,One_FOUR_Beat}  ,
	
	//��ʮһС��
	{3,Alto,One_Beat}      ,{3,Alto,One_Beat}			,{0,Alto,One_TWO_Beat}	 ,{1,Alto,One_FOUR_Beat} ,
	{2,Alto,One_FOUR_Beat} ,{1,Alto,One_FOUR_Beat},{2,Alto,One_FOUR_Beat}  ,{3,Alto,One_FOUR_Beat} ,
	
	//��ʮ��С��
	{6,Bass,One_TWO_Beat}  ,{1,Alto,One_FOUR_Beat},{6,Bass,One_TWO_Beat}	 ,{1,Alto,One_FOUR_Beat} ,
	{6,Bass,One_TWO_Beat}  ,{1,Alto,One_FOUR_Beat},{3,Alto,One_TWO_Beat}   ,{2,Alto,One_TWO_Beat}  ,
		
	//��ʮ��С��
	{7,Bass,One_TWO_Beat}  ,{7,Bass,One_FOUR_Beat},{0,Alto,One_TWO_Beat}	 ,{0,Alto,One_FOUR_Beat} ,
	
	//��ʮ��С��
	{6,Bass,One_FOUR_Beat} ,{1,Alto,One_FOUR_Beat},{6,Alto,One_TWO_Beat}	 ,{6,Alto,One_FOUR_Beat} ,
	{0,Alto,20 /*С�ν�*/} ,{6,Alto,One_FOUR_Beat},{6,Alto,One_FOUR_Beat}  ,{5,Alto,One_FOUR_Beat} ,
	{6,Alto,One_TWO_Beat}  ,{6,Alto,One_FOUR_Beat},{5,Alto,One_FOUR_Beat}  ,{6,Alto,One_FOUR_Beat} ,
	{5,Alto,One_FOUR_Beat} ,{6,Alto,One_FOUR_Beat},{5,Alto,One_FOUR_Beat}  ,
	
	//��ʮ��С��
	{3,Alto,One_FOUR_Beat} ,{3,Alto,One_TWO_Beat} ,{3,Alto,One_Beat}	     ,{0,Alto,20 /*С�ν�*/} ,
	{0,Alto,One_Beat}      ,{0,Alto,One_TWO_Beat} ,{6,Bass,One_FOUR_Beat}  ,{1,Alto,One_FOUR_Beat} ,
	
	//��ʮ��С��
	{6,Alto,One_TWO_Beat}  ,{6,Alto,One_FOUR_Beat},{0,Alto,20 /*С�ν�*/}  ,{6,Alto,One_FOUR_Beat} ,
	{5,Alto,One_FOUR_Beat} ,{6,Alto,One_FOUR_Beat},{5,Alto,One_FOUR_Beat}  ,{7,Alto,One_TWO_Beat}  ,
	{7,Alto,One_FOUR_Beat} ,{0,Alto,20 /*С�ν�*/},{7,Alto,One_FOUR_Beat}  ,{6,Alto,One_FOUR_Beat} ,
	{7,Alto,One_TWO_Beat}  ,
	
	//��ʮ��С��
	{7,Alto,One_FOUR_Beat} ,{6,Alto,One_TWO_Beat} ,{3,Alto,One_FOUR_Beat}  ,{3,Alto,One_TWO_Beat}  ,
	{3,Alto,One_TWO_Beat}  ,{0,Alto,One_FOUR_Beat},{3,Alto,One_FOUR_Beat}  ,{5,Alto,One_FOUR_Beat} ,
	{3,Alto,One_FOUR_Beat} ,

	//��ʮ��С��
	{2,Alto,One_TWO_Beat}  ,{3,Alto,One_FOUR_Beat},{2,Alto,One_TWO_Beat}   ,{3,Alto,One_FOUR_Beat} ,
	{2,Alto,One_TWO_Beat}  ,{3,Alto,One_FOUR_Beat},{5,Alto,One_FOUR_Beat}  ,{3,Alto,One_FOUR_Beat} ,
	{5,Alto,One_FOUR_Beat} ,{3,Alto,One_FOUR_Beat},
	
	//��ʮ��С��
	{2,Alto,One_TWO_Beat}  ,{3,Alto,One_FOUR_Beat},{2,Alto,One_TWO_Beat}   ,{3,Alto,One_FOUR_Beat} ,
	{2,Alto,One_Beat}      ,{0,Alto,One_TWO_Beat} ,{1,Alto,One_FOUR_Beat}  ,{2,Alto,One_FOUR_Beat} ,
	
	//�ڶ�ʮС��
	{3,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat} ,{1,Alto,One_TWO_Beat}   ,{3,Alto,One_TWO_Beat}  ,
	{2,Alto,One_TWO_Beat}  ,{3,Alto,One_FOUR_Beat},{2,Alto,One_FOUR_Beat}  ,{1,Alto,One_FOUR_Beat} ,
	{1,Alto,One_TWO_Beat}  ,
	
	//�ڶ�ʮһС��
	{6,Bass,One_Beat}      ,{6,Bass,One_Beat} 	  ,{0,Alto,One_Beat}       ,{0,Alto,One_TWO_Beat}  ,
	{6,Alto,One_FOUR_Beat} ,{7,Alto,One_FOUR_Beat},
	
	//�ڶ�ʮ��С��
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,306 /*С�ν�*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*С�ν�*/},{1,Teble,One_FOUR_Beat},
	{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,
	{1,Teble,One_FOUR_Beat},{0,Alto,306 /*С�ν�*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*С�ν�*/},
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	
	//�ڶ�ʮ��С��
	{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{0,Alto,306 /*С�ν�*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_TWO_Beat} ,{3,Teble,One_TWO_Beat} ,{6,Alto,One_FOUR_Beat} ,
	{7,Alto,One_FOUR_Beat} ,
	
	//�ڶ�ʮ��С��
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,306 /*С�ν�*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*С�ν�*/},{1,Teble,One_FOUR_Beat},
	{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,
	{1,Teble,One_FOUR_Beat},{0,Alto,306 /*С�ν�*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*С�ν�*/},
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	
	//�ڶ�ʮ��С��
	{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{0,Alto,306 /*С�ν�*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_TWO_Beat} ,{3,Teble,One_TWO_Beat} ,{5,Teble,One_TWO_Beat} ,
	
	//�ڶ�ʮ��С��
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{5,Teble,One_FOUR_Beat},{6,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{5,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{5,Teble,One_TWO_Beat} ,
	
	//�ڶ�ʮ��С��
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{5,Teble,One_FOUR_Beat},{6,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{5,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{5,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},
	{5,Teble,One_TWO_Beat} ,
	
	//�ڶ�ʮ��С��
	//{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,
	//{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},
	//{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{1,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},
	{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,184 /*С�ν�*/},{1,Teble,One_FOUR_Beat},
	
	//�ڶ�ʮ��С��
	{1,Teble,One_TWO_Beat}  ,{0,Alto,One_FOUR_Beat} ,{0,Alto,One_TWO_Beat}  ,{0,Alto,One_TWO_Beat}  ,
	{5,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{5,Teble,One_FOUR_Beat},
	
	//����ʮС��
	//{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,
	//{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},
	//{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{1,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},
	{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,184 /*С�ν�*/},{1,Teble,One_FOUR_Beat},
	
	//����ʮһС��
	{1,Teble,One_TWO_Beat} ,{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,
//	
//	//����ʮ��С��
//	{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,
//	
//	//����ʮ��С��
//	{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,
	
	//����ʮ��С��
	{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,{0,Alto,One_TWO_Beat}  ,
	{6,Teble,One_FOUR_Beat},{5,Alto,One_FOUR_Beat} ,
	
	//����ʮ��С��
	{6,Alto,One_TWO_Beat}  ,{5,Alto,One_FOUR_Beat} ,{6,Alto,One_FOUR_Beat} ,{5,Alto,One_FOUR_Beat} ,
	{6,Alto,One_FOUR_Beat} ,{5,Alto,One_FOUR_Beat} ,{6,Alto,One_TWO_Beat}  ,{0,Alto,184 /*С�ν�*/},
	{6,Alto,One_FOUR_Beat} ,{5,Alto,One_FOUR_Beat} ,{6,Alto,One_FOUR_Beat} ,{5,Alto,One_FOUR_Beat} ,
	{6,Alto,One_FOUR_Beat} ,{5,Alto,One_FOUR_Beat} ,
	
	//����ʮ��С��
//	{3,Alto,One_FOUR_Beat} ,{3,Alto,One_TWO_Beat}  ,{3,Alto,One_Beat}       ,{0,Alto,One_Beat}     ,
//	{0,Alto,One_TWO_Beat}  ,{6,Alto,One_FOUR_Beat} ,{5,Alto,One_FOUR_Beat}  ,
	{3,Alto,One_TWO_Beat}  ,{3,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,
	{0,Alto,One_TWO_Beat}  ,{6,Alto,One_FOUR_Beat} ,{5,Alto,One_FOUR_Beat} ,
	
	//����ʮ��С��
	{6,Alto,One_TWO_Beat}  ,{5,Alto,One_FOUR_Beat} ,{6,Alto,One_FOUR_Beat} ,{5,Alto,One_FOUR_Beat} ,
	{6,Alto,One_FOUR_Beat} ,{5,Alto,One_FOUR_Beat} ,{7,Alto,One_TWO_Beat}  ,{0,Alto,184 /*С�ν�*/} ,
	{7,Alto,One_FOUR_Beat} ,{0,Alto,184 /*С�ν�*/} ,{7,Alto,One_FOUR_Beat} ,{6,Alto,One_FOUR_Beat} ,
	{7,Alto,One_FOUR_Beat} ,{6,Alto,One_FOUR_Beat} ,

	//����ʮ��С��
//	{3,Alto,One_FOUR_Beat} ,{3,Alto,One_TWO_Beat}  ,{3,Alto,One_Beat}  ,{0,Alto,One_Beat}  ,
//	{0,Alto,One_FOUR_Beat},{3,Alto,One_FOUR_Beat}  ,{5,Alto,One_FOUR_Beat} ,{3,Alto,One_FOUR_Beat} ,
	{3,Alto,One_TWO_Beat}  ,{3,Alto,One_Beat}  ,{0,Alto,One_Beat}  ,{0,Alto,One_FOUR_Beat},
	{3,Alto,One_FOUR_Beat}  ,{5,Alto,One_FOUR_Beat} ,{3,Alto,One_FOUR_Beat} ,
	
	//����ʮ��С��
	{2,Alto,One_TWO_Beat}  ,{3,Alto,One_FOUR_Beat},{2,Alto,One_TWO_Beat}   ,{3,Alto,One_FOUR_Beat} ,
	{2,Alto,One_TWO_Beat}  ,{3,Alto,One_FOUR_Beat},{5,Alto,One_FOUR_Beat}  ,{3,Alto,One_FOUR_Beat} ,
	{5,Alto,One_FOUR_Beat} ,{3,Alto,One_FOUR_Beat},
	
	
	//����ʮС��
	{2,Alto,One_TWO_Beat}  ,{3,Alto,One_FOUR_Beat},{2,Alto,One_TWO_Beat}   ,{3,Alto,One_FOUR_Beat} ,
	{2,Alto,One_Beat}      ,{0,Alto,One_TWO_Beat} ,{1,Alto,One_FOUR_Beat}  ,{2,Alto,One_FOUR_Beat} ,
	
	//����ʮһС��
	{3,Alto,One_TWO_Beat}  ,{6,Alto,One_TWO_Beat} ,{1,Teble,One_TWO_Beat}   ,{3,Teble,One_TWO_Beat}  ,
	{2,Teble,One_TWO_Beat}  ,{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat}  ,{1,Teble,One_FOUR_Beat} ,
	{1,Teble,One_TWO_Beat}  ,
	
	//����ʮ��С��
	{6,Alto,One_Beat}  ,{0,Alto,One_Beat} ,{0,Alto,One_Beat}   ,{0,Alto,One_TWO_Beat}  ,
	{6,Alto,One_FOUR_Beat}  ,{7,Alto,One_FOUR_Beat},
	
	//��ʼ��һ��ѭ��
	//�ڶ�ʮ��С��
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,306 /*С�ν�*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*С�ν�*/},{1,Teble,One_FOUR_Beat},
	{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,
	{1,Teble,One_FOUR_Beat},{0,Alto,306 /*С�ν�*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*С�ν�*/},
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	
	//�ڶ�ʮ��С��
	{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{0,Alto,306 /*С�ν�*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_TWO_Beat} ,{3,Teble,One_TWO_Beat} ,{6,Alto,One_FOUR_Beat} ,
	{7,Alto,One_FOUR_Beat} ,
	
	//�ڶ�ʮ��С��
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,306 /*С�ν�*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*С�ν�*/},{1,Teble,One_FOUR_Beat},
	{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,
	{1,Teble,One_FOUR_Beat},{0,Alto,306 /*С�ν�*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*С�ν�*/},
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	
	//�ڶ�ʮ��С��
	{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{0,Alto,306 /*С�ν�*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_TWO_Beat} ,{3,Teble,One_TWO_Beat} ,{5,Teble,One_TWO_Beat} ,
	
	//�ڶ�ʮ��С��
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{5,Teble,One_FOUR_Beat},{6,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{5,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{5,Teble,One_TWO_Beat} ,
	
	//�ڶ�ʮ��С��
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{5,Teble,One_FOUR_Beat},{6,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{5,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{5,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},
	{5,Teble,One_TWO_Beat} ,
	
	//�ڶ�ʮ��С��
	//{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,
	//{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},
	//{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{1,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},
	{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,184 /*С�ν�*/},{1,Teble,One_FOUR_Beat},
	
	//�ڶ�ʮ��С��
	{1,Teble,One_TWO_Beat}  ,{0,Alto,One_FOUR_Beat} ,{0,Alto,One_TWO_Beat}  ,{0,Alto,One_TWO_Beat}  ,
	{5,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{5,Teble,One_FOUR_Beat},
	
	//����ʮС��
	//{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,
	//{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},
	//{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{1,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},
	{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,184 /*С�ν�*/},{1,Teble,One_FOUR_Beat},
	
	//��һ��ѭ������
	
	//����ʮ��С��
	{6,Alto,One_TWO_Beat}  ,{6,Alto,One_TWO_Beat} ,{1,Alto,One_TWO_Beat}  ,{3,Alto,One_TWO_Beat}  ,
	{7,Alto,One_Beat},{0,Alto,184 /*С�ν�*/},{7,Alto,One_TWO_Beat},{0,Alto,184 /*С�ν�*/},
	{7,Alto,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{7,Alto,One_FOUR_Beat},
	
	//����ʮ��С��
	//{6,Alto,One_FOUR_Beat}  ,{6,Alto,One_TWO_Beat} ,{6,Alto,One_Beat}  ,{0,Alto,One_Beat}  ,
	//{0,Alto,One_Beat},{0,Alto,One_Beat},
	{6,Alto,One_TWO_Beat} ,{6,Alto,One_TWO_Beat} ,{6,Alto,One_TWO_Beat} ,{0,Alto,One_Beat}  ,
	{0,Alto,One_Beat},{0,Alto,One_Beat},
	
	//����ʮ��С��
	{6,Alto,One_TWO_Beat}  ,{6,Alto,One_TWO_Beat} ,{1,Alto,One_TWO_Beat}  ,{3,Alto,One_TWO_Beat}  ,
	{7,Alto,One_Beat},{0,Alto,184 /*С�ν�*/},{7,Alto,One_TWO_Beat},{0,Alto,184 /*С�ν�*/},
	{7,Alto,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{7,Alto,One_FOUR_Beat},
	
	//����ʮ��С��
	{7,Alto,One_FOUR_Beat},{6,Alto,One_TWO_Beat},{6,Alto,One_Beat} ,{0,Alto,One_Beat},
	{0,Alto,One_TWO_Beat},{6,Alto,One_FOUR_Beat} ,{7,Alto,One_FOUR_Beat},
	
	
	//�ڶ���ѭ��
	//�ڶ�ʮ��С��
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,306 /*С�ν�*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*С�ν�*/},{1,Teble,One_FOUR_Beat},
	{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,
	{1,Teble,One_FOUR_Beat},{0,Alto,306 /*С�ν�*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*С�ν�*/},
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	
	//�ڶ�ʮ��С��
	{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{0,Alto,306 /*С�ν�*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_TWO_Beat} ,{3,Teble,One_TWO_Beat} ,{6,Alto,One_FOUR_Beat} ,
	{7,Alto,One_FOUR_Beat} ,
	
	//�ڶ�ʮ��С��
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,306 /*С�ν�*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*С�ν�*/},{1,Teble,One_FOUR_Beat},
	{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,
	{1,Teble,One_FOUR_Beat},{0,Alto,306 /*С�ν�*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*С�ν�*/},
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	
	//�ڶ�ʮ��С��
	{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{0,Alto,306 /*С�ν�*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_TWO_Beat} ,{3,Teble,One_TWO_Beat} ,{5,Teble,One_TWO_Beat} ,
	
	//�ڶ�ʮ��С��
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{5,Teble,One_FOUR_Beat},{6,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{5,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{5,Teble,One_TWO_Beat} ,
	
	//�ڶ�ʮ��С��
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{5,Teble,One_FOUR_Beat},{6,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{5,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{5,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},
	{5,Teble,One_TWO_Beat} ,
	
	//�ڶ�ʮ��С��
	//{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,
	//{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},
	//{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{1,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},
	{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,184 /*С�ν�*/},{1,Teble,One_FOUR_Beat},
	
	//�ڶ�ʮ��С��
	{1,Teble,One_TWO_Beat}  ,{0,Alto,One_FOUR_Beat} ,{0,Alto,One_TWO_Beat}  ,{0,Alto,One_TWO_Beat}  ,
	{5,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{5,Teble,One_FOUR_Beat},
	
	//����ʮС��
	//{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,
	//{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},
	//{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{1,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},
	{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,184 /*С�ν�*/},{1,Teble,One_FOUR_Beat},

	//�ڶ���ѭ������
	
	//����ʮ��С��
	{1,Teble,One_TWO_Beat} ,{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,
	
	{0,Alto,One_Beat} ,
};

void MUSIC_Analysis(void)
{
	uint16_t MusicBeatNum = ((((sizeof(Music_Lone_Brave))/2)/3)-1);
	uint16_t MusicSpeed = Music_Lone_Brave[0][2];

	for(uint16_t i = 1;i<=MusicBeatNum;i++)
	{
		gBSP->TIM8_BEEP->SetFREQ(Tone_Index[Music_Lone_Brave[i][0]][Music_Lone_Brave[i][1]]);
		gOS->delay_ms(MusicSpeed/Music_Lone_Brave[i][2]);
		if (gOS->flag_gyz == 0)
		{
			gBSP->TIM8_BEEP->SetDUTY(0);
			break;
		}
	}	
	gOS->flag_gyz=0;
}


void TASK_MUSIC::MUSIC_FUN(void* parameter)
{
	for(;;)
	{
		//���Ź�����
		if (gOS->flag_gyz == 1)
		{
			gBSP->TIM8_BEEP->SetDUTY(99);
			MUSIC_Analysis();
		}
		gOS->delay_ms(1000);
	}
}

TASK_MUSIC::TASK_MUSIC()
{
	func = (mainFun_t)MUSIC_FUN;
	stackSize = 1024;
	name = "TASK_MUSIC";
	thread_prioroty = 3;
}