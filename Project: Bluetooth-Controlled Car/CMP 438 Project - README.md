# CMP 438 Project - Bluetooth-Controlled Car

## Overview
This project is a Bluetooth-controlled robot car constructed using an Arduino Uno, an L298N motor driver, and an HC-05 Bluetooth module. A smartphone sends commands through Bluetooth, and the robot responds with corresponding movement.

---

## Simulation
View the TinkerCAD circuit here: https://www.tinkercad.com/things/igILUXtGBrG-cmp-438-project-keyboard-controlled-car?sharecode=ouXh349QThBm-k8ye4wscJ36WKpGQb2r2AGfotNXZYA

## Code
View the full Arduino code here: https://github.com/Chaotic-Legend/CMP-438-Codes/blob/main/Project%3A%20Bluetooth-Controlled%20Car/CMP%20438%20Project%20-%20Bluetooth-Controlled%20Car.ino

---

## Features
- Wireless Bluetooth control using HC-05
- Moves forward, backward, left, right, and stops
- Motor control using L298N driver
- Compatible with Android Bluetooth Controller apps
- TinkerCAD simulation included

---

## Components Used
- Arduino Uno  
- L298N Motor Driver  
- HC-05 Bluetooth Module  
- Two DC motors  
- Chassis + wheels  
- Battery pack  
- Jumper wires  
- Voltage divider (1kΩ + 2kΩ)

---

## Wiring Summary

### Bluetooth Module
| HC-05 Pin | Arduino Pin |
|----------|--------------|
| VCC | 5V |
| GND | GND |
| TX | RX (0) |
| RX | TX (1, with voltage divider) |

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
