#include <FastSPI_LED.h>

#define NUM_LEDS 100
#define NUM_COLS 32
#define SPEED 5

// Sometimes chipsets wire in a backwards sort of way
struct CRGB { unsigned char b; unsigned char r; unsigned char g; };
// struct CRGB { unsigned char r; unsigned char g; unsigned char b; };
struct CRGB *leds;

void setup()
{
  FastSPI_LED.setLeds(NUM_LEDS);//
//  FastSPI_LED.setChipset(CFastSPI_LED::SPI_TM1809);
  FastSPI_LED.setChipset(CFastSPI_LED::SPI_LPD6803);
  //FastSPI_LED.setChipset(CFastSPI_LED::SPI_HL1606);
  //FastSPI_LED.setChipset(CFastSPI_LED::SPI_595);
  //FastSPI_LED.setChipset(CFastSPI_LED::SPI_WS2801);
  
  FastSPI_LED.init();
  FastSPI_LED.setColorLevels(32);
  FastSPI_LED.start();

  leds = (struct CRGB*)FastSPI_LED.getRGBData(); 
}

void loop() {
  for (int j=0; j < NUM_COLS ; j++) {     // 3 cycles of all 96 colors in the wheel
    for (int i=0; i < NUM_LEDS; i++) {
      int WheelPos;
      WheelPos = ((i + j) % NUM_COLS);
      switch( WheelPos >> 5)
      {
    case 0:
      leds[i].r=NUM_COLS-1 - WheelPos % NUM_COLS;   //Red down
      leds[i].g=WheelPos % NUM_COLS;      // Green up
      leds[i].b=0;                  //blue off
      break; 
    case 1:
      leds[i].g=NUM_COLS-1 - WheelPos % NUM_COLS;  //green down
      leds[i].b=WheelPos % NUM_COLS;      //blue up
      leds[i].r=0;                  //red off
      break; 
    case 2:
      leds[i].b=NUM_COLS-1 - WheelPos % NUM_COLS;  //blue down 
      leds[i].r=WheelPos % NUM_COLS;      //red up
      leds[i].g=0;                  //green off
      break; 
  }      
    }  
    FastSPI_LED.show();
    delay(SPEED*10);
  }
}

