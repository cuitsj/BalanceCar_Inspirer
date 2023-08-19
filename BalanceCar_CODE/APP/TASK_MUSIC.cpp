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
	
//中速 每分钟65拍 一拍920ms
uint16_t Music_Lone_Brave[][3]={
//曲信息
	{0,0,920},
	
	//第一小节
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	
	//第二小节	
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	
	//第三小节	
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	
	//第四小节	
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	
	//第五小节	
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	
	//第六小节	
	{3,Alto,One_Beat}		   ,{3,Alto,One_Beat}		  ,{0,Alto,One_Beat}       ,{0,Alto,One_FOUR_Beat} ,
	{1,Alto,One_FOUR_Beat} ,{2,Alto,One_FOUR_Beat},{1,Alto,One_FOUR_Beat}  ,
	
	//第七小节
	{3,Alto,One_Beat}      ,{3,Alto,One_Beat}			,{0,Alto,One_TWO_Beat}	 ,{1,Alto,One_FOUR_Beat} ,
	{2,Alto,One_FOUR_Beat} ,{1,Alto,One_FOUR_Beat},{2,Alto,One_FOUR_Beat}  ,{3,Alto,One_FOUR_Beat} ,
	
	//第八小节
	{6,Bass,One_TWO_Beat}  ,{1,Alto,One_FOUR_Beat},{6,Bass,One_TWO_Beat}	 ,{1,Alto,One_FOUR_Beat} ,
	{6,Bass,One_TWO_Beat}  ,{1,Alto,One_FOUR_Beat},{2,Alto,One_TWO_Beat}   ,{1,Alto,One_TWO_Beat}  ,
	
	//第九小节
	{7,Bass,One_TWO_Beat}  ,{7,Bass,One_FOUR_Beat},{0,Alto,One_TWO_Beat}	 ,{0,Alto,One_FOUR_Beat} ,

	//第十小节
	{3,Alto,One_Beat}		   ,{3,Alto,One_Beat}		  ,{0,Alto,One_Beat}       ,{0,Alto,One_FOUR_Beat} ,
	{1,Alto,One_FOUR_Beat} ,{2,Alto,One_FOUR_Beat},{1,Alto,One_FOUR_Beat}  ,
	
	//第十一小节
	{3,Alto,One_Beat}      ,{3,Alto,One_Beat}			,{0,Alto,One_TWO_Beat}	 ,{1,Alto,One_FOUR_Beat} ,
	{2,Alto,One_FOUR_Beat} ,{1,Alto,One_FOUR_Beat},{2,Alto,One_FOUR_Beat}  ,{3,Alto,One_FOUR_Beat} ,
	
	//第十二小节
	{6,Bass,One_TWO_Beat}  ,{1,Alto,One_FOUR_Beat},{6,Bass,One_TWO_Beat}	 ,{1,Alto,One_FOUR_Beat} ,
	{6,Bass,One_TWO_Beat}  ,{1,Alto,One_FOUR_Beat},{3,Alto,One_TWO_Beat}   ,{2,Alto,One_TWO_Beat}  ,
		
	//第十三小节
	{7,Bass,One_TWO_Beat}  ,{7,Bass,One_FOUR_Beat},{0,Alto,One_TWO_Beat}	 ,{0,Alto,One_FOUR_Beat} ,
	
	//第十四小节
	{6,Bass,One_FOUR_Beat} ,{1,Alto,One_FOUR_Beat},{6,Alto,One_TWO_Beat}	 ,{6,Alto,One_FOUR_Beat} ,
	{0,Alto,20 /*小衔接*/} ,{6,Alto,One_FOUR_Beat},{6,Alto,One_FOUR_Beat}  ,{5,Alto,One_FOUR_Beat} ,
	{6,Alto,One_TWO_Beat}  ,{6,Alto,One_FOUR_Beat},{5,Alto,One_FOUR_Beat}  ,{6,Alto,One_FOUR_Beat} ,
	{5,Alto,One_FOUR_Beat} ,{6,Alto,One_FOUR_Beat},{5,Alto,One_FOUR_Beat}  ,
	
	//第十五小节
	{3,Alto,One_FOUR_Beat} ,{3,Alto,One_TWO_Beat} ,{3,Alto,One_Beat}	     ,{0,Alto,20 /*小衔接*/} ,
	{0,Alto,One_Beat}      ,{0,Alto,One_TWO_Beat} ,{6,Bass,One_FOUR_Beat}  ,{1,Alto,One_FOUR_Beat} ,
	
	//第十六小节
	{6,Alto,One_TWO_Beat}  ,{6,Alto,One_FOUR_Beat},{0,Alto,20 /*小衔接*/}  ,{6,Alto,One_FOUR_Beat} ,
	{5,Alto,One_FOUR_Beat} ,{6,Alto,One_FOUR_Beat},{5,Alto,One_FOUR_Beat}  ,{7,Alto,One_TWO_Beat}  ,
	{7,Alto,One_FOUR_Beat} ,{0,Alto,20 /*小衔接*/},{7,Alto,One_FOUR_Beat}  ,{6,Alto,One_FOUR_Beat} ,
	{7,Alto,One_TWO_Beat}  ,
	
	//第十七小节
	{7,Alto,One_FOUR_Beat} ,{6,Alto,One_TWO_Beat} ,{3,Alto,One_FOUR_Beat}  ,{3,Alto,One_TWO_Beat}  ,
	{3,Alto,One_TWO_Beat}  ,{0,Alto,One_FOUR_Beat},{3,Alto,One_FOUR_Beat}  ,{5,Alto,One_FOUR_Beat} ,
	{3,Alto,One_FOUR_Beat} ,

	//第十八小节
	{2,Alto,One_TWO_Beat}  ,{3,Alto,One_FOUR_Beat},{2,Alto,One_TWO_Beat}   ,{3,Alto,One_FOUR_Beat} ,
	{2,Alto,One_TWO_Beat}  ,{3,Alto,One_FOUR_Beat},{5,Alto,One_FOUR_Beat}  ,{3,Alto,One_FOUR_Beat} ,
	{5,Alto,One_FOUR_Beat} ,{3,Alto,One_FOUR_Beat},
	
	//第十九小节
	{2,Alto,One_TWO_Beat}  ,{3,Alto,One_FOUR_Beat},{2,Alto,One_TWO_Beat}   ,{3,Alto,One_FOUR_Beat} ,
	{2,Alto,One_Beat}      ,{0,Alto,One_TWO_Beat} ,{1,Alto,One_FOUR_Beat}  ,{2,Alto,One_FOUR_Beat} ,
	
	//第二十小节
	{3,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat} ,{1,Alto,One_TWO_Beat}   ,{3,Alto,One_TWO_Beat}  ,
	{2,Alto,One_TWO_Beat}  ,{3,Alto,One_FOUR_Beat},{2,Alto,One_FOUR_Beat}  ,{1,Alto,One_FOUR_Beat} ,
	{1,Alto,One_TWO_Beat}  ,
	
	//第二十一小节
	{6,Bass,One_Beat}      ,{6,Bass,One_Beat} 	  ,{0,Alto,One_Beat}       ,{0,Alto,One_TWO_Beat}  ,
	{6,Alto,One_FOUR_Beat} ,{7,Alto,One_FOUR_Beat},
	
	//第二十二小节
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,306 /*小衔接*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*小衔接*/},{1,Teble,One_FOUR_Beat},
	{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,
	{1,Teble,One_FOUR_Beat},{0,Alto,306 /*小衔接*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*小衔接*/},
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	
	//第二十三小节
	{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{0,Alto,306 /*小衔接*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_TWO_Beat} ,{3,Teble,One_TWO_Beat} ,{6,Alto,One_FOUR_Beat} ,
	{7,Alto,One_FOUR_Beat} ,
	
	//第二十四小节
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,306 /*小衔接*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*小衔接*/},{1,Teble,One_FOUR_Beat},
	{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,
	{1,Teble,One_FOUR_Beat},{0,Alto,306 /*小衔接*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*小衔接*/},
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	
	//第二十五小节
	{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{0,Alto,306 /*小衔接*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_TWO_Beat} ,{3,Teble,One_TWO_Beat} ,{5,Teble,One_TWO_Beat} ,
	
	//第二十六小节
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{5,Teble,One_FOUR_Beat},{6,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{5,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{5,Teble,One_TWO_Beat} ,
	
	//第二十七小节
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{5,Teble,One_FOUR_Beat},{6,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{5,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{5,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},
	{5,Teble,One_TWO_Beat} ,
	
	//第二十八小节
	//{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,
	//{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},
	//{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{1,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},
	{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,184 /*小衔接*/},{1,Teble,One_FOUR_Beat},
	
	//第二十九小节
	{1,Teble,One_TWO_Beat}  ,{0,Alto,One_FOUR_Beat} ,{0,Alto,One_TWO_Beat}  ,{0,Alto,One_TWO_Beat}  ,
	{5,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{5,Teble,One_FOUR_Beat},
	
	//第三十小节
	//{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,
	//{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},
	//{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{1,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},
	{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,184 /*小衔接*/},{1,Teble,One_FOUR_Beat},
	
	//第三十一小节
	{1,Teble,One_TWO_Beat} ,{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,
//	
//	//第三十二小节
//	{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,
//	
//	//第三十三小节
//	{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,
	
	//第三十四小节
	{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,{0,Alto,One_TWO_Beat}  ,
	{6,Teble,One_FOUR_Beat},{5,Alto,One_FOUR_Beat} ,
	
	//第三十五小节
	{6,Alto,One_TWO_Beat}  ,{5,Alto,One_FOUR_Beat} ,{6,Alto,One_FOUR_Beat} ,{5,Alto,One_FOUR_Beat} ,
	{6,Alto,One_FOUR_Beat} ,{5,Alto,One_FOUR_Beat} ,{6,Alto,One_TWO_Beat}  ,{0,Alto,184 /*小衔接*/},
	{6,Alto,One_FOUR_Beat} ,{5,Alto,One_FOUR_Beat} ,{6,Alto,One_FOUR_Beat} ,{5,Alto,One_FOUR_Beat} ,
	{6,Alto,One_FOUR_Beat} ,{5,Alto,One_FOUR_Beat} ,
	
	//第三十六小节
//	{3,Alto,One_FOUR_Beat} ,{3,Alto,One_TWO_Beat}  ,{3,Alto,One_Beat}       ,{0,Alto,One_Beat}     ,
//	{0,Alto,One_TWO_Beat}  ,{6,Alto,One_FOUR_Beat} ,{5,Alto,One_FOUR_Beat}  ,
	{3,Alto,One_TWO_Beat}  ,{3,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,
	{0,Alto,One_TWO_Beat}  ,{6,Alto,One_FOUR_Beat} ,{5,Alto,One_FOUR_Beat} ,
	
	//第三十七小节
	{6,Alto,One_TWO_Beat}  ,{5,Alto,One_FOUR_Beat} ,{6,Alto,One_FOUR_Beat} ,{5,Alto,One_FOUR_Beat} ,
	{6,Alto,One_FOUR_Beat} ,{5,Alto,One_FOUR_Beat} ,{7,Alto,One_TWO_Beat}  ,{0,Alto,184 /*小衔接*/} ,
	{7,Alto,One_FOUR_Beat} ,{0,Alto,184 /*小衔接*/} ,{7,Alto,One_FOUR_Beat} ,{6,Alto,One_FOUR_Beat} ,
	{7,Alto,One_FOUR_Beat} ,{6,Alto,One_FOUR_Beat} ,

	//第三十八小节
//	{3,Alto,One_FOUR_Beat} ,{3,Alto,One_TWO_Beat}  ,{3,Alto,One_Beat}  ,{0,Alto,One_Beat}  ,
//	{0,Alto,One_FOUR_Beat},{3,Alto,One_FOUR_Beat}  ,{5,Alto,One_FOUR_Beat} ,{3,Alto,One_FOUR_Beat} ,
	{3,Alto,One_TWO_Beat}  ,{3,Alto,One_Beat}  ,{0,Alto,One_Beat}  ,{0,Alto,One_FOUR_Beat},
	{3,Alto,One_FOUR_Beat}  ,{5,Alto,One_FOUR_Beat} ,{3,Alto,One_FOUR_Beat} ,
	
	//第三十九小节
	{2,Alto,One_TWO_Beat}  ,{3,Alto,One_FOUR_Beat},{2,Alto,One_TWO_Beat}   ,{3,Alto,One_FOUR_Beat} ,
	{2,Alto,One_TWO_Beat}  ,{3,Alto,One_FOUR_Beat},{5,Alto,One_FOUR_Beat}  ,{3,Alto,One_FOUR_Beat} ,
	{5,Alto,One_FOUR_Beat} ,{3,Alto,One_FOUR_Beat},
	
	
	//第四十小节
	{2,Alto,One_TWO_Beat}  ,{3,Alto,One_FOUR_Beat},{2,Alto,One_TWO_Beat}   ,{3,Alto,One_FOUR_Beat} ,
	{2,Alto,One_Beat}      ,{0,Alto,One_TWO_Beat} ,{1,Alto,One_FOUR_Beat}  ,{2,Alto,One_FOUR_Beat} ,
	
	//第四十一小节
	{3,Alto,One_TWO_Beat}  ,{6,Alto,One_TWO_Beat} ,{1,Teble,One_TWO_Beat}   ,{3,Teble,One_TWO_Beat}  ,
	{2,Teble,One_TWO_Beat}  ,{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat}  ,{1,Teble,One_FOUR_Beat} ,
	{1,Teble,One_TWO_Beat}  ,
	
	//第四十二小节
	{6,Alto,One_Beat}  ,{0,Alto,One_Beat} ,{0,Alto,One_Beat}   ,{0,Alto,One_TWO_Beat}  ,
	{6,Alto,One_FOUR_Beat}  ,{7,Alto,One_FOUR_Beat},
	
	//开始第一遍循环
	//第二十二小节
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,306 /*小衔接*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*小衔接*/},{1,Teble,One_FOUR_Beat},
	{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,
	{1,Teble,One_FOUR_Beat},{0,Alto,306 /*小衔接*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*小衔接*/},
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	
	//第二十三小节
	{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{0,Alto,306 /*小衔接*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_TWO_Beat} ,{3,Teble,One_TWO_Beat} ,{6,Alto,One_FOUR_Beat} ,
	{7,Alto,One_FOUR_Beat} ,
	
	//第二十四小节
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,306 /*小衔接*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*小衔接*/},{1,Teble,One_FOUR_Beat},
	{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,
	{1,Teble,One_FOUR_Beat},{0,Alto,306 /*小衔接*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*小衔接*/},
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	
	//第二十五小节
	{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{0,Alto,306 /*小衔接*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_TWO_Beat} ,{3,Teble,One_TWO_Beat} ,{5,Teble,One_TWO_Beat} ,
	
	//第二十六小节
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{5,Teble,One_FOUR_Beat},{6,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{5,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{5,Teble,One_TWO_Beat} ,
	
	//第二十七小节
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{5,Teble,One_FOUR_Beat},{6,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{5,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{5,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},
	{5,Teble,One_TWO_Beat} ,
	
	//第二十八小节
	//{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,
	//{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},
	//{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{1,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},
	{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,184 /*小衔接*/},{1,Teble,One_FOUR_Beat},
	
	//第二十九小节
	{1,Teble,One_TWO_Beat}  ,{0,Alto,One_FOUR_Beat} ,{0,Alto,One_TWO_Beat}  ,{0,Alto,One_TWO_Beat}  ,
	{5,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{5,Teble,One_FOUR_Beat},
	
	//第三十小节
	//{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,
	//{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},
	//{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{1,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},
	{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,184 /*小衔接*/},{1,Teble,One_FOUR_Beat},
	
	//第一遍循环结束
	
	//第四十三小节
	{6,Alto,One_TWO_Beat}  ,{6,Alto,One_TWO_Beat} ,{1,Alto,One_TWO_Beat}  ,{3,Alto,One_TWO_Beat}  ,
	{7,Alto,One_Beat},{0,Alto,184 /*小衔接*/},{7,Alto,One_TWO_Beat},{0,Alto,184 /*小衔接*/},
	{7,Alto,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{7,Alto,One_FOUR_Beat},
	
	//第四十四小节
	//{6,Alto,One_FOUR_Beat}  ,{6,Alto,One_TWO_Beat} ,{6,Alto,One_Beat}  ,{0,Alto,One_Beat}  ,
	//{0,Alto,One_Beat},{0,Alto,One_Beat},
	{6,Alto,One_TWO_Beat} ,{6,Alto,One_TWO_Beat} ,{6,Alto,One_TWO_Beat} ,{0,Alto,One_Beat}  ,
	{0,Alto,One_Beat},{0,Alto,One_Beat},
	
	//第四十五小节
	{6,Alto,One_TWO_Beat}  ,{6,Alto,One_TWO_Beat} ,{1,Alto,One_TWO_Beat}  ,{3,Alto,One_TWO_Beat}  ,
	{7,Alto,One_Beat},{0,Alto,184 /*小衔接*/},{7,Alto,One_TWO_Beat},{0,Alto,184 /*小衔接*/},
	{7,Alto,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{7,Alto,One_FOUR_Beat},
	
	//第四十六小节
	{7,Alto,One_FOUR_Beat},{6,Alto,One_TWO_Beat},{6,Alto,One_Beat} ,{0,Alto,One_Beat},
	{0,Alto,One_TWO_Beat},{6,Alto,One_FOUR_Beat} ,{7,Alto,One_FOUR_Beat},
	
	
	//第二次循环
	//第二十二小节
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,306 /*小衔接*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*小衔接*/},{1,Teble,One_FOUR_Beat},
	{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,
	{1,Teble,One_FOUR_Beat},{0,Alto,306 /*小衔接*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*小衔接*/},
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	
	//第二十三小节
	{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{0,Alto,306 /*小衔接*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_TWO_Beat} ,{3,Teble,One_TWO_Beat} ,{6,Alto,One_FOUR_Beat} ,
	{7,Alto,One_FOUR_Beat} ,
	
	//第二十四小节
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,306 /*小衔接*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*小衔接*/},{1,Teble,One_FOUR_Beat},
	{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,
	{1,Teble,One_FOUR_Beat},{0,Alto,306 /*小衔接*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*小衔接*/},
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	
	//第二十五小节
	{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{0,Alto,306 /*小衔接*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_TWO_Beat} ,{3,Teble,One_TWO_Beat} ,{5,Teble,One_TWO_Beat} ,
	
	//第二十六小节
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{5,Teble,One_FOUR_Beat},{6,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{5,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{5,Teble,One_TWO_Beat} ,
	
	//第二十七小节
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{5,Teble,One_FOUR_Beat},{6,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{5,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{5,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},
	{5,Teble,One_TWO_Beat} ,
	
	//第二十八小节
	//{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,
	//{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},
	//{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{1,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},
	{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,184 /*小衔接*/},{1,Teble,One_FOUR_Beat},
	
	//第二十九小节
	{1,Teble,One_TWO_Beat}  ,{0,Alto,One_FOUR_Beat} ,{0,Alto,One_TWO_Beat}  ,{0,Alto,One_TWO_Beat}  ,
	{5,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{5,Teble,One_FOUR_Beat},
	
	//第三十小节
	//{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,
	//{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},
	//{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{1,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},
	{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,184 /*小衔接*/},{1,Teble,One_FOUR_Beat},

	//第二次循环结束
	
	//第四十七小节
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
		//播放孤勇者
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