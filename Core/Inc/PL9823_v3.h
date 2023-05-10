#ifndef PL9823_V3_H
#define PL9823_V3_H
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"
#include "main.h"

void PL9823_Presetinit(void);

void PL9823_sendchannelPreset(uint8_t *color, uint16_t color_length, uint8_t channel);

#ifdef __cplusplus
}
#endif
#endif /* PL9823_V3_H */
