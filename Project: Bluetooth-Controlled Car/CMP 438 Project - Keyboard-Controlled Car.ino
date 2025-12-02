// CMP 438: Communicating Robots - Keyboard-Controlled Car - Isaac D. Hoyos & Roberto Morales

// Motor Driver Pins:
int IN1 = 8;  // This pin controls the forward movement of the right motor by sending a HIGH signal.
int IN2 = 9;  // This pin controls the backward movement of the right motor by sending a HIGH signal.
int IN3 = 10; // This pin controls the forward movement of the left motor by sending a HIGH signal.
int IN4 = 11; // This pin controls the backward movement of the left motor by sending a HIGH signal.
int ENA = 5;  // This pin adjusts the speed of the right motor through PWM output.
int ENB = 6;  // This pin adjusts the speed of the left motor through PWM output.
int LED = 13; // This pin controls the LED that provides visual feedback during motion.
char command; // This variable stores the keyboard command entered into the Serial Monitor.

void setup() {
  // These commands configure all motor and LED pins as outputs so they can send control signals.
  Serial.begin(9600);   // This initializes serial communication at a baud rate of 9600.
  pinMode(IN1, OUTPUT); // This sets the right motor forward-control pin as an output.
  pinMode(IN2, OUTPUT); // This sets the right motor backward-control pin as an output.
  pinMode(IN3, OUTPUT); // This sets the left motor forward-control pin as an output.
  pinMode(IN4, OUTPUT); // This sets the left motor backward-control pin as an output.
  pinMode(ENA, OUTPUT); // This sets the right motor speed-control pin as an output.
  pinMode(ENB, OUTPUT); // This sets the left motor speed-control pin as an output.
  pinMode(LED, OUTPUT); // This sets the LED indicator pin as an output.

  // These commands set both motors to full speed by writing maximum PWM values.
  analogWrite(ENA, 255); // This applies full-speed PWM to the right motor.
  analogWrite(ENB, 255); // This applies full-speed PWM to the left motor.

  // These commands display startup information and control instructions in the Serial Monitor.
  Serial.println("==============================");
  Serial.println("Keyboard-Controlled Car Ready!");
  Serial.println("By Isaac Hoyos & Roberto Morales.");
  Serial.println("==============================");
  Serial.println("Control Instructions:");
  Serial.println("  Enter F or f to Move Forward.");
  Serial.println("  Enter B or b to Move Backward.");
  Serial.println("  Enter L or l to Turn Left.");
  Serial.println("  Enter R or r to Turn Right.");
  Serial.println("  Enter S or s to Stop.");
  Serial.println("==============================");
}

void loop() {
  if (Serial.available()) {         // This checks whether a keyboard command is available to be read from the serial buffer.
    command = Serial.read();        // This reads the incoming character entered by the user.
    char originalCommand = command; // This stores the original character so it can be echoed exactly as typed.
    command = toupper(command);     // This converts the command to uppercase.

    // These conditions control the LED behavior based on movement or stopping.
    if (command == 'F' || command == 'B' || command == 'L' || command == 'R') {
      digitalWrite(LED, HIGH); // This turns the LED on whenever the robot begins to move.
    }
    
    if (command == 'S') {
      digitalWrite(LED, LOW);  // This turns the LED off when the robot receives a stop command.
    }

    // This switch statement selects the appropriate movement function based on the user's command.
    switch (command) {
      case 'F':    // This case activates forward motion.
        forward(); // This calls the function that drives both motors forward.
        Serial.print("\nCommand \""); Serial.print(originalCommand); Serial.println("\" Received: Moving Forward...");
        break;

      case 'B':     // This case activates backward motion.
        backward(); // This calls the function that drives both motors backward.
        Serial.print("\nCommand \""); Serial.print(originalCommand); Serial.println("\" Received: Moving Backward...");
        break;

      case 'L': // This case activates a left turn.
        left(); // This calls the function that turns the robot left.
        Serial.print("\nCommand \""); Serial.print(originalCommand); Serial.println("\" Received: Turning Left...");
        break;

      case 'R':  // This case activates a right turn.
        right(); // This calls the function that turns the robot right.
        Serial.print("\nCommand \""); Serial.print(originalCommand); Serial.println("\" Received: Turning Right...");
        break;

      case 'S':    // This case stops all motor movement.
        stopCar(); // This calls the function that shuts off all motor outputs.
        Serial.print("\nCommand \""); Serial.print(originalCommand); Serial.println("\" Received: Car Stopped.");
        break;

      default: // This case handles any invalid or unknown command.
        Serial.print("\nUnknown Command \""); Serial.print(originalCommand); Serial.println("\". Please use F, B, L, R, or S.");
    }
  }
}

// Movement Functions:
void forward() {
  digitalWrite(IN1, HIGH); // This activates the right motor in the forward direction.
  digitalWrite(IN2, LOW);  // This ensures the right motor does not run backward during forward motion.
  digitalWrite(IN3, HIGH); // This activates the left motor in the forward direction.
  digitalWrite(IN4, LOW);  // This ensures the left motor does not run backward during forward motion.
}

void backward() {
  digitalWrite(IN1, LOW);  // This ensures the right motor does not run forward while reversing.
  digitalWrite(IN2, HIGH); // This activates the right motor in the backward direction.
  digitalWrite(IN3, LOW);  // This ensures the left motor does not run forward while reversing.
  digitalWrite(IN4, HIGH); // This activates the left motor in the backward direction.
}

void left() {
  digitalWrite(IN1, LOW);  // This stops the right motor from moving forward during a left turn.
  digitalWrite(IN2, LOW);  // This stops the right motor from moving backward during a left turn.
  digitalWrite(IN3, HIGH); // This activates the left motor in the forward direction to pivot left.
  digitalWrite(IN4, LOW);  // This ensures the left motor does not run backward during the turn.
}

void right() {
  digitalWrite(IN1, HIGH); // This activates the right motor in the forward direction to pivot right.
  digitalWrite(IN2, LOW);  // This ensures the right motor does not run backward during the turn.
  digitalWrite(IN3, LOW);  // This prevents the left motor from moving forward during the right turn.
  digitalWrite(IN4, LOW);  // This prevents the left motor from moving backward during the right turn.
}

void stopCar() {
  digitalWrite(IN1, LOW); // This turns off the right motor's forward motion.
  digitalWrite(IN2, LOW); // This turns off the right motor's backward motion.
  digitalWrite(IN3, LOW); // This turns off the left motor's forward motion.
  digitalWrite(IN4, LOW); // This turns off the left motor's backward motion.
}
