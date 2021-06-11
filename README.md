
# Fan_Speed_Control
<h1 align="center">
   <img src="" alt="Project Image"/>
 </h1>
 
 
## Overview:
Fan speed controller for AvonValley farm preparation space air extraction, with incorporated menu allowing the user to select modes from automatic and manual.

The current controller offers little to no options for control other than 0-100%, the fan is also very noisy, this controller offers a possible solution to reduce the noise and give the user more control. 

## The users goals of this controller are:
* An easy to navigate menu.
* Low power consumption.
* Manual and Automaic operation.
* Automated monitoring of temperature and humidity and regulate fan speed accordingly.

## Features:
* Rotery encoder for navigation.
* Lcd display for real time data.
* Auto mode to allow automated control of fan speed relative to rises in room temperature or humidity, with user-programmable target parameters.
* Manual mode to allow the user to set a fan speed as desired.

## General Operation & Setup
* Manual Mode: This mode offers adjustment vis the rotary encoder to increase or decrease the fan speed form 0-100%

* Auto Temp Mode: This mode offers automated fan control via the air temperature, governed by the temperature minimum and temperature maximum, these values are preset by the user in the settings menu.

* Auto Hum Mode: This mode offers automated fan control via the air humidity, governed by the humidity minimum and humidity maximum, these values are preset by the user in the settings menu. 
#

### Note:

All settings are accessed by pressing the rotary encoder button to enter the settings menu, then rotating the button until the desired menu option is displayed, to enter each menu press the button again, to exit a certain menu once agin press the button. To exit the settings menu either scroll to the exit menu option and press the button, or hold the button down to activate the manual reset either option can be used, but it is better to scroll to the exit option.
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
This option will display debug information, Current Mode, Fan Speed %, PWM Pin Voltage, PWM Current Value, Min Temp, MaxTemp, Min Hum, Max Hum, PWM Min, PWM Max, Software Version.



## Parts:
* Arduino Uno [Here](https://en.wikipedia.org/wiki/Arduino_Uno)
* Crydom 25 A Solid State Relay, Phase Angle, Panel Mount. [Here](https://uk.rs-online.com/web/p/solid-state-relays/1450603/?cm_mmc=UK-PPC-DS3A-_-google-_-DSA_UK_EN_Relays_Index-_-Solid+State+Relays%7C+Products-_-DYNAMIC+SEARCH+ADS&matchtype=b&dsa-1193841357972&s_kwcid=AL!7457!3!504930549032!b!!g!!&gclid=Cj0KCQjw--GFBhDeARIsACH_kda--qfwiYqq5zjuV3pZ5H8Jwh-oOMkSBz1KMY0g-ov1plc-TYbbI9QaAs4UEALw_wcB&gclsrc=aw.ds)
* Solid State Relay Heat Sink Din mount [Here](https://uk.rs-online.com/web/p/solid-state-relay-heatsinks/7034564/?cm_mmc=UK-PPC-DS3A-_-google-_-3_UK_EN_Relays_Solid+State+Relay+Heatsinks_Phrase-_-Sensata+/+Crydom+-+7034564+-+HS301DR-_-hs301dr&matchtype=p&kwd-23861736400&s_kwcid=AL!7457!3!512563304828!p!!g!!hs301dr&gclid=Cj0KCQjw--GFBhDeARIsACH_kdZ8FfeA81j-OvZjZMheyz4FUox76YKj330JyLfjab7-JEgpXslKqpEaAsJ0EALw_wcB&gclsrc=aw.ds)
* LCD 16x2 I2C Screen blue [Here]() add link
* 3D printed screen bezel [Here](https://www.thingiverse.com/thing:2771280)
* Rotary Encoder Module KY-040 With Top Clickable Switch [Here]() add link
* HDR-15-12 240vac-12vdc 1.25A power supply din mount [Here](https://uk.rs-online.com/web/p/din-rail-power-supplies/1457860/?cm_mmc=UK-PPC-DS3A-_-google-_-3_UK_EN_DIN%20Rail%20Power%20Supplies_Mean%20Well_Exact-_-Mean%20Well%20-%20DIN%20Rail%20Power%20Supplies%20-%201457860%20-%205-_-hdr%2015%2012&gclid=Cj0KCQjw--GFBhDeARIsACH_kdbE-MJgkjSO6FHoLwMOmvp2tnu0kLxm3cejjB0S-6lC3Tamvx2wPN0aArpeEALw_wcB&gclsrc=aw.ds&grossPrice=Y&kwd-372001364330&matchtype=e&s_kwcid=AL!7457!3!442026574461!e!!g!!hdr%2015%2012)
* DHT22 Temperature Humidity sensor [Here](https://learn.adafruit.com/dht)
* Plastic box for Arduino and LCD display [Here](https://uk.rs-online.com/web/p/general-purpose-enclosures/4984025/)
* White rocker switch [Here](https://uk.rs-online.com/web/p/rocker-switches/5332970/)

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
* DHT_sensor_library for temperature humidity sensor [Here](https://github.com/jonathanw82/Fan_speed_control/blob/main/libraries/DHT_sensor_library.zip)
* encoder-arduino for the Rotary encoder [Here](https://github.com/jonathanw82/Fan_speed_control/blob/main/libraries/encoder-arduino.zip)
* Liquidcrystal-IC2 for the LCD Display [Here](https://github.com/jonathanw82/Fan_speed_control/blob/main/libraries/Liquidcrystal-IC2.zip)
* MapFloat-master to allow use of floating point integers with Map() functions [Here](https://github.com/jonathanw82/Fan_speed_control/blob/main/libraries/MapFloat-master.zip)
* TimerOne a timing library utalised by the Rotary encoder [Here](https://github.com/jonathanw82/Fan_speed_control/blob/main/libraries/TimerOne.zip)

## Construction:
* Wiring Schematic


<div align="center"><img src="https://github.com/jonathanw82/Fan_speed_control/blob/main/media/fan_speed_%20schematic.jpg" alt="Wiring Schematic" width="100%"/></div>


* 3D printed Bezel

<div align="center"><img src="https://github.com/jonathanw82/Fan_speed_control/blob/main/media/img1.jpg" alt="3D print" width="45%"/><img src="https://github.com/jonathanw82/Fan_speed_control/blob/main/media/img2.jpg" alt="3D print" width="43%"/></div>


## Setup program options:
On pressing the rotary encoder centre button

| Setup Menu.                | Options                     |
| :----------------          | :-------                    |
| Modes Auto/Manual.         | Manual, Auto Temp, Auto Hum |
| Min Target Temperature.    | +/- 0-30C                   |
| Max Target Temperature.    | +/- 0-30C                   |
| Min Target Humidity.       | +/- 0-100%                  |
| Max Target Humidity.       | +/- 0-100%                  |
| Max PWM                    | +/- 0-255                   |
| Min PWM                    | +/- 0-255                   |
| Diagnostic                 | Scrolling Display of all Saved Data |
| Menu Exit.                 |                             |

<div align="center"><img src="https://github.com/jonathanw82/Fan_speed_control/blob/main/media/setupflow.jpg" alt="Setup flow Chart" width="100%"/></div>

#






## Decals


## Credits:
The 3D printed LCD bezel, 
TheDreamMaster https://www.thingiverse.com/thing:2771280



## Media:


All other images are my own.

[Back_to_top](#Fan_Speed_Control)
