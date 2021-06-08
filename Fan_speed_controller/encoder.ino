//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Rotary Encoder ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void readRotaryEncoder()
{
  value += encoder->getValue();

  if (value / 3 > last) {
    last = value / 3;
    down = true;
    if (currentTime - previousTime >= 50) {
      currentTime = previousTime;
    }
  } else   if (value / 3 < last) {
    last = value / 3;
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

  if (currentMode == 0 && menuEnter == 0) {       // currentMode 0 = manual mode
    if (up && page == 1) {
      up = false;
      manualFanSpeed -= 5;
      //EEPROM.put(0, manualFanSpeed);
      writeToEEprom();
    }
    if (down && page == 1) {
      down = false;
      manualFanSpeed += 5;
      //EEPROM.put(0, manualFanSpeed);
      writeToEEprom();
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
    if (menuitem == 6)
    {
      menuitem == 7;
    }
    if (menuitem == 7)
    {
      menuitem == 8;
    }
    if (menuitem == 8)
    {
      menuitem == 9;
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
    // EEPROM.put(24, currentMode);
    writeToEEprom();
  }
  if (up && menuitem == 4 && enter == 1 && page == 2 ) {
    up = false;
    tempMin --;
    // EEPROM.put(8, tempMin);
    writeToEEprom();
  }
  if (up && menuitem == 5 && enter == 1 && page == 2 ) {
    up = false;
    humMax -= 5;
    // EEPROM.put(16, humMax);
    writeToEEprom();
  }
  if (up && menuitem == 6 && enter == 1 && page == 2 ) {
    up = false;
    fanMax -= 5;
    //EEPROM.put(32, fanMax);
    writeToEEprom();
  }
  if (up && menuitem == 7 && enter == 1 && page == 2 ) {
    up = false;
    fanMin --;
    writeToEEprom();
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
    if (down && menuitem == 7 && lastMenuItem == 6) {
      menuitem++;
    }
    if (down && menuitem == 8 && lastMenuItem == 7) {
      menuitem++;
    }
    lastMenuItem = menuitem;
    menuitem++;

    if (menuitem >= 9)
    {
      menuitem = 9;
    }
  }
  if (down && menuitem == 3 && enter == 1 && page == 2 ) {
    down = false;
    currentMode++;
    //EEPROM.put(24, currentMode);
    writeToEEprom();
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
    //EEPROM.put(8, tempMin);
    writeToEEprom();
  }
  if (tempMin >= 30) {
    tempMin = 30;
  }
  else if (tempMin < 0) {
    tempMin = 0;
  }
  if (down && menuitem == 5 && enter == 1 && page == 2 ) {
    down = false;
    humMax += 5;
    //EEPROM.put(16, humMax);
    writeToEEprom();
  }
  if (humMax >= 100) {
    humMax = 100;
  }
  else if (humMax < 20) {
    humMax = 20;
  }
  if (down && menuitem == 6 && enter == 1 && page == 2 ) {
    down = false;
    fanMax += 5;
    // EEPROM.put(32, fanMax);
    writeToEEprom();
  }
  if (fanMax >= 255) {
    fanMax = 255;
  }
  else if (fanMax < 0) {
    humMax = 0;
  }
  if (down && menuitem == 7 && enter == 1 && page == 2 ) {
    down = false;
    fanMin ++;
    writeToEEprom();
  }
  if (fanMin >= 255) {
    fanMin = 255;
  }
  else if (fanMin < 0) {
    fanMin = 0;
  }
}
