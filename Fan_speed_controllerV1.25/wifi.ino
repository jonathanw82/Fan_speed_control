bool wifi() {
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println(F("Communication with WiFi module failed!"));
    // don't continue
    while (true);
  }

  while (status != WL_CONNECTED) {                                // attempt to connect to WiFi network:
    Serial.println(F("Attempting to connect to wifi network"));
    Serial.print(F("WiFi name: "));
    Serial.println(WIFI_NAME);
    Serial.print(F("WiFi password: "));
    Serial.println(WIFI_PASSWORD);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
    // wait 10 seconds for connection:
    delay(10000);
    // you're connected now, so print out the data:
    if (status == WL_CONNECT_FAILED) {
      isWifiConnectedCounter++;
      Serial.print("Wifi Not connected");
      if (isWifiConnectedCounter == 2) {
        Serial.print("Wifi Not connected");
        return false;
      }
    }
    Serial.println("connection successfull!");
    return true;
  }
}
