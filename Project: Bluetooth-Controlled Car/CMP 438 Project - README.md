# CMP 438 Project - Bluetooth-Controlled Car

- Students: Isaac D. Hoyos & Roberto Morales
- Course: CMP 438 – Communicating Robots
- Professor: Yanilda Peralta Ramos
- Project Title: Bluetooth-Controlled Car
- Date: December 2nd, 2025

## Overview
This project is a Bluetooth-controlled robot car constructed using an Arduino Uno, an L298N motor driver, and an HC-05 Bluetooth module. A smartphone sends commands through Bluetooth, and the robot responds with corresponding movement.

- This directory folder contains the full Arduino source code for the project.
- It includes all wiring diagrams required to assemble the circuit.
- It provides complete design documentation explaining the system's structure.
- It also contains a simulation link for testing the project virtually.
- Finally, it includes the project report information for reference.

---

## Code
View the full Arduino code here: https://github.com/Chaotic-Legend/CMP-438-Codes/blob/main/Project%3A%20Bluetooth-Controlled%20Car/CMP%20438%20Project%20-%20Bluetooth-Controlled%20Car.ino

## Simulation
View the TinkerCAD circuit here: https://www.tinkercad.com/things/igILUXtGBrG-cmp-438-project-keyboard-controlled-car?sharecode=ouXh349QThBm-k8ye4wscJ36WKpGQb2r2AGfotNXZYA

---

## Features
- The robot uses wireless Bluetooth control through an HC-05 module.
- The system is fully compatible with Android Bluetooth controller apps, such as the Arduino Car Connect App.
- Its motors are driven using an L298N motor driver module.
- It is capable of moving forward, backward, turning left or right, and stopping on command.
- A complete TinkerCAD simulation is included to demonstrate an example circuit and code.

---

## Components Used 
- 4x DC 3-6V Gearbox Motor Dual Shaft 
- 1x L298N Motor Driver 
- 1x Inland UNO Board (Arduino UNO Replica)
- 1x 7.4v Li-Ion Battery 
- 1x HC-05 Bluetooth Module 
- 1x Blue LED
- Chassis
- Wheels  
- Jumper Wires 

---

## Wiring Summary

### Bluetooth Module
| HC-05 Pin | Arduino Pin |
|----------|--------------|
| VCC | 5V |
| GND | GND |
| TX | RX (0) |

### L298N Motor Driver
| L298N Pin | Arduino Pin |
|-----------|-------------|
| IN1 | 8 |
| IN2 | 9 |
| IN3 | 10 |
| IN4 | 11 |
| ENA | 5 |
| ENB | 6 |
| GND | GND |

---

## Commands
| Command | Action |
|---------|--------|
| F | Move Forward |
| B | Move Backward |
| L | Turn Left |
| R | Turn Right |
| S | Stop |

---
