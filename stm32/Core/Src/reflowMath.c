/*
 * reflowMath.c
 *
 *  Created on: Jan 4, 2024
 *      Author: Quentin Dela Torre
 */
#include "reflowMath.h"

void setReflowParameters(void) {
	ReflowParameters.KP = 10;
	ReflowParameters.Ki = 10;
	ReflowParameters.KD = 0;
	ReflowParameters.firstHeatUpRate = 1.2;
	ReflowParameters.SoakTempeture = 100;
	ReflowParameters.SoakTime = 100;
	ReflowParameters.secondHeatUpRate = 1.2;
	ReflowParameters.ReflowTempeture = 210;
	ReflowParameters.ReflowTime = 100;
	sprintf(ConsoleMSG, "IDLE");
}

void calculateReflowCurve(void) {
	for (int i = 0; i < 4000; i++) {
		ReflowCurve[i] = 0;
	}

	int index = 0;
	float timestep = 0.5;
	//First Heat Up:
	while (24 + timestep * ReflowParameters.firstHeatUpRate
			< ReflowParameters.SoakTempeture) {			// change to less than
		ReflowCurve[index] = 24 + timestep * ReflowParameters.firstHeatUpRate;
		index++;
		timestep = timestep + 0.5;
	}
	PhaseIndex[1] = index;

	//Soak
	int Soakduration = 2 * ReflowParameters.SoakTime;

	for (int i = 0; i < Soakduration; i++) {
		ReflowCurve[index + i] = ReflowParameters.SoakTempeture;
	}

	//Second Heat Up:
	index = index + Soakduration;
	PhaseIndex[2] = index;
	timestep = 0.5;
	while (ReflowParameters.SoakTempeture
			+ timestep * ReflowParameters.secondHeatUpRate
			<= ReflowParameters.ReflowTempeture) {
		ReflowCurve[index] = ReflowParameters.SoakTempeture
				+ (uint8_t) timestep * ReflowParameters.secondHeatUpRate;
		index++;
		timestep = timestep + 0.5;
	}
	PhaseIndex[3] = index;

	//Reflow
	int Reflowduration = 2 * ReflowParameters.ReflowTime;

	for (int i = 0; i < Reflowduration; i++) {
		ReflowCurve[index + i] = ReflowParameters.ReflowTempeture;
	}

	index = index + Reflowduration;
	ReflowCurve[index] = 0;
	PhaseIndex[4] = index;

	//Cooldown
	timestep = 0.5;
	while (ReflowParameters.ReflowTempeture - timestep * 1.8 >= 24) {
		ReflowCurve[index] = ReflowParameters.ReflowTempeture - timestep * 1.8;
		index++;
		timestep = timestep + 0.5;
	}

}

void Draw_Reflow_Curve(void) {
	float32_t dx = 0.625 / 4; //275px / 880s / 500 ms
	float32_t dy = 0.8333; //200px / 240 Grad
	uint32_t OffsetX = 35;
	uint32_t OffsetY = 230;
	uint32_t index = 0;

	while (ReflowCurve[index] != 0) {

		NextionDrawDot(OffsetX + (uint32_t) ((float32_t) (index) * dx),
				OffsetY - (uint32_t) ((float32_t) (ReflowCurve[index]) * dy));
		index = index + 4;

		if (strncmp((char*) UART_Recieved_Data, "p0b02", 5) == 0)
			break;
	}
}

void startReflow(void) {
	ReflowEnable = 1;
	NEXTION_CMD("page 0");
	Draw_Reflow_Curve();
	TempDrawCounter = 0;
	Update_Page_0();

}

void stopReflow(void) {
	if (ReflowEnable == 1) {
		ReflowEnable = 0;
		TempDrawEnable = 0;
		sprintf(ConsoleMSG, "STOPPED");
		Update_Page_0();
	}
}
