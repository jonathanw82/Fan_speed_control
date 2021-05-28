//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Lcd Display ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void updatedisplay() {
  if (menuitem == 1 && page == 1 && menuEnter == 0)
  {
    //~~~~~~~~~~~~~~~~~~~~~~~~~~ Display Manual Data ~~~~~~~~~~~~~~~~~~~~~~~~
    if (currentMode == 0) {               // currentMode == 0 Manual mode
      lcd.setCursor(0, 0);
      lcd.print("  Mode Manual   ");
      lcd.setCursor(0, 1);
      lcd.print(" Fan Speed ");
      lcd.setCursor(12, 1);
      lcd.print(fanPercentage);
      lcd.print("%");
      if (fanPercentage <= 0) {
        lcd.setCursor(14, 1);
        lcd.print("   ");
      }
      else if (fanPercentage < 100) {
        lcd.setCursor(15, 1);
        lcd.print("   ");
      }
    }
    //~~~~~~~~~~~~~~~~~~~~~~ Display Auto Temp control Data ~~~~~~~~~~~~~~~~~~~
    if (currentMode == 1) {            // currentMode == 1 Temperature control mode
      if (currentTime - previousTime >= 2000 && marker == 0)
      {
        previousTime = currentTime;
        lcd.setCursor(0, 0);
        lcd.print("Mode: Auto Temp ");
        lcd.setCursor(0, 1);
        lcd.print(" Fan Speed ");
        lcd.setCursor(12, 1);
        lcd.print(fanPercentage);
        lcd.print("%");
        if (fanPercentage <= 0) {
          lcd.setCursor(14, 1);
          lcd.print("   ");
        }
        else if (fanPercentage < 100) {
          lcd.setCursor(15, 1);
          lcd.print("   ");
        }
        marker = marker + 1;
      }
      if (currentTime - previousTime >= 4000 && marker == 1)
      {
        previousTime = currentTime;
        lcd.setCursor(0, 0);
        lcd.print("Air Temp        ");;
        lcd.setCursor(0, 1);
        lcd.print("C=");
        lcd.print(temp);
        lcd.print("         ");
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
          lcd.print("Mode: Auto Humd ");
          lcd.setCursor(0, 1);
          lcd.print(" Fan Speed ");
          lcd.setCursor(12, 1);
          lcd.print(fanPercentage);
          lcd.print("%");
          if (fanPercentage <= 0) {
            lcd.setCursor(14, 1);
            lcd.print("   ");
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
          if(currentMode == 0){
          lcd.print(F("Manual Mode     "));
            }
          else if(currentMode == 1){
          lcd.print(F("Auto Temp        "));
            }
           else if(currentMode == 2){
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
          lcd.print(F("MinTemp Fan 100%"));
          lcd.setCursor(0, 1);
          lcd.print(F("C= "));
          lcd.print(tempMin);
          lcd.print(F("          "));
        }
         if ( menuitem == 5 && page == 1 && menuEnter == 1)
        {
          lcd.setCursor(0, 0);
          lcd.print(F("Set MaxHum      "));
          lcd.setCursor(0, 1);
          lcd.print(F("Click to Enter  "));
        }
        if (menuitem == 5 && page == 2 && menuEnter == 1) {
          lcd.setCursor(0, 0);
          lcd.print(F("MaxHum  Fan 100%"));
          lcd.setCursor(0, 1);
          lcd.print(F("H= "));
          lcd.print(humMax);
          lcd.print(F("%"));
          if(humMax < 100){
            lcd.setCursor(6, 1);
            lcd.print("          ");
            }
        }
         if ( menuitem == 6 && page == 1 && menuEnter == 1)
        {
          lcd.setCursor(0, 0);
          lcd.print(F("Set MaxFan PWM  "));
          lcd.setCursor(0, 1);
          lcd.print(F("Click to Enter  "));
        }
        if (menuitem == 6 && page == 2 && menuEnter == 1) {
          lcd.setCursor(0, 0);
          lcd.print(F("Fan PWM Max     "));
          lcd.setCursor(0, 1);
          lcd.print(F("PWM Max ="));
          lcd.print(fanMax);
          lcd.print("    ");
          if(fanMax < 100){
            lcd.setCursor(11, 1);
            lcd.print("     ");
            }
        }
  
       
        if (menuitem == 7 && page == 1 && menuEnter == 1)
        {
          lcd.setCursor(0, 0);
          lcd.print(F("   Menu Exit    "));
          lcd.setCursor(0, 1);
          lcd.print(F(" Click to Exit  "));
        }
      }
