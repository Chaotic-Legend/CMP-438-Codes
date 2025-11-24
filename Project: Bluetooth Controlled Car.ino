// CMP 438: Communicating Robots - Bluetooth Controlled Car - Isaac D. Hoyos

// Motor driver pins
int IN1 = 8;
int IN2 = 9;
int IN3 = 10;
int IN4 = 11;
int ENA = 5;
int ENB = 6;

char command;

void setup() {
  Serial.begin(9600); // HC-05 default baud rate

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
}

void loop() {
  if (Serial.available()) {
    command = Serial.read();
    command = toupper(command);

    if (command == 'F') forward();
    if (command == 'B') backward();
    if (command == 'L') left();
    if (command == 'R') right();
    if (command == 'S') stopCar();
  }
}

// Movement functions
void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void stopCar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
