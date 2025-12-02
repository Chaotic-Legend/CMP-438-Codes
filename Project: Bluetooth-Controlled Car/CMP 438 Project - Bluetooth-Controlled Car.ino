// CMP 438: Communicating Robots - Bluetooth-Controlled Car - Isaac D. Hoyos & Roberto Morales

// Motor Driver Pins:
int IN1 = 8;  // This pin sends a signal that activates the right motor in the forward direction.
int IN2 = 9;  // This pin sends a signal that activates the right motor in the backward direction.
int IN3 = 10; // This pin sends a signal that activates the left motor in the forward direction.
int IN4 = 11; // This pin sends a signal that activates the left motor in the backward direction.
int IN5 = 13; // This pin provides control for an LED or auxiliary output used for visual feedback.
char command; // This variable stores the Bluetooth command character received from the smartphone.

void setup() { 
 // These commands configure all motor control pins and the LED pin as output pins.
 Serial.begin(9600); // This starts the Bluetooth serial communication at a baud rate of 9600.
 pinMode(IN1, OUTPUT); // This sets the right motor forward-control pin as an output.
 pinMode(IN2, OUTPUT); // This sets the right motor backward-control pin as an output.
 pinMode(IN3, OUTPUT); // This sets the left motor forward-control pin as an output.
 pinMode(IN4, OUTPUT); // This sets the left motor backward-control pin as an output.
 pinMode(IN5, OUTPUT); // This sets the auxiliary LED or indicator pin as an output.
 
 // This block prints a startup message to confirm that the system is powered and ready.
 Serial.println("==============================");
 Serial.println("Bluetooth-Controlled Car Ready!");
 Serial.println("By Isaac Hoyos & Roberto Morales.");
 Serial.println("==============================");
}

void loop() {
 if (Serial.available()) {  // This checks whether a Bluetooth command has been received and is ready to be read.
  command = Serial.read(); // This reads the incoming Bluetooth command character from the serial input buffer.
  
  // These conditional statements match the received command to a specific action and print a detailed status message.
  if (command == 'F') {
   forward(); // This calls the function that moves the robot forward.
   Serial.print("\nCommand \"");
   Serial.print(command);
   Serial.println("\" Received: Moving Forward..."); // This prints feedback confirming forward movement.
  }
  
  if (command == 'B') {
   backward(); // This calls the function that moves the robot backward.
   Serial.print("\nCommand \"");
   Serial.print(command);
   Serial.println("\" Received: Moving Backward..."); // This prints feedback confirming backward movement.
  }
  
  if (command == 'L') {
   left(); // This calls the function that turns the robot to the left.
   Serial.print("\nCommand \"");
   Serial.print(command);
   Serial.println("\" Received: Turning Left..."); // This prints feedback confirming a left turn.
  }
  
  if (command == 'R') {
   right(); // This calls the function that turns the robot to the right.
   Serial.print("\nCommand \"");
   Serial.print(command);
   Serial.println("\" Received: Turning Right..."); // This prints feedback confirming a right turn.
  }
  
  if (command == 'S') {
   stopCar(); // This calls the function that stops all motor movement
   Serial.print("\nCommand \"");
   Serial.print(command);
   Serial.println("\" Received: Car Stopped."); // This prints feedback confirming the stop command.
  }
  
  if (command == 'A') {
   pivotL(); // This calls the function that makes the robot pivot left in place.
   Serial.print("\nCommand \"");
   Serial.print(command);
   Serial.println("\" Received: Pivoting Left..."); // This prints feedback confirming the pivot-left command.
  }
  
  if (command == 'C') {
   pivotR(); // This calls the function that makes the robot pivot right in place.
   Serial.print("\nCommand \"");
   Serial.print(command);
   Serial.println("\" Received: Pivoting Right..."); // This prints feedback confirming the pivot-right command.
  }
  
  if (command == 'O') {
   lightOn(); // This calls the function that turns on the LED.
   Serial.print("\nCommand \"");
   Serial.print(command);
   Serial.println("\" Received: Lights On..."); // This prints feedback confirming the LED was turned on.
  }
  
  if (command == 's') {
   lightOff(); // This calls the function that turns off the LED.
   Serial.print("\nCommand \"");
   Serial.print(command);
   Serial.println("\" Received: Lights Off..."); // This prints feedback confirming the LED was turned off.
  }
 }
}

// Movement Functions:
void forward() {
 digitalWrite(IN1, HIGH); // This sends power to the right motor so it moves forward.
 digitalWrite(IN2, LOW);  // This ensures the right motor does not move backward during forward motion.
 digitalWrite(IN3, HIGH); // This sends power to the left motor so it moves forward.
 digitalWrite(IN4, LOW);  // This ensures the left motor does not move backward during forward motion.
 digitalWrite(IN5, HIGH); // This turns on the LED to indicate that the car is moving forward.
}

void backward() {
 digitalWrite(IN1, LOW);  // This prevents the right motor from moving forward while reversing.
 digitalWrite(IN2, HIGH); // This drives the right motor backward to initiate reverse movement.
 digitalWrite(IN3, LOW);  // This prevents the left motor from moving forward while reversing.
 digitalWrite(IN4, HIGH); // This drives the left motor backward to complete the reverse movement.
 digitalWrite(IN5, HIGH); // This turns on the LED to indicate that the car is moving backward.
}

void left() {
 digitalWrite(IN1, LOW);  // This stops the right motor from moving forward during a left turn.
 digitalWrite(IN2, LOW);  // This stops the right motor from moving backward during a left turn.
 digitalWrite(IN3, HIGH); // This powers the left motor forward to make the robot rotate left.
 digitalWrite(IN4, LOW);  // This ensures the left motor does not move backward while turning left.
 digitalWrite(IN5, HIGH); // This turns on the LED to provide visual feedback while turning left.
}

void right() {
 digitalWrite(IN1, HIGH); // This activates the right motor in the forward direction to initiate a right turn.
 digitalWrite(IN2, LOW);  // This ensures the right motor does not move backward during the turn.
 digitalWrite(IN3, LOW);  // This prevents the left motor from moving forward so the car can pivot right.
 digitalWrite(IN4, LOW);  // This prevents the left motor from moving backward during the turn.
 digitalWrite(IN5, HIGH); // This turns on the LED to provide visual feedback while turning right.
}

void pivotL() {
 digitalWrite(IN1, LOW);  // This ensures the right motor does not move forward while pivoting left.
 digitalWrite(IN2, HIGH); // This drives the right motor backward to help rotate the car left in place.
 digitalWrite(IN3, HIGH); // This drives the left motor forward to complete the pivoting motion to the left.
 digitalWrite(IN4, LOW);  // This ensures the left motor does not move backward during the pivot.
 digitalWrite(IN5, HIGH); // This turns on the LED to indicate that the car is pivoting left.
}

void pivotR() {
 digitalWrite(IN1, HIGH); // This drives the right motor forward to rotate the car right in place.
 digitalWrite(IN2, LOW);  // This ensures the right motor does not move backward during the pivot.
 digitalWrite(IN3, LOW);  // This prevents the left motor from moving forward while pivoting right.
 digitalWrite(IN4, HIGH); // This drives the left motor backward to complete the pivoting motion to the right.
 digitalWrite(IN5, HIGH); // This turns on the LED to indicate that the car is pivoting right.
}

void lightOn() {
 digitalWrite(IN5, HIGH); // This sends a high signal to pin IN5, turning on the LED for visual feedback.
}

void lightOff() {
 digitalWrite(IN5, LOW); // This sends a low signal to pin IN5, turning off the LED when it is not needed.
}

void stopCar() {
 digitalWrite(IN1, LOW); // This removes power from the right motor's forward direction to stop movement.
 digitalWrite(IN2, LOW); // This removes power from the right motor's backward direction to prevent reverse motion.
 digitalWrite(IN3, LOW); // This removes power from the left motor's forward direction to stop movement.
 digitalWrite(IN4, LOW); // This removes power from the left motor's backward direction to prevent reverse motion.
 digitalWrite(IN5, LOW); // This turns off the LED to indicate that the robot has fully stopped.
}
