// CMP 438: Communicating Robots - Isaac D. Hoyos
#include <Servo.h>
#include <math.h>

// Servo Objects:
Servo baseServo;
Servo shoulderServo;
Servo elbowServo;
Servo wristPitchServo;
Servo wristRotServo;
Servo gripperServo;

// Arm Link Lengths (cm):
const float L1 = 10.0;  // Shoulder to Elbow Length.
const float L2 = 7.0;   // Elbow to Wrist Length.
const float L3 = 7.0;   // Wrist to Gripper Length.

// Gripper Servo Positions:
const int GRIPPER_OPEN = 90;
const int GRIPPER_CLOSE = 30;

// Coordinates for pick and place points.
float x_pick = 8.0, y_pick = 5.0, z_pick = 5.0;
float x_place = 4.0, y_place = 10.0, z_place = 8.0;

void setup() {
  Serial.begin(9600);

  // Attach servos to appropriate pins.
  baseServo.attach(9);
  shoulderServo.attach(10);
  elbowServo.attach(11);
  wristPitchServo.attach(6);
  wristRotServo.attach(5);
  gripperServo.attach(3);

  Serial.println("Starting pick and place sequence...");
}

void loop() {
  // Run the pick and place sequence.
  pickAndPlace(x_pick, y_pick, z_pick, x_place, y_place, z_place);
  Serial.println("Pick and place sequence complete! Waiting before repeating...");
  delay(3000); // Wait 3 seconds before repeating.
}

// Move the arm to the given (x, y, z) coordinate.
void moveTo(float x, float y, float z) {
  // Calculate Base Rotation:
  float thetaBase = atan2(y, x);
  baseServo.write(degrees(thetaBase));

  // Project target point onto the vertical plane.
  float r = sqrt(x * x + y * y); // Horizontal Distance.
  float zEff = z;                // Vertical Height.

  // Inverse kinematics for shoulder and elbow.
  float D = (r * r + zEff * zEff - L1 * L1 - L2 * L2) / (2 * L1 * L2);

  if (D < -1 || D > 1) {
    Serial.println("Target Unreachable!");
    return;
  }

  float thetaElbow = acos(D);
  float thetaShoulder = atan2(zEff, r) - atan2(L2 * sin(thetaElbow), L1 + L2 * cos(thetaElbow));

  // Convert to Degrees:
  float shoulderAngle = degrees(thetaShoulder);
  float elbowAngle = degrees(thetaElbow);

  // Keep wrist roughly horizontal.
  float wristPitchAngle = -(shoulderAngle + elbowAngle);
  float wristRotAngle = 90; // Fixed for simplicity.

  // Move Servos:
  shoulderServo.write(shoulderAngle);
  elbowServo.write(elbowAngle);
  wristPitchServo.write(wristPitchAngle);
  wristRotServo.write(wristRotAngle);

  // Print joint details for debugging.
  Serial.print("\nBase: "); Serial.print(degrees(thetaBase));
  Serial.print(" | Shoulder: "); Serial.print(shoulderAngle);
  Serial.print(" | Elbow: "); Serial.print(elbowAngle);
  Serial.print(" | WristPitch: "); Serial.print(wristPitchAngle);
  Serial.println(String(" | WristRot: ") + wristRotAngle + "\n");
  delay(1500); // Allow movement time.
}

// Perform the pick and place sequence.
void pickAndPlace(float x1, float y1, float z1, float x2, float y2, float z2) {
  Serial.println("\nMoving to pick location...");
  moveTo(x1, y1, z1);

  Serial.println("Closing gripper...");
  gripperServo.write(GRIPPER_CLOSE);
  delay(1000);

  Serial.println("\nMoving to place location...");
  moveTo(x2, y2, z2);

  Serial.println("Opening gripper...");
  gripperServo.write(GRIPPER_OPEN);
  delay(1000);

  Serial.println("\nReturning to home position...");
  moveTo(6.0, 0.0, 10.0); // Example home coordinates.
  delay(1000);
}
