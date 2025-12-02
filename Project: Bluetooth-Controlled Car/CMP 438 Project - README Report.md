# CMP 438 Project - Bluetooth-Controlled Car Report

- Students: Isaac D. Hoyos & Roberto Morales
- Course: CMP 438 - Communicating Robots
- Professor: Yanilda Peralta Ramos
- Project Title: Bluetooth-Controlled Car
- Date: December 2nd, 2025

## Overview & Objectives
This project presents a fully operational Bluetooth-controlled robotic car designed and implemented for the CMP 438 Communicating Robots course. The robotic vehicle uses an Arduino-compatible Inland Uno R3 MainBoard, four DC 3–6V dual-shaft gearbox motors, an L298N dual H-bridge motor driver, a 7.4V Li-Ion battery pack, an HC-05 Bluetooth module, a blue LED for visual status feedback, and a variety of supporting components used to integrate all systems into a functional mobile platform. Through Bluetooth connectivity, we can remotely control the robot using an Android smartphone through the Arduino Car Connect App, which features directional arrow buttons and dedicated rotation controls. When the user presses the interface buttons, the app sends encoded commands, such as forward, backward, left, right, pivot left, pivot right, stop, LED on, or LED off, directly to the HC-05 module. The module interprets these commands and executes them through the Arduino by using precise motor control logic defined in the code.

The primary objective of this project is to build a functioning, small-scale robotic vehicle that demonstrates wireless communication, embedded programming, and coordinated motor control. The system shows how a microcontroller interprets Bluetooth commands and converts them into physical motion through the motor driver and hardware circuitry. Additional goals include implementing reliable wiring, developing clean and maintainable code, and verifying performance through simulation and real-world testing. Overall, the project highlights the complete process of designing, programming, assembling, and evaluating a Bluetooth-controlled robotic system.

All development tasks, including writing the Arduino code, creating the TinkerCAD simulation, preparing the GitHub repository, designing the diagrams and schematics, and writing the full project report, were completed by Isaac D. Hoyos. Roberto Morales was responsible for acquiring all hardware components, assembling the physical robotic car, wiring all components on the chassis, testing the uploaded Arduino code on the real robot, and capturing photos and a demonstration video of the final results. I used TinkerCAD to create a virtual model of the system, but the online simulator had limitations that prevented me from accurately simulating the real robotic vehicle. It does not support the HC-05 Bluetooth module, cannot simulate Bluetooth communication with an Android phone, and does not allow me to use more than two hobby gearmotors. For this reason, the TinkerCAD version uses keyboard input to demonstrate the concept, while the physical robot uses genuine Bluetooth communication with the necessary components.

- This directory folder contains the full Arduino source code for the project.
- It includes all wiring diagrams required to assemble the circuit.
- It provides complete design documentation explaining the system's structure.
- It also contains a simulation link for testing the project virtually.
- Finally, it includes the project report information for reference.

---

## Code
- View the full Arduino code here: https://github.com/Chaotic-Legend/CMP-438-Codes/blob/main/Project%3A%20Bluetooth-Controlled%20Car/CMP%20438%20Project%20-%20Bluetooth-Controlled%20Car.ino

## Simulation
- View the TinkerCAD circuit here: https://www.tinkercad.com/things/igILUXtGBrG-cmp-438-project-keyboard-controlled-car?sharecode=ouXh349QThBm-k8ye4wscJ36WKpGQb2r2AGfotNXZYA

---

## Features
- The robotic car uses wireless Bluetooth communication through an HC-05 module.
- The system is fully compatible with Android Bluetooth controller apps, such as the Arduino Car Connect App.
- Its motors are driven using an L298N motor driver module to move the wheels of the vehicle.
- It is capable of moving forward, backward, turning left or right, and stopping on command.
- A complete TinkerCAD simulation is included to demonstrate an example circuit and code.

## Components Used
- 1x Blue LED
- 4x Tire Wheels
- 1x Plastic Chassis
- 1x L298N Motor Driver
- 1x 7.4V Li-Ion Battery
- 1x HC-05 Bluetooth Module
- 2x Male to Male Jumper Wires
- 10x Female to Male Jumper Wires
- 1x Inland Uno R3 MainBoard Arduino Compatible
- 4x TT Motor With Leads, DC 3-6V Gearbox Motor Dual Shaft

## Component Assembly & Design Documentation
The design diagrams and schematics included in the repository illustrate the entire wiring layout of the motor driver, Bluetooth module, Arduino UNO, power distribution, and motor outputs. The assembly process began with mounting the four DC gearbox motors onto the chassis, installing the wheels, attaching the L298N motor driver, and positioning the Arduino UNO on the upper level of the platform. The HC-05 module was securely connected with jumper wires and positioned correctly to enable Bluetooth communication with the Android smartphone. All grounds were interconnected across the battery pack, motor driver, and Arduino UNO to ensure a proper reference voltage. The diagrams in the repository visually demonstrate each connected component, from power routing to directional motor control wiring.

---

## Wiring Summary
### HC-05 Bluetooth Module
| HC-05 Pin | Arduino Pin | Description |
|-----------|-------------| ------------|
| VCC | 5V | This pin supplies power to the HC-05 module using the Arduino's regulated 5V output. |
| GND | GND | This pin provides a common ground reference shared with the Arduino and motor driver. |
| TXD | RX (0) | This pin sends Bluetooth data to the Arduino, enabling the robot to receive movement commands. |
| RXD | TX (1) | This pin receives data from the Arduino's TX pin and can send status messages back to the module. |

### L298N Motor Driver
| L298N Pin | Arduino Pin | Description |
|-----------|-------------|-------------|
| IN1 | 8 | This pin sends a high or low signal to control the right motor in the forward direction. |
| IN2 | 9 | This pin sends a high or low signal to control the right motor in the backward direction. |
| IN3 | 10 | This pin sends a high or low signal to control the left motor in the forward direction. |
| IN4 | 11 | This pin sends a high or low signal to control the left motor in the backward direction. |
| GND | GND | This pin is connected to the shared ground to complete the electrical circuit. |

---

## Commands
| Command | Action |
|---------|--------|
| F or ⬆ | Move Forward |
| B or ⬇ | Move Backward |
| L or ⬅ | Turn Left |
| R or ➡ | Turn Right |
| A or ↺ | Pivot Left |
| C or ↻ | Pivot Right |
| O or 💡 | Lights On/Off |
| S or No Command | Stop Car |

## Flowchart
Below is a flowchart showing how the robotic vehicle processes the code and Bluetooth commands:

                 ┌────────────────────────┐
                 │      Start Program     │
                 └───────────┬────────────┘
                             │
                             ▼
                ┌──────────────────────────┐
                │ Initialize Pins & Serial │
                └────────────┬─────────────┘
                             │
                             ▼
               ┌────────────────────────────┐
               │  Wait for Bluetooth Input  │
               └─────────────┬──────────────┘
                             │
               ┌─────────────┴──────────────┐
               ▼                            ▼
       ┌──────────────────┐         ┌───────────────────────────────┐
       │ Command Received │───Yes───▶ Convert the Command to Upper │
       └───────┬──────────┘         └────────┬──────────────────────┘
               │                             │
               No                            ▼
               │                 ┌────────────────────────────────┐
               └───────Loop──────▶ Match the Command to Movement │
                                 └─────────┬──────────────────────┘
                                           │
                ┌──────────────────────────┼──────────────────────┼─────────────────────────┐
                ▼                          ▼                      ▼                         ▼
        ┌────────────────┐       ┌────────────────┐        ┌────────────────┐        ┌────────────────┐
        │  Forward (F)   │       │  Backward (B)  │        │ Turn Left (L)  │        │ Turn Right (R) │
        └───────┬────────┘       └───────┬────────┘        └──────┬─────────┘        └──────┬─────────┘
                │                        │                        │                         │
                ▼                        ▼                        ▼                         ▼
      ┌──────────────────┐      ┌─────────────────┐      ┌──────────────────┐       ┌──────────────────┐
      │ Execute Motor    │      │ Execute Motor   │      │ Execute Motor    │       │ Execute Motor    │
      │ Direction        │      │ Direction       │      │ Direction        │       │ Direction        │
      └──────────────────┘      └─────────┬───────┘      └──────────────────┘       └──────────────────┘
                                          │
                                          ▼
                               ┌─────────────────────┐
                               │  Stop (S) Command?  │
                               └──────────┬──────────┘
                                         Yes
                                          │
                                          ▼
                               ┌────────────────────┐
                               │   Stop All Motors  │
                               └──────────┬─────────┘
                                          │
                                          ▼
                               ┌────────────────────┐
                               │  Return to Waiting │
                               └────────────────────┘

## Explanation of Results
After assembling the entire robotic vehicle and uploading the final version of the Arduino code, the system successfully demonstrated complete Bluetooth functionality using the Arduino Car Connect App on an Android smartphone. Each directional command sent through the app was immediately reflected in the robot's movement, showing reliable real-time communication with the HC-05 module. Pressing F or tapping the upward directional arrow in the app caused the robot to move forward smoothly, while pressing B or the downward arrow correctly triggered backward motion. The turning controls were equally responsive: pressing L or the left arrow rotated the robot to the left, and pressing R or the right arrow rotated it to the right with accurate directional control. While the S command stops the motors, the robotic car also automatically halts when no directional commands are sent from the app on the Android smartphone.

The Arduino Car Connect App included buttons for rotating the robotic car clockwise and counterclockwise in its current position, and the app had an option to remotely turn the blue LED on or off using the on-screen Bluetooth command. These additional features provide safe, predictable, and intuitive control through the app's on-screen directional commands, showcasing the robot's ability to receive and execute various Bluetooth-controlled functions beyond just motor movement. The L298N motor driver delivered stable power to the four DC gear motors, allowing the robot to navigate across the testing surface without stalling or drifting. The Bluetooth signal remained stable within a range of several meters, demonstrating consistent communication between the Android smartphone and the robot's onboard electronics. Roberto recorded a final demonstration video showing the car moving in all directions on command to guarantee that the wiring, code, motor driver, Bluetooth module, and Android control interface were all functioning together as designed.

---
