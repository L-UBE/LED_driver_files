#ifndef PL9823_H
#define PL9823_H
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"
#include "main.h"
void PL9823_SendTest(uint32_t *color); //send all red bits, last bit as green

void PL9823_Send(uint32_t *color); // final usage

void PL9823_SendRGBTest(uint32_t *color);

void PL9823_ColorShift(uint32_t *color, uint32_t color_length); // continuous color shifting

void PL9823_ColorShiftC(uint32_t *color, uint32_t color_length, int channel); // choosing channel

void PL9823_send888(uint32_t *array); //send in the entire cube data. array is uin32_t array with size 8



#ifdef __cplusplus
}
#endif
#endif /* PL9823_H */
