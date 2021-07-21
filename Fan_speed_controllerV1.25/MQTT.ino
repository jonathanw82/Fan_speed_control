//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ MQTT Setup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void setUpMqtt() {
  mqtt_client.begin(MQTT_HOST, 1883, www_client); 
  mqtt_client.onMessageAdvanced(mqtt_message);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ String comparason ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool str_startwith(char* string, char* start) {
  return string == strstr(string, start);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Run MQTT  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void runMqtt() {
  if (!mqtt_client.connected()) {
    maintain_mqtt_connection();
  }
  else {
    wdt_reset();
    if (millis() - prevTime2 > 5000) {
      prevTime2 = millis();
      mqtt_client.publish(PUBLISH_PATH + String("SoftwareVersion"), String("Site-V1.20MQTT"));
      mqtt_client.publish(PUBLISH_PATH + String("HostName"), String(MQTT_HOST));
      mqtt_client.publish(PUBLISH_PATH + String("DeviceName"), String(DEVICE_NAME));
      mqtt_client.publish(PUBLISH_PATH + String("Location"), String(LOCATION));
    }
    String settingString = String(currentMode) + ',' + String(tempMin) + ',' + String(tempMax) + ',' + String(humMin) + ',' + String(humMax) + ',' + String(fanMin) + ',' + String(fanMax) + ',' + String(shutDown);

    if (millis() - prevTime > messageSendingTimeDelay) {
      prevTime = millis();
      if (shutDown == 0) {
        mqtt_client.publish(PUBLISH_PATH + String("Temp"), String(temp));
        mqtt_client.publish(PUBLISH_PATH + String("Humidity"), String(hum));
        mqtt_client.publish(PUBLISH_PATH + String("fan%"), String(fanPercentage));
        mqtt_client.publish(PUBLISH_PATH + String("fanVoltage"), String(fanInVolts));
      }
      mqtt_client.publish(PUBLISH_PATH + String("Settings"), String(settingString));
      mqtt_client.publish(PUBLISH_PATH + String("manFan"), String(manualFanSpeed));
    }
    wdt_reset(); 
    mqtt_client.loop();
  }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ MQTT Message recieved ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void mqtt_message(MQTTClient *client, char topic[], char payload[], int payload_length) {
  wdt_reset(); 
  Serial.print("message recieved: ");
  Serial.print(topic);
  Serial.print(" = ");
  Serial.println(payload);
  commands(topic, payload, payload_length);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Maintain Connection to MQTT ~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void maintain_mqtt_connection() {
  if (mqtt_client.connected()) {
    return;
  }
  // only attempt to connect once a second
  if (millis() - last_connection_attempt < 1000) {
    return;
  }
  last_connection_attempt = millis();
  Serial.print(F("Connecting to MQTT host \""));
  Serial.print(MQTT_HOST);
  Serial.print(F("\" ... "));
  lcd.setCursor(0, 0);
  lcd.print(F("Enable Mqtt     "));
  lcd.setCursor(0, 1);
  lcd.print(F("Please Wait!    "));
  if (!mqtt_client.connect(DEVICE_NAME)) {
    Serial.println(F(" connection failed."));
    isMQTTConnectedCounter++;
    if (isMQTTConnectedCounter == 1) {
      mqttNotConnected = 1;
     // watchdogSetup();
    }
    return;
  }
  Serial.println(F("success!"));
  mqtt_client.subscribe(SUBSCRIBE_PATH);
  mqtt_client.subscribe(SUBSCRIBE_PATH2);
//  watchdogSetup();
}
