#include <Adafruit_NeoPixel.h>

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>

#include <FastLED.h>
#include <Wire.h>

#include <avr/power.h>

#define PIN_A 4   
#define PIN_B 7
#define PIN_MATRIX 6
//#define BRIGHTNESS 10

//FastLED defines
#define NUM_STRIPS 2
#define NUM_LEDS_PER_STRIP 12
CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];


#define WIRE_ADDRESS 5     //I2C Address of this device

#define BOT_IDLE 0xa       //Robot idling - waiting for start or stopped
#define BOT_FORWARD 0xb    //Robot moving forward
#define BOT_BACKWARD 0xc   //Robot moving backward
#define BOT_LIFTTOTES 0xd  //Robot lifting totes
#define BOT_LIFTCAN 0xe    //Robot lifting garbage can
#define BOT_ARMS 0xf       //Robot change in arm state
#define BOT_UNLOAD 0x10    //Robot unloading
#define BOT_MESSAGE 0x11   //Robot display message

int PREVVAL = 0;



int CURRENT_ACTION = 0;    //Current action of robot - default as IDLE
int PULSE_STEP_SIZE = 1;  //Number of brightmess steps to increment by in pulseAll() function

//Define matrix object
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, PIN_MATRIX,
  NEO_MATRIX_BOTTOM     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);
  

void setup() {
 
  
  Wire.begin(WIRE_ADDRESS);        //Set I2C address of Arduino
  Wire.onReceive(receiveEvent);    //Set event to trigger when I2C data is received
  
  //LED strip on pin "A"
  FastLED.addLeds<NEOPIXEL, PIN_A>(leds[0], NUM_LEDS_PER_STRIP);

  //LED strip on pin "B"
  FastLED.addLeds<NEOPIXEL, PIN_B>(leds[1], NUM_LEDS_PER_STRIP);
  
  matrix.begin();                  //----Matrix setup parameters including brightness----
  matrix.setTextWrap(false);
  matrix.setBrightness(40);        //----------------------------------------------------  

  
}

//Matrix vars
int x    = matrix.width();
int pass = 0;


void loop() {
  
 //SWITCH logic to select current lighting sequence
 
 switch (CURRENT_ACTION) {

   case BOT_IDLE:
    pulseAll();
    break;
    
  case BOT_FORWARD:
    chaseblockbackground(10, CRGB(0, 255, 0), CRGB(255, 0,0), 8);
    break;
    
  case BOT_BACKWARD:
    chaseblock(10, CRGB(0, 255, 0),8);
    bar(60, CRGB(0,255,0));
    break;
    
  case BOT_LIFTTOTES:
    bar(NUM_LEDS_PER_STRIP, CRGB(random(0, 255),random(0, 255), random(0, 255)));
    break;
    
  case BOT_LIFTCAN:
    //statements
    pulseAll();
    break;
    
  case BOT_ARMS:
    //statements
    sparkle(5, CRGB(255, 255, 255));
    break;
    
  case BOT_UNLOAD:
    //statements
    rainbowCycle(0);
    break;
  case BOT_MESSAGE:
    displaymessage("Test 123 ");
    break;
    
  default:         //Run matrix message when no I2C input
    displaymessage("Test 123  ");
    BLINK(3, 10, CRGB(0,255,0));
    delay(200);
    chaseblockbackground(20, CRGB(0,255,0), CRGB(255,0, 0), 4);
    delay(200);
    chaseblock(20, CRGB(0, 255, 0),4);
    delay(200);
    bar(12, CRGB(random(0, 255),random(0, 255), random(0, 255)));
    delay(200);
    sparkle(10, CRGB(255, 255, 255));
    delay(200);
    pulseAll();
    delay(200);
    rainbowCycle(0);
    delay(200);
    chase(20, CRGB(255,255,0), CRGB(0,0,255));
    delay(200);
    break;
  
  }
  
}

//Event called upon I2C receive data
void receiveEvent(int)    //Event run when I2C data is received
{
 int recval = 0;
 while(Wire.available())
  {
    
    recval = Wire.read();
    if( recval != 0 )      //Strip out 0x0 secondary data sent from RoboRio
      {
        if (recval != PREVVAL)
        {
          PREVVAL = recval;
          CURRENT_ACTION = recval;    // receive current state from RoboRio
          Serial.println(CURRENT_ACTION);
        }
        
       }
    
  }

}

void displaymessage(String instring)   //Display text to LED matrix
{
  int count = 0;
  int numshifts = (instring.length() *6);   // Total shifts needed
  matrix.setTextColor(matrix.Color(0,255,0));
  while( --x > -numshifts )
  {
    matrix.fillScreen(0);
    matrix.setCursor(x, 0);
    matrix.print(instring);
    
    //if(--x < -numshifts) {
     // x = matrix.width();
      //if(++pass >= 3) pass = 0;
    //}
  matrix.show();
  count++;
  delay(25);
  }
  x = matrix.width();  //Reset global X to width of matrix so we can shift the width of the text plus the width of the matrix on next call
}
    
 
void pulseAll()        //Slowly pulse all LEDs 
{
  for( int intensity = 0; intensity <=255; intensity += PULSE_STEP_SIZE)    //intensity min to max
    {
             
        for (int i=0; i <=NUM_LEDS_PER_STRIP; i++)          //   *******!!!!!!Use strip.numpixels() for all LEDs!!!!!!!!*********
        {
           leds[0][i] = CRGB(intensity/2, intensity/2, intensity/2);
           leds[1][i] = CRGB(intensity/2, intensity/2, intensity/2);
           
        }  
        FastLED.show();
    }
   
  for( int intensity = 255 ; intensity >= 0; intensity -= PULSE_STEP_SIZE)    //intensity max to min
    {
      
       for (int i=0; i <=NUM_LEDS_PER_STRIP; i++)
        {
           leds[0][i] = CRGB(intensity/2, intensity/2, intensity/2);
           leds[1][i] = CRGB(intensity/2, intensity/2, intensity/2);
           
        }  
       FastLED.show();
    }  
   
  
}


void BLINK(int numblinks, int pixelnum, uint32_t colour)
{
    
  for (int i=0; i <=numblinks; i++)
    {
        leds[0][pixelnum] = CRGB::Green;
        leds[1][pixelnum] = CRGB::Green;
        FastLED.show();
        delay(100);
        leds[0][pixelnum] = CRGB::Black;
        leds[1][pixelnum] = CRGB::Black;
        FastLED.show();
        delay(100);
    } 
}



void bar(int barsize, CRGB colour)     //Draw a bar of barsize and then undraw it
{
  int counter;
  
  for (counter=0; counter <barsize; counter++)
  {
    leds[0][counter] = colour;
    leds[1][counter] = colour;
    FastLED.show();
    delay(8);
    Serial.println(counter,10);
  }
  delay(20);
  for(counter=counter; counter >=0; counter--)
  {
    leds[0][counter] = CRGB::Black;
    leds[1][counter] = CRGB::Black;
    FastLED.show();
    delay(8);
    Serial.println(counter,10);
  }
  delay(100);
}


// Random Pixel sparkle
void sparkle(uint8_t hangtime, CRGB colour)
{
  long randnum;     //Random pixel for strip 1
  long randnumB;    //Randon pixel for strip 2

  randnum = random(0, NUM_LEDS_PER_STRIP);
  randnumB = random(0, NUM_LEDS_PER_STRIP);
  
  leds[0][randnum] = colour;    //Turn on random pixel and pixel+1 on both strips
  leds[0][randnum+1] = colour;
  leds[1][randnum] = colour;
  leds[1][randnum+1] = colour;
  FastLED.show();
     
  delay(hangtime);      //Wait and turn pixels off
  
  leds[0][randnum] = CRGB::Black;    //Turn on random pixel and pixel+1 on both strips
  leds[0][randnum+1] = CRGB::Black;
  leds[1][randnum] = CRGB::Black;
  leds[1][randnum+1] = CRGB::Black;
  FastLED.show();
    
  delay(hangtime);
}

//Chaser bar with black background
void chaseblock(uint8_t hangtime, CRGB colour, uint8_t pixels)
{
    for(int i=0; i<pixels; i++)      //Illuminate chase bar length as per 'pixels' parameter
    {
      if( i < NUM_LEDS_PER_STRIP )
        {
          leds[0][i] = colour;
          leds[1][i] = colour;
          FastLED.show();
        }
    }
    
  delay(hangtime);
  for(int i=0; i < NUM_LEDS_PER_STRIP; i++)       //Move bar from low to high pixel range by turning off bottom bar pixel and turning on bar top + 1
    {
      leds[0][i] = CRGB::Black;
      leds[1][i] = CRGB::Black;  //Set bottom most pixel as backgroud colour
      
      if( (i+pixels) <= NUM_LEDS_PER_STRIP )    //Check if we are within the strip
        {
          leds[0][i+pixels] = colour;
          leds[1][i+pixels] = colour;
        }
      FastLED.show();
      delay(hangtime);
    }
    
  for (int i = 0; i < NUM_LEDS_PER_STRIP; i++)  //turn off all pixels when done
    {
      leds[0][i] = CRGB::Black;    //set to black
      leds[1][i] = CRGB::Black;
      
    }
  FastLED.show();
  
}

//Chaser bar with background
void chaseblockbackground(uint8_t hangtime, CRGB colour, CRGB bgcolour, uint8_t pixels)
{
  for(int i=0; i<pixels; i++)      //Illuminate chase bar length as per 'pixels' parameter
    {
      if( i < NUM_LEDS_PER_STRIP )
        {
          leds[0][i] = colour;
          leds[1][i] = colour;
          FastLED.show();
        }
    }
  for( int i=pixels; i< NUM_LEDS_PER_STRIP ; i++ )
    {
      leds[0][i] = bgcolour;        //Set remainder of pixels as bgcolour
      leds[1][i] = bgcolour;
      FastLED.show();
      
    }
    
  delay(hangtime);
  for(int i=0; i < NUM_LEDS_PER_STRIP; i++)       //Move bar from low to high pixel range by turning off bottom bar pixel and turning on bar top + 1
    {
      leds[0][i] = bgcolour;
      leds[1][i] = bgcolour;  //Set bottom most pixel as backgroud colour
      
      if( (i+pixels) <= NUM_LEDS_PER_STRIP )    //Check if we are within the strip
        {
          leds[0][i+pixels] = colour;
          leds[1][i+pixels] = colour;
        }
      FastLED.show();
      delay(hangtime);
    }
    
  for (int i = 0; i < NUM_LEDS_PER_STRIP; i++)  //turn off all pixels when done
    {
      leds[0][i] = CRGB::Black;    //set to black
      leds[1][i] = CRGB::Black;
      
    }
  FastLED.show();
    
 
}

//Chase individual pixel entire length of strip against a background
void chase(uint8_t hangtime, CRGB colour, CRGB bgcolour)
{
   
  for( int i=0; i<NUM_LEDS_PER_STRIP; i++ )    //Set background colour
    {
      leds[0][i] = bgcolour;
      leds[1][i] = bgcolour;
      
    }
    FastLED.show();
  
  for( int i=0; i<NUM_LEDS_PER_STRIP; i++)
    {
      leds[0][i] = colour;
      leds[1][i] = colour;
      FastLED.show();
      delay(hangtime);
      leds[0][i] = bgcolour;
      leds[1][i] = bgcolour;
      FastLED.show();
      delay(hangtime);
    }
  for( int i=0; i<NUM_LEDS_PER_STRIP; i++ )    //Turn off all pixels
    {
      leds[0][i] = CRGB::Black;
      leds[1][i] = CRGB::Black;
      
    }
    FastLED.show();
}

// Cycle rainbow across strip
void rainbowCycle(uint8_t wait) {
    
  uint16_t i, j;

  for(j=0; j<256*1; j++) { // 1 cycle of all colors on wheel
    for(i=0; i< NUM_LEDS_PER_STRIP; i++) {
      leds[0][i] = Wheel(((i * 256 / NUM_LEDS_PER_STRIP) + j) & 255);
      leds[1][i] = Wheel(((i * 256 / NUM_LEDS_PER_STRIP) + j) & 255);
    }
    FastLED.show();
    delay(wait);
  }
  
  for (i=0; i<=NUM_LEDS_PER_STRIP; i++)    //turn off all pixels
    {
      leds[0][i] = CRGB::Black;
      leds[1][i] = CRGB::Black;
      FastLED.show();
    }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
CRGB Wheel(byte WheelPos) {
   
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return CRGB(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return CRGB(0, WheelPos * 3, 255 - WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return CRGB(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}







