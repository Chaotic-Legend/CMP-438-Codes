// CMP 438: Communicating Robots - Isaac D. Hoyos
#include <Servo.h>

Servo shoulder;
Servo elbow;
Servo gripper;

const float L1 = 10.0;
const float L2 = 7.0;

// Pick and place coordinates.
float x_pick = 8.0, y_pick = 5.0;
float x_place = 4.0, y_place = 10.0;

// Servo positions for gripper.
const int GRIPPER_OPEN = 90;
const int GRIPPER_CLOSE = 30;

void setup() {
  Serial.begin(9600);
  shoulder.attach(9);
  elbow.attach(10);
  gripper.attach(11);

  Serial.println("Starting pick and place sequence...");
  pickAndPlace(x_pick, y_pick, x_place, y_place);
}

void loop() {
  // No repeated actions required.
}

// Function to calculate joint angles and move the arm.
void moveTo(float x, float y) {
  float r = sqrt(x*x + y*y);
  float cos_theta2 = (r*r - L1*L1 - L2*L2) / (2 * L1 * L2);

  // Safety check for unreachable positions.
  if (cos_theta2 < -1 || cos_theta2 > 1) {
    Serial.println("Target unreachable!");
    return;
  }

  float theta2 = acos(cos_theta2);
  float k1 = L1 + L2 * cos(theta2);
  float k2 = L2 * sin(theta2);
  float theta1 = atan2(y, x) - atan2(k2, k1);

  // Convert to degrees.
  float shoulderAngle = degrees(theta1);
  float elbowAngle = degrees(theta2);

  // Write angles to servos.
  shoulder.write(shoulderAngle);
  elbow.write(elbowAngle);
  
  Serial.print("Shoulder: "); Serial.print(shoulderAngle);
  Serial.print(" | Elbow: "); Serial.println(elbowAngle);
  // Wait for motion to complete.
  delay(1000);
}

// Function to pick up and place an object.
void pickAndPlace(float x1, float y1, float x2, float y2) {
  Serial.println("Moving to pick location...");
  moveTo(x1, y1);

  Serial.println("Closing gripper...");
  gripper.write(GRIPPER_CLOSE);
  delay(1000);

  Serial.println("Moving to place location...");
  moveTo(x2, y2);

  Serial.println("Opening Gripper...");
  gripper.write(GRIPPER_OPEN);
  delay(1000);

  Serial.println("Pick and place complete!");
}
