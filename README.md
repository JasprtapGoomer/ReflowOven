# Reflow Oven Control Software

This repository contains the source code for controlling a reflow oven using an STM32 microcontroller. The system is designed to manage the reflow process with precise temperature control and profile management, making it suitable for surface mount technology (SMT) soldering.

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Project Structure](#project-structure)
- [Dependencies](#dependencies)


## Introduction
The reflow oven control project uses an STM32 microcontroller to automate the reflow soldering process. It allows users to load temperature profiles, monitor the process, and control heating elements in real-time.

## Features
- Automated temperature control based on user-defined profiles
- Support for custom reflow profiles
- User interface integration with Nextion displays
- Real-time feedback on temperature and process status
- Safe handling of power failure and recovery

## Project Structure

| File/Folder                              | Description                                                                |
|------------------------------------------|----------------------------------------------------------------------------|
| `stm32/`                                 | Root folder containing the project files                                   |
| `stm32/Core/Inc/`                        | Header files for the core functionalities                                  |
| `stm32/Core/Src/`                        | Source files implementing core functionalities                             |
| `stm32/Drivers/STM32F1xx_HAL_Driver/`    | HAL driver files for the STM32F1xx microcontroller family                  |
| `stm32/Drivers/CMSIS/`                   | CMSIS libraries for ARM Cortex M3 processor                                |
| `stm32/Drivers/CMSIS/Device/ST/STM32F1xx`| STM32F1xx-specific device files                                            |
| `stm32/libs/`                            | Libraries used in the project                                              |

## Detailed File Description

<details>
  <summary><code>Core/Src/main.c</code></summary>
  
# Detailed Code Summary for main.c

This is a summary of the `main.c` file used in the reflow oven control system based on STM32. Below is a breakdown of each section, including relevant code snippets and explanations for key functionalities.

## File Description: `Core/Src/main.c`

<details>
  <summary>Overview</summary>
  The `main.c` file is the entry point of the application. It initializes the hardware peripherals and handles the core loop that controls the reflow oven process.

  **Main Responsibilities:**
  - Initialize hardware (GPIO, SPI, Timers, UART)
  - Configure system clock
  - Run the infinite loop that executes the reflow oven logic
</details>

<details>
  <summary>Detailed Explanation</summary>

  ### Includes
  ```c
  #include "main.h"
  #include "globVars.h"
  ```
  These includes bring in the STM32 HAL library and project-specific global variables.

  ### Private Variables
  ```c
  SPI_HandleTypeDef hspi1;
  TIM_HandleTypeDef htim1;
  TIM_HandleTypeDef htim4;
  UART_HandleTypeDef huart1;
  ```
  Handles for SPI, TIM, and UART peripherals used to control communication, timing, and serial input/output.

  ### Function Prototypes
  ```c
  void SystemClock_Config(void);
  static void MX_GPIO_Init(void);
  static void MX_SPI1_Init(void);
  static void MX_TIM4_Init(void);
  static void MX_TIM1_Init(void);
  static void MX_USART1_UART_Init(void);
  ```
  These are the prototypes for system initialization functions for peripherals like GPIO, SPI, Timers, and UART.

  ### Main Function
  ```c
  int main(void) {
    HAL_Init();  // Initialize the Hardware Abstraction Layer (HAL)
    SystemClock_Config();  // Configure the system clock
    
    MX_GPIO_Init();  // Initialize GPIO
    MX_SPI1_Init();  // Initialize SPI
    MX_TIM4_Init();  // Initialize Timer 4
    MX_TIM1_Init();  // Initialize Timer 1
    MX_USART1_UART_Init();  // Initialize UART

    while (1) {
      // Core reflow oven logic (temperature control, user interface, etc.)
    }
  }
  ```
  **Explanation:** 
  - **`HAL_Init`**: Resets all peripherals and initializes the HAL library.
  - **`SystemClock_Config`**: Sets up the system clock.
  - **Peripheral Initialization**: Each `MX_*_Init` function initializes specific peripherals.
  - **While Loop**: The infinite loop where the core reflow logic runs. **(Detailed explanation follows)**

  ### GPIO Initialization
  ```c
  static void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOA_CLK_ENABLE();  // Enable clock for GPIO Port A
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);  // Set PA5 to low

    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);  // Initialize GPIO Pin PA5
  }
  ```

  ### SPI Initialization
  ```c
  static void MX_SPI1_Init(void) {
    hspi1.Instance = SPI1;
    hspi1.Init.Mode = SPI_MODE_MASTER;
    hspi1.Init.Direction = SPI_DIRECTION_2LINES;
    hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
    hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
    hspi1.Init.NSS = SPI_NSS_SOFT;
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
    hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi1.Init.CRCPolynomial = 10;
    if (HAL_SPI_Init(&hspi1) != HAL_OK) {
      Error_Handler();  // Handle errors
    }
  }
  ```

  ### Timer Initialization
  ```c
  static void MX_TIM1_Init(void) {
    htim1.Instance = TIM1;
    htim1.Init.Prescaler = 0;
    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim1.Init.Period = 65535;
    htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    if (HAL_TIM_Base_Init(&htim1) != HAL_OK) {
      Error_Handler();  // Handle errors
    }
  }
  ```

  ### UART Initialization
  ```c
  static void MX_USART1_UART_Init(void) {
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart1) != HAL_OK) {
      Error_Handler();  // Handle errors
    }
  }
  ```

  ### Main While Loop
  The core logic for controlling the reflow oven is executed inside the infinite loop. Each iteration performs the necessary tasks to adjust the heating elements, monitor temperature, and handle user input/output.

  **Example pseudocode for the loop tasks:**
  - **Temperature Monitoring**: Read temperature data from sensors.
  - **Control Heating Elements**: Adjust heating power based on the current stage of the reflow process.
  - **Update User Interface**: Display the current status on the Nextion display.
  - **Handle User Inputs**: Respond to any user inputs from the display or serial interface.
  
  ### Error Handler
  ```c
  void Error_Handler(void) {
    while (1) {
      // Handle system errors (e.g., communication failure)
    }
  }
  ```

  ### System Clock Configuration
  ```c
  void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
      Error_Handler();
    }
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
      Error_Handler();
    }
  }
  ```
</details>

</details>

<details>
  <summary><code>Core/Src/reflowMath.c</code></summary>
  Contains algorithms for controlling the temperature profile during the reflow process.
</details>

<details>
  <summary><code>Core/Src/nextionGraphics.c</code></summary>
  Implements communication and graphics handling with the Nextion display.
</details>

<details>
  <summary><code>Core/Src/stm32f1xx_it.c</code></summary>
  Interrupt service routines for handling system-level interrupts.
</details>

<details>
  <summary><code>Drivers/STM32F1xx_HAL_Driver/</code></summary>
  STM32 HAL drivers for interacting with peripherals such as GPIO, UART, and timers.
</details>

## Dependencies
- STM32CubeMX (for project setup)
- STM32 HAL library
- CMSIS for ARM Cortex-M microcontrollers


