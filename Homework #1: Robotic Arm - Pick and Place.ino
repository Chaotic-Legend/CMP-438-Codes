#include <Servo.h>
#include <math.h>

// ===== Servo Objects =====
Servo baseServo;         // D9
Servo shoulderServo;     // D6
Servo elbowServo;        // D5
Servo wristPitchServo;   // D3
Servo gripperServo;      // D11

// ===== Arm Link Lengths (cm) =====
const float L1 = 10.0;  // Shoulder → Elbow
const float L2 = 7.0;   // Elbow → Wrist

// ===== Gripper Range =====
const int GRIPPER_OPEN  = 40;
const int GRIPPER_CLOSE = 120;

// ===== Pick and Place Coordinates =====
float x_pick = 8.0, y_pick = 5.0, z_pick = 5.0;
float x_place = 4.0, y_place = 10.0, z_place = 8.0;

void setup() {
  Serial.begin(9600);

  // Attach all servos to the corrected pins
  baseServo.attach(9);
  shoulderServo.attach(6);
  elbowServo.attach(5);
  wristPitchServo.attach(3);
  gripperServo.attach(11);

  Serial.println("=== Adeept 5-Servo Robotic Arm: Pick & Place ===");

  // Safe startup position
  baseServo.write(90);
  shoulderServo.write(90);
  elbowServo.write(90);
  wristPitchServo.write(90);
  gripperServo.write(GRIPPER_OPEN);
  delay(800);
}

// ===== MAIN LOOP =====
void loop() {
  pickAndPlace(x_pick, y_pick, z_pick, x_place, y_place, z_place);
  Serial.println("\nPick and Place Complete. Waiting...");
  delay(3000);
}

// ===== Move Arm to Target (x, y, z) =====
void moveTo(float x, float y, float z, bool slow=false) {

  // Base rotation angle
  float thetaBase = atan2(y, x);
  float baseDeg = constrain(degrees(thetaBase), 0, 180);

  // Planar distance
  float r = sqrt(x * x + y * y);

  // IK for shoulder & elbow
  float D = (r * r + z * z - L1 * L1 - L2 * L2) / (2 * L1 * L2);
  if (D < -1 || D > 1) {
    Serial.println("⚠️ Target Unreachable! Skipping...");
    return;
  }

  float thetaElbow = acos(D);
  float thetaShoulder = atan2(z, r) - atan2(L2 * sin(thetaElbow), L1 + L2 * cos(thetaElbow));
  float shoulderDeg = constrain(degrees(thetaShoulder), 0, 180);
  float elbowDeg = constrain(degrees(thetaElbow), 0, 180);

  // Wrist keeps end-effector level
  float wristDeg = constrain(90 - (shoulderDeg + elbowDeg), 0, 180);

  // If slow movement is requested, interpolate
  if (slow) {
    const int steps = 20;
    float startBase = baseServo.read();
    float startShoulder = shoulderServo.read();
    float startElbow = elbowServo.read();
    float startWrist = wristPitchServo.read();

    for (int i = 1; i <= steps; i++) {
      baseServo.write(startBase + (baseDeg - startBase) * i / steps);
      shoulderServo.write(startShoulder + (shoulderDeg - startShoulder) * i / steps);
      elbowServo.write(startElbow + (elbowDeg - startElbow) * i / steps);
      wristPitchServo.write(startWrist + (wristDeg - startWrist) * i / steps);
      delay(80);  // Adjust delay for slower/faster movement
    }
  } else {
    shoulderServo.write(shoulderDeg);
    elbowServo.write(elbowDeg);
    wristPitchServo.write(wristDeg);
  }

  baseServo.write(baseDeg);

  // Debug output
  Serial.print("\nBase: "); Serial.print(baseDeg);
  Serial.print(" | Shoulder: "); Serial.print(shoulderDeg);
  Serial.print(" | Elbow: "); Serial.print(elbowDeg);
  Serial.print(" | Wrist: "); Serial.println(wristDeg);
}

// ===== Pick and Place Sequence =====
void pickAndPlace(float x1, float y1, float z1,
                  float x2, float y2, float z2) {

  Serial.println("\nMoving to Pick Location...");
  // Lower shoulder by reducing z slightly for pick-up
  moveTo(x1, y1, z1 - 2.0, false);

  Serial.println("\nClosing Gripper...");
  gripperServo.write(GRIPPER_CLOSE);
  delay(1000);

  Serial.println("\nMoving to Place Location (slower)...");
  moveTo(x2, y2, z2, true);  // Slow movement while carrying object

  Serial.println("\nOpening Gripper...");
  gripperServo.write(GRIPPER_OPEN);
  delay(1000);

  Serial.println("\nReturning to Home...");
  moveTo(6.0, 0.0, 10.0, false);
  delay(1000);
}
