#include <megaAVR_ISR_Timer.h>      // Timer Lib for rotary encoder         
#include <BB_Adafruit_SHT31.h>      // Temperature Humidity Sensor
#include <EEPROM.h>                 // EEprom Lib
#include <Wire.h>                   // I2c enable Lib
#include <avr/wdt.h>                // Watchdog Lib
#include <ClickEncoder.h>           // Rotery Encoder Lib
#include <LiquidCrystal_I2C.h>      // Lcd Display Lib
#include <WiFiNINA.h>               // Lib to activate the Wifi
#include <MQTT.h>                   // Access to MQTT service
#include <SPI.h>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Define WiFi & Mqtt Settings  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define WIFI_NAME "EE-Hub-St62"
#define WIFI_PASSWORD "SHIP-sit-ahead"
#define MQTT_HOST "192.168.1.88"
#define PUBLISH_PATH "AVfanControl/"
#define SUBSCRIBE_PATH "AVfanControl"
#define SUBSCRIBE_PATH2 "avFanManual"
#define DEVICE_NAME "Fan Speed Control"
#define LOCATION "AvonVally"
int status = WL_IDLE_STATUS;
MQTTClient mqtt_client;
WiFiClient www_client;
long last_connection_attempt = 0;

//~~~~~~~~~ Define Timers and timer Clock refquency before megaAVR_TimerInterrupt.h  ~~~~~~~~~~
#define USE_TIMER_1     true        // Setup using Timer1
#define USING_16MHZ     true        // Set clock frequency for Timer1
#include <megaAVR_TimerInterrupt.h> //Interupt Lib

String SoftwareVersion = " Site-V1.25MQTT ";
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
int isWifiConnectedCounter = 0;
int isMQTTConnectedCounter = 0;
int mqttNotConnected = 0;

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
int last, value;
int marker = 0;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Air Temperature & Humidity sensor ~~~~~~~~~~~~~~~~~~~~~~~~~
BB_Adafruit_SHT31 sht31 = BB_Adafruit_SHT31();  // declare the sensor function
int SHT31_Address = 0x44;                       // Set to 0x45 for alternate i2c address
float temp;                                     //Stores temperature value as a floating point integer
float hum;                                      //Stores humidity value as a floating point integer

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Millis declarations ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
unsigned long currentTime;
unsigned long previousTime = 0;
unsigned long prevTime = 0;
unsigned long prevTime2 =0;
unsigned long prevTime3 =0;
unsigned long lastDebounceTime = 0;  // the last time the standby pin was toggled
unsigned long debounceDelay = 50;    // the debounce time for standby pin
int messageSendingTimeDelay = 1000;  // wait period for publishing data

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
  // -- Display startup screens -
  startUpScreen();                          // Initising screen

  if (wifi()) {
    wifi();
  }                                        // Initialise the wifi connection

  // -- Initialise sensors -
  sht31.begin(SHT31_Address);               // Initialise the Temp Humid sensor at the adress 0x44
  sensors();                                // Collect initial temp and humidity

  // ---- Setup I/O and set status ----
  pinMode(standBySwitch, INPUT);            // sets the switch to an input
  pinMode(PWMoutput, OUTPUT);               // sets the relay pin to outputs
  digitalWrite(PWMoutput, Off);             // Set Inital pin status low

  // ---- Get saved data from memory --
  EEPROM.get(0, manualFanSpeed);            // Get inital fanSpeed from EEprom
  EEPROM.get(8, tempMin);                   // Get inital min temp
  EEPROM.get(12, tempMax);                  // Get inital max temp
  EEPROM.get(16, humMax);                   // Get inital hum max
  EEPROM.get(20, humMin);                   // Get inital hum max
  EEPROM.get(24, currentMode);              // Get inital mode (0 = Manual)(1 = Temp control)(2 = Hum control)
  EEPROM.get(32, fanMax);                   // Get the fan max in PWM 255 is the total max
  EEPROM.get(40, fanMin);                   // Get the fan min

  // ------ SetUp encoder ------
  encoder = new ClickEncoder(A1, A0, A2);   // set analog channel 0,1,2 for use with the rotary encoder
  encoder->setAccelerationEnabled(true);    // enable encode acelleration
  ITimer1.init();                           // timer interupt for the rotary encoder
  ITimer1.attachInterrupt(1000, timerIsr);  // set the interup fot timerIsr @ 1 millisecond
  last = encoder->getValue();               // Get the current encoder value
  lcd.clear();
}

// ---- Enable the watchdog ---
//void watchdogSetup() {
//  Serial.print(F("Setting up watchdog for 2 second delay"));
//#ifdef ARDUINO_ARCH_MEGAAVR
//  if (RSTCTRL.RSTFR & RSTCTRL_WDRF_bm) {
//    Serial.println(F("It was a watchdog reset."));
//  }
//  RSTCTRL.RSTFR |= RSTCTRL_WDRF_bm ;
//  wdt_enable(WDT_PERIOD_2KCLK_gc); // one second watchdog
//  wdt_reset(); 
//#endif
//}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Loop ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void loop() {
  wdt_reset();                     // Reset Watchdog and reset processor if crashed or inactive
  currentTime = millis();          // declare the current time is equal to millis
  // if mqtt connected run mqtt
  if (status == WL_CONNECTED) {
    if (mqttNotConnected == 0) {
      runMqtt();
    }
  }

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
  temp = sht31.readTemperature() - 1;                      // Get current Temperature
  hum = sht31.readHumidity();                           // Get current Humidity
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Watchdog overide ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void manualReset() {                  // Kick the watchdog if the reset is held down to activated
  if (button) {
    button = false;
    delay(2010);
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
        //standbyControl();
      }
      else {
        delay(2010);
      }
    }
  }
  lastButtonState = standBySwitchValue;
}

void standbyControl() {
  lcd.noBacklight();
  digitalWrite(PWMoutput, Off);
  shutDown = 1;
  lcd.clear();
  Wire.flush();
}

void wake(){
   lcd.backlight();
   shutDown = 0;
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
