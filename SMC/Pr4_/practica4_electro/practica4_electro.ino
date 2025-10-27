#include <LiquidCrystal.h>
#include <math.h>

LiquidCrystal lcd(22, 23, 25, 24, 26, 27);

const uint8_t PIN_DER = A0;
const uint8_t PIN_IZQ = A1;

const float Vs = 5.00f;

const float EMA_ALPHA = 0.20f;
const int AVG_SAMPLES = 16;
const unsigned long SWITCH_MS = 1000;

float emaVd = 0.0f, emaVi = 0.0f;
unsigned long lastSwitch = 0;
bool showVin = true;

static int leerRawProm(uint8_t pin) {
  long acc = 0;
  analogRead(pin);
  for (int i = 0; i < AVG_SAMPLES; ++i) {
    acc += analogRead(pin);
  }
  return (int)((acc + AVG_SAMPLES / 2) / AVG_SAMPLES);
}

static float rawAVolt(int raw) {
  return raw * (Vs / 1023.0f);
}

void intToBin8(int val, char *buf) {
  for (int i = 7; i >= 0; --i) {
    *buf++ = (val & (1 << i)) ? '1' : '0';
  }
  *buf = '\0';
}

void printFloatFixedAt(LiquidCrystal &L, int col, int row, float val, int dec, int width) {
  char tmp[12];
  dtostrf(val, 0, dec, tmp);
  L.setCursor(col, row);
  L.print(tmp);
  int len = strlen(tmp);
  for (int i = len; i < width; ++i) L.print(' ');
}

void setup() {
  analogReference(DEFAULT);
  pinMode(PIN_DER, INPUT);
  pinMode(PIN_IZQ, INPUT);

  lcd.begin(16, 2);
  lcd.clear();

  lcd.setCursor(0, 1);

  emaVd = rawAVolt(leerRawProm(PIN_DER));
  emaVi = rawAVolt(leerRawProm(PIN_IZQ));
  lastSwitch = millis();
}

void loop() {
  int rawVd = leerRawProm(PIN_DER);
  int rawVi = leerRawProm(PIN_IZQ);

  float Vd = rawAVolt(rawVd);
  float Vi = rawAVolt(rawVi);

  emaVd += EMA_ALPHA * (Vd - emaVd);
  emaVi += EMA_ALPHA * (Vi - emaVi);
  Vd = emaVd;
  Vi = emaVi;

  const float eps = 0.0001f;
  if (Vd < eps) Vd = eps;
  if (Vd > Vs - eps) Vd = Vs - eps;

  float Vg = Vd - Vi;

  if ((millis() - lastSwitch) >= SWITCH_MS) {
    showVin = !showVin;
    lastSwitch = millis();
  }

  if (showVin) {
    lcd.setCursor(0, 0);
    lcd.print("Vin:");
    printFloatFixedAt(lcd, 5, 0, Vd, 3, 10);
    lcd.setCursor(15, 0);
    lcd.print('V');
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Vg: ");
    printFloatFixedAt(lcd, 5, 0, Vg, 3, 10);
    lcd.setCursor(15, 0);
    lcd.print('V');
  }

  char binbuf[11];
  
  intToBin8(rawVd/4, binbuf);
  lcd.setCursor(0, 1);
  lcd.print(binbuf);
  int bLen = strlen(binbuf);
  lcd.print(' ');
  int di=rawVd/4;
  lcd.print(di);

  delay(150);
}