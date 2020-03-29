#define RED_LED 0
#define GREEN_LED 5
#define BLUE_LED 4

/*
 * Copyright (c) 2015, circuits4you.com
 * All rights reserved.
/* Generates PWM on Internal LED Pin GPIO 2 of ESP8266*/
 
#include <ESP8266WiFi.h>
#include <stdio.h>

#define LED 13
 
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

void PWM_demo(int led_gpio) {
  //PWM Value varries from 0 to 1023  
  Serial.println("10 % PWM");
  analogWrite(led_gpio,102);
  delay(2000);
 
  Serial.println("20 % PWM");
  analogWrite(led_gpio,205);
  delay(2000);
 
  Serial.println("40 % PWM");
  analogWrite(led_gpio,410);
  delay(2000);
 
  Serial.println("70 % PWM");
  analogWrite(led_gpio,714);
  delay(2000);
 
  Serial.println("100 % PWM");
  analogWrite(led_gpio,1024);
  delay(2000);
}

//=======================================================================
//                    Power on setup
//=======================================================================
void setup() {
  Serial.begin(115200);
  pinMode(LED,OUTPUT);
}
 
//=======================================================================
//                    Main Program Loop
//=======================================================================
void loop() {
  PWM_demo(RED_LED);
  PWM_demo(GREEN_LED);
  PWM_demo(BLUE_LED);
    
  //Continuous Fading
  Serial.println("Fadding Started");
  while(1)
  {
    // set the brightness of pin 9:
    analogWrite(LED, brightness);
  
    // change the brightness for next time through the loop:
    brightness = brightness + fadeAmount;
  
    // reverse the direction of the fading at the ends of the fade:
    if (brightness <= 0 || brightness >= 1023) {
      fadeAmount = -fadeAmount;
    }
    // wait for 30 milliseconds to see the dimming effect
    delay(10);
  }
}
