// CMP 438: Communicating Robots - Bluetooth-Controlled Car - Isaac D. Hoyos & Roberto Morales

// Motor Driver Pins:
#define int IN1 = 8;   // This pin controls the forward direction of the right motor.
#define int IN2 = 9;   // This pin controls the backward direction of the right motor.
#define int IN3 = 10;  // This pin controls the forward direction of the left motor.
#define int IN4 = 11;  // This pin controls the backward direction of the left motor.
#define int IN5 = 13;
#define int IN6 = 7;
#define int ENA = 5;   // This pin provides PWM speed control for the right motor.
#define int ENB = 6;   // This pin provides PWM speed control for the left motor.
char command;  // This variable holds the incoming Bluetooth command character.

void setup() {
  Serial.begin(9600); // This initializes Bluetooth serial communication at 9600 baud.

  pinMode(8, OUTPUT); // This sets the right motor forward pin as an output.
  pinMode(9, OUTPUT); // This sets the right motor backward pin as an output.
  pinMode(10, OUTPUT); // This sets the left motor forward pin as an output.
  pinMode(11, OUTPUT); // This sets the left motor backward pin as an output.
  pinMode(13, OUTPUT);
  // pinMode(ENA, OUTPUT); // This configures the right motor speed pin as an output.
  // pinMode(ENB, OUTPUT); // This configures the left motor speed pin as an output.

  // analogWrite(ENA, 255); // This sets the right motor to full speed.
  // analogWrite(ENB, 255); // This sets the left motor to full speed.

  Serial.println("Bluetooth Car Ready!"); // This prints a startup confirmation message to the Serial Monitor.
}

void loop() {
  if (Serial.available()) {            // This checks if a Bluetooth command is available to read.
    command = Serial.read();    
    
    Serial.print("Received: ");
    Serial.println(command);        // This reads the incoming Bluetooth command from the Serial Monitor.
        // This converts the command to uppercase for consistency.
    if (command == 'F') forward();     // This executes the forward movement function if the command is 'F'.
    if (command == 'B') backward();    // This executes the backward movement function if the command is 'B'.
    if (command == 'L') left();        // This executes the left turn function if the command is 'L'.
    if (command == 'R') right();       // This executes the right turn function if the command is 'R'.
    if (command == 'S') stopCar();     // This executes the stop function if the command is 'S'.
    if(command == 'A') pivotL();
    if(command == 'C') pivotR();
    if(command == 'O') lightOn();
    if(command == 's') lightOff();
  }


}

// Movement Functions:

void forward() {
  digitalWrite(8, HIGH); // This activates the right motor in the forward direction.
  digitalWrite(9, LOW);  // This deactivates the right motor in the backward direction.
  digitalWrite(10, HIGH); // This activates the left motor in the forward direction.
  digitalWrite(11, LOW);  // This deactivates the left motor in the backward direction.

  Serial.println("\nMoving Forward..."); // This prints the forward movement status to the Serial Monitor.
}

void backward() {
  digitalWrite(8, LOW);  // This deactivates the right motor in the forward direction.
  digitalWrite(9, HIGH); // This activates the right motor in the backward direction.
  digitalWrite(10, LOW);  // This deactivates the left motor in the forward direction.
  digitalWrite(11, HIGH); // This activates the left motor in the backward direction.

  Serial.println("\nMoving Backward..."); // This prints the backward movement status to the Serial Monitor.
}

void left() {
  digitalWrite(8, LOW);  // This stops the right motor from moving forward.
  digitalWrite(9, LOW);  // This stops the right motor from moving backward.
  digitalWrite(10, HIGH); // This activates the left motor to turn the car left.
  digitalWrite(11, LOW);  // This deactivates the left motor in the backward direction.

  Serial.println("\nTurning Left..."); // This prints the left turn status to the Serial Monitor.
}

void right() {
  digitalWrite(8, HIGH); // This activates the right motor to turn the car right.
  digitalWrite(9, LOW);  // This deactivates the right motor in the backward direction.
  digitalWrite(10, LOW);  // This stops the left motor from moving forward.
  digitalWrite(11, LOW);  // This stops the left motor from moving backward.
digitalWrite(7, HIGH);
  Serial.println("\nTurning Right..."); // This prints the right turn status to the Serial Monitor.
}
void pivotL(){

    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(13, HIGH);
}

void pivotR(){
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
    digitalWrite(7, HIGH);



}

void lightOn(){
digitalWrite(13, HIGH);
digitalWrite(7, HIGH);
}

void lightOff(){
  digitalWrite(13, LOW);
  digitalWrite(7, LOW);



}

void stopCar() {
  digitalWrite(8, LOW); // This stops the right motor from moving forward.
  digitalWrite(9, LOW); // This stops the right motor from moving backward.
  digitalWrite(10, LOW); // This stops the left motor from moving forward.
  digitalWrite(11, LOW); // This stops the left motor from moving backward.
  
  Serial.println("\nCar Stopped."); // This prints the stop status to the Serial Monitor.
}
