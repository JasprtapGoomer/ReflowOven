/* nextionGraphics.h
 *
 *  Created on: Jan 4, 2024
 *      Author: Julian Olano Medina
 *		Lecture CRN: 70607
 *		Tutorial CRN: 70620
 */

#ifndef INC_NEXTIONGRAPHICS_H_
#define INC_NEXTIONGRAPHICS_H_


#include "globVars.h"
#include "stm32f1xx_hal.h"

void SaveParameters();
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void NEXTION_SendString(char *ID, char *string);
void NEXTION_SendFloat(char *ID, float32_t number);
void NEXTION_SenduInt(char *ID, uint32_t number);
void NEXTION_CMD(char *string);
void UpdatePage();
void NextionDrawDot(uint32_t x, uint32_t y);
void NextionDrawTemp(uint32_t x, uint32_t y);
float32_t HandleKeyPad();
void Update_Page_3();
void Update_Page_0();
void Update_Page_2();
void HandleGui();

#endif /* INC_NEXTIONGRAPHICS_H_ */
