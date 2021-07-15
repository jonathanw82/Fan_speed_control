
void setUpMqtt() {
    // you're connected now, so print out the data:
  Serial.println("connection successfull!");
  mqtt_client.begin(MQTT_HOST, 1883, www_client);
  mqtt_client.onMessageAdvanced(mqtt_message);
}

bool str_startwith(char* string, char* start) {
  return string == strstr(string, start);
}

void runMqtt() {
   maintain_mqtt_connection();
    if (millis() - prevTime > messageSendingTimeDelay) {
    prevTime = millis();
    mqtt_client.publish(PUBLISH_PATH + String("temp"), String(temp));
    mqtt_client.publish(PUBLISH_PATH + String("Humidity"), String(hum));
  }
   mqtt_client.loop();
   maintain_mqtt_connection();
}

void mqtt_message(MQTTClient *client, char topic[], char payload[], int payload_length) {
  Serial.print("message recieved: ");
  Serial.print(topic);
  Serial.print(" = ");
  Serial.println(payload);
  commands(payload);
}

long last_connection_attempt = 0;

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
  if (!mqtt_client.connect(DEVICE_NAME)) {
    Serial.println(F(" connection failed."));
    return;
  }
  Serial.println(F("success!"));
  mqtt_client.subscribe(SUBSCRIBE_PATH);
}
