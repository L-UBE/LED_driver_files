/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

#include "PL9823_v2.h"
#include <string.h>
#include <stdio.h>

#define NUMLED 64
#define RESET_CYCLE 50
#define HIGHTIME 100
#define LOWTIME 27

#define CHANNEL_1_TIM htim1
#define CHANNEL_1_TIM_CHANNEL TIM_CHANNEL_1
#define CHANNEL_2_TIM htim1
#define CHANNEL_2_TIM_CHANNEL TIM_CHANNEL_4
#define CHANNEL_3_TIM htim2
#define CHANNEL_3_TIM_CHANNEL TIM_CHANNEL_1
#define CHANNEL_4_TIM htim2
#define CHANNEL_4_TIM_CHANNEL TIM_CHANNEL_3

// PRESET COLORS, 16
uint32_t COLORS[16] = {0x000000, 0xff0000, 0x00ff00, 0x0000ff, 
					  0xffff00, 0xff00ff, 0x00ffff, 0xffffff,
					  0x000000, 0xff0000, 0x00ff00, 0x0000ff, 
					  0xffff00, 0xff00ff, 0x00ffff, 0xffffff
					 };

// call PL9823Presetinit to set these
uint16_t COLORS_FOR_DMA[16][24];

// preallocate an array for DMA
// 24 * NUMLED + reset_cyle*2
uint16_t LEDbuffer[24*NUMLED + RESET_CYCLE*2];

void PL9823_Presetinit(void){
	for (int j = 0; j < 16; j++){ //for each 24 sized array
		for (int i = 23; i>=0; i--){
			if (COLORS[j]&((0x800000)>>i)){
				COLORS_FOR_DMA[j][i] = HIGHTIME;
			}else{
				COLORS_FOR_DMA[j][i] = LOWTIME;
			} 
		}
	}
}

// takes in a array for a specific channel
void PL9823_sendchannel(uint32_t *color, uint32_t color_length, int channel){ 
	// RESET_CYCLE, set to 0
	for (int j=0; j< NUMLED; j++){ //for each LED
		for (int i = 23; i>=0; i--){
				if (color[j%color_length]&((0x800000)>>i)){
						LEDbuffer[i+24*j+RESET_CYCLE] = HIGHTIME;
				}else{
						LEDbuffer[i+24*j+RESET_CYCLE] = LOWTIME;
				} 
		}
	}
	// RESET_CYCLE, set to 0
	switch(channel){
		case 1 : // the other channel still seems to update even with me putting breaks. 
			HAL_TIM_PWM_Start_DMA(&CHANNEL_1_TIM, CHANNEL_1_TIM_CHANNEL, (uint32_t *)LEDbuffer, 24*NUMLED + RESET_CYCLE*2);
			break;
		case 2 :	
			HAL_TIM_PWM_Start_DMA(&CHANNEL_2_TIM, CHANNEL_2_TIM_CHANNEL, (uint32_t *)LEDbuffer, 24*NUMLED + RESET_CYCLE*2);
			break;
		case 3 :
			HAL_TIM_PWM_Start_DMA(&CHANNEL_3_TIM, CHANNEL_3_TIM_CHANNEL, (uint32_t *)LEDbuffer, 24*NUMLED + RESET_CYCLE*2);
			break;
		case 4 :
			HAL_TIM_PWM_Start_DMA(&CHANNEL_4_TIM, CHANNEL_4_TIM_CHANNEL, (uint32_t *)LEDbuffer, 24*NUMLED + RESET_CYCLE*2);
			break;
	}
}


// takes in a array for a specific channel
void PL9823_sendchannelPreset(uint8_t *color, uint8_t color_length, uint8_t channel){ 
	// RESET_CYCLE, set to 0
	for (int j=0; j< color_length/2; j++){ //for each LED
		// color should have size color_length/2. each byte consists of two LED data 
		
		// first LED, 24*2, 2 is cuz uint16_t
		memcpy(LEDbuffer+RESET_CYCLE+2*j*24, COLORS_FOR_DMA + ((color[j]) >> 4), 24*2 );
		
		// second LED
		memcpy(LEDbuffer+RESET_CYCLE+(2*j+1)*24, COLORS_FOR_DMA[(color[j]) & 0xf], 24*2 );
	}
	// RESET_CYCLE, set to 0
	switch(channel){
		case 1 : // the other channel still seems to update even with me putting breaks. 
			HAL_TIM_PWM_Start_DMA(&CHANNEL_1_TIM, CHANNEL_1_TIM_CHANNEL, (uint32_t *)LEDbuffer, 24*NUMLED + RESET_CYCLE*2);
			break;
		case 2 :	
			HAL_TIM_PWM_Start_DMA(&CHANNEL_2_TIM, CHANNEL_2_TIM_CHANNEL, (uint32_t *)LEDbuffer, 24*NUMLED + RESET_CYCLE*2);
			break;
		case 3 :
			HAL_TIM_PWM_Start_DMA(&CHANNEL_3_TIM, CHANNEL_3_TIM_CHANNEL, (uint32_t *)LEDbuffer, 24*NUMLED + RESET_CYCLE*2);
			break;
		case 4 :
			HAL_TIM_PWM_Start_DMA(&CHANNEL_4_TIM, CHANNEL_4_TIM_CHANNEL, (uint32_t *)LEDbuffer, 24*NUMLED + RESET_CYCLE*2);
			break;
	}
}





