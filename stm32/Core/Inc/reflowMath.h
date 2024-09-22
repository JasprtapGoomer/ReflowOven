/*
 * reflowMath.h
 *
 *  Created on: Jan 4, 2024
 *      Author: Quentin Dela Torre
 */

#ifndef INC_REFLOWMATH_H_
#define INC_REFLOWMATH_H_

#include "globVars.h"
#include "stm32f1xx_hal.h"

void setReflowParameters(void);// still need extern in header
void calculateReflowCurve(void);
void Draw_Reflow_Curve(void);
void startReflow(void);
void stopReflow(void);

#endif /* INC_REFLOWMATH_H_ */
