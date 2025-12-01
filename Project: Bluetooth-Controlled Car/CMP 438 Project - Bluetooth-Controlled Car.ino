// CMP 438: Communicating Robots - Bluetooth-Controlled Car - Isaac D. Hoyos & Roberto Morales

// Motor Driver Pins:
#define int IN1 = 8;   // This pin controls the forward direction of the right motor.
#define int IN2 = 9;   // This pin controls the backward direction of the right motor.
#define int IN3 = 10;  // This pin controls the forward direction of the left motor.
#define int IN4 = 11;  // This pin controls the backward direction of the left motor.
#define int IN5 = 13;  // This pin controls one of the LEDs or auxiliary outputs.
#define int IN6 = 7;   // This pin controls another LED or auxiliary output.
#define int ENA = 5;   // This pin provides PWM speed control for the right motor.
#define int ENB = 6;   // This pin provides PWM speed control for the left motor.
char command;  // This variable holds the incoming Bluetooth command character.

void setup() {
  Serial.begin(9600); // This initializes Bluetooth serial communication at 9600 baud.

  // These commands set all motor and LED pins as outputs.
  pinMode(8, OUTPUT);  // This sets the right motor forward pin as an output.
  pinMode(9, OUTPUT);  // This sets the right motor backward pin as an output.
  pinMode(10, OUTPUT); // This sets the left motor forward pin as an output.
  pinMode(11, OUTPUT); // This sets the left motor backward pin as an output.
  pinMode(13, OUTPUT); // This sets the first auxiliary pin or LED as an output.
  pinMode(7, OUTPUT);  // This sets the second auxiliary pin or LED as an output.
  Serial.println("Bluetooth-Controlled Car Ready!"); // This prints a startup confirmation message to the Serial Monitor.
}

void loop() {
  if (Serial.available()) {  // This checks if a Bluetooth command is available to read.
    command = Serial.read(); // This reads the incoming Bluetooth command from the Serial Monitor.
    Serial.print("Received: "); 
    Serial.println(command); // This prints the received command for feedback.

    // These conditions execute the appropriate movement or action based on the command.
    if (command == 'F') forward();     
    if (command == 'B') backward();    
    if (command == 'L') left();        
    if (command == 'R') right();       
    if (command == 'S') stopCar();     
    if (command == 'A') pivotL();      
    if (command == 'C') pivotR();      
    if (command == 'O') lightOn();     
    if (command == 's') lightOff();    
  }
}

// Movement Functions:
void forward() {
  digitalWrite(8, HIGH);  // This activates the right motor in the forward direction.
  digitalWrite(9, LOW);   // This deactivates the right motor in the backward direction.
  digitalWrite(10, HIGH); // This activates the left motor in the forward direction.
  digitalWrite(11, LOW);  // This deactivates the left motor in the backward direction.
  Serial.println("\nMoving Forward..."); // This prints the forward movement status.
}

void backward() {
  digitalWrite(8, LOW);   // This deactivates the right motor in the forward direction.
  digitalWrite(9, HIGH);  // This activates the right motor in the backward direction.
  digitalWrite(10, LOW);  // This deactivates the left motor in the forward direction.
  digitalWrite(11, HIGH); // This activates the left motor in the backward direction.
  Serial.println("\nMoving Backward..."); // This prints the backward movement status.
}

void left() {
  digitalWrite(8, LOW);   // This stops the right motor from moving forward.
  digitalWrite(9, LOW);   // This stops the right motor from moving backward.
  digitalWrite(10, HIGH); // This activates the left motor to turn the car left.
  digitalWrite(11, LOW);  // This deactivates the left motor in the backward direction.
  Serial.println("\nTurning Left..."); // This prints the left turn status.
}

void right() {
  digitalWrite(8, HIGH);  // This activates the right motor to turn the car right.
  digitalWrite(9, LOW);   // This deactivates the right motor in the backward direction.
  digitalWrite(10, LOW);  // This stops the left motor from moving forward.
  digitalWrite(11, LOW);  // This stops the left motor from moving backward.
  digitalWrite(7, HIGH);  // This activates auxiliary pin 7 for visual feedback while turning right.
  Serial.println("\nTurning Right..."); // This prints the right turn status.
}

void pivotL() {
  digitalWrite(8, LOW);   // This stops the right motor from moving forward.
  digitalWrite(9, HIGH);  // This activates the right motor backward for pivoting left.
  digitalWrite(10, HIGH); // This activates the left motor forward for pivoting left.
  digitalWrite(11, LOW);  // This deactivates the left motor in the backward direction.
  digitalWrite(13, HIGH); // This activates auxiliary pin 13 while pivoting left.
}

void pivotR() {
  digitalWrite(8, HIGH);  // This activates the right motor forward for pivoting right.
  digitalWrite(9, LOW);   // This deactivates the right motor in the backward direction.
  digitalWrite(10, LOW);  // This stops the left motor from moving forward.
  digitalWrite(11, HIGH); // This activates the left motor backward for pivoting right.
  digitalWrite(7, HIGH);  // This activates auxiliary pin 7 while pivoting right.
}

void lightOn() {
  digitalWrite(13, HIGH);
  digitalWrite(7, HIGH);
}

void lightOff() {
  digitalWrite(13, LOW);  // This turns off the first LED or auxiliary light.
  digitalWrite(7, LOW);   // This turns off the second LED or auxiliary light.
}

void stopCar() {
  digitalWrite(8, LOW);   // This stops the right motor from moving forward.
  digitalWrite(9, LOW);   // This stops the right motor from moving backward.
  digitalWrite(10, LOW);  // This stops the left motor from moving forward.
  digitalWrite(11, LOW);  // This stops the left motor from moving backward.
  Serial.println("\nCar Stopped."); // This prints the stop status.
}
