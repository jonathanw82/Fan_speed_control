#include <DHT.h>                // Temp Humidity Lib
#include <TimerOne.h>           // Timer for encoder
#include <EEPROM.h>             // EEprom Lib
#include <Wire.h>               // I2c enable Lib
#include <avr/wdt.h>            // Watchdog Lib
#include <ClickEncoder.h>       // Rotery Encoder Lib
#include <LiquidCrystal_I2C.h>  // Lcd Display Lib
#include <MapFloat.h>           // Helpful implimetation of floating point ints in maps
           
int on = HIGH;
int off = LOW;
int spinner[] = {'\\','|','/'};    // Spinner Array
int spinnerArrayIndex = 0;         // Index value of current spinner array 
char spinnerSegment;               // define the segments
int eeAddress = 0;                 // Address to start saving to EEprom  
const byte PWMoutput = 3;           // realy pin

float fanMin = 0;
float fanMax = 255;
float tempMin = 0;
float tempMax = 0;
float humMin = 0;
float humMax = 0;
byte manMin = 0;
byte manMax = 0;

float fanInVolts = 0;
float fanPercentage = 0;
float fanSpeed = 0;

int currentMode;                  // depending on the currentMode the voltage and % menue can use this get correct data
byte autoFan = 0;             // initial fan control methods
byte manualFan = 0;
byte tempControl = 0;     
byte humControl = 0;

int manualFanSpeed = 0;           // Initial manual fanspeed



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Menu items and encoder control  ~~~~~~~~~~~~~~~~~~~~~~~~
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
int chk;
float hum;                   //Stores humidity value
float temp;                  //Stores temperature value
//float checkTemp;
//float checkHum;

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
  
  pinMode(PWMoutput, OUTPUT);                // sets the relay pin to outputs 
  digitalWrite(PWMoutput, off);              // Set Inital pin status low
  EEPROM.get(0,manualFanSpeed);              // Get inital fanSpeed from EEprom
  EEPROM.get(8, tempMax);
  EEPROM.get(16, humMax);
  EEPROM.get(24, currentMode);

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

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Loop ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void loop() {
  wdt_reset();                     // Reset Watchdog and reset processor if crashed or inactive
  currentTime = millis();          // declare the current time is equal to millis
  //fanSpinner();
  fanControl();                    // Adjust PWM output to fans controller
  readRotaryEncoder();             // Check status of rotery encoder
  encoderControl();                // set and check what the encoder button status are
  buttonPressed();                 // Is button pressed
  timerIsr();                      // timerIsr for rotery encoder
  manualReset();                   // If button is held down reset
  sensors();                       // Read Temp and Humidity sensors
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Fan Control ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void fanControl(){
  if(autoFan == 1){
    if(tempControl == 1){
      fanSpeed = map(temp, tempMin, tempMax, fanMin, fanMax);  // Fan speed from temerature control
      currentMode = temp;                                      // Set currentMode so the volate and speed % can be seen in the menu 
      controlFanSpeed();                                       // control digital channel will the PWM value
    }
    else if(humControl == 1){
      fanSpeed = map(hum, humMin, humMax, fanMin, fanMax);     // Fan speed from temerature control
      currentMode = hum;
      controlFanSpeed();   
      }
  }
  if(manualFan == 1){
    fanSpeed = map(manualFanSpeed, manMin, manMax, fanMin, fanMax); // Fan speed from manual control
    currentMode = manualFanSpeed;
    controlFanSpeed();
  }
 }

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# Fan Speed Control ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void controlFanSpeed(){
  analogWrite(PWMoutput, fanSpeed);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Rotary Encoder ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void readRotaryEncoder()
{
  value += encoder->getValue();

  if (value / 2 > last) {
    last = value / 2;
    down = true;
    if (currentTime - previousTime >= 50) {
      currentTime = previousTime;
    }
  } else   if (value / 2 < last) {
    last = value / 2;
    up = true;
    if (currentTime - previousTime >= 50) {
      currentTime = previousTime;
    }
  }
}

void timerIsr() {
  encoder->service();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Enter Pressed ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void buttonPressed(){

  if (middle) //Middle Button is Pressed
  {
    middle = false;

    if (page == 1 && menuitem == 1)
    {
      middle = false;
      menuitem ++;
      menuEnter ++;
      lcd.clear();
      value =0;
     
    }
    if (page == 1 && menuitem == 3 && menuEnter ==1)
    {
      middle = false;
      page =2;
      enter =1;
     
    }

   else if (page == 2 && menuitem == 3 && enter ==1 && menuEnter ==1)
    {
      middle = false;
      page =1;
      enter =0;
  
    }
    if (page == 1 && menuitem == 4 && menuEnter ==1)
    {
      middle = false;
      page =2;
      enter =1;
  
    }
    else if (page == 2 && menuitem == 4 && enter ==1 && menuEnter ==1)
    {
      middle = false;
      page =1;
      enter =0;
   
    }
    if (page == 1 && menuitem == 5 && menuEnter ==1)
    {
      middle = false;
      page =2;
      enter =1;
  
    }
    else if (page == 2 && menuitem == 5 && enter ==1 && menuEnter ==1)
    {
      middle = false;
      page =1;
      enter =0;
   
    }
    else if (page == 1 && menuitem == 6 && menuEnter ==1)
    {
      middle = false;
      page =1;
      enter =0;
      menuEnter =0;
      menuitem =1;
      lcd.clear();
      value =0;
      
    }
  }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Encoder Control ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void encoderControl()
{
  ClickEncoder::Button b = encoder->getButton();
  if (b != ClickEncoder::Open) {
    switch (b) {
      case ClickEncoder::Clicked:
        middle = true;
        break;
        case ClickEncoder::Held:                          // Setup button held time in ClickEncoder.cpp
        button = true;
        break;
    }
  }
 //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ROTATION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if (up && page == 1 && menuEnter == 1 ) {
      up = false;
    if (menuitem == 1)
    {
      menuitem == 2;
    }
    if (menuitem == 2)
    {
      menuitem == 3;
    }
    if (menuitem == 3)
    {
      menuitem == 4;
    }
    if (menuitem == 4)
    {
      menuitem == 5;
    }
    if (menuitem == 5)
    {
      menuitem == 6;
    }
    if (menuitem == 6)
    {
      menuitem == 6;
    }
    lastMenuItem = menuitem;
    menuitem--;
    if (menuitem <= 0)
    {
      menuitem = 1;
    }
  } else if (up && menuitem == 3 && enter == 1 && page == 2 ) {
    up = false;
    manualFanSpeed--;
    EEPROM.put(0, manualFanSpeed);

  }
  else if (up && menuitem == 4 && enter == 1 && page == 2 ) {
    up = false;
    tempMax--;
    EEPROM.put(8, tempMax);

  }
  else if (up && menuitem == 5 && enter == 1 && page == 2 ) {
//    up = false;
//    ledMode--;
//    EEPROM.put(16, ledMode);
  }

  if (down && page == 1 && menuEnter == 1) //We have turned the Rotary Encoder Clockwise
  {

    down = false;
    if (down && menuitem ==2 && lastMenuItem == 1){
      menuitem++;
    }

    if (down && menuitem == 3 && lastMenuItem == 2) {
      menuitem++;

    }
    else if (down && menuitem == 4 && lastMenuItem == 3) {
      menuitem++;

    }
    else if (down && menuitem == 5 &&  lastMenuItem == 4) {
      menuitem++;

    }
    else if (down && menuitem == 6 && lastMenuItem == 5) {
      menuitem++;

    }
    lastMenuItem = menuitem;
    menuitem++;

    if (menuitem >= 7)
    {
      menuitem =6;
    }
  }
  else if (down && menuitem == 3 && enter == 1 && page == 2 ) {
     down = false;
     manualFanSpeed++;
     EEPROM.put(0, manualFanSpeed);
  }
   if (manualFanSpeed > 10) {
      manualFanSpeed = 10;
    }
   else if(manualFanSpeed < 0) {
    manualFanSpeed = 0;
    }
   else if (down && menuitem == 4 && enter == 1 && page == 2 ) {
    tempMax++;
    EEPROM.put(8, tempMax);
  }
   if (tempMax > 30) {
    tempMax = 30;
  }
   else if (tempMax < 0) {
    tempMax = 0;
  }
//  else if (down && menuitem == 5 && enter == 1 && page == 2) {
//    down = false;
//    ledMode ++;
//    EEPROM.put(16, ledMode);
//  }
//  if (ledMode >= 1) {
//    ledMode = 1;
//  }
//  else if (ledMode <= 0) {
//    ledMode = 0;
//  }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Lcd Display ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void updatedisplay() {
    if (menuitem == 1 && page == 1 && menuEnter == 0)
  {
//    if (currentTime - previousTime >= 2000 && marker == 0)
//    {
//      previousTime = currentTime;
//      lcd.setCursor(0, 0);
//      lcd.print("Air Temp & Humid");
//      lcd.setCursor(0, 1);
//      lcd.print("C=");
//      lcd.print(temp);
//      lcd.print("  H=");
//      lcd.print(hum);
//      lcd.print("%");
//      marker = marker + 1;
//    }
//    if (currentTime - previousTime >= 2000 && marker == 1)
//    {
//      previousTime = currentTime;
//      lcd.setCursor(0, 0);
//      lcd.print("    Low Temp    ");
//      lcd.setCursor(0, 1);
//      lcd.print("     ");
//
//      if (lowTemp < 10) {
//        lcd.setCursor(5, 1);
//        lcd.print(" ");
//        lcd.print(lowTemp);
//        lcd.print("=C       ");
//      }
//      else if (lowTemp > 10) {
//        lcd.setCursor(5, 1);
//        lcd.print(lowTemp);
//        lcd.print("=C       ");
//      } 
//      marker = marker + 1;
//    }
//      if (currentTime - previousTime >= 2000 && marker == 2)
//      {
//        previousTime = currentTime;
//        lcd.setCursor(0, 0);
//        lcd.print("   High Temp    ");
//        lcd.setCursor(0, 1);
//        lcd.print("     ");
//        lcd.setCursor(5, 1);
//        lcd.print(highTemp);
//        lcd.print("=C       ");
//        marker = 0;
//      }
//
//      if (marker > 3) {
//        marker = 0;
//      }

    }
    if ( menuitem == 2 && page == 1 && menuEnter == 1)
    {
      lcd.setCursor(0, 0);
      lcd.print(F("Setup           "));
      lcd.setCursor(0, 1);
      lcd.print(F("Use UP & Down   "));
    }
    if ( menuitem == 3 && page == 1 && menuEnter == 1)
    {
      lcd.setCursor(0, 0);
      lcd.print(F("Set Low Temp    "));
      lcd.setCursor(0, 1);
      lcd.print(F("Click to Enter  "));
    }
    if (menuitem == 3 && page == 2 && menuEnter == 1) {
      lcd.setCursor(0, 0);
      lcd.print(F("Set Temp-   0-20"));
      lcd.setCursor(0, 1);
      lcd.print(tempMin);
      lcd.setCursor(2, 1);
      lcd.print(F("=C"));
      lcd.setCursor(4, 1);
      lcd.print(F("           "));

      if (tempMin < 10) {
        lcd.setCursor(1, 1);
        lcd.print(F(" "));
      }
    }
    if ( menuitem == 4 && page == 1 && menuEnter == 1)
    {
      lcd.setCursor(0, 0);
      lcd.print(F("Set High Temp   "));
      lcd.setCursor(0, 1);
      lcd.print(F("Click to Enter  "));
    }
    if (menuitem == 4 && page == 2 && menuEnter == 1)
    {
      lcd.setCursor(0, 0);
      lcd.print(F("Set Temp-  20-40"));
      lcd.setCursor(0, 1);
      lcd.print(tempMax);
      lcd.setCursor(2, 1);
      lcd.print(F("=C"));
      lcd.setCursor(4, 1);
      lcd.print(F("           "));

    }
    if ( menuitem == 5 && page == 1 && menuEnter == 1)
    {
      lcd.setCursor(0, 0);
      lcd.print(F("Status Leds     "));
      lcd.setCursor(0, 1);
      lcd.print(F("Click to Enter  "));
    }
    if (menuitem == 5 && page == 2 && menuEnter == 1)
    {
      lcd.setCursor(0, 0);
      lcd.print(F("Fade or Static  "));
      lcd.setCursor(0, 1);
     // lcd.print(ledMode);
//     if (ledMode ==0)
//     {
//      lcd.print(F("Fade            "));
//     }
//     else if (ledMode ==1);
//     {
//      lcd.print(F("Static          "));
//     }
     

    }
    if (menuitem == 6 && page == 1 && menuEnter == 1)
    {
      lcd.setCursor(0, 0);
      lcd.print(F("   Menu Exit    "));
      lcd.setCursor(0, 1);
      lcd.print(F(" Click to Exit  "));
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Watchdog overide ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void manualReset() {                  // Kick the watchdog if the reset is activated
  if (button) {
    button = false;
    delay(2000);
  }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Temp Humid Sensors ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void sensors(){
   hum = dht.readHumidity();                 
   temp = dht.readTemperature();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ DeBug ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 void deBug(){
    fanSpeed = map(currentMode, tempMin, tempMax, fanMin, fanMax);   // Fan speed from temerature control
    fanInVolts = fanSpeed *(5.0 / 255);
    fanPercentage = mapFloat(fanInVolts + 0.01, 0.0, 5.0, 0.0, 100.0);   // fan speed in %
    Serial.print(fanInVolts);
    Serial.println(" volts");
    Serial.print(fanPercentage);
    Serial.println(F( " %"));
    Serial.print(" Encoder Value =");
    Serial.println(value);
    Serial.print(" Menu Item =");
    Serial.println(menuitem);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Visual representation of spinning fan ~~~~~~~~~~~~~~~~~~~~~~~
void fanSpinner(){
      if (currentTime - previousTime >= 70) {
        previousTime = currentTime;
        if(spinnerArrayIndex <= 2){
           spinnerSegment = spinner[spinnerArrayIndex];
           Serial.println(spinnerSegment);
            spinnerArrayIndex++;
         }
         else{
            spinnerSegment = '-';
            Serial.println(spinnerSegment);
            spinnerArrayIndex = 0;
          }
    }
  }
