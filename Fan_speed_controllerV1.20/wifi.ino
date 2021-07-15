void wifi(){
    // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  while (status != WL_CONNECTED) {                                // attempt to connect to WiFi network:
    Serial.println("Attempting to connect to wifi network");
    Serial.print("WiFi name: ");
    Serial.println(WIFI_NAME);
    Serial.print("WiFi password: ");
    Serial.println(WIFI_PASSWORD);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(WIFI_NAME, WIFI_PASSWORD);

    // wait 10 seconds for connection:
    delay(10000);
  }
  }
