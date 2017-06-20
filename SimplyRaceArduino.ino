#include<ISALiquidCrystal.h>
ISALiquidCrystal lcd;
int secs;
int minutes;
void setup() {
  // put your setup code here, to run once:
  lcd.begin();
  //nie ma daty
  secs = 0;
  minutes = 0;
  newMin();
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,0);
  lcd.print(minutes);
  lcd.setCursor(3,0);
  lcd.print(secs);
  delay(1000);
  if(secs < 59){
    secs++; 
    } else {
     secs = 0;
    minutes++;
    newMin();
  }
}

void newMin() {
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print(":");
}


