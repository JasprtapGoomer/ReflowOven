/* globVars.h
 *
 *  Created on: Jan 8, 2024
 *      Author: Julian Olano Medina
 *		Lecture CRN: 70607
 *		Tutorial CRN: 70620
 */

#ifndef INC_GLOBVARS_H_
#define INC_GLOBVARS_H_

#define ARM_MATH_CM3
#include "stm32f1xx_hal.h"
#include "arm_math.h"
#include "FLASH_PAGE.h"
#include "stdio.h"
#include <stdlib.h>
#include "string.h"
#include "nextionGraphics.h"
#include "reflowMath.h"

extern SPI_HandleTypeDef hspi1;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim4;

extern UART_HandleTypeDef huart1;

typedef struct {// ensure all items here are 32-bit
	float32_t KP;
	float32_t Ki;
	float32_t KD;
	float32_t firstHeatUpRate;
	uint32_t SoakTempeture;
	uint32_t SoakTime;
	float32_t secondHeatUpRate;
	uint32_t ReflowTempeture;
	uint32_t ReflowTime;
} ReflowTemplate;

extern ReflowTemplate myReflowTemplate;

extern uint8_t data[2];
extern uint8_t ReflowCurve[4000];
extern float temp;
extern float duty;
extern uint32_t data_flash[6];
extern arm_pid_instance_f32 PID;
extern ReflowTemplate ReflowParameters;
extern uint8_t ReflowEnable;
extern uint16_t ReflowIndex;
extern float32_t debug;
extern uint8_t Cmd_End[3];
extern uint8_t UART_Recieved_Data[5];
extern uint8_t UART_Recieved_Flag;
extern char input[20];
extern uint16_t PhaseIndex[5];
extern char ConsoleMSG[20];
extern uint8_t TempDrawEnable;
extern uint32_t TempDrawCounter;
extern uint8_t test2[5];

#endif /* INC_GLOBVARS_H_ */
