#include "FastLED.h"

#define DATA_PIN    4
#define NUM_LEDS    50
#define LIT_LEDS    15
#define BRIGHTNESS  1
#define LED_TYPE    WS2811 
#define COLOR_ORDER RGB
#define DELAY       150

#define MAX_FADER   128

// This directly maps to the LED in memory
CRGB leds[NUM_LEDS];

// Which LEDs are lit?
int active_leds[LIT_LEDS];
// Speed the LEDs are fading
int active_R_speeds[LIT_LEDS];
int active_G_speeds[LIT_LEDS];
int active_B_speeds[LIT_LEDS];
// The Current RGB of an LED
int actual_R[LIT_LEDS];
int actual_G[LIT_LEDS];
int actual_B[LIT_LEDS];

void setup() {
  delay(2000);
  
  Serial.begin(2000000);
  Serial.println("resetting!");
  FastLED.addLeds<LED_TYPE, DATA_PIN>(leds, NUM_LEDS);
  for(int initLeds = 0; initLeds < LIT_LEDS; initLeds = initLeds + 1) {
    active_leds[initLeds] = get_led();
    active_R_speeds[initLeds] = get_speed();
    active_G_speeds[initLeds] = get_speed(); 
    active_B_speeds[initLeds] = get_speed();
    actual_R[initLeds] = 0;
    actual_G[initLeds] = 0;
    actual_B[initLeds] = 0;
  }
}

void loop() {
  for(int initLeds = 0; initLeds < LIT_LEDS; initLeds = initLeds + 1) {
    bool toggled = false;
    actual_R[initLeds] = actual_R[initLeds] + active_R_speeds[initLeds];
    actual_G[initLeds] = actual_G[initLeds] + active_G_speeds[initLeds];
    actual_B[initLeds] = actual_B[initLeds] + active_B_speeds[initLeds];    

    // Manage RED out of bounds
    if(actual_R[initLeds] > 255) {
      actual_R[initLeds] = 255;
      invert_leds(initLeds);
      toggled = true;
    } else if(actual_R[initLeds] < 0) {
      actual_R[initLeds] = 0;
      active_R_speeds[initLeds] = 0;
    }

    // Manage GREEN out of bounds
    if((!toggled) && (actual_G[initLeds] > 255)) {
      actual_G[initLeds] = 255;
      invert_leds(initLeds);
      toggled = true;
    } else if(actual_G[initLeds] < 0 ) {
      actual_G[initLeds] = 0;
      active_G_speeds[initLeds] = 0;
    }

    // Manage BLUE out of bounds
    if((!toggled) && (actual_B[initLeds] > 255)) {
      actual_B[initLeds] = 255;
      invert_leds(initLeds);
      toggled = true;
    } else if(actual_B[initLeds] < 0 ) {
      actual_B[initLeds] = 0;
      active_B_speeds[initLeds] = 0;
    }

    leds[active_leds[initLeds]] = CRGB(actual_R[initLeds], actual_G[initLeds], actual_B[initLeds]);

    // Everything is black now...
    if((actual_R[initLeds]==0) &&
       (actual_G[initLeds]==0) &&
       (actual_B[initLeds]==0)) {
        active_leds[initLeds] = get_led();
        
        Serial.print("New LED is : "); Serial.println(active_leds[initLeds]);
        active_R_speeds[initLeds] = get_speed();
        active_G_speeds[initLeds] = get_speed(); 
        active_B_speeds[initLeds] = get_speed();
   
    }
  }

  // Write RAM to LEDs
  FastLED.show();
  
  // Wait a little bit
  delay(DELAY);
}

int get_speed() {
  return random(1, MAX_FADER);
}

int get_led() {
  return random(1, NUM_LEDS);
}

void invert_leds(initLeds) {
  active_R_speeds[initLeds] = -1 * active_R_speeds[initLeds];
  active_G_speeds[initLeds] = -1 * active_G_speeds[initLeds];
  active_B_speeds[initLeds] = -1 * active_B_speeds[initLeds];
}

