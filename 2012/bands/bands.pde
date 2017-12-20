// stripy band sequence
// known bugs - eventually hangs when z gets large enough


/* vim: set noexpandtab ai ts=4 sw=4 tw=4: */

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
  FastSPI_LED.setChipset(CFastSPI_LED::SPI_LPD6803);
  
  FastSPI_LED.init();
  FastSPI_LED.setColorLevels(256);
  FastSPI_LED.start();

  leds = (struct CRGB*)FastSPI_LED.getRGBData(); 
}


// g is really b, r is really g, b is really r
float ct=0;
    int k;
    
float z=0, h,s,v,r,g,b, hi, f, p, q, t;    

void loop() {
  for (int j=0; j < NUM_COLS ; j++) {     // 3 cycles of all 96 colors in the wheel

    for (int i=0; i < NUM_LEDS; i++) {
		// increment, sets the speed
		z += .025;

		// rotate a colourwheel
		// convert HSV to RGB
		h = z+2.4*i;
		v = 255;
		s=1;
		hi = (int)(h/60.0) % 6;
		f = (h/60.0)-floor(h/60.0);
		p = v * (1.0-s);
		q = v * (1.0 - (f*s));
		t = v * (1.0 - ((1.0-f)*s));
	
		switch ((int)hi) {
			case 0: r=v; g=t; b=b; break;
			case 1: r=q; g=v; b=p; break;
			case 2: r=p; g=v; b=t; break;
			case 3: r=p; g=q; b=v; break;
			case 4: r=t; g=p; b=v; break;
			case 5: r=v; g=p; b=q; break;		
		}

		// hard limit on or off
		// comment out for smooth stripes
		if (r>128) r=255; else r=0;
		if (g>128) g=255; else g=0;
		if (b>128) b=255; else b=0;

		leds[i].g=b;
		leds[i].b=r;
		leds[i].r=g;
      
    } 


    FastSPI_LED.show();
    //delay(analogRead(0));
    delay(5);
  }
}

