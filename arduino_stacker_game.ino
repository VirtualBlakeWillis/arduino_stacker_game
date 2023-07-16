#include <Adafruit_LEDBackpack.h>

#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_GrayOLED.h>
#include <Adafruit_SPITFT_Macros.h>
#include <Adafruit_SPITFT.h>
#include <gfxfont.h>

#include <math.h>

#ifndef _BV
#define _BV(bit) (1<<(bit))
#endif


uint8_t counter = 0;

#define SIGNED_MAX(x) (~(-1 << (sizeof(x) * 8 - 1)))
uint8_t DELAY = 120; //"refresh rate" in ms


#define DELETE_LEFT(bit, height, count) (bit - (height - count))
#define ADD_RIGHT(bit, height, count) (bit + (height - count))

Adafruit_LEDBackpack matrix1 = Adafruit_LEDBackpack();
Adafruit_LEDBackpack matrix2 = Adafruit_LEDBackpack();
uint8_t height = 4;
uint8_t lost = 0;

int buttonPin = 10; //D9 or D10
int buttonRead;
void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  matrix1.begin(0x72);  // Initialize matrix1 with its assigned address
  matrix2.begin(0x70);  // Initialize matrix2 with its assigned address

  matrix1.setBrightness(5);
  matrix2.setBrightness(5);


  Serial.println("------------ Welcome to the Test ------------");
  randomSeed(analogRead(0));




  }

int row = 0;
void loop() {
   uint8_t bit = 0b10000000; // Starting bit pattern
   uint8_t temp = bit;
   uint8_t tail = 0b00000000;
   uint8_t head = 64;
   uint8_t len = 0;
   uint8_t previous_val = 0;

   for (uint8_t i = 0; i < ((7 + (height-1)) * 2); i++) {

      if (!digitalRead(buttonPin) == HIGH) {
        Serial.println("good shit");
        // exit out of function
        row = row + 1;
	      // Get a random number
	      int random_mult = random(4, 15);

	      // Print the random number
        delay(DELAY * random_mult);
        DELAY = DELAY * 0.94;
        Serial.println(DELAY);
        break;

      }
     if (i < (7+height)) 
     {
      if (i > 0)
      {
        /* bit shift once, fill in spaces below*/
        temp = temp + static_cast<uint8_t>(pow(2, i-1));
        if (i >= 3) {
          temp++;
        }

        /* remove last 1. keep # of lights on = height */
        if (i > height) 
        {
          if (tail >= 1)
          {
            tail = tail<<1;
            temp = temp - tail; // old method
          }
          else {
            temp = temp - 1;
            tail = 1;
          }
          // /* as bar hits left size, fix sign to correct position */
          if (temp > 128)
          {
            temp = temp - 128;
          }
        }
        // /* Switch sign from - to + when height reached*/
        if (i == height && temp > 128)
        {
          temp = temp - 128;
        }
      }
     } else {
      if (i == ((7+height)))
      {
        tail = 128;
      }
        // temp = temp - tail;

        if (i < ((((height + 7) * 2) - 1) - (height - 2))) {
          head = head>>1;
          temp = temp + head;

          if (temp > 128 && i > 13) { // i is comparing arbatrary number, i dont care to figure it out now.
            temp = temp - 128;
          }
          /* keep len at height, remove trailing light */
          if (len >= (height-1)) {
            tail = tail>>1;
            temp = temp - tail;
          }
          if (i >= 16) {
            temp = temp + 128;
          }
        }
      len++;
    }

    Serial.print("row :");
    Serial.println(row);
    if (row <= 7) {
    matrix1.displaybuffer[row] = temp;
    matrix1.writeDisplay(); // Update the display
    previous_val = matrix1.displaybuffer[row];
    } else {
    matrix2.displaybuffer[row - 8] = temp;
    matrix2.writeDisplay(); // Update the display
    previous_val = matrix1.displaybuffer[row - 8];

    }
    if (row == 3 && lost == 0) {
      height = height - 1;
      lost = lost + 1;
    }
        delay(DELAY); // Delay for 200 milliseconds    

   }
    if (row == 7 && lost == 1) {
      height = height - 1;
      lost = lost + 1;
    }
    if (row == 10 && lost == 2) {
      height = height - 1;
      lost = lost + 1;
    }
  }
    // temp = temp;
    // tail = temp;
    // uint8_t head = 128;
    // for (uint8_t x = (7 + height - 1); x > 1; x--) {
    //   if (digitalRead(buttonPin) == 0)
    //   {
    //     Serial.println("button Pressed!");
    //   }
    //   /* bit shift once, fill in spaces below*/
    //   tail = tail>>1;
    //   temp = temp + tail;
    //   if (x < ((height + 7 - 1) - (height - 2))) {
    //     head = head>>1;
    //     temp = temp - head;
    //   }
    //   if (x <= height && temp < 128) {
    //     temp = temp + 128;
    //   }
    //   matrix.displaybuffer[0] = temp; // Set the row with the current bit pattern in reverse order
    //   matrix.writeDisplay(); // Update the display
    //   delay(DELAY); // Delay for 200 milliseconds
    // }
    




