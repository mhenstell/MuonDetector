#include "LedControl.h"
#include <EEPROM.h>

int anode1 = 4;           // the pin that the LED is attached to
int anode2 = 9;
int anode3 = 10;

int level = 150;    // how bright the LED is

int led = 11;
int button_led = 12;
int button_switch = 14;

volatile unsigned int count = 0;
volatile long lastMuon = 0;

int nums[4];

boolean buttonState = LOW;
boolean lastButtonState = HIGH;

int buttonLedLevel = 0;
int buttonLedStep = 1;

LedControl lc=LedControl(0,1,2,1);

void setup()  { 

  int a = EEPROM.read(0);
  int b = EEPROM.read(1);

  count = a << 8;
  count |= b;

  pinMode(led, OUTPUT);
  pinMode(button_led, OUTPUT);
  pinMode(button_switch, INPUT);
  pinMode(anode1, OUTPUT);
  pinMode(anode2, OUTPUT);
  pinMode(anode3, OUTPUT);
  pinMode(6, INPUT);

  digitalWrite(button_switch, HIGH);

  lc.shutdown(0,true);
  lc.setIntensity(0,0);
  lc.clearDisplay(0);

  Serial.begin(115200);
  Serial.println("Hello, world.");

  attachInterrupt(1, blink, RISING);



} 


void readButton() {
  buttonState = digitalRead(button_switch);
  if (lastButtonState != buttonState) {
    lc.clearDisplay(0);
    lastButtonState = buttonState; 
    
    if (buttonState == LOW) {

      analogWrite(button_led, 255);
      
      lc.shutdown(0, false);

      lc.setRow(0,0,B01011011);
      lc.setRow(0,1,B00011100);
      lc.setChar(0,2,'p',false);
      
      for (int x=0; x < 9; x++) {
        lc.setIntensity(0,x); 
        delay(300);
      }
      lc.clearDisplay(0);


      analogWrite(anode1, level); 
      analogWrite(anode2, level); 
      analogWrite(anode3, level); 

      sei(); 

    } 
    else {

      cli();

      lc.setRow(0,1, B00111011);
      lc.setChar(0,2,'e',false);
      delay(3000);
      for (int x=8; x > 0; x--) {
        lc.setIntensity(0,x); 
        delay(250);
      }
      lc.clearDisplay(0);
      lc.shutdown(0, true);

      analogWrite(anode1, 0); 
      analogWrite(anode2, 0); 
      analogWrite(anode3, 0);

    }
  }
}

void loop()  { 

  readButton();
  
  while (buttonState == LOW) {
    
    long num = count;

    nums[0] = num / 1000;
    num = num - (nums[0] * 1000);

    nums[1] = num / 100;
    num = num - (nums[1] * 100);

    nums[2] = num / 10;
    num = num - (nums[2] * 10);

    nums[3] = num;


    if (nums[0] == 0) {

      lc.setRow(0, 0, B00000000);

      if (nums[1] == 0) {

        lc.setRow(0, 1, B00000000);

        if (nums[2] == 0) {

          lc.setRow(0, 2, B0000000);

        } 
        else lc.setDigit(0, 2, nums[2], false);
      } 
      else {
        lc.setDigit(0, 1, nums[1], false);
        lc.setDigit(0, 2, nums[2], false);
      }
    } 
    else {
      lc.setDigit(0, 0, nums[0], false);
      lc.setDigit(0, 1, nums[1], false);
      lc.setDigit(0, 2, nums[2], false);
    }

    lc.setDigit(0, 3, nums[3], false);

    readButton();
    checkSerial();

  }

  while (buttonState == HIGH) {

    buttonLedLevel += buttonLedStep;

    if (buttonLedLevel == 150 && buttonLedStep > 0) {
      buttonLedStep = -buttonLedStep; 
    } 
    else if (buttonLedLevel == 0 && buttonLedStep < 0) {
      buttonLedStep = -buttonLedStep; 
    }

    analogWrite(button_led, buttonLedLevel);

    if (buttonLedLevel > 30) delay(20);
    else delay(80);

    readButton();
    checkSerial();
  }
}

void checkSerial() {
  if (Serial.available() > 0) {
    char incoming = Serial.read();
    if (incoming == 'r') {
      count = 0; 
      EEPROM.write(0, (byte)count >> 8);
      EEPROM.write(1, (byte)count);
    }
  }
}

void blink() {
  cli();

  digitalWrite(led, HIGH);
  delay(1);
  digitalWrite(led, LOW);
  delay(1);

  if (millis() - lastMuon > 5) {
    count += 1;
    if (count > 9999) count = 0;
    lastMuon = millis();

    EEPROM.write(0, (byte)count >> 8);
    EEPROM.write(1, (byte)count);

    Serial.print('m');

    //    lc.setRow(0,0,B10000000);
    //    lc.setRow(0,1,B10000000);
    //    lc.setRow(0,2,B10000000);
    //    lc.setRow(0,3,B10000000);
    delay(1);
  }

  sei();
}

