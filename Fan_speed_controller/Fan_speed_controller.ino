#include <TimerOne.h>           // Timer for encoder
#include <EEPROM.h>             // EEprom Lib
#include <avr/wdt.h>            // Watchdog Lib
#include <ClickEncoder.h>       // Rotery Encoder Lib
#include <LiquidCrystal_I2C.h>  // Lcd Display Lib


int on = HIGH;
int off = LOW;
int spinner[] = {'\\','|','/'};    // Spinner Array
int fanSpeed = 0;                  // Initial manual fanspeed
int eeAddress = 0;                 // Adress to start saving to EEprom
char spinnerSegment;
const byte fanRelay = 3;           // realy pin
int i = 0;
int fanMin = 0;
int fanMax = 255;
int tempMin = 0;
int tempMax = 30;
int autoFan;
int manualFan;
int currentTemp = 10;

int manualFanSpeed = 0;
int manMin = 0;
int manMax = 10;

boolean up = false;
boolean down = false;
boolean middle = false;
boolean ButReset = false;

ClickEncoder *encoder;
int16_t last, value;



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Millis declarations ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
unsigned long currentTime;
unsigned long previousTime = 0;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Lcd Display ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);      // Set the LCD I2C address
// set the LCD address to 0x3F or 0x27 depending what display using for a 16 chars 2 line display
// Set the pins on the I2C chip used for LCD connections:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Set Up ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void setup() {
  Serial.begin(9600);                       // initialise Serial monitor    
  lcd.begin(16, 2);                         // initialize the lcd for 16 chars 2 lines
  lcd.backlight();                          // Turns backlight LCD on
  pinMode(fanRelay, OUTPUT);                // sets the relay pin to outputs 
  digitalWrite(fanRelay, off);              // Set Inital pin status low
  EEPROM.get(0, fanSpeed);                  // Get inital fanSpeed from EEprom
  wdt_enable(WDTO_1S);                      // Enable watchdog and wait 1 seconds before reset
  
  // ------ SetUp encoder ------
  encoder = new ClickEncoder(A1, A0, A2);   // set analog channel 0,1,2 for use with the rotery encoder
  encoder->setAccelerationEnabled(false);   // disable encode acelleration
  Timer1.initialize(1000);                  // timer iterupt for the rotery encoder
  Timer1.attachInterrupt(timerIsr);
  last = encoder->getValue();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Loop ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void loop() {
  currentTime = millis();          // declare the current time is equal to millis
  wdt_reset();                     // Reset Watchdog and reset processor if crashed or inactive
  fanSpinner();
  fanControl();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Fan Control ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void fanControl(){
  if(autoFan){
    fanSpeed = map(currentTemp, tempMin, tempMax, fanMin, fanMax);  // Fan speed from temerature control
    analogWrite(fanRelay, fanSpeed);                                // control digital channel will the PWM value
  }
  if(manualFan){
    fanSpeed = map(manualFanSpeed, manMin, manMax, fanMin, fanMax); // Fan speed from manual control
    analogWrite(fanRelay, fanSpeed);
  }
 }

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Rotary Encoder ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void readRotaryEncoder()
{
  value += encoder->getValue();

  if (value / 4 > last) {
    last = value / 4;
    down = true;
    if (currentTime - previousTime >= 50) {
      currentTime = previousTime;
    }
  } else   if (value / 4 < last) {
    last = value / 4;
    up = true;
    if (currentTime - previousTime >= 50) {
      currentTime = previousTime;
    }
  }
}

void timerIsr() {
  encoder->service();
}

// Kick the dog if the reset is activated
void Reset() {
  if (ButReset) {
    ButReset = false;
    delay(2000);
  }
}


void fanSpinner(){
      if (currentTime - previousTime >= 70) {
        previousTime = currentTime;
        if(i <= 2){
           spinnerSegment = spinner[i];
           Serial.println(spinnerSegment);
            i++;
         }
         else{
            spinnerSegment = '-';
            Serial.println(spinnerSegment);
            i = 0;
          }
    }
  }
