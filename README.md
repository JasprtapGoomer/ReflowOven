# Reflow Oven Control Software

This repository contains the source code for controlling a reflow oven using an STM32 microcontroller. The system is designed to manage the reflow process with precise temperature control and profile management, making it suitable for surface mount technology (SMT) soldering.

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Project Structure](#project-structure)
- [Dependencies](#dependencies)
- [Installation](#installation)
- [Usage](#usage)
- [License](#license)

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
  Main entry point of the application, responsible for initializing hardware components and starting the main control loop.
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


