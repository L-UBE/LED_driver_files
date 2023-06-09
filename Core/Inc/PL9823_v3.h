#ifndef PL9823_V3_H
#define PL9823_V3_H
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"
#include "main.h"

void PL9823_Presetinit(void);

void PL9823_SetBrightness(uint8_t brightness);

void PL9823_SetColor(uint32_t color, uint8_t idx);

void PL9823_sendchannelPreset(uint8_t *color, uint16_t color_length, uint8_t channel);

#ifdef __cplusplus
}
#endif
#endif /* PL9823_V3_H */
