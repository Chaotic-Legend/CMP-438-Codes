// CMP 438: Communicating Robots - Bluetooth-Controlled Car - Isaac D. Hoyos

// Motor Driver Pins:
int IN1 = 8;   // Controls the right motor forward direction.
int IN2 = 9;   // Controls the right motor backward direction.
int IN3 = 10;  // Controls the left motor forward direction.
int IN4 = 11;  // Controls the left motor backward direction.
int ENA = 5;   // PWM speed control for the right motor.
int ENB = 6;   // PWM speed control for the left motor.
char command;  // Holds the incoming Bluetooth command character.

void setup() {
  Serial.begin(9600); // Initializes Bluetooth serial communication.

  pinMode(IN1, OUTPUT); // Sets right-motor forward pin as an output.
  pinMode(IN2, OUTPUT); // Sets right-motor backward pin as an output.
  pinMode(IN3, OUTPUT); // Sets left-motor forward pin as an output.
  pinMode(IN4, OUTPUT); // Sets left-motor backward pin as an output.

  pinMode(ENA, OUTPUT); // Configures the right-motor speed pin as output.
  pinMode(ENB, OUTPUT); // Configures the left-motor speed pin as output.

  analogWrite(ENA, 255); // Sets right motor to full speed.
  analogWrite(ENB, 255); // Sets left motor to full speed.

  Serial.println("Bluetooth Car Ready!"); // Prints startup confirmation.
}

void loop() {
  if (Serial.available()) {            // Checks if a Bluetooth command is available.
    command = Serial.read();           // Reads the incoming command.
    command = toupper(command);        // Converts the command to uppercase.
    if (command == 'F') forward();     // Executes forward movement.
    if (command == 'B') backward();    // Executes backward movement.
    if (command == 'L') left();        // Executes left turn.
    if (command == 'R') right();       // Executes right turn.
    if (command == 'S') stopCar();     // Stops all motor actions.
  }
}

// Movement Functions:
void forward() {
  digitalWrite(IN1, HIGH); // Activates right motor forward.
  digitalWrite(IN2, LOW);  // Deactivates right motor backward.
  digitalWrite(IN3, HIGH); // Activates left motor forward.
  digitalWrite(IN4, LOW);  // Deactivates left motor backward.

  Serial.println("\nMoving Forward..."); // Prints forward movement status.
}

void backward() {
  digitalWrite(IN1, LOW);  // Deactivates right motor forward.
  digitalWrite(IN2, HIGH); // Activates right motor backward.
  digitalWrite(IN3, LOW);  // Deactivates left motor forward.
  digitalWrite(IN4, HIGH); // Activates left motor backward.

  Serial.println("\nMoving Backward..."); // Prints backward movement status.
}

void left() {
  digitalWrite(IN1, LOW);  // Stops right motor forward direction.
  digitalWrite(IN2, LOW);  // Stops right motor backward direction.
  digitalWrite(IN3, HIGH); // Activates left motor forward.
  digitalWrite(IN4, LOW);  // Deactivates left motor backward.

  Serial.println("\nTurning Left..."); // Prints left turn status.
}

void right() {
  digitalWrite(IN1, HIGH); // Activates right motor forward.
  digitalWrite(IN2, LOW);  // Deactivates right motor backward.
  digitalWrite(IN3, LOW);  // Stops left motor forward direction.
  digitalWrite(IN4, LOW);  // Stops left motor backward direction.

  Serial.println("\nTurning Right..."); // Prints right turn status.
}

void stopCar() {
  digitalWrite(IN1, LOW); // Stops right motor.
  digitalWrite(IN2, LOW); // Stops right motor.
  digitalWrite(IN3, LOW); // Stops left motor.
  digitalWrite(IN4, LOW); // Stops left motor.
  
  Serial.println("\nCar Stopped."); // Prints stop status.
}
