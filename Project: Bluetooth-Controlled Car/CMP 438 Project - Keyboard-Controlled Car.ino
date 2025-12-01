// CMP 438: Communicating Robots - Keyboard-Controlled Car - Isaac D. Hoyos & Roberto Morales

// Motor Driver Pins:
int IN1 = 8;   // This pin controls the forward movement of the right motor.
int IN2 = 9;   // This pin controls the backward movement of the right motor.
int IN3 = 10;  // This pin controls the forward movement of the left motor.
int IN4 = 11;  // This pin controls the backward movement of the left motor.
int ENA = 5;   // This pin controls the speed of the right motor.
int ENB = 6;   // This pin controls the speed of the left motor.
int LED = 13;  // This pin controls the LED to turn on and off.

char command;  // This variable stores the keyboard command entered in the Serial Monitor.

void setup() {
  Serial.begin(9600); // This command opens the serial communication at 9600 baud.

  // These commands set all motor control pins and the LED pin as outputs.
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(LED, OUTPUT);

  // These commands set the motors to full speed.
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);

  // These commands display instructions in the Serial Monitor for clarity.
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
  if (Serial.available()) {
    command = Serial.read();        // This command reads the input from the Serial Monitor.
    
    char originalCommand = command; // This line stores the original command for feedback purposes.
    command = toupper(command);     // This command converts the input to uppercase for consistency.

    // Turn the LED on for any movement and off when stopping.
    if (command == 'F' || command == 'B' || command == 'L' || command == 'R') {
      digitalWrite(LED, HIGH);  // Turn the LED on for when moving.
    }
    if (command == 'S') {
      digitalWrite(LED, LOW);   // Turn the LED off when stopping.
    }

    switch (command) {
      case 'F':
        forward();
        Serial.print("\nCommand \""); Serial.print(originalCommand); Serial.println("\" Received: Moving Forward...");
        break;
      case 'B':
        backward();
        Serial.print("\nCommand \""); Serial.print(originalCommand); Serial.println("\" Received: Moving Backward...");
        break;
      case 'L':
        left();
        Serial.print("\nCommand \""); Serial.print(originalCommand); Serial.println("\" Received: Turning Left...");
        break;
      case 'R':
        right();
        Serial.print("\nCommand \""); Serial.print(originalCommand); Serial.println("\" Received: Turning Right...");
        break;
      case 'S':
        stopCar();
        Serial.print("\nCommand \""); Serial.print(originalCommand); Serial.println("\" Received: Car Stopped.");
        break;
      default:
        Serial.print("\nUnknown Command \""); Serial.print(originalCommand); Serial.println("\". Please use F, B, L, R, or S.");
    }
  }
}

// Movement Functions:
void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void stopCar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
