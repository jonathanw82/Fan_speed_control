//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# Start Screen ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void startUpScreen(){
  lcd.setCursor(0, 0);
  lcd.print(F("   LettUsGrow   "));
  lcd.setCursor(0, 1);
  lcd.print(F(" AvonVally Farm "));
  delay(1500);
  lcd.setCursor(0, 0);
  lcd.print(F("   Preperation   "));
  lcd.setCursor(0, 1);
  lcd.print(F("  Extractor fan  "));
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Software Version"));
  lcd.setCursor(0, 1);
  lcd.print(F("   Site-V1.00   ")); 
  lcd.clear();
}
