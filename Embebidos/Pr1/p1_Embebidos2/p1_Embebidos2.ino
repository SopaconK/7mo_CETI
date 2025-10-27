#include <LiquidCrystal.h>
#include <Keypad.h>

#define MAX_RPM 60
#define PULSOS_POR_VUELTA 1
#define TIMEOUT_US 2000000UL
#define ALPHA_NUM 3
#define ALPHA_DEN 10

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
Keypad customKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const int ENA = 9;
const int IN1 = 8;
const int IN2 = 7;
const int VELOCIDAD_MINIMA_ARRANQUE = 70;

const int SENSOR_PIN = 2;
volatile unsigned long ultimoPulso_us = 0;
volatile unsigned long intervalo_us = 0;

int rpm_disp = 0;
long rpm_f = 0;
String tiempoString = "";
bool valorIngresado = false;

void calcularIntervalo() {
  unsigned long t = micros();
  unsigned long dt = t - ultimoPulso_us;
  ultimoPulso_us = t;
  if (dt == 0) return;
  unsigned long rpmCalc = (60000000UL / dt) / PULSOS_POR_VUELTA;
  if (rpmCalc <= MAX_RPM) intervalo_us = dt;
}

void setup() {
  lcd.begin(16, 2);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(SENSOR_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), calcularIntervalo, RISING);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
  mostrarPantallaInicial();
}

void loop() {
  if (!valorIngresado) {
    char key = customKeypad.getKey();
    if (key) {
      if (key >= '0' && key <= '9') {
        tiempoString += key;
        lcd.print(key);
      } else if (key == 'C') {
        mostrarPantallaInicial();
      } else if (key == '*') {
        if (tiempoString.length() > 0) {
          valorIngresado = true;
          iniciarAceleracion();
        }
      }
    }
  }
}

void mostrarPantallaInicial() {
  lcd.clear();
  lcd.print("Tiempo (seg):");
  lcd.setCursor(0, 1);
  lcd.print("RPM: 0      ");
  lcd.setCursor(14, 0);
  tiempoString = "";
}

static inline void printLineaEstado(int porcentaje, int rpmVal) {
  if (rpmVal > MAX_RPM) rpmVal = MAX_RPM;
  lcd.setCursor(0, 1);
  lcd.print("%:");
  if (porcentaje < 10) lcd.print(' ');
  lcd.print(porcentaje);
  lcd.print(" RPM:");
  char buf[6];
  snprintf(buf, sizeof(buf), "%4d", rpmVal);
  lcd.print(buf);
  lcd.print(" ");
}

static inline void actualizarRPM() {
  unsigned long intervaloCopia, ultimoPulsoCopia;
  noInterrupts();
  intervaloCopia = intervalo_us;
  ultimoPulsoCopia = ultimoPulso_us;
  interrupts();

  if (intervaloCopia > 0) {
    unsigned long rpmCalc = (60000000UL / intervaloCopia) / PULSOS_POR_VUELTA;
    if (rpmCalc > MAX_RPM) rpmCalc = MAX_RPM;
    rpm_f = (ALPHA_NUM * (long)rpmCalc + (ALPHA_DEN - ALPHA_NUM) * rpm_f) / ALPHA_DEN;
    rpm_disp = (int)rpm_f;
  }

  if ((micros() - ultimoPulsoCopia) > TIMEOUT_US) {
    rpm_f = 0;
    rpm_disp = 0;
    noInterrupts();
    intervalo_us = 0;
    interrupts();
  }
}

void iniciarAceleracion() {
  long tiempoSegundos = tiempoString.toInt();
  if (tiempoSegundos > 300) tiempoSegundos = 300;
  if (tiempoSegundos <= 0) { valorIngresado = false; mostrarPantallaInicial(); return; }

  lcd.clear();
  lcd.print("Acelerando...");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  long tiempoMilisegundos = tiempoSegundos * 1000L;
  int delayPorPaso = tiempoMilisegundos / 255;
  if (delayPorPaso <= 0) delayPorPaso = 1;

  noInterrupts();
  ultimoPulso_us = micros();
  intervalo_us = 0;
  interrupts();
  rpm_f = 0;
  rpm_disp = 0;

  for (int velocidad = 0; velocidad <= 255; velocidad++) {
    int potenciaReal = map(velocidad, 0, 255, 0, 255);
    if (potenciaReal > 0 && potenciaReal < VELOCIDAD_MINIMA_ARRANQUE) {
      potenciaReal = VELOCIDAD_MINIMA_ARRANQUE;
    }
    analogWrite(ENA, potenciaReal);

    actualizarRPM();

    int porcentaje = (velocidad * 100) / 255;
    printLineaEstado(porcentaje, rpm_disp);

    delay(delayPorPaso);
  }

  lcd.setCursor(0, 0);
  lcd.print("Vel. Maxima!  ");
  unsigned long t0 = millis();
  while (millis() - t0 < 5000UL) {
    actualizarRPM();
    printLineaEstado(100, rpm_disp);
    delay(100);
  }

  analogWrite(ENA, 0);
  lcd.clear();
  lcd.print("Proceso");
  lcd.setCursor(0, 1);
  lcd.print("Finalizado   ");
  delay(2000);

  valorIngresado = false;
  mostrarPantallaInicial();
}
