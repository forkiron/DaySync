#include <FastLED.h>

#define DATA_PIN 3
#define NUM_LEDS 12

// NOTE: the code is set up in a way that functions can pull from an API, but the API was not working for pulling so a preset with sped up delays was used. 
// This delay would be extremely slow for transitions and hold periods to maintain a natural ambient state for the individual's lighting, promoting the health benefits mentioned.

CRGB leds[NUM_LEDS];

int colors[18];
int ledCols[6][3];

int clrStore [NUM_LEDS][3];

void setup() {

  fill_solid(leds, NUM_LEDS, CRGB::Black);
  delay(1000);

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  gradient();

  delay(1000);
  fadeToVal(0, 0, 0, 255, 103, 255, 50);
  delay(5000); 

  // example for dayCase case
  int reads[] = {255, 103, 255, 255, 255, 0, 255, 178, 102, 255, 0, 127, 0, 102, 51, 102, 0, 102};

  for (int i = 0; i < 18; i++) {
    colors[i] = reads[i];
  }

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 3; j++) {
      ledCols[i][j] = colors[j*(i+1)];
    }
  }
}

void loop() {
  fadeToVal(ledCols[0][0], ledCols[0][1], ledCols[0][2], ledCols[1][0], ledCols[1][1], ledCols[1][2], 10);
  delay(5000); 
  fadeToVal(ledCols[1][0], ledCols[1][1], ledCols[1][2], ledCols[2][0], ledCols[2][1], ledCols[2][2], 10);
  delay(5000);
  fadeToVal(ledCols[2][0], ledCols[2][1], ledCols[2][2], ledCols[3][0], ledCols[3][1], ledCols[3][2], 10);
  delay(5000);
  fadeToVal(ledCols[3][0], ledCols[3][1], ledCols[3][2], ledCols[4][0], ledCols[4][1], ledCols[4][2], 10);
  delay(5000);
  fadeToVal(ledCols[4][0], ledCols[4][1], ledCols[4][2], ledCols[5][0], ledCols[5][1], ledCols[5][2], 10); 
  delay(5000); 
  fadeToVal(ledCols[5][0], ledCols[5][1], ledCols[5][2], ledCols[0][0], ledCols[0][1], ledCols[1][2], 10);
  delay(5000);  
}

void gradient() {

  for (int i = 0; i < NUM_LEDS; i++) {
    int fraction = 255 / (NUM_LEDS-1);
    fadeOn(i, (255-(i*fraction)), 0, i*fraction, 1);
    clrStore [i][0] = (255-(i*fraction));
    clrStore [i][1] = 0;
    clrStore [i][2] = i*fraction;
  }

  for (int i = NUM_LEDS-1; i > -1; i--) {
    int fraction = 255 / (NUM_LEDS-1);
    fadeOff(i, (255-(i*fraction)), 0, i*fraction, 1);
    clrStore [i][0] = (255-(i*fraction));
    clrStore [i][1] = 0;
    clrStore [i][2] = i*fraction;
  }
}

void twinkle() {

  for (int i = 0; i < 20; i++) {
    int rand = random(12);

    fadeOn(rand, clrStore[rand][0], clrStore[rand][1], clrStore[rand][2], 0);

    fadeOff(rand, clrStore[rand][0], clrStore[rand][1], clrStore[rand][2], 0);

  }

  for (int i = NUM_LEDS-1; i > -1; i--) {
    int fraction = 255 / (NUM_LEDS-1);
    fadeOff(i, (255-(i*fraction)), 0, i*fraction, 0);
  }
}

void fadeOff(int ledIndex, int r, int g, int b, int delayAmt) {

  int outR, outG, outB;

  for (int i = 1; i < 255; i++) {

    if (r-i < 0) {
      outR = 0;
    } else {
      outR = r-i;
    }

    if (g-i < 0) {
      outG = 0;
    } else {
      outG = g-i;
    }

    if (b-i < 0) {
      outB = 0;
    } else {
      outB = b-i;
    }

    leds[ledIndex].setRGB(outR, outG, outB);
    FastLED.show();
    if ((outR = 0) && (outG = 0) && (outB = 0)) {
      break;
    }
    delay(delayAmt);
  }
}

void fadeOn(int ledIndex, int r, int g, int b, int delayAmt) {
  int outR, outG, outB;
  for (int i = 0; i < 255; i+=5) {
    if (i > r) {
      outR = r;
    } else {
      outR = i;
    }

    if (i > g) {
      outG = g;
    } else {
      outG = i;
    }

    if (i > b) {
      outB = b;
    } else {
      outB = i;
    }

    leds[ledIndex].setRGB(outR, outG, outB);
    FastLED.show();
    delay(delayAmt);
  }
}

void fadeToVal(int rA, int gA, int bA, int rB, int gB, int bB, int delayAmt) {
  int outR, outG, outB;
  int i = 0;
  while(true) {
    i++;
    if (rB > rA) {
      if ((rA + i) > rB) {
        outR = rB;
      } else {
        outR = rA + i;
      }
    } else {
      if ((rA - i) < rB) {
        outR = rB;
      } else {
        outR = rA - i;
      }
    }

    if (gB > gA) {
      if ((gA + i) > gB) {
        outG = gB;
      } else {
        outG = gA + i;
      }
    } else {
      if ((gA - i) < gB) {
        outG = gB;
      } else {
        outG = gA - i;
      }
    }

    if (bB > bA) {
      if ((bA + i) > bB) {
        outB = bB;
      } else {
        outB = bA + i;
      }
    } else {
      if ((bA - i) < bB) {
        outB = bB;
      } else {
        outB = bA - i;
      }
    }
    
    fill_solid(leds, NUM_LEDS, CRGB(outR,outG,outB));
    FastLED.show();
    delay(delayAmt);

    if((outB == bB) && (outG == gB) && (outR == rB)) {
      break;
    }
  }
}