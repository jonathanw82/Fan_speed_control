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
      case ClickEncoder::DoubleClicked:
        standByButton = true;
       break;
    }
  }

  //~~~~~~~~~~~~~~~~~ Manual Control only avalable in Manual mode ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  if (currentMode == 0 && menuEnter == 0) {       // currentMode 0 = manual mode
    if (up && page == 1) {
      up = false;
      manualFanSpeed -= 10;
      EEPROM.put(0, manualFanSpeed);
    }
    if (down && page == 1) {
      down = false;
      manualFanSpeed += 10;
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

    lastMenuItem = menuitem;
    menuitem--;
    if (menuitem <= 0)
    {
      menuitem = 1;
    }
  }
  if (up && menuitem == 3 && enter == 1 && page == 2 ) {
    up = false;
    currentMode--;
    EEPROM.put(24, currentMode);
  }
  if (up && menuitem == 4 && enter == 1 && page == 2 ) {
    up = false;
    tempMin --;
    EEPROM.put(8, tempMin);
  }
  if (up && menuitem == 5 && enter == 1 && page == 2 ) {
    up = false;
    humMax -=5;
    EEPROM.put(16, humMax);
  }
   if (up && menuitem == 6 && enter == 1 && page == 2 ) {
    up = false;
    fanMax -=5;
    EEPROM.put(32, fanMax);
  }

  //~~~~~~~~~~~~~~~~~~~~~~ Down ~~~~~~~~~~~~~~~~~~~~~~~
  if (down && page == 1 && menuEnter == 1) //We have turned the Rotary Encoder Clockwise
  {
    down = false;
    if (down && menuitem == 2 && lastMenuItem == 1) {
      menuitem++;
    }

    if (down && menuitem == 3 && lastMenuItem == 2) {
      menuitem++;
    }

    if (down && menuitem == 4 && lastMenuItem == 3) {
      menuitem++;
    }

     if (down && menuitem == 5 && lastMenuItem == 4) {
      menuitem++;
    }
     if (down && menuitem == 6 && lastMenuItem == 5) {
      menuitem++;
    }
    lastMenuItem = menuitem;
    menuitem++;

    if (menuitem >= 7)
    {
      menuitem = 7;
    }
  }
  if (down && menuitem == 3 && enter == 1 && page == 2 ) {
    down = false;
    currentMode++;
    EEPROM.put(24, currentMode);
  }
  if (currentMode >= 2) {
    currentMode = 2;
  }
  else if (currentMode <= 0) {
    currentMode = 0;
  }
   if (down && menuitem == 4 && enter == 1 && page == 2 ) {
    down = false;
    tempMin ++;
    EEPROM.put(8, tempMin);
  }
  if (tempMin >= 30) {
    tempMin = 30;
  }
  else if (tempMin < 0) {
    tempMin = 0;
  }
    if (down && menuitem == 5 && enter == 1 && page == 2 ) {
    down = false;
    humMax +=5;
    EEPROM.put(16, humMax);
  }
  if (humMax >= 100) {
    humMax = 100;
  }
  else if (humMax < 20) {
    humMax = 20;
  }
    if (down && menuitem == 6 && enter == 1 && page == 2 ) {
    down = false;
    fanMax +=5;
    EEPROM.put(32, fanMax);
  }
  if (fanMax >= 255) {
    fanMax = 255;
  }
  else if (fanMax < 0) {
    humMax = 0;
  }
}
