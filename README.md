
# Fan_Speed_Control
<h1 align="center">
   <img src="https://github.com/jonathanw82/Fan_speed_control/blob/main/media/fanspeedcontrol.gif" alt="Project Image"/>
 </h1>
 

## Overview:
Fan speed controller for AvonValley farm preparation space air extraction, with incorporated menu allowing the user to select modes from automatic and manual.

The current controller offers little to no options for control other than 0-100%, the fan is also very noisy, this controller offers a possible solution to reduce the noise and give the user more control. 

## The user's goals of this controller are:
* An easy to navigate menu.
* Controll via webpage/intergration into Ostara.
* Low power consumption.
* Manual and Automatic operation.
* Automated monitoring of temperature and humidity to regulate fan speed accordingly.

## Features:
* Rotary encoder for navigation.
* Lcd display for real time data.
* Auto mode to allow automated control of fan speed relative to rises in room temperature or humidity, with user-programmable target parameters.
* Manual mode to allow the user to set a fan speed as desired.
* Standby Switch.
* Website Control.

## General Operation & Setup:
* If the rocker switch is in the off position, the LCD display is not illuminated, the controller is in standby. Switching the rocker switch to the on position, the LCD will illuminate, the controller will display startup screens and fan control will start from the previous mode that was selected.


### Selectable Modes:
* Manual: This mode offers adjustment via the rotary encoder to increase or decrease the fan speed form 0-100%

* Auto Temp: This mode offers automated fan control via the air temperature, governed by the temperature minimum and temperature maximum, these values are preset by the user in the settings menu.

* Auto Hum: This mode offers automated fan control via the air humidity, governed by the humidity minimum and humidity maximum, these values are preset by the user in the settings menu. 

#

### Note:

All settings are accessed by pressing the rotary encoder once. From here rotate the button clockwise/anti-clockwise to reach desired menu option. To enter each menu press the button again, to exit a certain menu once agin press the button. To exit the settings menu either scroll to the exit menu option and press the button, or hold the button down to activate the manual reset. Either option can be used but it is better to scroll to the exit option.
#

* Auto Temperature Settings:
Auto Temp has a couple of settings that can be changed to get the desired effect from the controller.
The 2 settings minimum temp and maximum temp, (EG) setting the minimum temp to 20 and the max to 30 the fan will be running @0% at 20 and 100% at 30.
Temp Min can be set between 10-30C.

* Auto Humidity Settings:
Auto Hum has a couple of settings that can be changed to get the desired effect from the controller.
The 2 settings minimum Hum and maximum Hum, (EG) setting the minimum Hum to 20% and the max to 100% the fan will be running @0% at 20 and 100% at 100%.
Hum Min can be set between 20%-100%.

* PWM Settings:
It is recommended these settings are left as standard PWM Min = 0 and PWM Max = 255, in certain circumstances the PWM Min can be increased if the fan motor is having trouble getting started.
Or the PWM Max can be decreased if 100% is too loud or the fan is far too powerful.

* Diagnostics:
This option will display debug information, Current Mode, T/H Sensor Serial Number, Fan Speed %, PWM Pin Voltage, PWM Current Value, Min Temp, MaxTemp, Min Hum, Max Hum, PWM Min, PWM Max, Software Version.



## Parts Required:
* Arduino Uno WiFi Rev2 [Here](https://store.arduino.cc/arduino-uno-wifi-rev2)
* PMP2425W Crydom 25Amp configurable panel mount proportional control relay. [Here](https://uk.rs-online.com/web/p/solid-state-relays/1450603/?cm_mmc=UK-PPC-DS3A-_-google-_-DSA_UK_EN_Relays_Index-_-Solid+State+Relays%7C+Products-_-DYNAMIC+SEARCH+ADS&matchtype=b&dsa-1193841357972&s_kwcid=AL!7457!3!504930549032!b!!g!!&gclid=Cj0KCQjw--GFBhDeARIsACH_kda--qfwiYqq5zjuV3pZ5H8Jwh-oOMkSBz1KMY0g-ov1plc-TYbbI9QaAs4UEALw_wcB&gclsrc=aw.ds)
* Solid State Relay Heat Sink Din mount [Here](https://uk.rs-online.com/web/p/solid-state-relay-heatsinks/7034564/?cm_mmc=UK-PPC-DS3A-_-google-_-3_UK_EN_Relays_Solid+State+Relay+Heatsinks_Phrase-_-Sensata+/+Crydom+-+7034564+-+HS301DR-_-hs301dr&matchtype=p&kwd-23861736400&s_kwcid=AL!7457!3!512563304828!p!!g!!hs301dr&gclid=Cj0KCQjw--GFBhDeARIsACH_kdZ8FfeA81j-OvZjZMheyz4FUox76YKj330JyLfjab7-JEgpXslKqpEaAsJ0EALw_wcB&gclsrc=aw.ds)
* LCD 16x2 I2C Screen blue [Here]() add link
* 3D printed screen bezel [Here](https://www.thingiverse.com/thing:2771280)
* Rotary Encoder Module KY-040 With Clickable Switch [Here]() add link
* HDR-15-12 240vac-12vdc 1.25A power supply din mount [Here](https://uk.rs-online.com/web/p/din-rail-power-supplies/1457860/?cm_mmc=UK-PPC-DS3A-_-google-_-3_UK_EN_DIN%20Rail%20Power%20Supplies_Mean%20Well_Exact-_-Mean%20Well%20-%20DIN%20Rail%20Power%20Supplies%20-%201457860%20-%205-_-hdr%2015%2012&gclid=Cj0KCQjw--GFBhDeARIsACH_kdbE-MJgkjSO6FHoLwMOmvp2tnu0kLxm3cejjB0S-6lC3Tamvx2wPN0aArpeEALw_wcB&gclsrc=aw.ds&grossPrice=Y&kwd-372001364330&matchtype=e&s_kwcid=AL!7457!3!442026574461!e!!g!!hdr%2015%2012)
* SHT31 Temperature Humidity sensor [Here](https://wiki.dfrobot.com/SHT31_Temperature_Humidity_Sensor_Weatherproof_SKU_SEN0385)
* Plastic box for Arduino and LCD display [Here](https://uk.rs-online.com/web/p/general-purpose-enclosures/4984025/)
* White rocker switch [Here](https://uk.rs-online.com/web/p/rocker-switches/5332970/)
* Connecting cables
* 10k resistor
* 4.7uf capacitor

## Technology Used:
* [Arduino Ide](https://www.arduino.cc/en/software)
* [VsCode](https://code.visualstudio.com/)
* [drawio](https://www.diagrams.net/)

## Software:
The Software is written in C++, compiled and uploaded to the micro controller by the Arduino Ide, most libraries used are Arduino standard, apart from the items listed in the additional section.

### Standard
* EEPROM for writing to the controller memory
* Wire for use of I2C bus
* avr/wdt for use of the built in watchdog 

### Additional
* BB_Adafruit_SHT31 custom BitBang library for temperature humidity sensor 
* encoder-arduino for the Rotary encoder 
* Liquidcrystal-IC2 for the LCD Display
* megaAVR_TimerInterrupt-1.3.0 a timing library utalised by the Rotary encoder for ATmega4809 architecture
* BitBang_I2C-2.1.3 for asigning new I2C GPIO pins 
### All Libraries can be found [Here](https://github.com/jonathanw82/Fan_speed_control/tree/main/libraries)


## Construction:
* Wiring Schematic

<div align="center"><img src="https://github.com/jonathanw82/Fan_speed_control/blob/main/media/fan_speed_%20schematic.jpg" alt="Wiring Schematic" width="100%"/></div>

<div align="center"><img src="https://github.com/jonathanw82/Fan_speed_control/blob/main/media/fan_speed_schematic_power.jpg" alt="Wiring Schematic" width="100%"/></div>


* 3D printed Bezel

<div align="center"><img src="https://github.com/jonathanw82/Fan_speed_control/blob/main/media/img1.jpg" alt="3D print" width="45%"/><img src="https://github.com/jonathanw82/Fan_speed_control/blob/main/media/img2.jpg" alt="3D print" width="43%"/></div>

#
<div align="center"><img src="https://github.com/jonathanw82/Fan_speed_control/blob/main/media/bezelconstuction1.jpg" alt="bezel constuction" width="45%"/><img src="https://github.com/jonathanw82/Fan_speed_control/blob/main/media/bezelcon2.jpg" alt="bezel construction" width="45%"/></div>

## Note on PWM
A resistor-capacitor filter was added to the PWM channel to flatten the signal, as the crydom really needed a smooth 0-5v (EG, 50% duty cycle the output voltage is 2.5v and 100% duty cycle 5v).

<div align="center"><img src="https://github.com/jonathanw82/Fan_speed_control/blob/main/media/new%20end%20point.png" alt="bezel constuction" width="45%"/></div>



## Power Consumption:
Estimated Power Consumption as rated in docs, actual may vary.

| Component              | Consumption        |
| :----------------      | :-------           |
| Arduino Uno Wifi Rev2  | @ 9v 150 ma        |
| Lcd i2c                | @ 5v 200 ma        |
| SHT31 temp/hum sensor  | @ 5v < 1.5 ma      |
| KY-040 Rotary Encoder  | @ 5v < 0.05 ma     |
| PMP2425W Relay         | @ 9v 30 ma         |
|                        |Total = 381.55 ma   |
#

## Setup program options:
On pressing the rotary encoder centre button

| Setup Menu.                | Options                     |
| :----------------          | :-------                    |
| Modes Auto/Manual.         | Manual, Auto Temp, Auto Hum |
| Min Target Temperature.    | +/- 0-30C                   |
| Max Target Temperature.    | +/- 0-30C                   |
| Min Target Humidity.       | +/- 0-100%                  |
| Max Target Humidity.       | +/- 0-100%                  |
| Min PWM                    | +/- 0-255 steps of 5        |
| Max PWM                    | +/- 0-255 steps of 5        |
| Diagnostic                 | Scrolling Display of all Saved Data |
| Menu Exit.                 |                             |

### Note for setup
When setting the Min and Max values if the the Min value exceeds the Max value it will become the whatever the current Max value is -5, the opsoite if Max is less than the Min value it will become whatever the Min value is +5.


<div align="center"><img src="https://github.com/jonathanw82/Fan_speed_control/blob/main/media/setupflow.jpg" alt="Setup flow Chart" width="100%"/></div>

#

## Mqtt Connection:

### Mqtt Commands:

| Commands as strings:       | Topic:                      |
| :----------------          | :-------                    |
| sleep                      | AVfanControl                |
| wake                       | AVfanControl                |
| avFanManual                | avFanManual                 |
| tempMin                    | avFanTempMin                |
| tempMax                    | avFanTempMax                |
| humMin                     | avFanHumMin                 | 
| humMax                     | avFanHumMax                 |  
| fanMin                     | AVfanMin                    | 
| fanMax                     | AVfanMax                    |
| modeMan                    | AVfanControl                |
| modeTemp                   | AVfanControl                |
| modeHum                    | AVfanControl                |


## Nice to have:
* Bluetooth connectivity.
* Intergration with Ostara. 


## Credits:
The 3D printed LCD bezel, 
TheDreamMaster https://www.thingiverse.com/thing:2771280



## Media:


All other images and or Diagrams are property of LettUs Grow.

[Back_to_top](#Fan_Speed_Control)
