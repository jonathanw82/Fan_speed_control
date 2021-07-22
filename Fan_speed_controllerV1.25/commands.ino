void commands(char* topic, char* payload, int payload_length) {
  Serial.print(topic);
  if (str_startwith(payload, "sleep")) {
    standbyControl();
  }
  if (str_startwith(payload, "wake")) {
    wake();
  }
  if (str_startwith(topic, "avFanManual")) {
    int tempNum = payloadCovertedToInt(payload, payload_length);
    manualFanSpeed = tempNum;
    writeToEEprom();
  }
  if (str_startwith(topic, "tempMin")) {
    int tempNum = payloadCovertedToInt(payload, payload_length);
    tempMin = tempNum;
    writeToEEprom();
  }
  if (str_startwith(topic, "tempMax")) {
    int tempNum = payloadCovertedToInt(payload, payload_length);
    tempMax = tempNum;
    writeToEEprom();
  }
  if (str_startwith(topic, "humMin")) {
    int tempNum = payloadCovertedToInt(payload, payload_length);
    humMin = tempNum;
    writeToEEprom();
  }
  if (str_startwith(topic, "humMax")) {
    int tempNum = payloadCovertedToInt(payload, payload_length);
    humMax = tempNum;
    writeToEEprom();
  }
  if (str_startwith(topic, "fanMin")) {
    int tempNum = payloadCovertedToInt(payload, payload_length);
    fanMin = tempNum;
    writeToEEprom();
  }
  if (str_startwith(topic, "fanMax")) {
    int tempNum = payloadCovertedToInt(payload, payload_length);
    fanMax = tempNum;
    writeToEEprom();
  }
  if (str_startwith(payload, "modeMan")) {        // Get inital mode (0 = Manual)(1 = Temp control)(2 = Hum control)
    currentMode = 0;
    writeToEEprom();
  }
  if (str_startwith(payload, "modeTemp")) {
    currentMode = 1;
    writeToEEprom();
  }
  if (str_startwith(payload, "modeHum")) {
    currentMode = 2;
    writeToEEprom();
  }
}
