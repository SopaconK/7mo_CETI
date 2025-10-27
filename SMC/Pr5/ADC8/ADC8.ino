#include <LiquidCrystal.h>

// --- Definición de Pines ---
LiquidCrystal lcd(22, 23, 25, 24, 26, 27);
const int pinADC = A5;
// Usaremos solo 8 LEDs para el valor de 8 bits
const int leds[] = {42, 43, 44, 45, 46, 47, 48, 49}; // <-- CAMBIO (ahora 8 LEDs)

// --- Parámetros de Calibración y Filtrado ---
const int SAMPLES = 16;
const float ALPHA = 0.25f;
const int DEADBAND = 1;
const float VREF = 4.78;

// --- Variables Globales ---
// 'shownADC' seguirá guardando el valor de 10 bits para mantener la sensibilidad del filtro
int shownADC_10bit = -1;
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


void updateLCD(int adc_8bit) { 

  float voltaje = (adc_8bit * VREF) / 255.0;

  // Muestra el valor ADC de 8 bits
  lcd.setCursor(5, 0);
  lcd.print("    ");
  lcd.setCursor(5, 0);
  lcd.print(adc_8bit);

  // Muestra el voltaje calculado
  lcd.setCursor(9, 1);
  lcd.print("     ");
  lcd.setCursor(9, 1);
  lcd.print(voltaje, 3);
}

/**
 * Muestra el valor ADC de 8 BITS en formato binario en los 8 LEDs.
 */

/**
 * Función de configuración inicial.
 */
void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Iniciando...");
  delay(600);

  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Temp:");
  lcd.setCursor(0, 1); lcd.print("Voltaje:");


  for (int i = 0; i < 8; i++) { 
    pinMode(leds[i], OUTPUT);
  }

  int init_10bit = readADCavg(SAMPLES * 2);
  ema = init_10bit;
  shownADC_10bit = init_10bit;


  int init_8bit = init_10bit >> 2;
  updateLCD(init_8bit);
}

/**
 * Bucle principal del programa.
 */
void loop() {
  // El filtro sigue trabajando con la resolución completa de 10 bits
  int raw_10bit = readADCavg(SAMPLES);
  ema = ema + ALPHA * (raw_10bit - ema);
  int filtered_10bit = (int)lround(ema);

  if (abs(filtered_10bit - shownADC_10bit) >= DEADBAND) {
    shownADC_10bit = filtered_10bit;

    int adc_8bit = shownADC_10bit >> 2; 

 
    updateLCD(adc_8bit);

  }

  delay(30);
}