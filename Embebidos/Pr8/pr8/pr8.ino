#include <LiquidCrystal.h>
LiquidCrystal lcd(22, 23, 25, 24, 26, 27);

String mensajeRecibido = "";

void setup() {

  Serial.begin(9600);
  Serial1.begin(9600);

  lcd.begin(16, 2);
  

  lcd.print("Bluetooth LCD");
  lcd.setCursor(0, 1); 
  lcd.print("Esperando msg...");
}

void loop() {

  while (Serial1.available()) {

    char caracter = (char)Serial1.read();


    if (caracter == '\n') {
      

      Serial.print("Mensaje completo: ");
      Serial.println(mensajeRecibido);


      lcd.clear(); 
      lcd.setCursor(0, 0); 


      if (mensajeRecibido.length() > 16) {
        lcd.print(mensajeRecibido.substring(0, 16)); 
        lcd.setCursor(0, 1);                         
        lcd.print(mensajeRecibido.substring(16));    
      } else {

        lcd.print(mensajeRecibido);
      }


      mensajeRecibido = "";
      
    } else {

      if (caracter != '\r') {
        mensajeRecibido += caracter;
      }
    }
  }
}