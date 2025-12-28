// CMP 438: Communicating Robots - Isaac D. Hoyos
// Tinkercad Link: https://tinyurl.com/5y2kns7j

// These constants define the Arduino pins connected to the L293D.
const int motorLeftPinForward = 4;   // IN3 on L293D motor driver.
const int motorLeftPinBackward = 5;  // IN4 on L293D motor driver.
const int motorRightPinForward = 2;  // IN1 on L293D motor driver.
const int motorRightPinBackward = 3; // IN2 on L293D motor driver.
const int enable1 = 9;               // EN1 on L293D motor driver.
const int enable2 = 10;              // EN2 on L293D motor driver.

void setup() {
  // These pins are configured to control motor direction.
  pinMode(motorLeftPinForward, OUTPUT);
  pinMode(motorLeftPinBackward, OUTPUT);
  pinMode(motorRightPinForward, OUTPUT);
  pinMode(motorRightPinBackward, OUTPUT);
  
  // These pins are configured to control motor direction.
  pinMode(enable1, OUTPUT);
  pinMode(enable2, OUTPUT);

  // These lines set both motors to run at full speed using PWM.
  analogWrite(enable1, 255);
  analogWrite(enable2, 255);
}

void loop() {
  // This sequence shows forward movement, turning, and stopping.
  moveForward();
  delay(2000);
  turnLeft();
  delay(1500);
  moveForward();
  delay(2000);
  turnRight();
  delay(1500);
  stopMotors();
  delay(2000);
}

// This function moves the left motor forward.
void motorLeftMoveForward() {
  digitalWrite(motorLeftPinForward, HIGH);
  digitalWrite(motorLeftPinBackward, LOW);
}

// This function moves the right motor forward.
void motorRightMoveForward() {
  digitalWrite(motorRightPinForward, HIGH);
  digitalWrite(motorRightPinBackward, LOW);
}

// This function moves the left motor backward.
void motorLeftMoveBackward() {
  digitalWrite(motorLeftPinForward, LOW);
  digitalWrite(motorLeftPinBackward, HIGH);
}

// This function moves the right motor backward.
void motorRightMoveBackward() {
  digitalWrite(motorRightPinForward, LOW);
  digitalWrite(motorRightPinBackward, HIGH);
}

// This function moves both motors forward.
void moveForward() {
  motorLeftMoveForward();
  motorRightMoveForward();
}

// This function moves both motors backward.
void moveBackward() {
  motorLeftMoveBackward();
  motorRightMoveBackward();
}

// This function turns left by stopping the left motor.
void turnLeft() {
  digitalWrite(motorLeftPinForward, LOW);
  digitalWrite(motorLeftPinBackward, LOW);
  motorRightMoveForward();
}

// This function turns right by stopping the right motor.
void turnRight() {
  digitalWrite(motorRightPinForward, LOW);
  digitalWrite(motorRightPinBackward, LOW);
  motorLeftMoveForward();
}

// This function performs a pivot turn by moving the motors.
void pivotTurn() {
  motorLeftMoveForward();
  motorRightMoveBackward();
}

// This function stops all motor movement.
void stopMotors() {
  digitalWrite(motorLeftPinForward, LOW);
  digitalWrite(motorLeftPinBackward, LOW);
  digitalWrite(motorRightPinForward, LOW);
  digitalWrite(motorRightPinBackward, LOW);
}
