// CMP 438: Communicating Robots - Isaac D. Hoyos
#include <Servo.h>
#include <math.h>

// Servos:
Servo baseServo;
Servo shoulderServo;
Servo elbowServo;
Servo wristPitchServo;
Servo wristRotServo;
Servo gripperServo;

// Arm lengths:
const float L1 = 10.0;  // Shoulder to elbow
const float L2 = 7.0;   // Elbow to wrist
const float L3 = 7.0;   // Wrist to gripper

// Gripper positions:
const int GRIPPER_OPEN = 90;
const int GRIPPER_CLOSE = 30;

// Pick and place coordinates:
float x_pick = 8.0, y_pick = 5.0, z_pick = 5.0;
float x_place = 4.0, y_place = 10.0, z_place = 8.0;

void setup() {
  Serial.begin(9600);

  // Attach servos:
  baseServo.attach(9);
  shoulderServo.attach(10);
  elbowServo.attach(11);
  wristPitchServo.attach(6);
  wristRotServo.attach(5);
  gripperServo.attach(3);

  Serial.println("Starting pick-and-place sequence...");

  pickAndPlace(x_pick, y_pick, z_pick, x_place, y_place, z_place);
}

void loop() {
  // No repeated actions needed.
}

void moveTo(float x, float y, float z) {
  // Base rotation:
  float thetaBase = atan2(y, x);
  baseServo.write(degrees(thetaBase));

  // Project target into the plane of the shoulder/elbow.
  float r = sqrt(x*x + y*y);
  float zEff = z;

  // Calculate shoulder and elbow using planar IK.
  float D = (r*r + zEff*zEff - L1*L1 - L2*L2) / (2 * L1 * L2);
  if (D < -1 || D > 1) {
    Serial.println("Target Unreachable!");
    return;
  }

  float thetaElbow = acos(D);
  float thetaShoulder = atan2(zEff, r) - atan2(L2 * sin(thetaElbow), L1 + L2 * cos(thetaElbow));

  // Convert to degrees:
  float shoulderAngle = degrees(thetaShoulder);
  float elbowAngle = degrees(thetaElbow);

  // For simplicity, keep wrist horizontal.
  float wristPitchAngle = -(shoulderAngle + elbowAngle);
  float wristRotAngle = 90;

  // Write servo positions:
  shoulderServo.write(shoulderAngle);
  elbowServo.write(elbowAngle);
  wristPitchServo.write(wristPitchAngle);
  wristRotServo.write(wristRotAngle);

  Serial.print("Base: "); Serial.print(degrees(thetaBase));
  Serial.print(" | Shoulder: "); Serial.print(shoulderAngle);
  Serial.print(" | Elbow: "); Serial.print(elbowAngle);
  Serial.print(" | WristPitch: "); Serial.print(wristPitchAngle);
  Serial.print(" | WristRot: "); Serial.println(wristRotAngle);

  delay(1000);
}

void pickAndPlace(float x1, float y1, float z1, float x2, float y2, float z2) {
  Serial.println("Moving to pick location...");
  moveTo(x1, y1, z1);

  Serial.println("Closing gripper...");
  gripperServo.write(GRIPPER_CLOSE);
  delay(1000);

  Serial.println("Moving to place location...");
  moveTo(x2, y2, z2);

  Serial.println("Opening gripper...");
  gripperServo.write(GRIPPER_OPEN);
  delay(1000);

  Serial.println("Pick-and-place complete!");
}
