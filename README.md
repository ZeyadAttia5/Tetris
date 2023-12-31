# Tetris Game for STM32F401CC and 8x8 Dot Matrix




## Table of Contents
- [Introduction](#introduction)
- [Hardware Setup](#hardware-setup)
- [Software Architecture](#software-architecture)
- [How to Build and Flash](#how-to-build-and-flash)
- [Controls](#controls)
- [See It in action!](#see-it-in-action)
- [License](#license)
---

### Introduction

Welcome to the Tetris game for the STM32F401CC microcontroller, played on an 8x8 dot matrix! This project demonstrates the implementation of Tetris on embedded hardware and serves as a learning resource for embedded systems enthusiasts. The game is designed to run efficiently on the STM32F401CC microcontroller, making use of GPIO, EXTI, STK, NVIC, and HAL drivers.

### Hardware Setup

To play Tetris on your STM32F401CC with an 8x8 dot matrix, you'll need the following hardware connections:

- **Dot Matrix Connections (IOA):**
  - IOA0 to IOA7 are connected to Row 7 to Row 0 of the dot matrix.
  
- **Dot Matrix Connections (IOB):**
  - IOB0 to IOB7 are connected to Col 0 to Col 7 of the dot matrix.
  
- **Controls:**
  - IOA8:  Move block right
  - IOA9:  Move block left
  - IOA10: Rotate block
  
Ensure that your hardware connections match the above configuration for the game to work correctly.

### Software Architecture

The game is built upon a modular architecture, making it easy to understand and extend. Key components of the software architecture include:

- **MCAL (Microcontroller Abstraction Layer) Drivers:** These drivers, including GPIO, EXTI, STK, and NVIC, provide low-level control over the STM32F401CC hardware.

- **HAL (Hardware Abstraction Layer) Driver:** The HAL driver for the dot matrix abstracts the low-level details of controlling the display, making it easier to work with the dot matrix.

- **Game Logic:** The core Tetris game logic is implemented, handling block movement, collision detection, and scoring.

- **User Interface:** The game's user interface is optimized for the 8x8 dot matrix, providing an enjoyable gaming experience.

### How to Build and Flash

To build and flash the Tetris game onto your STM32F401CC, follow these steps:

1. Clone the repository: `git clone https://github.com/ZeyadAttia5/Tetris`
2. Set up your development environment with the necessary toolchain and STM32CubeMX if you haven't already.
3. Open the project in your development environment.
4. Configure the project settings to target the STM32F401CC microcontroller.
5. Build the project.
6. Flash the generated binary onto your STM32F401CC microcontroller.


### Controls

Control the Tetris game using the following buttons:

- **Move Block Right:** IOA8
- **Move Block Left:** IOA9
- **Rotate Block:** IOA10

### See It in Action!
https://github.com/ZeyadAttia5/Tetris/assets/85710632/0f6b8446-41f5-45e6-858a-d689bea5c491


### License

This Tetris game is open-source and available under the [GPL v3 License]([license_link](https://www.gnu.org/licenses/gpl-3.0.en.html)). Feel free to use, modify, and distribute it as you see fit.
