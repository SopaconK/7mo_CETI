#include <LiquidCrystal.h>

// --- Definición de Pines ---
LiquidCrystal lcd(22, 23, 25, 24, 26, 27);
const int pinADC = A1;
const int leds[] = {42, 43, 44, 45, 46, 47, 48, 49, 50, 51}; // 10 LEDs


const int SAMPLES = 16;
const float ALPHA = 0.25f;
const int DEADBAND = 1;
const float VREF = 4.78; 


int shownADC = -1;
float ema = -1;

/**
 * Lee el pin analógico varias veces y devuelve el promedio.
 */
int readADCavg(int samples) {
  long acc = 0;
  for (int i = 0; i < samples; ++i) {
    acc += analogRead(pinADC);
    delayMicroseconds(120);
  }
  return (int)(acc / samples);
}

/**
 * Actualiza la pantalla LCD con el valor ADC y el voltaje calculado.
 */
void updateLCD(int adc) {

  float voltaje = (adc * VREF) / 1023.0;

  // Muestra el valor ADC
  lcd.setCursor(5, 0);
  lcd.print("    "); 
  lcd.setCursor(5, 0);
  lcd.print(adc);

  // Muestra el voltaje calculado
  lcd.setCursor(9, 1);
  lcd.print("     "); 
  lcd.setCursor(9, 1);
  lcd.print(voltaje, 3); 
}

/**
 * Muestra el valor ADC en formato binario en los 10 LEDs.
 */
void updateLEDs(int adc) {
  for (int i = 0; i < 10; i++) {
    // Extrae cada bit del valor 'adc' y lo asigna a un LED
    bool on = ((adc >> i) & 1);
    digitalWrite(leds[i], on ? HIGH : LOW);
  }
}


void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Iniciando...");
  delay(600);


  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("ADC:");
  lcd.setCursor(0, 1); lcd.print("Voltaje:");


  for (int i = 0; i < 10; i++) {
    pinMode(leds[i], OUTPUT);
  }


  int init = readADCavg(SAMPLES * 2);
  ema = init;
  shownADC = init;


  updateLCD(shownADC);
  updateLEDs(shownADC);
}


void loop() {

  int raw = readADCavg(SAMPLES);
  ema = ema + ALPHA * (raw - ema);
  int filtered = (int)lround(ema);


  if (abs(filtered - shownADC) >= DEADBAND) {
    shownADC = filtered;
    updateLCD(shownADC);
    updateLEDs(shownADC);
  }

  delay(30); // Pequeña pausa para no saturar
}