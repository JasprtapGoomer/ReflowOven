# STM32 Reflow Oven Project

## Overview
This project uses an STM32 Blue Pill microcontroller to control a reflow oven for soldering purposes. The project aims to achieve a proper reflow curve using a PID control loop. It utilizes the MAX6675 thermocouple for temperature measurement, a Nextion display for visual feedback, and an ESP32 for remote monitoring and control.

The project directory is organized to ensure modularity, making it easier to understand and maintain each specific function.

## File Descriptions

### **Header Files (`/Core/Inc`)**

1. **`main.h`**: 
   - The main header file that contains function prototypes, system includes, and shared definitions required by the `main.c` file.

2. **`globals.h`**: 
   - Contains global variables, constants, and shared structs that are used throughout the project. This includes settings like PID parameters, oven status flags, and sensor data variables, providing centralized control for easy modifications.

3. **`max6675.h`**:
   - Interface header for the MAX6675 thermocouple sensor. It declares functions and constants necessary for reading temperature data from the MAX6675.

4. **`display.h`**:
   - Defines functions used to interact with the Nextion display, such as updating temperature values, plotting graphs, and sending control commands. 

5. **`oven_control.h`**:
   - Header file containing function declarations for the oven control logic, including PID controller implementation, heating, and cooling stages. This ensures smooth transitions between different phases of the reflow process.

6. **`communication.h`**:
   - Contains function prototypes for communication between the STM32 and ESP32 over UART. The communication allows for remote monitoring and controlling oven operations.

### **Source Files (`/Core/Src`)**

1. **`main.c`**:
   - The main entry point for the STM32 project. It initializes peripherals (such as ADC, UART, GPIO, and timers), sets up the system, and runs the main control loop. This file also manages the overall flow of the reflow process by calling relevant functions from other modules.

2. **`max6675.c`**:
   - Implements the logic for reading temperature data from the MAX6675 thermocouple sensor. This file contains the code necessary to initialize the SPI communication, read temperature values, and perform any necessary conversions.

3. **`display.c`**:
   - Contains the code for interfacing with the Nextion display, including sending temperature data, displaying real-time graphs, and updating control parameters. This ensures users have a visual understanding of the oven's current state and performance.

4. **`oven_control.c`**:
   - Implements the PID control loop and the logic to control the oven's heating and cooling stages. This file contains functions that adjust heating elements based on the PID algorithm to maintain a proper reflow temperature profile for soldering.

5. **`communication.c`**:
   - Manages UART communication between the STM32 and the ESP32. This allows data such as current oven temperature, error status, and control commands to be exchanged for remote monitoring and operation.

## Usage Instructions

1. **Setup Hardware**:
   - Connect the STM32 Blue Pill to the MAX6675 thermocouple, toaster oven relay, Nextion display, and ESP32 as described in the project's documentation.

2. **Flash Firmware**:
   - Use STM32 CubeIDE to build and flash the firmware to the STM32.

3. **Run Reflow Process**:
   - Power on the system. The main loop in `main.c` will start by reading sensor data (`max6675.c`), controlling the oven (`oven_control.c`), and displaying information (`display.c`).

4. **Remote Monitoring**:
   - The ESP32 can be used to monitor and control the oven remotely, with communication managed by `communication.c`.

## Project Goals

- **Modularity**: The code is divided into different files based on functionality to ensure easy maintenance and expansion.
- **Real-Time Control**: The project uses a PID algorithm to manage the heating and cooling of the oven for a precise reflow profile.
- **Remote Monitoring**: Communication with an ESP32 allows users to control and monitor the oven remotely via a web interface or mobile app.

## Getting Started

- Ensure you have STM32 CubeIDE installed.
- Connect all hardware components according to the wiring diagram in the `Documentation` folder.
- Build and upload the project using CubeIDE.
- Monitor the oven through the Nextion display or remotely using the ESP32.

## Future Improvements

- **Wi-Fi Capability**: Extend the ESP32 capabilities to provide a web interface for more intuitive control.
- **Data Logging**: Log temperature profiles for analysis and process optimization.
- **Enhanced UI**: Improve the display's interface to add more information such as real-time error reporting or power usage.

---

Feel free to explore each file to gain a deeper understanding of how each module interacts to achieve a fully functional reflow oven controller.
