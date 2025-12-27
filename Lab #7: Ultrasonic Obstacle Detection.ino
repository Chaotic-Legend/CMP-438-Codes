// CMP 438: Communicating Robots - Isaac D. Hoyos
// Tinkercad Link: https://tinyurl.com/3h2w897m

// These pins control the L293D motor driver for the right and left motors.
int IN1 = 8;  // This pin controls the right motor moving forward.
int IN2 = 9;  // This pin controls the right motor moving backward.
int IN3 = 10; // This pin controls the left motor moving forward.
int IN4 = 11; // This pin controls the left motor moving backward.

// These pins are used to connect the ultrasonic distance sensor.
int trigPin = 6; // This pin sends the ultrasonic trigger pulse.
int echoPin = 7; // This pin receives the ultrasonic echo pulse.

// These variables store distance calculation values.
long duration;          // This variable stores the echo pulse duration.
float distanceInches;   // This variable stores the calculated distance in inches.
float threshold = 15.0; // This is the distance threshold for obstacle avoidance.
float closeThreshold = 8.0; // This is a closer threshold for sharper avoidance.

// These variables control how often distance information is printed.
unsigned long lastPrintTime = 0;   // This stores the last time data was printed.
unsigned long printInterval = 500; // This sets the delay between serial prints.

void setup() {
  // This initializes serial communication for debugging output.
  Serial.begin(9600);

  // These pins are configured as outputs for motor control.
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // These pins are configured for the ultrasonic sensor.
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // This reads the current distance from the ultrasonic sensor.
  distanceInches = getDistanceInches();

  // This logic determines the robot's movement based on distance.
  if (distanceInches <= closeThreshold) {
    turnRight();
  } else if (distanceInches <= threshold) {
    turnLeft();
  } else {
    moveForward();
  }

  // This section limits how often distance data is printed to the Serial Monitor.
  if (millis() - lastPrintTime >= printInterval) {
    Serial.print("Distance: ");
    Serial.print(distanceInches);
    Serial.println(" in");

    if (distanceInches <= closeThreshold) {
      Serial.println("\nTurning Right...\n");
    } else if (distanceInches <= threshold) {
      Serial.println("\nTurning Left...\n");
    } else {
      Serial.println("\nMoving Forward...\n");
    }
    lastPrintTime = millis();
  }
}

// This function moves both motors forward so the robot drives straight.
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// This function turns the robot left by stopping the left motor.
void turnLeft() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// This function turns the robot right by stopping the right motor.
void turnRight() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// This function measures the distance to the nearest object in inches.
float getDistanceInches() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  return duration * 0.0135 / 2;
}
