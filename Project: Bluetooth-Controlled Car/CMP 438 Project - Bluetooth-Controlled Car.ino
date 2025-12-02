// CMP 438: Communicating Robots - Bluetooth-Controlled Car - Isaac D. Hoyos & Roberto Morales

// Motor Driver Pins:
 int IN1 = 8;   // This pin controls the forward direction of the right motor.
 int IN2 = 9;   // This pin controls the backward direction of the right motor.
 int IN3 = 10;  // This pin controls the forward direction of the left motor.
 int IN4 =11;  // This pin controls the backward direction of the left motor.
 int IN5 =13;  // This pin controls one of the LEDs or auxiliary outputs.
 
char command;  // This variable holds the incoming Bluetooth command character.

void setup() {
  Serial.begin(9600); // This initializes Bluetooth serial communication at 9600 baud.

  // These commands set all motor and LED pins as outputs.
  pinMode(IN1, OUTPUT);  // This sets the right motor forward pin as an output.
  pinMode(IN2, OUTPUT);  // This sets the right motor backward pin as an output.
  pinMode(IN3, OUTPUT); // This sets the left motor forward pin as an output.
  pinMode(IN4, OUTPUT); // This sets the left motor backward pin as an output.
  pinMode(IN5, OUTPUT); // This sets the first auxiliary pin or LED as an output.
 
  // This prints a startup confirmation message to the Serial Monitor.
  Serial.println("==============================");
  Serial.println("Bluetooth-Controlled Car Ready!");
  Serial.println("By Isaac Hoyos & Roberto Morales.");
  Serial.println("==============================");
}

void loop() {
  if (Serial.available()) {           // This checks if a Bluetooth command is available to read.
    command = Serial.read();          // This reads the incoming command from the Serial Monitor.

    // These conditions execute the appropriate movement or action based on the command, and print detailed feedback messages.
    if (command == 'F') {
      forward();
      Serial.print("\nCommand \""); 
      Serial.print(command); 
      Serial.println("\" Received: Moving Forward...");
    }

    if (command == 'B') {
      backward();
      Serial.print("\nCommand \""); 
      Serial.print(command); 
      Serial.println("\" Received: Moving Backward...");
    }

    if (command == 'L') {
      left();
      Serial.print("\nCommand \""); 
      Serial.print(command); 
      Serial.println("\" Received: Turning Left...");
    }

    if (command == 'R') {
      right();
      Serial.print("\nCommand \""); 
      Serial.print(command); 
      Serial.println("\" Received: Turning Right...");
    }

    if (command == 'S') {
      stopCar();
      Serial.print("\nCommand \""); 
      Serial.print(command); 
      Serial.println("\" Received: Car Stopped.");
    }

    if (command == 'A') {
      pivotL();
      Serial.print("\nCommand \""); 
      Serial.print(command); 
      Serial.println("\" Received: Pivoting Left...");
    }

    if (command == 'C') {
      pivotR();
      Serial.print("\nCommand \""); 
      Serial.print(command); 
      Serial.println("\" Received: Pivoting Right...");
    }

    if (command == 'O') {
      lightOn();
      Serial.print("\nCommand \""); 
      Serial.print(command); 
      Serial.println("\" Received: Lights On...");
    }

    if (command == 's') {
      lightOff();
      Serial.print("\nCommand \""); 
      Serial.print(command); 
      Serial.println("\" Received: Lights Off...");
    }
  }
}

// Movement Functions:
void forward() {
  digitalWrite(IN1, HIGH);  // This activates the right motor in the forward direction.
  digitalWrite(IN2, LOW);   // This deactivates the right motor in the backward direction.
  digitalWrite(IN3, HIGH); // This activates the left motor in the forward direction.
  digitalWrite(IN4, LOW);  // This deactivates the left motor in the backward direction.
}

void backward() {
  digitalWrite(IN1, LOW);   // This deactivates the right motor in the forward direction.
  digitalWrite(IN2, HIGH);  // This activates the right motor in the backward direction.
  digitalWrite(IN3, LOW);  // This deactivates the left motor in the forward direction.
  digitalWrite(IN4, HIGH); // This activates the left motor in the backward direction.
}

void left() {
  digitalWrite(IN1, LOW);   // This stops the right motor from moving forward.
  digitalWrite(IN2, LOW);   // This stops the right motor from moving backward.
  digitalWrite(IN3, HIGH); // This activates the left motor to turn the car left.
  digitalWrite(IN4, LOW);  // This deactivates the left motor in the backward direction.
}

void right() {
  digitalWrite(IN1, HIGH);  // This activates the right motor to turn the car right.
  digitalWrite(IN2, LOW);   // This deactivates the right motor in the backward direction.
  digitalWrite(IN3, LOW);  // This stops the left motor from moving forward.
  digitalWrite(IN4, LOW);  // This stops the left motor from moving backward.
  digitalWrite(IN5, HIGH);  // This activates auxiliary pin 7 for visual feedback while turning right.
}

void pivotL() {
  digitalWrite(IN1, LOW);   // This stops the right motor from moving forward.
  digitalWrite(IN2, HIGH);  // This activates the right motor backward for pivoting left.
  digitalWrite(IN3, HIGH); // This activates the left motor forward for pivoting left.
  digitalWrite(IN4, LOW);  // This deactivates the left motor in the backward direction.
  digitalWrite(IN5, HIGH); // This activates auxiliary pin 13 while pivoting left.
}

void pivotR() {
  digitalWrite(IN1, HIGH);  // This activates the right motor forward for pivoting right.
  digitalWrite(IN2, LOW);   // This deactivates the right motor in the backward direction.
  digitalWrite(IN3, LOW);  // This stops the left motor from moving forward.
  digitalWrite(IN4, HIGH); // This activates the left motor backward for pivoting right.
  digitalWrite(IN5, HIGH);  // This activates auxiliary pin 7 while pivoting right.
}

void lightOn() {
  
  digitalWrite(IN5, HIGH);
}

void lightOff() {
  
  digitalWrite(IN5, LOW);   // This turns off the second LED or auxiliary light.
}

void stopCar() {
  digitalWrite(IN1, LOW);   // This stops the right motor from moving forward.
  digitalWrite(IN2, LOW);   // This stops the right motor from moving backward.
  digitalWrite(IN3, LOW);  // This stops the left motor from moving forward.
  digitalWrite(IN4, LOW);  // This stops the left motor from moving backward.
  digitalWrite(IN5, LOW); // This turns led off
}
