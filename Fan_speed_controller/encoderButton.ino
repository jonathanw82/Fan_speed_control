//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Enter Pressed ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void buttonPressed() {

  if (middle) //Middle Button is Pressed
  {
    middle = false;

    if (page == 1 && menuitem == 1)
    {
      middle = false;
      menuitem ++;
      menuEnter ++;
      lcd.clear();
      value = 0;

    }
    if (page == 1 && menuitem == 3 && menuEnter == 1)
    {
      middle = false;
      page = 2;
      enter = 1;
    }

    else if (page == 2 && menuitem == 3 && enter == 1 && menuEnter == 1)
    {
      middle = false;
      page = 1;
      enter = 0;
    }
    if (page == 1 && menuitem == 4 && menuEnter == 1)
    {
      middle = false;
      page = 2;
      enter = 1;
    }

    else if (page == 2 && menuitem == 4 && enter == 1 && menuEnter == 1)
    {
      middle = false;
      page = 1;
      enter = 0;
    }
    if (page == 1 && menuitem == 5 && menuEnter == 1)
    {
      middle = false;
      page = 2;
      enter = 1;
    }

    else if (page == 2 && menuitem == 5 && enter == 1 && menuEnter == 1)
    {
      middle = false;
      page = 1;
      enter = 0;
    }
     if (page == 1 && menuitem == 6 && menuEnter == 1)
    {
      middle = false;
      page = 2;
      enter = 1;
    }

    else if (page == 2 && menuitem == 6 && enter == 1 && menuEnter == 1)
    {
      middle = false;
      page = 1;
      enter = 0;
    }

    else if (page == 1 && menuitem == 7 && menuEnter == 1)
    {
      middle = false;
//      page = 1;
//      enter = 0;
//      menuEnter = 0;
//      menuitem = 1;
//      lcd.clear();
//      value = 0;
        delay(2000);
    }
  }
}
