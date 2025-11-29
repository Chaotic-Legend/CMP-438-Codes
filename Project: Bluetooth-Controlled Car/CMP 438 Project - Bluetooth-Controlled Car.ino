// CMP 438: Communicating Robots - Bluetooth-Controlled Car - Isaac D. Hoyos & Roberto Morales

// Motor Driver Pins:
int IN1 = 8;   // This pin controls the forward direction of the right motor.
int IN2 = 9;   // This pin controls the backward direction of the right motor.
int IN3 = 10;  // This pin controls the forward direction of the left motor.
int IN4 = 11;  // This pin controls the backward direction of the left motor.
int ENA = 5;   // This pin provides PWM speed control for the right motor.
int ENB = 6;   // This pin provides PWM speed control for the left motor.
char command;  // This variable holds the incoming Bluetooth command character.

void setup() {
  Serial.begin(9600); // This initializes Bluetooth serial communication at 9600 baud.

  pinMode(IN1, OUTPUT); // This sets the right motor forward pin as an output.
  pinMode(IN2, OUTPUT); // This sets the right motor backward pin as an output.
  pinMode(IN3, OUTPUT); // This sets the left motor forward pin as an output.
  pinMode(IN4, OUTPUT); // This sets the left motor backward pin as an output.
  pinMode(ENA, OUTPUT); // This configures the right motor speed pin as an output.
  pinMode(ENB, OUTPUT); // This configures the left motor speed pin as an output.

  analogWrite(ENA, 255); // This sets the right motor to full speed.
  analogWrite(ENB, 255); // This sets the left motor to full speed.

  Serial.println("Bluetooth Car Ready!"); // This prints a startup confirmation message to the Serial Monitor.
}

void loop() {
  if (Serial.available()) {            // This checks if a Bluetooth command is available to read.
    command = Serial.read();           // This reads the incoming Bluetooth command from the Serial Monitor.
    command = toupper(command);        // This converts the command to uppercase for consistency.
    if (command == 'F') forward();     // This executes the forward movement function if the command is 'F'.
    if (command == 'B') backward();    // This executes the backward movement function if the command is 'B'.
    if (command == 'L') left();        // This executes the left turn function if the command is 'L'.
    if (command == 'R') right();       // This executes the right turn function if the command is 'R'.
    if (command == 'S') stopCar();     // This executes the stop function if the command is 'S'.
  }
}

// Movement Functions:

void forward() {
  digitalWrite(IN1, HIGH); // This activates the right motor in the forward direction.
  digitalWrite(IN2, LOW);  // This deactivates the right motor in the backward direction.
  digitalWrite(IN3, HIGH); // This activates the left motor in the forward direction.
  digitalWrite(IN4, LOW);  // This deactivates the left motor in the backward direction.

  Serial.println("\nMoving Forward..."); // This prints the forward movement status to the Serial Monitor.
}

void backward() {
  digitalWrite(IN1, LOW);  // This deactivates the right motor in the forward direction.
  digitalWrite(IN2, HIGH); // This activates the right motor in the backward direction.
  digitalWrite(IN3, LOW);  // This deactivates the left motor in the forward direction.
  digitalWrite(IN4, HIGH); // This activates the left motor in the backward direction.

  Serial.println("\nMoving Backward..."); // This prints the backward movement status to the Serial Monitor.
}

void left() {
  digitalWrite(IN1, LOW);  // This stops the right motor from moving forward.
  digitalWrite(IN2, LOW);  // This stops the right motor from moving backward.
  digitalWrite(IN3, HIGH); // This activates the left motor to turn the car left.
  digitalWrite(IN4, LOW);  // This deactivates the left motor in the backward direction.

  Serial.println("\nTurning Left..."); // This prints the left turn status to the Serial Monitor.
}

void right() {
  digitalWrite(IN1, HIGH); // This activates the right motor to turn the car right.
  digitalWrite(IN2, LOW);  // This deactivates the right motor in the backward direction.
  digitalWrite(IN3, LOW);  // This stops the left motor from moving forward.
  digitalWrite(IN4, LOW);  // This stops the left motor from moving backward.

  Serial.println("\nTurning Right..."); // This prints the right turn status to the Serial Monitor.
}

void stopCar() {
  digitalWrite(IN1, LOW); // This stops the right motor from moving forward.
  digitalWrite(IN2, LOW); // This stops the right motor from moving backward.
  digitalWrite(IN3, LOW); // This stops the left motor from moving forward.
  digitalWrite(IN4, LOW); // This stops the left motor from moving backward.
  
  Serial.println("\nCar Stopped."); // This prints the stop status to the Serial Monitor.
}
