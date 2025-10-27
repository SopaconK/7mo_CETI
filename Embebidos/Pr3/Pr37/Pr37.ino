#include <LiquidCrystal.h>
#include <Keypad.h>

const int LCD_RS = 22;
const int LCD_E  = 23;
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

int modo=0;
int sentido=0;
int delayPaso=5;


#include <Servo.h>
Servo servo1;
int PINSERV=8;

int read2digit(){
  delay(500);
  int x=0;
  while(true){
    char key= teclado.getKey();
    if(key){
      x+=(key-'0');
      break;
    }
  }
  delay(500);
  x*=10;
  while(true){
    char key= teclado.getKey();
    if(key){
      x+=(key-'0');
      break;
    }
  }
  return x;
}


void setup() {
    lcd.begin(16, 2); 
  servo1.attach(PINSERV);

}

void loop() {
  lcd.clear();
  lcd.print("Escoge valor");
  lcd.setCursor(0,1);
  lcd.print("01 al 24");

  int x=read2digit();

  int angulo=x*7;
  angulo+=(x/2);

  servo1.write(angulo);
  delay(3000);
  servo1.write(0);


}
