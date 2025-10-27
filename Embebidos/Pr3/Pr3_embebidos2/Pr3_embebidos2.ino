#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>

const int LCD_RS = 22;
const int LCD_E = 23;
const int LCD_D4 = 24;
const int LCD_D5 = 25;
const int LCD_D6 = 26;
const int LCD_D7 = 27;
LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','/'},
  {'4','5','6','-'},
  {'7','8','9','+'},
  {'C','0','=','*'}
};
byte rowPins[ROWS] = {31, 33, 35, 37};
byte colPins[COLS] = {30, 32, 34, 36};
Keypad teclado = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

Servo servo1;
int PINSERV = 8;

int readdigit_and_confirm(){
  delay(500);
  int x = 0;
  int digit_count = 0;
  lcd.setCursor(0, 1);
  lcd.print("                "); // Limpia la segunda línea antes de escribir
  lcd.setCursor(0, 1);
  
  while(true){
    char key = teclado.getKey();
    if(key){
      if(isdigit(key)){ // Verifica si la tecla es un dígito
        x = x * 10 + (key - '0');
        lcd.print(key); // Muestra el dígito en la pantalla
        digit_count++;
      } else if (key == '*' && digit_count > 0){
        break; // Sale del bucle si se presiona '*' después de un dígito
      } else if (key == 'C'){
        x = 0; // Reinicia el valor
        digit_count = 0;
        lcd.setCursor(0, 1);
        lcd.print("                "); // Limpia la línea
        lcd.setCursor(0, 1);
      }
    }
  }
  return x;
}

void setup() {
  delay(500);
  lcd.begin(16, 2); 
  servo1.attach(PINSERV);
    servo1.attach(PINSERV, 500, 2500);

}

void loop() {
  lcd.clear();
  lcd.print("Escoge valor");
  lcd.setCursor(0, 1);
  lcd.print("01 al 24");
  
  int x = readdigit_and_confirm();
  
  lcd.clear();
  lcd.print("Valor leido:");
  lcd.setCursor(0, 1);
  lcd.print(x);
  delay(2000); // Muestra el valor leído por 2 segundos
  

  int angulos[x];
  for(int i=0; i<x; i++){
    lcd.clear();
    lcd.print("Angulo ");
    lcd.print(i);
    lcd.setCursor(0,1);
    angulos[i]=readdigit_and_confirm();
  }  

  servo1.write(0);
  
  for(int i=0; i<x; i++){

  lcd.clear();
  lcd.print(angulos[i]);
  servo1.write(angulos[i]);
  delay(3000);
  }
  servo1.write(0);
}