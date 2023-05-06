#include <Adafruit_NeoPixel.h>
#include "EyePatterns.h"

#define LED_PIN       4
#define NUMPIXELS    74

int LED_BRIGHTNESS = 8;  // 0-255

Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN);

void eyes_setup();
void display_eyes(const byte arr[], int hue);

void run_emotions();

void change_emotions(String command);
