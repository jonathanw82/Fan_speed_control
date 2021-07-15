void commands(char payload){
  
  if (payload == "sleep") {
    standbyControl();
  }
  if (payload == "wake") {
    Serial.print(F("ReBooting"));
    delay(1500);
  }
  if (payload == "manFan+") {
    manualFanSpeed += 5;
    writeToEEprom();
  }
  if (payload == "manFan-") {
    manualFanSpeed -= 5;
    writeToEEprom();
  }
  if (payload == "tempMin+") {
    tempMin++;
    writeToEEprom();
  }
    if (payload == "tempMin-") {
    tempMin--;
    writeToEEprom();
  }
   if (payload == "tempMax+") {
    tempMax++;
    writeToEEprom();
  }
    if (payload == "tempMax-") {
    tempMax--;
    writeToEEprom();
  }
    if (payload == "humMin+") {
     humMin += 5;
    writeToEEprom();
  }
    if (payload == "humMin-") {
     humMin -= 5;
    writeToEEprom();
  }
   if (payload == "humMax+") {
     humMax += 5;
    writeToEEprom();
  }
    if (payload == "humMax-") {
     humMax -= 5;
    writeToEEprom();
  }
      if (payload == "fanMin+") {
     fanMin--;
    writeToEEprom();
  }
    if (payload == "fanMin-") {
     fanMin--;
    writeToEEprom();
  }
   if (payload == "fanMax+") {
     fanMax++;
    writeToEEprom();
  }
    if (payload == "fanMax-") {
     fanMax++;
    writeToEEprom();
  }
  // Get inital mode (0 = Manual)(1 = Temp control)(2 = Hum control)
     if (payload == "fanModeMan") {
     currentMode = 0;
    writeToEEprom();
  }
   if (payload == "fanModeTemp") {
     currentMode = 1;
    writeToEEprom();
  }
     if (payload == "fanModeHum") {
     currentMode = 2;
    writeToEEprom();
  }
}
