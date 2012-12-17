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
  FastSPI_LED.setColorLevels(256);
  FastSPI_LED.start();

  leds = (struct CRGB*)FastSPI_LED.getRGBData(); 
}


// g is really b, r is really g, b is really r
float ct=0, t=0, rate;
int k,j, r;

void loop() {	

    rate = 30+27*sin(t/10);
    for (int i=0; i < NUM_LEDS; i++) {
	
	r = 127+127*sin(t+ i / rate * 3.14159);
	
	leds[i].g=0;
	leds[i].b=r;
	leds[i].r=255-r;
      
    } 

    t += 0.1;
    //j+=0.1;
    FastSPI_LED.show();
    delay(1);
}

