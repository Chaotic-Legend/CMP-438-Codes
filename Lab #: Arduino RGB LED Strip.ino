// CMP 438: Communicating Robots - Isaac D. Hoyos
#include <Adafruit_NeoPixel.h>
#define PIN 12
#define NUMPIXELS 4

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayVal = 100;
int redColor = 0;
int greenColor = 0;
int blueColor = 0;

void setup() {
  pixels.begin();
  pixels.show();
}

void loop() {
  setColor();
  
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(redColor, greenColor, blueColor));
    pixels.show();
    delay(delayVal);
  }
}

void setColor() {
  redColor = random(0, 255);
  greenColor = random(0, 255);
  blueColor = random(0, 255);
}
