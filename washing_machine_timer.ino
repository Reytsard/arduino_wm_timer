#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

//pins
const int setTimerButtonPin = 13;
const int startButtonPin = 12;

//relay pins
const int relayIn1Pin = 2;
int relay1State = LOW;
const int relayIn2Pin = 3;
int relay2State = LOW;
const unsigned long debounceDelay = 2;

//option tracking
bool isChangable = true;
bool isTimerStarted = false;

//set timer value
int timerButtonState;
int timerValue = 0;
int timerLastButtonState = LOW;
unsigned long lastDebounceTime = 0;

//start button
int startButtonState;
int startButtonLastState = LOW;
unsigned long startButtonLastDebounceTime = 0;

//timer
unsigned long countdownTimer = 0;

//test variables
unsigned long timer = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init();  // initialize the lcd
  lcd.init();
  // lcd.backlight();
  // lcd.setCursor(1, 0);
  // lcd.print("Timer:");
  // displayTimer(timerValue);

  pinMode(setTimerButtonPin, INPUT);
  pinMode(startButtonPin, INPUT);
  pinMode(relayIn1Pin, OUTPUT);
  timer = millis();
}

long duration = 5000;
int state = 0;
void loop() {
  
 

  

  
  
  


  // checkChangeTimerValue();
  // checkStartValue();

  if(isTimerStarted){
    startTimer();
  }
}

void startTimer() {
   long time = millis();

  if(time - timer >= duration){
    Serial.println("Timer Reached Duration");
    if(state == 1){
      state = 0;
      // digitalWrite(relayIn1Pin,LOW);
    }else if(state == 0){
      state = 1;
      // digitalWrite(relayIn1Pin,HIGH);
    }
    timer = time;
  }

  /*
    Create a stop here maybe 3 seconds
  */

  if(time - timer >= duration){
    Serial.println("Timer Reached Duration");
    if(state == 1){
      state = 0;
      // digitalWrite(relayIn1Pin,LOW);
    }else if(state == 0){
      state = 1;
      // digitalWrite(relayIn1Pin,HIGH);
    }
    timer = time;
  }
}

void checkChangeTimerValue() {
  // put your main code here, to run repeatedly:
  timerButtonState = digitalRead(setTimerButtonPin);

  //debounce
  if (timerButtonState != timerLastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) < debounceDelay) {
    if (timerButtonState != timerLastButtonState) {
      timerLastButtonState = timerButtonState;
    }
    if (timerLastButtonState == HIGH) {
      if (isChangable && !isTimerStarted) {
        Serial.println("Pressed");
        timerValue += 5;
        if (timerValue > 35) {
          clear2ndRowDisplay();
          timerValue = 0;
        }
        displayTimer(timerValue);
        // turnOnRelay();
     