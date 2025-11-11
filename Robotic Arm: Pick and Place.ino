// CMP 438: Communicating Robots - Isaac D. Hoyos
#include <Servo.h>
#include <math.h>

// ===== Servo Objects =====
Servo baseServo;
Servo shoulderServo;
Servo elbowServo;
Servo wristPitchServo;
Servo wristRotServo;
Servo gripperServo;

// ===== Arm Link Lengths (cm) =====
const float L1 = 10.0;  // Shoulder to Elbow
const float L2 = 7.0;   // Elbow to Wrist
const float L3 = 7.0;   // Wrist to Gripper

// ===== Gripper Servo Positions =====
const int GRIPPER_OPEN = 90;
const int GRIPPER_CLOSE = 30;

// ===== Pick and Place Coordinates =====
float x_pick = 8.0, y_pick = 5.0, z_pick = 5.0;
float x_place = 4.0, y_place = 10.0, z_place = 8.0;

// ===== Setup =====
void setup() {
  Serial.begin(9600);

  // Attach all servos to their corresponding pins.
  baseServo.attach(9);
  shoulderServo.attach(10);
  elbowServo.attach(11);
  wristPitchServo.attach(6);
  wristRotServo.attach(5);
  gripperServo.attach(3);
  Serial.println("=== Robotic Arm: Pick and Place ===");
  Serial.println("\nStarting Pick and Place Sequence...");
}

// ===== Main Loop =====
void loop() {
  pickAndPlace(x_pick, y_pick, z_pick, x_place, y_place, z_place);
  Serial.println("Pick and Place Sequence Complete! Waiting before repeating...");
  delay(3000);  // Wait three seconds to repeat indefinitely.
}

// ===== Move Arm to Target (x, y, z) =====
void moveTo(float x, float y, float z) {
  // --- Base Rotation ---
  float thetaBase = atan2(y, x);
  baseServo.write(constrain(degrees(thetaBase), 0, 180));

  // --- Planar Distance ---
  float r = sqrt(x * x + y * y);
  float zEff = z;

  // --- Inverse Kinematics for Shoulder and Elbow ---
  float D = (r * r + zEff * zEff - L1 * L1 - L2 * L2) / (2 * L1 * L2);

  if (D < -1 || D > 1) {
    Serial.println("⚠️ Error: Target Unreachable! Skipping Movement...");
    return;
  }

  float thetaElbow = acos(D);
  float thetaShoulder = atan2(zEff, r) - atan2(L2 * sin(thetaElbow), L1 + L2 * cos(thetaElbow));

  // --- Convert to Degrees ---
  float shoulderAngle = degrees(thetaShoulder);
  float elbowAngle = degrees(thetaElbow);

  // --- Maintain Wrist Orientation ---
  float wristPitchAngle = 90 - (shoulderAngle + elbowAngle);
  float wristRotAngle = 90; // Fixed for simplicity.

  // Constrain all angles to servo range.
  shoulderAngle = constrain(shoulderAngle, 0, 180);
  elbowAngle = constrain(elbowAngle, 0, 180);
  wristPitchAngle = constrain(wristPitchAngle, 0, 180);

  // --- Move Servos ---
  shoulderServo.write(shoulderAngle);
  elbowServo.write(elbowAngle);
  wristPitchServo.write(wristPitchAngle);
  wristRotServo.write(wristRotAngle);

  // --- Debug Info ---
  Serial.print("\nBase: "); Serial.print(degrees(thetaBase));
  Serial.print(" | Shoulder: "); Serial.print(shoulderAngle);
  Serial.print(" | Elbow: "); Serial.print(elbowAngle);
  Serial.print(" | WristPitch: "); Serial.print(wristPitchAngle);
  Serial.print(" | WristRot: "); Serial.println(wristRotAngle);
  Serial.println();

  delay(1500); // Allow time for servos to reach position.
}

// ===== Pick and Place Sequence =====
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
  moveTo(6.0, 0.0, 10.0); // Home Position Coordinates
  delay(1000);
}
