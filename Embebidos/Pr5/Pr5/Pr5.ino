#include <LiquidCrystal.h>
#include <Keypad.h>


const int LCD_RS = 22;
const int LCD_E = 23;
const int LCD_D4 = 25;
const int LCD_D5 = 24;
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
Keypad teclado = Keypad(makeKeymap(keys), rowPins, colPins,ROWS,COLS);
String s="";
int readnumber(){
  delay(500);
  int x = 0;

  
  while(true){
    leerSerial();
    char key = teclado.getKey();
    if(key){
      if(isdigit(key)){ 
        x = x * 10 + (key - '0');
      } else if (key == '*' ){
        break; 
      } 
    }
  }
  return x;
}




void imprimir(){
  lcd.clear();
  lcd.print(s);
}


void leerSerial(){
  if(Serial3.available()>0){
    char c=Serial3.read();
    s+=c;
    imprimir();
  }
}


void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);         
   lcd.begin(16, 2);
   lcd.print("hola");
}



void loop() {
  char c=readnumber();
  Serial.println(c);
  Serial3.print(c);
  

}
