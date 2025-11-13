

#include <LiquidCrystal.h>

LiquidCrystal lcd(22, 23, 24, 25, 26, 27);

int pin0=A0;
int pin1=A1;
int pin2=A2;
int pin3=A3;
int pin4=A4;

void setup() {
    lcd.begin(16, 2); 
    pinMode(pin0, INPUT);
    pinMode(pin1, INPUT);
    pinMode(pin2, INPUT);
    pinMode(pin3, INPUT);
    pinMode(pin4, INPUT);

}

void loop() {
  lcd.clear();
  if(!digitalRead(pin0)){
    lcd.print("Nivel 0");
    lcd.setCursor(0,1);
    lcd.print("0 ml");
  }
  else{
    if(!digitalRead(pin1)){
    lcd.print("Nivel 1");
    lcd.setCursor(0,1);
    lcd.print("100 ml");
    }
    else{
      if(!digitalRead(pin2)){
      lcd.print("Nivel 2");
      lcd.setCursor(0,1);
      lcd.print("200 ml");
      }
      else{
        if(!digitalRead(pin3)){
        lcd.print("Nivel 3");
        lcd.setCursor(0,1);
        lcd.print("300 ml");
        }
        else{
          if(!digitalRead(pin4)){
          lcd.print("Nivel 4");
          lcd.setCursor(0,1);
          lcd.print("400 ml");
          }
          else{
            lcd.print("Nivel 5");
            lcd.setCursor(0,1);
          lcd.print("500 ml");
          }
        }

      }
    }
  }

}
