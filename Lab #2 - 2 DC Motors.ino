// CMP 438: Communicating Robots - Isaac D. Hoyos

// === Define Motor Control Pins ===
const int motorLeftPinForward = 4;   // IN3 on L293D
const int motorLeftPinBackward = 5;  // IN4 on L293D
const int motorRightPinForward = 2;  // IN1 on L293D
const int motorRightPinBackward = 3; // IN2 on L293D
const int enable1 = 9;               // EN1 on L293D
const int enable2 = 10;              // EN2 on L293D

void setup() {
  // Set up motor control pins.
  pinMode(motorLeftPinForward, OUTPUT);
  pinMode(motorLeftPinBackward, OUTPUT);
  pinMode(motorRightPinForward, OUTPUT);
  pinMode(motorRightPinBackward, OUTPUT);
  
  // Set up enable pins.
  pinMode(enable1, OUTPUT);
  pinMode(enable2, OUTPUT);

  // Set enable pins to max speed (255).
  analogWrite(enable1, 255); // Fully Enable Motor 1
  analogWrite(enable2, 255); // Fully Enable Motor 2
}

void loop() {
  // === Movement Sequence ===
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

// -------------------- Motor Functions --------------------

// === Individual Motor Controls ===
void motorLeftMoveForward() {
  digitalWrite(motorLeftPinForward, HIGH);
  digitalWrite(motorLeftPinBackward, LOW);
}
void motorRightMoveForward() {
  digitalWrite(motorRightPinForward, HIGH);
  digitalWrite(motorRightPinBackward, LOW);
}
void motorLeftMoveBackward() {
  digitalWrite(motorLeftPinForward, LOW);
  digitalWrite(motorLeftPinBackward, HIGH);
}
void motorRightMoveBackward() {
  digitalWrite(motorRightPinForward, LOW);
  digitalWrite(motorRightPinBackward, HIGH);
}

// === Robot Movements ===
void moveForward() {
  motorLeftMoveForward();
  motorRightMoveForward();
}
void moveBackward() {
  motorLeftMoveBackward();
  motorRightMoveBackward();
}
void turnLeft() {
  // Right motor forward, left motor stopped.
  digitalWrite(motorLeftPinForward, LOW);
  digitalWrite(motorLeftPinBackward, LOW);
  motorRightMoveForward();
}
void turnRight() {
  // Left motor forward, right motor stopped.
  digitalWrite(motorRightPinForward, LOW);
  digitalWrite(motorRightPinBackward, LOW);
  motorLeftMoveForward();
}
void pivotTurn() {
  // Spin in place: left forward, right backward.
  motorLeftMoveForward();
  motorRightMoveBackward();
}
void stopMotors() {
  digitalWrite(motorLeftPinForward, LOW);
  digitalWrite(motorLeftPinBackward, LOW);
  digitalWrite(motorRightPinForward, LOW);
  digitalWrite(motorRightPinBackward, LOW);
}