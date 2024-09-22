/* nextionGraphics.c
 *
 *  Created on: Jan 4, 2024
 *      Author: Julian Olano Medina
 *		Lecture CRN: 70607
 *		Tutorial CRN: 70620
 */
#include "nextionGraphics.h"
//only initialize variables in main, see documentation

void SaveParameters() {
	Flash_Write_Data(0x0801FC00, &ReflowParameters, 9);//ignore warning for now. see documentation
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	HAL_UART_Receive_IT(&huart1, UART_Recieved_Data, 5);
	UART_Recieved_Flag = 1;
}
void NEXTION_SendString(char *ID, char *string) {
	char buf[50];
	int len = sprintf(buf, "%s.txt=\"%s\"", ID, string);
	HAL_UART_Transmit(&huart1, (uint8_t*) buf, len, 1000);
	HAL_UART_Transmit(&huart1, Cmd_End, 3, 100);

}
void NEXTION_SendFloat(char *ID, float32_t number) {
	char buf[50];
	int len = sprintf(buf, "%s.txt=\"%.2f\"", ID, number);
	HAL_UART_Transmit(&huart1, (uint8_t*) buf, len, 1000);
	HAL_UART_Transmit(&huart1, Cmd_End, 3, 100);
}
void NEXTION_SenduInt(char *ID, uint32_t number) {
	char buf[50];
	int len = sprintf(buf, "%s.txt=\"%lu\"", ID, number);
	HAL_UART_Transmit(&huart1, (uint8_t*) buf, len, 1000);
	HAL_UART_Transmit(&huart1, Cmd_End, 3, 100);
}
void NEXTION_CMD(char *string) {
	HAL_UART_Transmit(&huart1, (uint8_t*) string, strlen(string), 1000);
	HAL_UART_Transmit(&huart1, Cmd_End, 3, 100);
}
void UpdatePage() {
	NEXTION_SendFloat("t1", ReflowParameters.firstHeatUpRate);
	NEXTION_SenduInt("t2", ReflowParameters.SoakTempeture);
	NEXTION_SenduInt("t3", ReflowParameters.SoakTime);
	NEXTION_SendFloat("t4", ReflowParameters.secondHeatUpRate);
	NEXTION_SenduInt("t5", ReflowParameters.ReflowTempeture);
	NEXTION_SenduInt("t6", ReflowParameters.ReflowTime);
}
void NextionDrawDot(uint32_t x, uint32_t y) {
	char buf[50];
	int len = sprintf(buf, "cirs %lu,%lu,2,BLUE", x, y);
	HAL_UART_Transmit(&huart1, (uint8_t*) buf, len, 1000);
	HAL_UART_Transmit(&huart1, Cmd_End, 3, 100);
}
void NextionDrawTemp(uint32_t x, uint32_t y) {
	char buf[50];
	int len = sprintf(buf, "cirs %lu,%lu,2,RED", x, y);
	HAL_UART_Transmit(&huart1, (uint8_t*) buf, len, 1000);
	HAL_UART_Transmit(&huart1, Cmd_End, 3, 100);
}
float32_t HandleKeyPad() {
	//clear Input
	for (int i = 0; i < 20; i++) {
		input[i] = 0;
	}
	uint8_t index = 0;

	NEXTION_SendString("t0", "");
	UART_Recieved_Flag = 0;
	while (strncmp((char*) UART_Recieved_Data, "enter", 5) != 0) {
		if (strncmp((char*) UART_Recieved_Data, "abbre", 5) == 0)
			return 9999;
		if (strncmp((char*) UART_Recieved_Data, "kback", 5) == 0)
			return 8888;
		if (UART_Recieved_Flag == 1) {
			input[index] = UART_Recieved_Data[4];
			UART_Recieved_Flag = 0;
			index++;
			NEXTION_SendString("t0", input);
		}
	}
	return atof(input);
}
void Update_Page_3() {
	uint8_t defaultUart[5] = { 'p', '3', 'x', 'x', 'x' };
	for (int i = 0; i < 5; i++) {
		UART_Recieved_Data[i] = defaultUart[i];
	}
	NEXTION_SendFloat("t0", ReflowParameters.firstHeatUpRate);
	NEXTION_SenduInt("t1", ReflowParameters.SoakTime);
	NEXTION_SenduInt("t2", ReflowParameters.SoakTempeture);
	NEXTION_SendFloat("t3", ReflowParameters.secondHeatUpRate);
	NEXTION_SenduInt("t4", ReflowParameters.ReflowTime);
	NEXTION_SenduInt("t5", ReflowParameters.ReflowTempeture);
}
void Update_Page_0() {
	uint8_t defaultUart[5] = { 'p', '0', 'x', 'x', 'x' };
	for (int i = 0; i < 5; i++) {
		UART_Recieved_Data[i] = defaultUart[i];
	}
	float32_t dx = 0.625 / 4; //275px / 400s
	float32_t dy = 0.8333; //200px / 240 Grad
	uint32_t OffsetX = 35;
	uint32_t OffsetY = 230;
	//Reflow Aktuelle Temperatur anzeigen: | Show Current Reflow Temperature
	if (ReflowEnable == 1) {
		TempDrawEnable = 1;
	}
	if (TempDrawEnable == 1) {
		NextionDrawTemp(
				OffsetX + (uint32_t) ((float32_t) (TempDrawCounter) * dx),
				OffsetY - (uint32_t) ((float32_t) (temp) * dy));
		if (ReflowCurve[TempDrawCounter] == 0) {
			TempDrawEnable = 0;
		}
	}
	NEXTION_SendFloat("t0", temp);
	NEXTION_SendFloat("t1", ReflowParameters.firstHeatUpRate);
	NEXTION_SenduInt("t3", ReflowParameters.SoakTime);
	NEXTION_SenduInt("t2", ReflowParameters.SoakTempeture);
	NEXTION_SendFloat("t4", ReflowParameters.secondHeatUpRate);
	NEXTION_SenduInt("t6", ReflowParameters.ReflowTime);
	NEXTION_SenduInt("t5", ReflowParameters.ReflowTempeture);
	NEXTION_SendString("g1", ConsoleMSG);
}
void Update_Page_2() {
	uint8_t defaultUart[5] = { 'p', '2', 'x', 'x', 'x' };
	for (int i = 0; i < 5; i++) {
		UART_Recieved_Data[i] = defaultUart[i];
	}

	NEXTION_SendFloat("t0", ReflowParameters.KP);
	NEXTION_SendFloat("t1", ReflowParameters.Ki);
	NEXTION_SendFloat("t2", ReflowParameters.KD);
}
void HandleGui() {
	//###################Page0##########################

	if (strncmp((char*) UART_Recieved_Data, "p0xxx", 5) == 0) {
		Update_Page_0();
	}

	if (strncmp((char*) UART_Recieved_Data, "p0b02", 5) == 0) {
		Update_Page_3();
	}

	if (strncmp((char*) UART_Recieved_Data, "p0b00", 5) == 0) {
		startReflow();
		Update_Page_0();
	}

	if (strncmp((char*) UART_Recieved_Data, "p0b01", 5) == 0) {
		stopReflow();
		Update_Page_0();
	}

	if (strncmp((char*) UART_Recieved_Data, "p0b02", 5) == 0) {
		Update_Page_3();
	}

	//###################Page2##########################

	if (strncmp((char*) UART_Recieved_Data, "p2xxx", 5) == 0) {
		Update_Page_2();
	}

	if (strncmp((char*) UART_Recieved_Data, "p2b00", 5) == 0) {
		float32_t Output = 0;
		Output = HandleKeyPad();
		while (Output == 9999) {
			uint8_t defaultUart[5] = { 'x', 'x', 'x', 'x', 'x' };
			for (int i = 0; i < 5; i++) {
				UART_Recieved_Data[i] = defaultUart[i];
			}
			Output = HandleKeyPad();
		}
		if (Output == 8888) {
			Output = ReflowParameters.KP;
		}
		ReflowParameters.KP = Output;
		PID.Kp = ReflowParameters.KP;
		arm_pid_init_f32(&PID, 1);
		Update_Page_2();
		NEXTION_CMD("page 2");

	}

	if (strncmp((char*) UART_Recieved_Data, "p2b01", 5) == 0) {
		float32_t Output = 0;
		Output = HandleKeyPad();
		while (Output == 9999) {
			uint8_t defaultUart[5] = { 'x', 'x', 'x', 'x', 'x' };
			for (int i = 0; i < 5; i++) {
				UART_Recieved_Data[i] = defaultUart[i];
			}
			Output = HandleKeyPad();
		}
		if (Output == 8888) {
			Output = ReflowParameters.Ki;
		}
		ReflowParameters.Ki = Output;
		PID.Ki = ReflowParameters.Ki;
		arm_pid_init_f32(&PID, 1);
		Update_Page_2();
		NEXTION_CMD("page 2");

	}

	if (strncmp((char*) UART_Recieved_Data, "p2b02", 5) == 0) {
		float32_t Output = 0;
		Output = HandleKeyPad();
		while (Output == 9999) {
			uint8_t defaultUart[5] = { 'x', 'x', 'x', 'x', 'x' };
			for (int i = 0; i < 5; i++) {
				UART_Recieved_Data[i] = defaultUart[i];
			}
			Output = HandleKeyPad();
		}
		if (Output == 8888) {
			Output = ReflowParameters.KD;
		}
		ReflowParameters.KD = Output;
		PID.Kd = ReflowParameters.KD;
		arm_pid_init_f32(&PID, 1);
		Update_Page_2();
		NEXTION_CMD("page 2");

	}

	if (strncmp((char*) UART_Recieved_Data, "p2b03", 5) == 0) {
		Update_Page_3();
	}

	//###################Page 3########################

	if (strncmp((char*) UART_Recieved_Data, "p3xxx", 5) == 0) {
		Update_Page_3();
	}

	if (strncmp((char*) UART_Recieved_Data, "p3b00", 5) == 0) {
		float32_t Output = 0;
		Output = HandleKeyPad();
		while (Output == 9999) {
			uint8_t defaultUart[5] = { 'x', 'x', 'x', 'x', 'x' };
			for (int i = 0; i < 5; i++) {
				UART_Recieved_Data[i] = defaultUart[i];
			}
			Output = HandleKeyPad();
		}
		if (Output == 8888) {
			Output = ReflowParameters.firstHeatUpRate;
		}

		if (Output < 0.2)
			Output = 0.2;

		ReflowParameters.firstHeatUpRate = Output;
		Update_Page_3();
		NEXTION_CMD("page 3");
		calculateReflowCurve();

	}
	//NEXTION_SendFloat("t0", ReflowParameters.firstHeatUpRate);

	if (strncmp((char*) UART_Recieved_Data, "p3b01", 5) == 0) {
		float32_t Output = 0;
		Output = HandleKeyPad();
		while (Output == 9999) {
			uint8_t defaultUart[5] = { 'x', 'x', 'x', 'x', 'x' };
			for (int i = 0; i < 5; i++) {
				UART_Recieved_Data[i] = defaultUart[i];
			}
			Output = HandleKeyPad();
		}
		if (Output == 8888) {
			Output = ReflowParameters.SoakTime;
		}
		ReflowParameters.SoakTime = Output;
		Update_Page_3();
		NEXTION_CMD("page 3");
		calculateReflowCurve();

	}
	//NEXTION_SendFloat("t0", ReflowParameters.firstHeatUpRate);

	if (strncmp((char*) UART_Recieved_Data, "p3b02", 5) == 0) {
		float32_t Output = 0;
		Output = HandleKeyPad();
		while (Output == 9999) {
			uint8_t defaultUart[5] = { 'x', 'x', 'x', 'x', 'x' };
			for (int i = 0; i < 5; i++) {
				UART_Recieved_Data[i] = defaultUart[i];
			}
			Output = HandleKeyPad();
		}
		if (Output == 8888) {
			Output = ReflowParameters.SoakTempeture;
		}
		ReflowParameters.SoakTempeture = Output;
		Update_Page_3();
		NEXTION_CMD("page 3");
		calculateReflowCurve();

	}
	//NEXTION_SendFloat("t0", ReflowParameters.firstHeatUpRate);

	if (strncmp((char*) UART_Recieved_Data, "p3b03", 5) == 0) {
		float32_t Output = 0;
		Output = HandleKeyPad();
		while (Output == 9999) {
			uint8_t defaultUart[5] = { 'x', 'x', 'x', 'x', 'x' };
			for (int i = 0; i < 5; i++) {
				UART_Recieved_Data[i] = defaultUart[i];
			}
			Output = HandleKeyPad();
		}
		if (Output == 8888) {
			Output = ReflowParameters.secondHeatUpRate;
		}
		if (Output < 0.2)
			Output = 0.2;
		ReflowParameters.secondHeatUpRate = Output;
		Update_Page_3();
		NEXTION_CMD("page 3");
		calculateReflowCurve();

	}

	//NEXTION_SendFloat("t0", ReflowParameters.firstHeatUpRate);

	if (strncmp((char*) UART_Recieved_Data, "p3b04", 5) == 0) {
		float32_t Output = 0;
		Output = HandleKeyPad();
		while (Output == 9999) {
			uint8_t defaultUart[5] = { 'x', 'x', 'x', 'x', 'x' };
			for (int i = 0; i < 5; i++) {
				UART_Recieved_Data[i] = defaultUart[i];
			}
			Output = HandleKeyPad();
		}
		if (Output == 8888) {
			Output = ReflowParameters.ReflowTime;
		}
		ReflowParameters.ReflowTime = Output;
		Update_Page_3();
		NEXTION_CMD("page 3");
		calculateReflowCurve();

	}

	if (strncmp((char*) UART_Recieved_Data, "p3b05", 5) == 0) {
		float32_t Output = 0;
		Output = HandleKeyPad();
		while (Output == 9999) {
			uint8_t defaultUart[5] = { 'x', 'x', 'x', 'x', 'x' };
			for (int i = 0; i < 5; i++) {
				UART_Recieved_Data[i] = defaultUart[i];
			}
			Output = HandleKeyPad();
		}
		if (Output == 8888) {
			Output = ReflowParameters.ReflowTempeture;
		}
		ReflowParameters.ReflowTempeture = Output;
		Update_Page_3();
		NEXTION_CMD("page 3");
		calculateReflowCurve();

	}

	if (strncmp((char*) UART_Recieved_Data, "p3b06", 5) == 0) {
		Update_Page_2();
	}

	if (strncmp((char*) UART_Recieved_Data, "p3b07", 5) == 0) {
		Update_Page_0();
		Draw_Reflow_Curve();
		SaveParameters();
	}
}
