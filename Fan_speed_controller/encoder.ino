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
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  Encoder  Timer ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void timerIsr() {
  encoder->service();
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
        case ClickEncoder::Held:                  // Setup button held time in ClickEncoder.cpp
        button = true;
        break;
    }
  }

//~~~~~~~~~~~~~~~~~ Manual Control only avalable in Manual mode ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  if(currentMode == 0 && menuEnter == 0){         // currentMode 0 = manual mode
    if(up && page == 1){
      up = false;
      manualFanSpeed -=10;
      EEPROM.put(0, manualFanSpeed);
      }
    if(down && page == 1){
      down = false;
      manualFanSpeed +=10;
      EEPROM.put(0, manualFanSpeed);
      }
     if (manualFanSpeed > 100) {
      manualFanSpeed = 100;
    }
     else if (manualFanSpeed < 0) {
      manualFanSpeed = 0;
      }
    }
 //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Menu Rotation ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
   
    lastMenuItem = menuitem;
    menuitem--;
    if (menuitem <= 0)
    {
      menuitem = 1;
    }
  } else if (up && menuitem == 3 && enter == 1 && page == 2 ) {
    up = false;
    currentMode--;
    EEPROM.put(24, currentMode);
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
  
    lastMenuItem = menuitem;
    menuitem++;

    if (menuitem >= 4)
    {
      menuitem =4;
    }
  }
  else if (down && menuitem == 3 && enter == 1 && page == 2 ) {
     down = false;
     currentMode++;
     EEPROM.put(24, currentMode);
  }
   if (currentMode >= 2) {
      currentMode = 2;
    }
   else if(currentMode <= 0) {
    currentMode = 0;
    }
}
