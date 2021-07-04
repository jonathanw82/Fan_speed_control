//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Lcd Display ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void updatedisplay() {
  if (menuitem == 1 && page == 1 && menuEnter == 0)
  {
    //~~~~~~~~~~~~~~~~~~~~~~~~~~ Display Manual Data ~~~~~~~~~~~~~~~~~~~~~~~~
    if (currentMode == 0) {               // currentMode == 0 Manual mode
      lcd.setCursor(0, 0);
      lcd.print(F("  Mode Manual   "));
      lcd.setCursor(0, 1);
      lcd.print(F(" Fan Speed "));
      lcd.setCursor(12, 1);
      lcd.print(manualFanSpeed);
      lcd.print(F("%"));
      if (manualFanSpeed < 10) {
        lcd.setCursor(14, 1);
        lcd.print(F("   "));
      }
      else if (manualFanSpeed < 100) {
        lcd.setCursor(15, 1);
        lcd.print(F("   "));
      }
    }
    //~~~~~~~~~~~~~~~~~~~~~~ Display Auto Temp control Data ~~~~~~~~~~~~~~~~~~~
    if (currentMode == 1) {            // currentMode == 1 Temperature control mode
      if (currentTime - previousTime >= 2000 && marker == 0)
      {
        previousTime = currentTime;
        lcd.setCursor(0, 0);
        lcd.print(F("Mode: Auto Temp "));
        lcd.setCursor(0, 1);
        lcd.print(F(" Fan Speed "));
        lcd.setCursor(12, 1);
        lcd.print(fanPercentage);
        lcd.print(F("%"));
        if (fanPercentage <= 0) {
          lcd.setCursor(14, 1);
          lcd.print(F("   "));
        }
        else if (fanPercentage < 100) {
          lcd.setCursor(15, 1);
          lcd.print(F("   "));
        }
        marker = marker + 1;
      }
      if (currentTime - previousTime >= 4000 && marker == 1)
      {
        previousTime = currentTime;
        lcd.setCursor(0, 0);
        lcd.print(F("Air Temp        "));
        lcd.setCursor(0, 1);
        lcd.print(F("C="));
        lcd.print(temp);
        lcd.print(F("         "));
        marker = marker + 1;
      }
      if (marker > 1) {
        marker = 0;
      }
    }
    //~~~~~~~~~~~~~~~~~~~~~~ Display Auto Hum control Data ~~~~~~~~~~~~~~~~~~~
    if (currentMode == 2) {            // currentMode == 2 Humidity control mode
      if (currentTime - previousTime >= 2000 && marker == 0)
      {
        previousTime = currentTime;
        lcd.setCursor(0, 0);
        lcd.print(F("Mode: Auto Humd "));
        lcd.setCursor(0, 1);
        lcd.print(F(" Fan Speed "));
        lcd.setCursor(12, 1);
        lcd.print(fanPercentage);
        lcd.print(F("%"));
        if (fanPercentage <= 10) {
          lcd.setCursor(14, 1);
          lcd.print(F("   "));
        }
        else if (fanPercentage < 100) {
          lcd.setCursor(15, 1);
          lcd.print(F("   "));
        }
        marker = marker + 1;
      }
      if (currentTime - previousTime >= 4000 && marker == 1)
      {
        previousTime = currentTime;
        lcd.setCursor(0, 0);
        lcd.print(F("Air Hum        "));;
        lcd.setCursor(0, 1);
        lcd.print(F("H="));
        lcd.print(hum);
        lcd.print(F("         "));
        marker = marker + 1;
      }
      if (marker > 1) {
        marker = 0;
      }
    }
  }
  //~~~~~~~~~~~~~~~~~~~~~~~~~ Display Setup data ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if ( menuitem == 2 && page == 1 && menuEnter == 1)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("Setup           "));
    lcd.setCursor(0, 1);
    lcd.print(F("Use Up & Down   "));
  }
  if ( menuitem == 3 && page == 1 && menuEnter == 1)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("Set Mode        "));
    lcd.setCursor(0, 1);
    lcd.print(F("Click to Enter  "));
  }
  if (menuitem == 3 && page == 2 && menuEnter == 1) {
    lcd.setCursor(0, 0);
    lcd.print(F("Select Mode:    "));
    lcd.setCursor(0, 1);
    if (currentMode == 0) {
      lcd.print(F("Manual Mode     "));
    }
    else if (currentMode == 1) {
      lcd.print(F("Auto Temp        "));
    }
    else if (currentMode == 2) {
      lcd.print(F("Auto Hum         "));
    }
  }
  if ( menuitem == 4 && page == 1 && menuEnter == 1)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("Set MinTemp     "));
    lcd.setCursor(0, 1);
    lcd.print(F("Click to Enter  "));
  }
  if (menuitem == 4 && page == 2 && menuEnter == 1) {
    lcd.setCursor(0, 0);
    lcd.print(F("MinTemp         "));
    lcd.setCursor(0, 1);
    lcd.print(F("C= "));
    lcd.print(tempMin);
    lcd.print(F("          "));
  }

  if ( menuitem == 5 && page == 1 && menuEnter == 1)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("Set MaxTemp     "));
    lcd.setCursor(0, 1);
    lcd.print(F("Click to Enter  "));
  }
  if (menuitem == 5 && page == 2 && menuEnter == 1) {
    lcd.setCursor(0, 0);
    lcd.print(F("maxTemp         "));
    lcd.setCursor(0, 1);
    lcd.print(F("C= "));
    lcd.print(tempMax);
    lcd.print(F("          "));
  }

  if ( menuitem == 6 && page == 1 && menuEnter == 1)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("Set MinHum      "));
    lcd.setCursor(0, 1);
    lcd.print(F("Click to Enter  "));
  }
  if (menuitem == 6 && page == 2 && menuEnter == 1) {
    lcd.setCursor(0, 0);
    lcd.print(F("minHum          "));
    lcd.setCursor(0, 1);
    lcd.print(F("H= "));
    lcd.print(humMin);
    lcd.print(F("%"));
    if (humMin < 100) {
      lcd.setCursor(6, 1);
      lcd.print(F("          "));
    }
  }

  if ( menuitem == 7 && page == 1 && menuEnter == 1)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("Set MaxHum      "));
    lcd.setCursor(0, 1);
    lcd.print(F("Click to Enter  "));
  }
  if (menuitem == 7 && page == 2 && menuEnter == 1) {
    lcd.setCursor(0, 0);
    lcd.print(F("MaxHum  Fan 100%"));
    lcd.setCursor(0, 1);
    lcd.print(F("H= "));
    lcd.print(humMax);
    lcd.print(F("%"));
    if (humMax < 100) {
      lcd.setCursor(6, 1);
      lcd.print(F("          "));
    } else {
      lcd.setCursor(7, 1);
      lcd.print(F("         "));
    }
  }
  if ( menuitem == 8 && page == 1 && menuEnter == 1)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("Set PWM Max     "));
    lcd.setCursor(0, 1);
    lcd.print(F("Click to Enter  "));
  }
  if (menuitem == 8 && page == 2 && menuEnter == 1) {
    lcd.setCursor(0, 0);
    lcd.print(F("Fan PWM Max     "));
    lcd.setCursor(0, 1);
    lcd.print(F("PWM Max ="));
    lcd.print(fanMax);
    lcd.print(F("      "));
    if (fanMax < 100) {
      lcd.setCursor(11, 1);
      lcd.print(F("     "));
    }
  }
  if ( menuitem == 9 && page == 1 && menuEnter == 1)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("Set PWM Min     "));
    lcd.setCursor(0, 1);
    lcd.print(F("Click to Enter  "));
  }
  if (menuitem == 9 && page == 2 && menuEnter == 1) {
    lcd.setCursor(0, 0);
    lcd.print(F("Fan PWM Min     "));
    lcd.setCursor(0, 1);
    lcd.print(F("PWM Min ="));
    lcd.print(fanMin);
    lcd.print(F("      "));
    if (fanMin < 100) {
      lcd.setCursor(11, 1);
      lcd.print(F("     "));
    }
  }
  //~~~~~~~~~~~~~~~~~~~~~~~~~ Diagnostic ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if ( menuitem == 10 && page == 1 && menuEnter == 1)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("Diagnostic      "));
    lcd.setCursor(0, 1);
    lcd.print(F("Click to Enter  "));
  }
  if (menuitem == 10 && page == 2 && menuEnter == 1) {
    if (currentTime - previousTime >= 2000 && marker == 0)
    {
      previousTime = currentTime;
      lcd.setCursor(0, 0);
      lcd.print(F("Current Mode    "));
      lcd.setCursor(0, 1);
      if (currentMode == 0) {
        lcd.print(F("Manual Mode     "));
      }
      else if (currentMode == 1) {
        lcd.print(F("Auto Temp       "));
      }
      else if (currentMode == 2) {
        lcd.print(F("Auto Hum        "));
      }
      marker = marker + 1;
    }
    if (currentTime - previousTime >= 2000 && marker == 1)
    {
      previousTime = currentTime;
      lcd.setCursor(0, 0);
      lcd.print(F("T/H SensorStatus"));
      lcd.setCursor(0, 1);
      lcd.print(SHT31_Address + sht31.readStatus());
      Serial.print(sht31.readStatus());
      lcd.print(F("        "));
      marker = marker + 1;
    }
    if (currentTime - previousTime >= 2000 && marker == 2)
    {
      previousTime = currentTime;
      lcd.setCursor(0, 0);
      lcd.print(F("Air Temp & Humid"));
      lcd.setCursor(0, 1);
      lcd.print(F("C="));
      lcd.print(temp);
      lcd.print(F("  H="));
      lcd.print(hum);
      lcd.print(F("%"));
      marker = marker + 1;
    }
    if (currentTime - previousTime >= 2000 && marker == 3)
    {
      previousTime = currentTime;
      if (currentMode == 0) {
        lcd.setCursor(0, 0);
        lcd.print(F("Fan Speed in %  "));
        lcd.setCursor(0, 1);
        lcd.print(F("Speed  "));
        lcd.print(manualFanSpeed);
        lcd.print(F("%"));
        if (manualFanSpeed < 100) {
          lcd.setCursor(10, 1);
          lcd.print(F("      "));
        }
        if (manualFanSpeed < 10) {
          lcd.setCursor(9, 1);
          lcd.print(F("       "));
        }
      }
      else {
        lcd.setCursor(0, 0);
        lcd.print(F("Fan Speed in %  "));
        lcd.setCursor(0, 1);
        lcd.print(F("Speed  "));
        lcd.print(fanPercentage);
        lcd.print(F("%"));
        if (fanPercentage < 100) {
          lcd.setCursor(10, 1);
          lcd.print(F("      "));
        }
        if (fanPercentage < 10) {
          lcd.setCursor(9, 1);
          lcd.print(F("       "));
        }
      }
      marker = marker + 1;
    }
    if (currentTime - previousTime >= 2000 && marker == 4)
    {
      previousTime = currentTime;
      lcd.setCursor(0, 0);
      lcd.print(F("PWM Voltage:    "));
      lcd.setCursor(0, 1);
      lcd.print(F("V= "));
      lcd.print(fanInVolts);
      lcd.print(F("        "));
      marker = marker + 1;
    }
    if (currentTime - previousTime >= 2000 && marker == 5)
    {
      previousTime = currentTime;
      int PWMnow = fanSpeed;
      if (PWMnow <= 0) {
        PWMnow = 0;
      }
      lcd.setCursor(0, 0);
      lcd.print(F("PWM Value       "));
      lcd.setCursor(0, 1);
      lcd.print(F("PWM= "));
      lcd.print(PWMnow);
      if (PWMnow < 100) {
        lcd.setCursor(8, 1);
        lcd.print(F("        "));
      }
      if (PWMnow < 10) {
        lcd.setCursor(7, 0);
        lcd.print(F("     "));
      }
      lcd.print(F("        "));
      marker = marker + 1;
    }
    if (currentTime - previousTime >= 2000 && marker == 6)
    {
      previousTime = currentTime;
      lcd.setCursor(0, 0);
      lcd.print(F("Min Temp = "));
      lcd.print(tempMin);
      lcd.print(F("C"));
      if (tempMin < 10) {
        lcd.setCursor(15, 0);
        lcd.print(F(" "));
      }
      lcd.setCursor(0, 1);
      lcd.print(F("Max Temp = "));
      lcd.print(tempMax);
      lcd.print(F("C"));
      if (tempMax < 10) {
        lcd.setCursor(15, 1);
        lcd.print(F(" "));
      }
      marker = marker + 1;
    }
    if (currentTime - previousTime >= 2000 && marker == 7)
    {
      previousTime = currentTime;
      lcd.setCursor(0, 0);
      lcd.print(F("Min Hum =  "));
      lcd.print(humMin);
      lcd.print(F("%"));
      if (humMin < 10) {
        lcd.setCursor(13, 0);
        lcd.print(F("   "));
      }
      lcd.setCursor(0, 1);
      lcd.print(F("Max Hum =  "));
      lcd.print(humMax);
      lcd.print(F("%"));
      if (humMax < 10) {
        lcd.setCursor(13, 1);
        lcd.print(F("   "));
      }
      marker = marker + 1;
    }
    if (currentTime - previousTime >= 2000 && marker == 8)
    {
      previousTime = currentTime;
      lcd.setCursor(0, 0);
      lcd.print(F("PWM min = "));
      lcd.print(fanMin);
      if (fanMin < 100) {
        lcd.setCursor(13, 0);
        lcd.print(F("   "));
      }
      if (fanMin < 10) {
        lcd.setCursor(11, 0);
        lcd.print(F("     "));
      }
      lcd.setCursor(0, 1);
      lcd.print(F("PWM max = "));
      lcd.print(fanMax);
      lcd.print(F("   "));
      if (fanMax < 100) {
        lcd.setCursor(13, 0);
        lcd.print(F("   "));
      }
      if (fanMax < 10) {
        lcd.setCursor(12, 1);
        lcd.print(F("    "));
      }
      marker = marker + 1;
    }
    if (currentTime - previousTime >= 2000 && marker == 9)
    {
      previousTime = currentTime;
      lcd.setCursor(0, 0);
      lcd.print(F("SoftWare Version"));
      lcd.setCursor(0, 1);
      lcd.print(SoftwareVersion);

      marker = marker + 1;
    }
    if (marker > 9) {
      marker = 0;
    }
  }
  if (menuitem == 11 && page == 1 && menuEnter == 1)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("   Menu Exit    "));
    lcd.setCursor(0, 1);
    lcd.print(F(" Click to Exit  "));
  }
}
