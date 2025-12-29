// CMP 438: Communicating Robots - Isaac D. Hoyos
// Tinkercad Link: https://tinyurl.com/kehmmbfh

#include <Servo.h>
#include <math.h>

// These Servo objects represent each joint of the robotic arm.
Servo baseServo;       // This servo controls the base rotation and is connected to pin D9.
Servo shoulderServo;   // This servo controls the shoulder joint and is connected to pin D6.
Servo elbowServo;      // This servo controls the elbow joint and is connected to pin D5.
Servo wristPitchServo; // This servo controls the wrist pitch and is connected to pin D3.
Servo gripperServo;    // This servo controls the gripper and is connected to pin D11.

// These constants define the physical link lengths of the robotic arm in centimeters.
const float L1 = 10.0; // This is the distance from the shoulder joint to the elbow joint.
const float L2 = 7.0;  // This is the distance from the elbow joint to the wrist joint.

// These constants define the open and closed positions of the gripper servo.
const int GRIPPER_OPEN  = 40;
const int GRIPPER_CLOSE = 120;

// These variables define the 3D coordinates for the pick and place locations.
float x_pick = 8.0, y_pick = 5.0, z_pick = 5.0;
float x_place = 4.0, y_place = 10.0, z_place = 8.0;

void setup() {
  Serial.begin(9600);

  // These commands attach each servo to its corresponding Arduino pin.
  baseServo.attach(9);
  shoulderServo.attach(6);
  elbowServo.attach(5);
  wristPitchServo.attach(3);
  gripperServo.attach(11);
  Serial.println("=== Adeept 5-Servo Robotic Arm: Pick & Place ===");

  // This section moves the robotic arm to a safe startup position.
  baseServo.write(90);
  shoulderServo.write(90);
  elbowServo.write(90);
  wristPitchServo.write(90);
  gripperServo.write(GRIPPER_OPEN);
  delay(800);
}

// This loop continuously performs the pick-and-place sequence.
void loop() {
  pickAndPlace(x_pick, y_pick, z_pick, x_place, y_place, z_place);
  Serial.println("\nPick and Place Complete. Waiting...");
  delay(3000);
}

// This function calculates inverse kinematics and moves the arm to the target position.
void moveTo(float x, float y, float z, bool slow=false) {
  // This calculation determines the base rotation angle using atan2.
  float thetaBase = atan2(y, x);
  float baseDeg = constrain(degrees(thetaBase), 0, 180);

  // This value represents the planar distance from the base to the target.
  float r = sqrt(x * x + y * y);

  // These calculations perform inverse kinematics for the shoulder and elbow joints.
  float D = (r * r + z * z - L1 * L1 - L2 * L2) / (2 * L1 * L2);
  if (D < -1 || D > 1) {
    Serial.println("⚠️ Target Unreachable! Skipping...");
    return;
  }

  // These calculations compute joint angles using inverse kinematics.
  float thetaElbow = acos(D);
  float thetaShoulder = atan2(z, r) - atan2(L2 * sin(thetaElbow), L1 + L2 * cos(thetaElbow));
  float shoulderDeg = constrain(degrees(thetaShoulder), 0, 180);
  float elbowDeg = constrain(degrees(thetaElbow), 0, 180);
  float wristDeg = constrain(90 - (shoulderDeg + elbowDeg), 0, 180);

  // This section smoothly interpolates joint movement when slow motion is enabled.
  if (slow) {
    const int steps = 25; // This constant defines the number of interpolation steps for smooth motion.
    float startBase = baseServo.read();
    float startShoulder = shoulderServo.read();
    float startElbow = elbowServo.read();
    float startWrist = wristPitchServo.read();
    for (int i = 1; i <= steps; i++) {
      baseServo.write(startBase + (baseDeg - startBase) * i / steps);
      shoulderServo.write(startShoulder + (shoulderDeg - startShoulder) * i / steps);
      elbowServo.write(startElbow + (elbowDeg - startElbow) * i / steps);
      wristPitchServo.write(startWrist + (wristDeg - startWrist) * i / steps);
      delay(60); // This delay controls the speed of the smooth motion.
    }
  } else {
    shoulderServo.write(shoulderDeg);
    elbowServo.write(elbowDeg);
    wristPitchServo.write(wristDeg);
  }
  baseServo.write(baseDeg);

  // This output prints joint angles to the Serial Monitor for debugging.
  Serial.print("\nBase: "); Serial.print(baseDeg);
  Serial.print(" | Shoulder: "); Serial.print(shoulderDeg);
  Serial.print(" | Elbow: "); Serial.print(elbowDeg);
  Serial.print(" | Wrist: "); Serial.println(wristDeg);
}

// This function performs the full pick-and-place operation.
void pickAndPlace(float x1, float y1, float z1,
                  float x2, float y2, float z2) {
  Serial.println("\nMoving to Pick Location...");
  moveTo(x1, y1, z1 - 2.0, true); // This movement lowers the arm slowly to the pick position.
  Serial.println("\nClosing Gripper...");
  gripperServo.write(GRIPPER_CLOSE);
  delay(1000);
  Serial.println("\nMoving to Place Location...");
  moveTo(x2, y2, z2, true); // This movement carries the object slowly to the place location.
  Serial.println("\nOpening Gripper...");
  gripperServo.write(GRIPPER_OPEN);
  delay(1000);
  Serial.println("\nReturning to Home Location...");
  moveTo(6.0, 0.0, 10.0, true); // This movement smoothly returns the arm to a home position.
  delay(1000);
}
