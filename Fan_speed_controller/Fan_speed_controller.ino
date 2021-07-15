
#include <megaAVR_ISR_Timer.h>

#include <DFRobot_SHT3x.h>      // Temperature Humidity Sensor
//#include <TimerOne.h>           // Timer for encoder
#include <EEPROM.h>             // EEprom Lib
#include <Wire.h>               // I2c enable Lib
#include <avr/wdt.h>            // Watchdog Lib
#include <ClickEncoder.h>       // Rotery Encoder Lib
#include <LiquidCrystal_I2C.h>  // Lcd Display Lib

#define USE_TIMER_1     true
#define USING_16MHZ     true
#include <megaAVR_TimerInterrupt.h>

String SoftwareVersion = "   Site-V1.00   ";
int On = HIGH;
int Off = LOW;
int eeAddress = 0;              // Address to start saving to EEprom
const byte PWMoutput = 3;       // PWM output pin to fan control realy

int fanMin = 0;
int fanMax = 255;
int tempMin = 0;
int tempMax = 30;
int humMin = 0;
int humMax = 100;
byte manMin = 0;
byte manMax = 100;
float fanInVolts = 0;
int fanPercentage = 0;
float fanSpeed = 0;
int currentMode = 0;            // depending on the currentMode the voltage and % menu can use this get correct data
int manualFanSpeed = 0;         // Initial manual fanspeed
int shutDown = 0;
const byte standBySwitch = 7;
int standByValue = 0;
int buttonState;               // the current reading from the standby input pin
int lastButtonState = LOW;     // the previous reading from the standby input pin

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

DFRobot_SHT3x sht3x(&Wire,/*address=*/0x44,/*RST=*/4); // set the temp/hum sensor to I2C address to 0x45
float temp;                    //Stores temperature value
float hum;                     //Stores humidity value


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Millis declarations ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
unsigned long currentTime;
unsigned long previousTime = 0;
unsigned long lastDebounceTime = 0;  // the last time the standby pin was toggled
unsigned long debounceDelay = 50;    // the debounce time for standby pin

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Lcd Display ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);      // Set the LCD I2C address
// set the LCD address to 0x3F or 0x27 depending what display using for a 16 chars 2 line display
// Set the pins on the I2C chip used for LCD connections:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Set Up ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void setup() {
  // ----- Initialise devices -------
  Serial.begin(9600);                       // initialise Serial monitor
  Wire.begin();                             // Begin I2c on arduino nano
  lcd.begin(16, 2);                         // initialize the lcd for 16 chars 2 lines
  lcd.backlight();                          // Turns backlight LCD on                         
  sht3x.begin();                            // Initialise the Temp Humid sensor and diaplay the serial number via Serial
  sensors();                                // Collect initial temp and humidity

  // ---- Setup I/O and set status ----
  pinMode(standBySwitch, INPUT);            // sets the switch to an input
  pinMode(PWMoutput, OUTPUT);               // sets the relay pin to outputs
  digitalWrite(PWMoutput, Off);             // Set Inital pin status low

  // ---- Get saves data from memory --
  EEPROM.get(0, manualFanSpeed);            // Get inital fanSpeed from EEprom
  EEPROM.get(8, tempMin);                   // Get inital min temp
  EEPROM.get(12, tempMax);                  // Get inital max temp
  EEPROM.get(16, humMax);                   // Get inital hum max
  EEPROM.get(20, humMin);                   // Get inital hum max
  EEPROM.get(24, currentMode);              // Get inital mode (0 = Manual)(1 = Temp control)(2 = Hum control)
  EEPROM.get(32, fanMax);                   // Get the fan max in PWM 255 is the total max
  EEPROM.get(40, fanMin);                   // Get the fan min

  // ------ SetUp encoder ------
  encoder = new ClickEncoder(A0, A1, A2);   // set analog channel 0,1,2 for use with the rotery encoder
  encoder->setAccelerationEnabled(false);   // disable encode acelleration
  ITimer1.init();                  // timer iterupt for the rotery encoder
  ITimer1.attachInterrupt(1000, timerIsr);
  last = encoder->getValue();

  // -- Display startup screens -
  startUpScreen();                          // Initising screen

  // ---- Enable the watchdog ---
  wdt_enable(WDTO_1S);                      // Enable watchdog and wait 1 seconds before reset
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Loop ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void loop() {
  wdt_reset();                     // Reset Watchdog and reset processor if crashed or inactive
  currentTime = millis();          // declare the current time is equal to millis
  if (shutDown == 0) {
    sensors();                     // Read Temp and Humidity sensors
    fanControl();                  // Adjust PWM output to fans controller
    readRotaryEncoder();           // Check status of rotery encoder
    encoderControl();              // set and check what the encoder button status are
    buttonPressed();               // Is button pressed
    timerIsr();                    // timerIsr for rotery encoder
    updatedisplay();               // Lcd screen transitions
    deBug();                       // enable Debug function
  }
  manualReset();                   // If button is held down reset
  standBy();                       // Set stand by mode
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Fan Control ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void fanControl() {
  if (currentMode == 0) {
    fanSpeed = map(manualFanSpeed, manMin, manMax, fanMin, fanMax); // Fan speed from manual control
    controlFanSpeed();
  }
  if (currentMode == 1) {
    fanSpeed = map(temp, tempMin, tempMax, fanMin, fanMax);         // Fan speed Auto Temp control
    controlFanSpeed();
  }
  if (currentMode == 2) {
    fanSpeed = map(hum, humMin, humMax, fanMin, fanMax);            // Fan speed Auto Humid control
    controlFanSpeed();
  }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Fan Speed Control ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void controlFanSpeed() {
  fanInVolts = fanSpeed * (5.0 / 255);                    // Estimated voltage output of PWM pin
   if (fanInVolts <= 0) {
    fanInVolts = 0;
  }
  fanPercentage = map(fanSpeed, fanMin, fanMax, 0, 100);  // fan speed in %
  if (fanPercentage <= 0) {
    fanPercentage = 0;
  }
  analogWrite(PWMoutput, fanSpeed);                       // Control PWM pin
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Get Temp Humid Data ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void sensors() {
  temp = sht3x.getTemperatureC();                       // Get current Temperature
  hum = sht3x.getHumidityRH();                          // Get current Humidity
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Watchdog overide ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void manualReset() {                  // Kick the watchdog if the reset is held down to activated
  if (button) {
    button = false;
    delay(2000);
  }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Shutdown/Standby ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void standBy() {
  /*
    This function also uses button debounce to steady the standby button.
  */
  int standBySwitchValue = digitalRead(standBySwitch);
  if (standBySwitchValue != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (standBySwitchValue != buttonState) {
      buttonState = standBySwitchValue;

      if (buttonState == HIGH) {
        lcd.noBacklight();
        digitalWrite(PWMoutput, Off);
        shutDown = 1;
        lcd.clear();
        Wire.flush();
      }
      else {
        delay(1500);
      }
    }
  }
  lastButtonState = standBySwitchValue;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  Write to EEPROM  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/*
   This function adds the variables to EEprom, using the (put) method only allows data to be written to memory
   if it has changed else it get ignored.
*/
void writeToEEprom() {
  EEPROM.put(0, manualFanSpeed);    // Write data to eeprom
  EEPROM.put(8, tempMin);
  EEPROM.put(12, tempMax);
  EEPROM.put(16, humMax);
  EEPROM.put(20, humMin);
  EEPROM.put(24, currentMode);
  EEPROM.put(32, fanMax);
  EEPROM.put(40, fanMin);
}
