#include <Adafruit_NeoPixel.h>
#include <Wire.h>

#include <avr/power.h>

#define PIN 4
#define BRIGHTNESS 255

#define WIRE_ADDRESS 5     //I2C Address of this device

#define BOT_IDLE 0xa       //Robot idling - waiting for start or stopped
#define BOT_FORWARD 0xb    //Robot moving forward
#define BOT_BACKWARD 0xc   //Robot moving backward
#define BOT_LIFTTOTES 0xd  //Robot lifting totes
#define BOT_LIFTCAN 0xe    //Robot lifting garbage can
#define BOT_ARMS 0xf       //Robot change in arm state
#define BOT_UNLOAD 0x10    //Robot unloading



// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

int CURRENT_ACTION = 0;    //Current action of robot - default as IDLE


// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  Wire.begin(WIRE_ADDRESS);        //Set I2C address of Arduino
  Wire.onReceive(receiveEvent);    //Set event to trigger when I2C data is received
  strip.begin();                   //Reset strip object
  strip.show();                    // Initialize all pixels to 'off'
}

void loop() {
  
 // bar(72, strip.Color(40,60,180));
  
 // baradam(strip.Color(40,60,180));
 // baradam2(strip.Color(30,20,200));
 
 //SWITCH logic to select current lighting sequence
 
 switch (CURRENT_ACTION) {
  case BOT_IDLE:
    pulseAll();
   // BLINK(50, 50, strip.Color(60,60,30));
 // BLINKADAM(5);
  
  
  //chaseblock(10, strip.Color(0,255,0), 10);
   
    
  //chaseblock(10, strip.Color(255, 255, 255),14);
  //chaseblock(10, strip.Color(255, 0, 0), 17);
  //chaseblock(10, strip.Color(0, 255, 0),20);
  //chaseblock(10, strip.Color(0, 0, 255),24);
  //for (int i=0; i <=100; i++)
  //  {
    //  sparkle(10, strip.Color(255, 0, 0));
   // }
  //for (int i=0; i <=100; i++)
   // {
    //  sparkle(10, strip.Color(0, 255, 0));
   // }
  //for (int i=0; i <=100; i++)
   // {
     // sparkle(10, strip.Color(0, 0, 255));
   // }
  //for (int i=0; i <=200; i++)
   // {
    //  sparkle(10, strip.Color(255, 255, 255));
    //}
    
  // Some example procedures showing how to display to the pixels:
  //colorWipe(strip.Color(255, 0, 0), 50); // Red
  //colorWipe(strip.Color(0, 255, 0), 50); // Green
  //colorWipe(strip.Color(0, 0, 255), 50); // Blue
  // Send a theater pixel chase in...
  //theaterChase(strip.Color(127, 127, 127), 50); // White
  //theaterChase(strip.Color(127,   0,   0), 50); // Red
  //theaterChase(strip.Color(  0,   0, 127), 50); // Blue

  //rainbow(20);
  //rainbowCycle(20);
  //theaterChaseRainbow(50);
    // statements
    break;
  case BOT_FORWARD:
    // statements
    break;
  case BOT_BACKWARD:
    //statements
    break;
  case BOT_LIFTTOTES:
    //statements
    break;
  case BOT_LIFTCAN:
    //statements
    break;
  case BOT_ARMS:
    //statements
    break;
  case BOT_UNLOAD:
    //statements
    break;
  default: 
    
    
    for( int i=1 ; i<=2; i++)
      {
        chaseblockbackground(10, strip.Color(0, 255, 0), strip.Color(255, 0,0), 8);
        
      }
      
    chaseblock(10, strip.Color(0, 255, 0),8);
    chaseblock(10, strip.Color(255, 0, 0),8);
    for (int i=0; i <=50; i++)
    {
      sparkle(10, strip.Color(255, 255, 255));
    }
    bar(60, strip.Color(0,255,0));
    rainbowCycle(1);
    rainbowCycle(1);
   
}


  
}

void receiveEvent(int)    //Event run when I2C data is received
{

 while(Wire.available())
  {
    CURRENT_ACTION = Wire.read();    // receive current state from RoboRio
  }

}

void pulseAll()        //Slowly pulse all LEDs 
{
  
 
  
  for( int intensity = 20; intensity <=255; intensity += 3)    //intensity min to max
    {
      
        strip.setBrightness(intensity); 
        strip.show();        
        for (int i=0; i <=strip.numPixels(); i++)          //   *******!!!!!!Use strip.numpixels() for all LEDs!!!!!!!!*********
        {
           strip.setPixelColor(i, strip.Color(255,255,255));    
           strip.show();
           
       
        }  
        
    }
   
  for( int intensity = 255 ; intensity >= 20; intensity -= 3)    //intensity max to min
    {
      
        strip.setBrightness(intensity); 
        strip.show();        
        for (int i=0; i <=strip.numPixels(); i++)
        {
           strip.setPixelColor(i, strip.Color(255,255,255));    
           strip.show();
           
       
        }  
        
    }  
    
  for (int i=0; i <=strip.numPixels(); i++)  //Loop to turn off all pixels
        {
           strip.setPixelColor(i, 0);  
           strip.show();
           
       
        }  
}


void BLINK(int numblinks, int pixelnum, uint32_t colour)
{
  strip.setBrightness(BRIGHTNESS);
  for (int i=0; i <=numblinks; i++)
    {
       strip.setPixelColor(pixelnum, colour);
       strip.show();
       delay(100);
       strip.setPixelColor(pixelnum, 0);
       strip.show();
       delay(100);
    } 
}



void BLINKADAM(int numblinks)
{
  for (int count=0; count <numblinks; count++)
   { 
      strip.setBrightness(BRIGHTNESS);
      for (int i=0; i <=strip.numPixels(); i++)
        {
          strip.setPixelColor(i, strip.Color(i,60,70));
        }
          strip.show();
          delay(1000);
      for (int i=0; i <= strip.numPixels(); i++)
        {
          strip.setPixelColor(i, 0);
        }
          strip.show();
          delay(1000);
    }
}    

void bar(int barsize, uint32_t colour)     //Draw a bar of barsize and then undraw it
{
  strip.setBrightness(BRIGHTNESS);
  for (int counter=0; counter <=barsize; counter=counter+1)
  {
    strip.setPixelColor(counter, colour);
    strip.show();
    delay(5);
  }
  delay(50);
  for(int counter=counter; counter >=0; counter=counter-1)
  {
    strip.setPixelColor(counter, 0);
    strip.show();
    delay(5);
  }
  delay(50);
}



void baradam(uint32_t colour)
{
  strip.setBrightness(BRIGHTNESS);
  for (int counter=0; counter <=72; counter=counter+1)
  {
    strip.setPixelColor(counter, colour);
    strip.setPixelColor(strip.numPixels()-counter, colour);
    strip.show();
    delay(20);
  }
  delay(500);
  for(int counter=counter; counter >=0; counter=counter-1)
  {
    strip.setPixelColor(counter, 0);
    strip.setPixelColor (strip.numPixels()-counter,0);
    strip.show();
    delay(20);
  }
  delay(500);
}

void baradam2(uint32_t colour)
{
  strip.setBrightness(BRIGHTNESS);
  for (int counter=0; counter <=72; counter=counter+1)
  {
    strip.setPixelColor(counter, colour);
    strip.setPixelColor(strip.numPixels()-counter, colour);
    strip.show();
    delay(20);
  }
  delay(500);
  for(int counter=counter; counter >=35; counter=counter-1)
  {
    strip.setPixelColor(counter, 0);
    strip.setPixelColor (strip.numPixels()-counter,0);
    strip.show();
    delay(20);
  }
  for (int counter=counter; counter <=50; counter=counter+1)
  {
    strip.setPixelColor(counter, colour);
    strip.setPixelColor(strip.numPixels()-counter, colour);
    strip.show();
    delay(20);
  }
   for(int counter=counter; counter >=0; counter=counter-1)
  {
    strip.setPixelColor(counter, 0);
    strip.setPixelColor (strip.numPixels()-counter,0);
    strip.show();
    delay(20);
  }
  delay(500);
}


// Random Pixel sparkle
void sparkle(uint8_t hangtime, uint32_t colour)
{
  long randnum;

  randnum = random(0, strip.numPixels());
  strip.setBrightness(BRIGHTNESS);
  strip.setPixelColor(randnum, colour);
  strip.setPixelColor(randnum+1, colour);
  strip.show();
  delay(hangtime);
  strip.setPixelColor(randnum, 0);
  strip.setPixelColor(randnum+1, 0);
  strip.show();
  delay(hangtime);
}

void chaseblock(uint8_t hangtime, uint32_t colour, uint8_t pixels)
{
  strip.setBrightness(BRIGHTNESS);
  for(int i=0; i<pixels; i++)
    {
      if( i < strip.numPixels() )
        {
          strip.setPixelColor(i, colour);
        }
    }
  strip.show();
  delay(hangtime);
  for(int i=0; i<strip.numPixels(); i++)
    {
      strip.setPixelColor(i, 0);  //Turn off bottom most pixel
      if( (i+pixels) <= strip.numPixels() )
        {
          strip.setPixelColor(i+pixels, colour);
        }
      strip.show();
      delay(hangtime);
      
    }
    

  
}

void chaseblockbackground(uint8_t hangtime, uint32_t colour, uint32_t bgcolour, uint8_t pixels)
{
  
  strip.setBrightness(BRIGHTNESS);
  
  for(int i=0; i<pixels; i++)      //Illuminate chase bar length as per 'pixels' parameter
    {
      if( i < strip.numPixels() )
        {
          strip.setPixelColor(i, colour);
        }
    }
  for( int i=pixels; i<strip.numPixels(); i++ )
    {
      strip.setPixelColor(i, bgcolour);  //Set remainder of pixels as bgcolour
    }
    
  strip.show();
  delay(hangtime);
  for(int i=0; i<strip.numPixels(); i++)       //Move bar from low to high pixel range by turning off bottom bar pixel and turning on bar top + 1
    {
      strip.setPixelColor(i, bgcolour);  //Turn off bottom most pixel as bgcolour
      if( (i+pixels) <= strip.numPixels() )
        {
          strip.setPixelColor(i+pixels, colour);
        }
      strip.show();
      delay(hangtime);
    }
    
  for (int i = 0; i < strip.numPixels(); i++)  //turn off all pixels when done
    {
      strip.setPixelColor(i, 0);    //set to black
    }
    
    
 
}

void chase(uint8_t hangtime, uint32_t colour)
{
  strip.setBrightness(BRIGHTNESS);
  for( uint8_t i=0; i<strip.numPixels(); i++)
    {
      strip.setPixelColor(i, colour);
      strip.show();
      delay(hangtime);
      strip.setPixelColor(i, 0);
    }
}




// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  strip.setBrightness(BRIGHTNESS);
  uint16_t i, j;

  for(j=0; j<256*1; j++) { // 1 cycle of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
  for (i=0; i<=strip.numPixels(); i++)  //turn off all pixels
    strip.setPixelColor(i, 0);
  strip.show();
  
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  strip.setBrightness(BRIGHTNESS);
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}


