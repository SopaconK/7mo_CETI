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

int modo = 0;
int sentido = 0;
int delayPaso = 5;

const int in1 = 6;
const int in2 = 5;
const int in3 = 4;
const int in4 = 3;

void setBobinas(int a, int b, int c, int d) {
  digitalWrite(in1, a);
  digitalWrite(in2, b);
  digitalWrite(in3, c);
  digitalWrite(in4, d);
}

void pasoCompletoCW() {
  setBobinas(1,0,0,0); delay(delayPaso);
  setBobinas(0,1,0,0); delay(delayPaso);
  setBobinas(0,0,1,0); delay(delayPaso);
  setBobinas(0,0,0,1); delay(delayPaso);
}

void pasoCompletoCCW() {
  setBobinas(0,0,0,1); delay(delayPaso);
  setBobinas(0,0,1,0); delay(delayPaso);
  setBobinas(0,1,0,0); delay(delayPaso);
  setBobinas(1,0,0,0); delay(delayPaso);
}

void medioPasoCW() {
  setBobinas(1,0,0,0); delay(delayPaso);
  setBobinas(1,1,0,0); delay(delayPaso);
  setBobinas(0,1,0,0); delay(delayPaso);
  setBobinas(0,1,1,0); delay(delayPaso);
  setBobinas(0,0,1,0); delay(delayPaso);
  setBobinas(0,0,1,1); delay(delayPaso);
  setBobinas(0,0,0,1); delay(delayPaso);
  setBobinas(1,0,0,1); delay(delayPaso);
}

void medioPasoCCW() {
  setBobinas(1,0,0,1); delay(delayPaso);
  setBobinas(0,0,0,1); delay(delayPaso);
  setBobinas(0,0,1,1); delay(delayPaso);
  setBobinas(0,0,1,0); delay(delayPaso);
  setBobinas(0,1,1,0); delay(delayPaso);
  setBobinas(0,1,0,0); delay(delayPaso);
  setBobinas(1,1,0,0); delay(delayPaso);
  setBobinas(1,0,0,0); delay(delayPaso);
}

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  lcd.begin(16, 2);
}

void loop() {
  lcd.clear();
  lcd.print("Seleccionar modo:");
  lcd.setCursor(0,1);
  lcd.print("1:Medio 2:Comp");

  char mod = NO_KEY;
  while(mod != '1' && mod != '2'){
    mod = teclado.getKey();
  }

  lcd.clear();
  lcd.print("Seleccionar sentido:");
  lcd.setCursor(0,1);
  lcd.print("1:CW 2:CCW"); 
  
  char sen = NO_KEY;
  while(sen != '1' && sen != '2'){
    sen = teclado.getKey();
  }
  
  modo = mod - '0';
  sentido = sen - '0';

  lcd.clear();
  lcd.print("Motor Corriendo");
  lcd.setCursor(0,1);
  lcd.print("Presione C para parar");

  char tecla = NO_KEY;
  while(tecla != 'C'){
    tecla = teclado.getKey();

    if (modo == 2 && sentido == 1) {
      pasoCompletoCW();
    } else if (modo == 2 && sentido == 2) {
      pasoCompletoCCW();
    } else if (modo == 1 && sentido == 1) {
      medioPasoCW();
    } else if (modo == 1 && sentido == 2) {
      medioPasoCCW();
    }
  }

  setBobinas(0,0,0,0); // Apaga las bobinas al detener
}