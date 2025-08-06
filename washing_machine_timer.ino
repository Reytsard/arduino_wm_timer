/**
  Problem: Washing Machine Timer Replaced With Arduino timer and relays

  The washing machine has a knob that needs to be turned to set its minutes. The washing machine turns CW and CCW to turn the machine.
  The mechanical washing machine timer has a relay that turns on and off to make the machine move at a certain direction.

  Pseudo code
  1. set constant variables, delayBetweenRelays, durationPerSpin. Set variables like isWashing, isChangable
  2. There is a button that can be pressed to change the time of the washing machine, intervals are in 5 mins.
      This Button cannot be pressed when isWashing is true. This prevents the user to add/change time while it is turning.
  3. There is a button that can be pressed to start the washing, this will not trigger if the input for the timer is 0. 
      This button can be pressed to stop the washing of the machine, it will disable both relays making it not spin in any way.
  4. When the washing has started, the first relay will be activated making the machine spin cw, after the duration per spin, 
      the delayBetweenRelays will activate, this will ensure that the machine can stop after a certain time before turning the other way, CCW.

  Modules needed for the arduino project
  1. 1 Arduino Uno/Micro controller
  2. Jumper Wires
  3. 2 10k ohm resistor. (For the buttons)
  4. 2 Channel 5v relay
  5. IC2 Liquid Display

  Libraries used
  1. LiquidCrystal_I2C
  2. Bounce2
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Bounce2.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int startButtonPin = 2;
const int editButtonPin = 3;
const int DELAYBETWEENRELAYS = 4000; //4s
const int DURATIONPERSPIN = 5000; //5s

bool isWashing = false;
bool isChangable = true;
int minutesValue = 0;
unsigned long timeRemaining = 0;

Bounce startButtonDebouncer = Bounce();
Bounce editButtonDebouncer = Bounce();

void setup() {
  Serial.begin(9600);

  pinMode(startButtonPin, INPUT_PULLUP);
  pinMode(editButtonPin, INPUT_PULLUP);

  startButtonDebouncer.attach(startButtonPin);
  startButtonDebouncer.interval(25);

  editButtonDebouncer.attach(editButtonPin);
  editButtonDebouncer.interval(25);


  lcd.init();  // initialize the lcd
  // lcd.backlight();
  // lcd.setCursor(1, 0);
  // lcd.print("Timer:");
  // displayTimer(timerValue);

}

void loop() {
  startButtonDebouncer.update();
  editButtonDebouncer.update();

  if(startButtonDebouncer.fell()){
    //start has been pressed
    if(minutesValue !== 0){
      isWashing = true;
      isChangable = false;
    }else{
      isWashing = false;
      isChangable = true;
    }
  }

  if(editButtonDebouncer.fell()){
    //edit button has been pressed
    if(isChangable){
      minutesValue += 5;
      if(minutesValue > 35){
        minutesValue = 0;
      }
    }
  }

}