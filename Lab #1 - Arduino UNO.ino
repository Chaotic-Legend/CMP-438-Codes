// CMP 438: Communicating Robots - Isaac D. Hoyos
// Lab 1 - Raspberry Pi Pico: https://wokwi.com/projects/450055821058964481

int ledPin = 12;    // The LED is connected to digital pin 12.
int pushButton = 2; // The push button is connected to digital pin 2.
int pushState = 0;  // This variable stores the button's current state.
int previousState = HIGH; // This variable stores the button's previous state.

void setup() {
  // This statement configures the LED pin as an output.
  pinMode(ledPin, OUTPUT);

  // This statement configures the button pin as a pull-up input.
  pinMode(pushButton, INPUT_PULLUP);

  // This starts serial communication for printing.
  Serial.begin(9600);
}

void loop() {
  // This statement reads the current state of the push button.
  pushState = digitalRead(pushButton);

  // This statement turns the LED on when the button is pressed.
  if (pushState == LOW) {
    digitalWrite(ledPin, HIGH);
  } else {
    // This statement turns the LED off when the button is not pressed.
    digitalWrite(ledPin, LOW);
  }

  // This statement prints only when the button state changes.
  if (pushState != previousState) {
    if (pushState == LOW) {
      Serial.println("PushButton Pressed.\n");
    } else {
      Serial.println("PushButton Unpressed.\n");
    }
    previousState = pushState;
  }
  
  // This delay reduces noise by adding a short pause between readings.
  delay(20);
}