//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ DeBug ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void deBug() {
//  fanSpeed = map(currentMode, tempMin, tempMax, fanMin, fanMax);   // Fan speed from temerature control
//  fanInVolts = fanSpeed * (5.0 / 255);
//  fanPercentage = mapFloat(fanInVolts + 0.01, 0.0, 5.0, 0.0, 100.0);   // fan speed in %
//  Serial.print(fanInVolts);
//  Serial.println(" volts");
//  Serial.print(fanPercentage);
//  Serial.println(F( " %"));
//  Serial.print(" Encoder Value =");
//  Serial.println(value);
//  Serial.print(" Menu Item =");
//  Serial.println(menuitem);
//  Serial.print(" page =");
//  Serial.println(page);
//  Serial.print(" menuEnter =");
//  Serial.println(menuEnter);
//  Serial.print(" currentMode =");
//  Serial.println(currentMode);
//  Serial.println(manualFanSpeed);
//  Serial.print("fan % = ");
//  Serial.println(fanPercentage);
//  Serial.print("Speed = ");
//  Serial.println(fanSpeed);
//  Serial.print("tempMax = ");
//  Serial.println(tempMax);
//  Serial.print("Current Temp = ");
//  Serial.println(temp);
    Serial.print("Chip serial number");
    Serial.println(sht3x.readSerialNumber());
    Serial.print("Current Hum = ");
    Serial.println(hum);
    Serial.print("Current Temp = ");
    Serial.println(temp);
    
//  int sb = digitalRead(standBySwitch);
//  Serial.print("SBSWITCH = ");
//  Serial.println(sb);
//  Serial.println(fanInVolts);
 // Serial.println(target);
//  Serial.println(fanMax);
//  Serial.print("Volts = ");
//  Serial.println(fanInVolts);
//  Serial.print("shutDown = ");
//  Serial.println(shutDown);
}
