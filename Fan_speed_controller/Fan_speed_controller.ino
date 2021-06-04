#include <DHT.h>                // Temp Humidity Lib
#include <TimerOne.h>           // Timer for encoder
#include <EEPROM.h>             // EEprom Lib
#include <Wire.h>               // I2c enable Lib
#include <avr/wdt.h>            // Watchdog Lib
#include <ClickEncoder.h>       // Rotery Encoder Lib
#include <LiquidCrystal_I2C.h>  // Lcd Display Lib
#include <MapFloat.h>           // Helpful implimetation of floating point ints in maps

int On = HIGH;
int Off = LOW;
int eeAddress = 0;              // Address to start saving to EEprom
const byte PWMoutput = 3;       // PWM output pin to fan control realy

int fanMin = 0;
int fanMax = 255;
int tempMin = 0;
int tempMax = 30;
int humMin = 50;
int humMax = 0;
byte manMin = 0;
byte manMax = 100;
float fanInVolts = 0;
int fanPercentage = 0;
float fanSpeed = 0;
int currentMode = 0;            // depending on the currentMode the voltage and % menue can use this get correct data
int manualFanSpeed = 0;         // Initial manual fanspeed
int shutDown = 0;
//int acFail = 0;                 // This is set to 1 when the controller is put in standby, it holds control in standby incase of ac power falure
const byte ledR = 10;
int standBySwitch = 7;
int standByValue = 0;

int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Menu items and encoder control  ~~~~~~~~~~~~~~~~~~~~~~~~~~
int menuitem = 1;
int page = 1;
int lastMenuItem = 1;
int enter = 0;
int menuEnter = 0;

boolean up = false;
boolean down = false;
boolean middle = false;
boolean button = false;

ClickEncoder *encoder;
int16_t last, value;
int marker = 0;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Air Temperature & Humidity sensor ~~~~~~~~~~~~~~~~~~~~~~~~~

#define DHTPIN 6             // what pin we're connected to
#define DHTTYPE DHT22        // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE);    // Initialize DHT sensor
// int chk;
float hum;                   //Stores humidity value
float temp;                  //Stores temperature value

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Millis declarations ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
unsigned long currentTime;
unsigned long previousTime = 0;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Lcd Display ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);      // Set the LCD I2C address
// set the LCD address to 0x3F or 0x27 depending what display using for a 16 chars 2 line display
// Set the pins on the I2C chip used for LCD connections:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Set Up ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void setup() {
  Serial.begin(9600);                       // initialise Serial monitor
  Wire.begin();                             // Begin I2c on arduino nano
  lcd.begin(16, 2);                         // initialize the lcd for 16 chars 2 lines
  lcd.backlight();                          // Turns backlight LCD on
  dht.begin();                              // temp humid sensor

  pinMode(standBySwitch, INPUT);     // sets the switch to an input
//  digitalWrite(standBySwitch, Off);         // Set switch status low
  pinMode(PWMoutput, OUTPUT);               // sets the relay pin to outputs
  digitalWrite(PWMoutput, Off);             // Set Inital pin status low
  EEPROM.get(0, manualFanSpeed);            // Get inital fanSpeed from EEprom
  EEPROM.get(8, tempMin);                   // Get inital min temp
  EEPROM.get(16, humMax);                   // Get inital hum max
  EEPROM.get(24, currentMode);              // Get inital mode (0 = Manual)(1 = Temp control)(2 = Hum control)
  EEPROM.get(32, fanMax);                   // Get the fan max in PWM 255 is the total max
//  EEPROM.get(40, shutDown);                 // Get the Shutdown Status incase or pwer falure

  pinMode(ledR, OUTPUT);                    // Control standby light
  digitalWrite(ledR, Off);                  // truen the led initially off

  sensors();                                // Setup and collect initial temp and humidity
  startUpScreen();                          // Initising screen

  wdt_enable(WDTO_1S);                      // Enable watchdog and wait 1 seconds before reset

  // ------ SetUp encoder ------
  encoder = new ClickEncoder(A1, A0, A2);   // set analog channel 0,1,2 for use with the rotery encoder
  encoder->setAccelerationEnabled(false);   // disable encode acelleration
  Timer1.initialize(1000);                  // timer iterupt for the rotery encoder
  Timer1.attachInterrupt(timerIsr);
  last = encoder->getValue();

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Loop ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void loop() {
  wdt_reset();                     // Reset Watchdog and reset processor if crashed or inactive
  currentTime = millis();          // declare the current time is equal to millis
  if (shutDown == 0){
    fanControl();                    // Adjust PWM output to fans controller
    readRotaryEncoder();             // Check status of rotery encoder
    encoderControl();                // set and check what the encoder button status are
    buttonPressed();                 // Is button pressed
    timerIsr();                      // timerIsr for rotery encoder
    manualReset();                   // If button is held down reset
    sensors();                       // Read Temp and Humidity sensors
    updatedisplay();                 // Lcd screen transitions
    deBug();                         // enable Debug function
  }
  standBy();                       // Set stand by mode
  
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Fan Control ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void fanControl() {
  if (currentMode == 0) {
    fanSpeed = map(manualFanSpeed, manMin, manMax, fanMin, fanMax); // Fan speed from manual control
    controlFanSpeed();
  }
  if (currentMode == 1) {
    fanSpeed = map(temp, tempMin, tempMax, fanMin, fanMax); // Fan speed Auto Temp control
    controlFanSpeed();
  }
  if (currentMode == 2) {
    fanSpeed = map(hum, humMin, humMax, fanMin, fanMax);        // Fan speed Auto Humid control
    controlFanSpeed();
  }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# Fan Speed Control ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void controlFanSpeed() {
  fanInVolts = fanSpeed * (5.0 / 255);                    // Estimated voltage output of PWM pin
//  fanPercentage = map(fanSpeed, 0, 255, 0, 100);          // fan speed in %
  fanPercentage = map(fanSpeed, 0, fanMax, 0, 100);    // fan speed in %               // Check this works~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  analogWrite(PWMoutput, fanSpeed);                       // Control PWM pin
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Temp Humid Sensors ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void sensors() {
  hum = dht.readHumidity();                               // Get current Humidity
  temp = dht.readTemperature();                           // Get current Temperature
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Watchdog overide ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void manualReset() {                  // Kick the watchdog if the reset is activated
  if (button) {
    button = false;
    delay(2000);
  }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Shutdown/Standby ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void standBy() {  
  
  int reading = digitalRead(standBySwitch);
  if(reading != lastButtonState){
    lastDebounceTime = millis();
    }

  if((millis() - lastDebounceTime) > debounceDelay){
     if (reading != buttonState) {
      buttonState = reading;
     
     if(buttonState == HIGH){
       Serial.println("Stand By ON");
       lcd.noBacklight();
       digitalWrite(ledR, On);
       digitalWrite(PWMoutput, Off);
       shutDown = 1;
       lcd.flush();
       }
     else{
        Serial.println("StandBy OFF");
        delay(2000);
        }
     }
    }
     lastButtonState = reading;
} 

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  Write to EEPROM  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/* This function adds the variables to EEprom, using this method only allows data to be written to memory 
   if it has changed else it get ignored*/
void writeToEEprom() {
  Serial.print("Wrtiting to EEprom");
  EEPROM.put(0, manualFanSpeed);    // Write data to eeprom 
  EEPROM.put(8, tempMin);
  EEPROM.put(16, humMax);
  EEPROM.put(24, currentMode);
  EEPROM.put(32, fanMax);
}
