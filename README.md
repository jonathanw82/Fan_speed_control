
# Fan_Speed_Control
<h1 align="center">
   <img src="" alt="Project Image"/>
 </h1>
 
 
## Overview:
Fan speed controller for AvonValley farm preparation space air extraction system, with incorporated menu system to allow the user to select modes from automatic and manual.

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

## Construction:
* 3D printed Bezel

<div align="center"><img src="https://github.com/jonathanw82/Fan_speed_control/blob/main/media/img1.jpg" alt="3D print" width="45%"/><img src="https://github.com/jonathanw82/Fan_speed_control/blob/main/media/img2.jpg" alt="3D print" width="43%"/></div>


## Setup program options:
On pressing the rotary encoder centre button
* Setup Menu.
* Modes Auto/Manual.
* Min Target Temperature.
* Max Target Humidity.
* Max Fan PWM (255 = Max).
_________________________________________________
Possible add debug scrolling screens.
* Menu Exit.


## Setup program flow:


## General Operation


## Decals


## Credits:
The 3D printed LCD bezel, 
TheDreamMaster https://www.thingiverse.com/thing:2771280



## Media:


All other images are my own.

[Back_to_top](#Fan_Speed_Control)
