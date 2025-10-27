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
Keypad teclado = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


const int PIN_RELE_1 = 14;
const int PIN_RELE_2 = 15;
const int PIN_MOTOR_VELOCIDAD = 9; 

void setup() {
  lcd.begin(16, 2);
  lcd.print("Practica #4");
  lcd.setCursor(0, 1);
  lcd.print("Control de Motor");

 
  pinMode(PIN_RELE_1, OUTPUT);
  pinMode(PIN_RELE_2, OUTPUT);
  pinMode(PIN_MOTOR_VELOCIDAD, OUTPUT);


  digitalWrite(PIN_RELE_1, LOW);
  digitalWrite(PIN_RELE_2, LOW);
  analogWrite(PIN_MOTOR_VELOCIDAD, 0); 

  delay(2000);
}

void loop() {

  lcd.clear();
  lcd.print("Sentido de Giro:");
  lcd.setCursor(0, 1);
  lcd.print("1:Izq / 2:Der");
  char sentidoGiro = 0;
  while (sentidoGiro != '1' && sentidoGiro != '2') {
    sentidoGiro = teclado.waitForKey();
  }

/*
  lcd.clear();
  lcd.print("Velocidad (%):");
  lcd.setCursor(0, 1);
  lcd.print("1:25 2:50 3:75 4:100");
  char opcionVelocidad = 0;
  while (opcionVelocidad < '1' || opcionVelocidad > '4') {
    opcionVelocidad = teclado.waitForKey();
  }

  // Convertir la opción a un valor PWM
  int valorPWM = 0;
  if (opcionVelocidad == '1') valorPWM = 64;
  if (opcionVelocidad == '2') valorPWM = 128;
  if (opcionVelocidad == '3') valorPWM = 192;
  if (opcionVelocidad == '4') valorPWM = 255;

*/
  lcd.clear();
  lcd.print("Tiempo (1-120s):");
  int tiempoSegundos = readNumberFromKeypad();
  
  if (tiempoSegundos < 1) tiempoSegundos = 1;
  if (tiempoSegundos > 120) tiempoSegundos = 120;


  lcd.clear();
  lcd.print("Motor girando...");
  lcd.setCursor(0, 1);
  lcd.print("25");

  if (sentidoGiro == '1') { // Izquierda
    digitalWrite(PIN_RELE_1, HIGH);
    digitalWrite(PIN_RELE_2, HIGH);
  } else { // Derecha
    digitalWrite(PIN_RELE_1, LOW);
    digitalWrite(PIN_RELE_2, LOW);
  }

  // Encender el motor a la velocidad deseada
  analogWrite(PIN_MOTOR_VELOCIDAD, 60);

  // Esperar el tiempo especificado
  delay(tiempoSegundos * 250L);
  lcd.clear();
  lcd.print("Motor girando...");
  lcd.setCursor(0, 1);
  lcd.print("50");
  analogWrite(PIN_MOTOR_VELOCIDAD, 100);

  // Esperar el tiempo especificado
  delay(tiempoSegundos * 250L);
  analogWrite(PIN_MOTOR_VELOCIDAD, 130);
  lcd.clear();
  lcd.print("Motor girando...");
  lcd.setCursor(0, 1);
  lcd.print("75");
  // Esperar el tiempo especificado
  delay(tiempoSegundos * 250L);
  analogWrite(PIN_MOTOR_VELOCIDAD, 255);
  lcd.clear();
  lcd.print("Motor girando...");
  lcd.setCursor(0, 1);
  lcd.print("100");
  // Esperar el tiempo especificado
  delay(tiempoSegundos * 250L);
  //DETENER EL MOTOR 
  lcd.clear();
  lcd.print("Proceso Finalizado");
  
  // Apagar el motor cortando la tierra con el transistor
  analogWrite(PIN_MOTOR_VELOCIDAD, 0);
  
  // Regresar los relés al estado por defecto (Derecha)
  digitalWrite(PIN_RELE_1, LOW);
  digitalWrite(PIN_RELE_2, LOW);

  delay(2000);
}

int readNumberFromKeypad() {
  String inputString = "";
  int number = 0;
  
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.cursor();

  while (true) {
    char key = teclado.getKey();
    if (key) {
      if (isdigit(key)) {
        inputString += key;
        lcd.print(key);
      } else if (key == 'C') {
        inputString = "";
        lcd.setCursor(0, 1);
        lcd.print("                ");
        lcd.setCursor(0, 1);
      } else if (key == '*' || key == '=') {
        break;
      }
    }
  }
  
  lcd.noCursor();
  if (inputString.length() > 0) {
      number = inputString.toInt();
  }
  return number;
}
