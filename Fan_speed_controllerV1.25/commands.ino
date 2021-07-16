void commands(char* payload) {

  if (str_startwith(payload, "sleep")) {
    standbyControl();
  }
  if (str_startwith(payload, "wake")) {
    shutDown = 0;
    lcd.backlight();
  }
  if (str_startwith(payload, "manFan+")) {
    manualFanSpeed += 5;
    writeToEEprom();
  }
  if (str_startwith(payload, "manFan-")) {
    manualFanSpeed -= 5;
    writeToEEprom();
  }
  if (str_startwith(payload, "tempMin+")) {
    tempMin++;
    writeToEEprom();
  }
  if (str_startwith(payload, "tempMin-")) {
    tempMin--;
    writeToEEprom();
  }
  if (str_startwith(payload, "tempMax+")) {
    tempMax++;
    writeToEEprom();
  }
  if (str_startwith(payload, "tempMax-")) {
    tempMax--;
    writeToEEprom();
  }
  if (str_startwith(payload, "humMin+")) {
    humMin += 5;
    writeToEEprom();
  }
  if (str_startwith(payload, "humMin-")) {
    humMin -= 5;
    writeToEEprom();
  }
  if (str_startwith(payload, "humMax+")) {
    humMax += 5;
    writeToEEprom();
  }
  if (str_startwith(payload, "humMax-")) {
    humMax -= 5;
    writeToEEprom();
  }
  if (str_startwith(payload, "fanMin+")) {
    fanMin++;
    writeToEEprom();
  }
  if (str_startwith(payload, "fanMin-")) {
    fanMin--;
    writeToEEprom();
  }
  if (str_startwith(payload, "fanMax+")) {
    fanMax++;
    writeToEEprom();
  }
  if (str_startwith(payload, "fanMax-")) {
    fanMax--;
    writeToEEprom();
  }
  // Get inital mode (0 = Manual)(1 = Temp control)(2 = Hum control)
  if (str_startwith(payload, "fanModeMan")) {
    currentMode = 0;
    writeToEEprom();
  }
  if (str_startwith(payload, "fanModeTemp")) {
    currentMode = 1;
    writeToEEprom();
  }
  if (str_startwith(payload, "fanModeHum")) {
    currentMode = 2;
    writeToEEprom();
  }
}
