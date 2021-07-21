void commands(char* topic, char* payload, int payload_length) {
  Serial.print(topic);
  if (str_startwith(payload, "sleep")) {
    standbyControl();
  }
  if (str_startwith(payload, "wake")) {
    wake();
  }
  if (str_startwith(topic, "avFanManual")) {
    payload[payload_length] = '\0';
    String s = String((char*)payload);
    int stringtoint = s.toInt();
    manualFanSpeed = stringtoint;
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
  if (str_startwith(payload, "ModeMan")) {
    currentMode = 0;
    writeToEEprom();
  }
  if (str_startwith(payload, "ModeTemp")) {
    currentMode = 1;
    writeToEEprom();
  }
  if (str_startwith(payload, "ModeHum")) {
    currentMode = 2;
    writeToEEprom();
  }
}
