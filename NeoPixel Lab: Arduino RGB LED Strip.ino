// CMP 438: Communicating Robots - Isaac D. Hoyos
// Tinkercad Link: https://tinyurl.com/yc72kyn8

#include <Adafruit_NeoPixel.h>

// This pin connects the Arduino to the NeoPixel data line.
#define PIN 12

// This constant defines the number of NeoPixel LEDs.
#define NUMPIXELS 4

// Sets up the NeoPixel strip with specified LEDs and data pin.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayVal = 100; // This value controls the LED lighting delay.
int redColor = 0;   // This variable stores the red color value.
int greenColor = 0; // This variable stores the green color value.
int blueColor = 0;  // This variable stores the blue color value.

// This function initializes the NeoPixel LEDs.
void setup() {
  pixels.begin();
  pixels.show();
}

// This function selects a new random LED color.
void loop() {
  setColor();
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, redColor, greenColor, blueColor);
    pixels.show();
    delay(delayVal);
  }
}

// This function generates random RGB values for the LED color.
void setColor() {
  redColor = random(0, 255);
  greenColor = random(0, 255);
  blueColor = random(0, 255);
}
