// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LIS3DH.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 13
#define NUMPIXELS 3

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

Adafruit_LIS3DH lis = Adafruit_LIS3DH();

void setup() {
  Serial.begin(9600);
  
  lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!

  lis.begin(0x18);
  pixels.begin();
}

void loop() {
  lis.read();
  sensors_event_t event; 
  lis.getEvent(&event);

  //finds magnitude of acceleration
  double accMag = sqrt(event.acceleration.x*event.acceleration.x + 
            event.acceleration.y*event.acceleration.y + 
            event.acceleration.z*event.acceleration.z);

  for(int i=0;i<NUMPIXELS;i++){
    if(accMag>10 || accMag<9.3)
       pixels.setPixelColor(i, pixels.Color(0,0,255));
    else
      pixels.setPixelColor(i,pixels.Color(255,0,255));
      
    pixels.show(); // This sends the updated pixel color to the hardware.
  }

  Serial.print("Mag:  ");Serial.print(accMag);
  Serial.println(" m/s^2 ");

  Serial.println();

  delay(1000);
}
