/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

#include "PL9823.h"
#include <string.h>
#include <stdio.h>
// preallocate an array for DMA
// 24 * NUMLED + reset_cyle*2
// each take up 4 bytes for 2 spaces 
// 24*256 + 3200 = 9344. takes up 18688 bytes
//uint16_t pwmData1[24*256 + 1600*2];
uint16_t pwmData2[24*256 + 1600*2];


// 4 PWM, 4 selecting GPIO, each has 256 LED. (or NUMLED) 
// hash will tell which channel, which stage.
// uint16_t = 0x0000; (channel)(stage)(LED). 
// 0x44ff --> channel 4, stage 4, LED 256
// 0x1100 --> channel 1, stage 1, LED 1
// LEDhash[x][y][z]
//uint16_t LEDhash[16][16][16]; //for big cube
/*
	(0,7) (1,7) ---- >  (7,7)
	(0,6) (1,6) ---- >  (7,6)
	(0,5) (1,5)
	(0,4) (1,4)
	(0,3) (1,3)
	(0,2) (1,2)
	(0,1) (1,1)
	(0,0) (1,0) ---- >  (7,0)
*/
//uint16_t LEDhash[8][8][8] = {
//	{	{0x313f, 0x313e, 0x313d, 0x313c, 0x313b, 0x313a, 0x3139, 0x3138},
//		{0x3130, 0x3131, 0x3132, 0x3133, 0x3134, 0x3135, 0x3136, 0x3137},
//		{0x312f, 0x312e, 0x312d, 0x312c, 0x312b, 0x312a, 0x3129, 0x3128},
//		{0x3120, 0x3121, 0x3122, 0x3123, 0x3124, 0x3125, 0x3126, 0x3127},
//		{0x113f, 0x113e, 0x113d, 0x113c, 0x113b, 0x113a, 0x1139, 0x1138},
//		{0x1130, 0x1131, 0x1132, 0x1133, 0x1134, 0x1135, 0x1136, 0x1137},
//		{0x112f, 0x112e, 0x112d, 0x112c, 0x112b, 0x112a, 0x1129, 0x1128},
//		{0x1120, 0x1121, 0x1122, 0x1123, 0x1124, 0x1125, 0x1126, 0x1127}},
//	{	{0x3100, 0x3101, 0x3102, 0x3103, 0x3104, 0x3105, 0x3106, 0x3107},
//		{0x310f, 0x310e, 0x310d, 0x310c, 0x310b, 0x310a, 0x3109, 0x3108},
//		{0x3110, 0x3111, 0x3112, 0x3113, 0x3114, 0x3115, 0x3116, 0x3117},
//		{0x311f, 0x311e, 0x311d, 0x311c, 0x311b, 0x311a, 0x3119, 0x3118},
//		{0x1100, 0x1101, 0x1102, 0x1103, 0x1104, 0x1105, 0x1106, 0x1107},
//		{0x110f, 0x110e, 0x110d, 0x110c, 0x110b, 0x110a, 0x1109, 0x1108},
//		{0x1110, 0x1111, 0x1112, 0x1113, 0x1114, 0x1115, 0x1116, 0x1117},
//		{0x111f, 0x111e, 0x111d, 0x111c, 0x111b, 0x111a, 0x1119, 0x1118}},
//	{	{0x413f, 0x413e, 0x413d, 0x413c, 0x413b, 0x413a, 0x4139, 0x4138},
//		{0x4130, 0x4131, 0x4132, 0x4133, 0x4134, 0x4135, 0x4136, 0x4137},
//		{0x412f, 0x412e, 0x412d, 0x412c, 0x412b, 0x412a, 0x4129, 0x4128},
//		{0x4120, 0x4121, 0x4122, 0x4123, 0x4124, 0x4125, 0x4126, 0x4127},
//		{0x213f, 0x213e, 0x213d, 0x213c, 0x213b, 0x213a, 0x2139, 0x2138},
//		{0x2130, 0x2131, 0x2132, 0x2133, 0x2134, 0x2135, 0x2136, 0x2137},
//		{0x212f, 0x212e, 0x212d, 0x212c, 0x212b, 0x212a, 0x2129, 0x2128},
//		{0x2120, 0x2121, 0x2122, 0x2123, 0x2124, 0x2125, 0x2126, 0x2127}},
//	{	{0x4100, 0x4101, 0x4102, 0x4103, 0x4104, 0x4105, 0x4106, 0x4107},
//		{0x410f, 0x410e, 0x410d, 0x410c, 0x410b, 0x410a, 0x4109, 0x4108},
//		{0x4110, 0x4111, 0x4112, 0x4113, 0x4114, 0x4115, 0x4116, 0x4117},
//		{0x411f, 0x411e, 0x411d, 0x411c, 0x411b, 0x411a, 0x4119, 0x4118},
//		{0x2100, 0x2101, 0x2102, 0x2103, 0x2104, 0x2105, 0x2106, 0x2107},
//		{0x210f, 0x210e, 0x210d, 0x210c, 0x210b, 0x210a, 0x2109, 0x2108},
//		{0x2110, 0x2111, 0x2112, 0x2113, 0x2114, 0x2115, 0x2116, 0x2117},
//		{0x211f, 0x211e, 0x211d, 0x211c, 0x211b, 0x211a, 0x2119, 0x2118}},
//	{	{0x323f, 0x323e, 0x323d, 0x323c, 0x323b, 0x323a, 0x3239, 0x3238},
//		{0x3230, 0x3231, 0x3232, 0x3233, 0x3234, 0x3235, 0x3236, 0x3237},
//		{0x322f, 0x322e, 0x322d, 0x322c, 0x322b, 0x322a, 0x3229, 0x3228},
//		{0x3220, 0x3221, 0x3222, 0x3223, 0x3224, 0x3225, 0x3226, 0x3227},
//		{0x123f, 0x123e, 0x123d, 0x123c, 0x123b, 0x123a, 0x1239, 0x1238},
//		{0x1230, 0x1231, 0x1232, 0x1233, 0x1234, 0x1235, 0x1236, 0x1237},
//		{0x122f, 0x122e, 0x122d, 0x122c, 0x122b, 0x122a, 0x1229, 0x1228},
//		{0x1220, 0x1221, 0x1222, 0x1223, 0x1224, 0x1225, 0x1226, 0x1227}},
//	{	{0x3200, 0x3201, 0x3202, 0x3203, 0x3204, 0x3205, 0x3206, 0x3207},
//		{0x320f, 0x320e, 0x320d, 0x320c, 0x320b, 0x320a, 0x3209, 0x3208},
//		{0x3210, 0x3211, 0x3212, 0x3213, 0x3214, 0x3215, 0x3216, 0x3217},
//		{0x321f, 0x321e, 0x321d, 0x321c, 0x321b, 0x321a, 0x3219, 0x3218},
//		{0x1200, 0x1201, 0x1202, 0x1203, 0x1204, 0x1205, 0x1206, 0x1207},
//		{0x120f, 0x120e, 0x120d, 0x120c, 0x120b, 0x120a, 0x1209, 0x1208},
//		{0x1210, 0x1211, 0x1212, 0x1213, 0x1214, 0x1215, 0x1216, 0x1217},
//		{0x121f, 0x121e, 0x121d, 0x121c, 0x121b, 0x121a, 0x1219, 0x1218}},
//	{	{0x423f, 0x423e, 0x423d, 0x423c, 0x423b, 0x423a, 0x4239, 0x4238},
//		{0x4230, 0x4231, 0x4232, 0x4233, 0x4234, 0x4235, 0x4236, 0x4237},
//		{0x422f, 0x422e, 0x422d, 0x422c, 0x422b, 0x422a, 0x4229, 0x4228},
//		{0x4220, 0x4221, 0x4222, 0x4223, 0x4224, 0x4225, 0x4226, 0x4227},
//		{0x223f, 0x223e, 0x223d, 0x223c, 0x223b, 0x223a, 0x2239, 0x2238},
//		{0x2230, 0x2231, 0x2232, 0x2233, 0x2234, 0x2235, 0x2236, 0x2237},
//		{0x222f, 0x222e, 0x222d, 0x222c, 0x222b, 0x222a, 0x2229, 0x2228},
//		{0x2220, 0x2221, 0x2222, 0x2223, 0x2224, 0x2225, 0x2226, 0x2227}},
//	{	{0x4200, 0x4201, 0x4202, 0x4203, 0x4204, 0x4205, 0x4206, 0x4207},
//		{0x420f, 0x420e, 0x420d, 0x420c, 0x420b, 0x420a, 0x4209, 0x4208},
//		{0x4210, 0x4211, 0x4212, 0x4213, 0x4214, 0x4215, 0x4216, 0x4217},
//		{0x421f, 0x421e, 0x421d, 0x421c, 0x421b, 0x421a, 0x4219, 0x4218},
//		{0x2200, 0x2201, 0x2202, 0x2203, 0x2204, 0x2205, 0x2206, 0x2207},
//		{0x220f, 0x220e, 0x220d, 0x220c, 0x220b, 0x220a, 0x2209, 0x2208},
//		{0x2210, 0x2211, 0x2212, 0x2213, 0x2214, 0x2215, 0x2216, 0x2217},
//		{0x221f, 0x221e, 0x221d, 0x221c, 0x221b, 0x221a, 0x2219, 0x2218}},
//};


// number of LEDs filled. 
int NUMLED = 256;
uint16_t hightime = 127-27;
uint16_t lowtime = 27;
uint16_t reset_cycle = 1600; // has to be high enough. Or else you are going to see big white areas.

void PL9823_SendTest (uint32_t *color)
{
	//drive LEDs fillers
	for (int i=23; i>=0; i--)
	{
		if (color[0]&(1<<i))
		{
			for (int j=0; j< NUMLED; j++){
				pwmData2[i+24*j] = hightime;
				//printf("1");
			}
		}
		else
		{ for (int j=0; j< NUMLED; j++){
				pwmData2[i+24*j] = lowtime;
				//printf("0");
			}
		}
	}
	//printf("\n");
	//shift = 12 * #of bits shifted
	// 24 * 6 (actual bits present) 
	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)pwmData2, 24);
}




void PL9823_Send(uint32_t *color)
{
	
	
	//drive LEDs fillers
	for (int i=23; i>=0; i--)
	{
		if (color[0]&(1<<i))
		{
			for (int j=0; j< NUMLED; j++){
				pwmData2[i+24*j] = 66;
			}
		}
		else
		{ for (int j=0; j< NUMLED; j++){
				pwmData2[i+24*j] = 33;
			}
		}
	}
	//
	for (int j=0; j<NUMLED; j++){
		for (int i=23; i>=0; i--){
			if (color[0]&(1<<i))
			{
				pwmData2[i+24*j] = 66;
			}
			else
			{ 
				pwmData2[i+24*j] = 33;
			}
		}
	}
	//shift = 12 * #of bits shifted
	// 24 * 6 (actual bits present) 
	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)pwmData2+12*(NUMLED-6), 24*6);
}










void PL9823_SendRGBTest(uint32_t *color){ //remember to send in 3 colors
	//reset matrix
	//memset(pwmData2,0,24*NUMLED);
	for (int j=0; j < reset_cycle; j++){ //THIS IS FKING CRUCIAL HOLY SHIT
			pwmData2[j] = 0;
	}
	
	for (int j=0; j< NUMLED; j++){ //for each LED
			for (int i = 23; i>=0; i--){
					if (color[j%3]&(1<<i)){
							pwmData2[i+24*j+reset_cycle] = hightime;
					}else{
							pwmData2[i+24*j+reset_cycle] = lowtime;
					} 
			}
	}
	for (int j=0; j < reset_cycle; j++){ //THIS IS ALSO FKING CRUCIAL HOLY SHIT
			pwmData2[j+24*NUMLED + reset_cycle] = 0;
	}
	
	// i have no idea why it has to + 4
	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)pwmData2, 24*NUMLED+reset_cycle*2);
	//HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_2, (uint32_t *)pwmData2, 24*NUMLED+50);
}






void PL9823_ColorShift(uint32_t *color, uint32_t color_length){ 
	for (int j=0; j < reset_cycle; j++){ //THIS IS FKING CRUCIAL HOLY SHIT
			pwmData2[j] = 0;
	}
	
	for (int j=0; j< NUMLED; j++){ //for each LED
			for (int i = 23; i>=0; i--){
					if (color[j%color_length]&(1<<i)){
							pwmData2[i+24*j+reset_cycle] = hightime;
					}else{
							pwmData2[i+24*j+reset_cycle] = lowtime;
					} 
			}
	}
	for (int j=0; j < reset_cycle; j++){ //THIS IS ALSO FKING CRUCIAL HOLY SHIT
			pwmData2[j+24*NUMLED + reset_cycle] = 0;
	}
	
	// i have no idea why it has to + 4
	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)pwmData2, 24*NUMLED+reset_cycle*2);
}






void PL9823_ColorShiftC(uint32_t *color, uint32_t color_length, int channel){ 
	/*
	for (int j=0; j < reset_cycle; j++){ //THIS IS FKING CRUCIAL HOLY SHIT
			pwmData2[j] = 0;
	}
	for (int j=0; j< NUMLED; j++){ //for each LED
			for (int i = 23; i>=0; i--){
					if (color[j%color_length]&(1<<i)){
							pwmData2[i+24*j+reset_cycle] = hightime;
					}else{
							pwmData2[i+24*j+reset_cycle] = lowtime;
					} 
			}
	}
	for (int j=0; j < reset_cycle; j++){ //THIS IS ALSO FKING CRUCIAL HOLY SHIT
			pwmData2[j+24*NUMLED + reset_cycle] = 0;
	}
	//printf("%d\n", channel);
	
	*/
	
	switch(channel){
		case 1 : // the other channel still seems to update even with me putting breaks. 
			// SKIP FOR RESET CYCLE
			for (int j=0; j< NUMLED; j++){ //for each LED
					for (int i = 23; i>=0; i--){
							if (color[j%color_length]&(1<<i)){
									pwmData2[i+24*j+reset_cycle] = hightime;
							}else{
									pwmData2[i+24*j+reset_cycle] = lowtime;
							} 
					}
			}
			// SKIP FOR RESET CYCLE
			HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)pwmData2, 24*NUMLED+reset_cycle*2);
			break;
		case 2 :	
			// SKIP FOR RESET CYCLE
			for (int j=0; j< NUMLED; j++){ //for each LED
					for (int i = 23; i>=0; i--){
							if (color[j%color_length]&(1<<i)){
									pwmData2[i+24*j+reset_cycle] = hightime;
							}else{
									pwmData2[i+24*j+reset_cycle] = lowtime;
							} 
					}
			}
			// SKIP FOR RESET CYCLE
			HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_2, (uint32_t *)pwmData2, 24*NUMLED+reset_cycle*2);
			break;
		case 3 :
			// SKIP FOR RESET CYCLE
			for (int j=0; j< NUMLED; j++){ //for each LED
					for (int i = 23; i>=0; i--){
							if (color[j%color_length]&(1<<i)){
									pwmData2[i+24*j+reset_cycle] = hightime;
							}else{
									pwmData2[i+24*j+reset_cycle] = lowtime;
							} 
					}
			}
			// SKIP FOR RESET CYCLE
			HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_3, (uint32_t *)pwmData2, 24*NUMLED+reset_cycle*2);
			break;
		case 4 :
			// SKIP FOR RESET CYCLE
			for (int j=0; j< NUMLED; j++){ //for each LED
					for (int i = 23; i>=0; i--){
							if (color[j%color_length]&(1<<i)){
									pwmData2[i+24*j+reset_cycle] = hightime;
							}else{
									pwmData2[i+24*j+reset_cycle] = lowtime;
							} 
					}
			}
			// SKIP FOR RESET CYCLE
			HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_4, (uint32_t *)pwmData2, 24*NUMLED+reset_cycle*2);
			break;
	}
}





void PL9823_send888(uint32_t *array){
	
}




