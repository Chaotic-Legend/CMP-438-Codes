// CMP 438: Communicating Robots - Isaac D. Hoyos

// Motor Pins (L293D)
int IN1 = 8;   // Right Motor Forward
int IN2 = 9;   // Right Motor Backward
int IN3 = 10;  // Left Motor Forward
int IN4 = 11;  // Left Motor Backward

// Ultrasonic Sensor Pins
int trigPin = 6;
int echoPin = 7;

long duration;
float distanceInches;
float threshold = 15.0;

// Print timer
unsigned long lastPrintTime = 0;
unsigned long printInterval = 500;

void setup() {
  Serial.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  digitalWrite(1, HIGH); // Enable Right Motor
  digitalWrite(9, HIGH); // Enable Left Motor
}

void loop() {
  distanceInches = getDistanceInches();

  // Movement Logic
  if (distanceInches <= threshold) {
    turnLeft();
  } else {
    moveForward();
  }

  // Slow Printing Logic
  if (millis() - lastPrintTime >= printInterval) {
    Serial.print("Distance: ");
    Serial.print(distanceInches);
    Serial.println(" in");

    if (distanceInches <= threshold) {
      Serial.println("\nMoving Left...\n");
    } else {
      Serial.println("\nMoving Forward...\n");
    }

    lastPrintTime = millis();
  }
}

// ----- Motor Functions -----

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnLeft() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// ----- Ultrasonic Distance in Inches -----

float getDistanceInches() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  return duration * 0.0135 / 2;
}