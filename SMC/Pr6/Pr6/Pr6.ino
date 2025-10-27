
#include <LiquidCrystal.h>

LiquidCrystal lcd(22, 23, 25, 24, 26, 27);


int maximo=120;

const int Trigger = 2;   //Pin digital 2 para el Trigger del sensor
const int Echo = 3;   //Pin digital 3 para el Echo del sensor

void print4digit(int x){
  char d=(x%10)+'0';
  char c=(x/10)%10+'0';
  char b=(x/100)%10+'0';
   char a=(x/1000)%10+'0';
  lcd.print(a);
  lcd.print(b);
  lcd.print(c);
  lcd.print(d);
}

void setup() {

  Serial.begin(9600);
  pinMode(Trigger,OUTPUT);
  pinMode(Echo,INPUT);
  digitalWrite(Trigger,0);
   lcd.begin(16, 2); 

}

int dismm(){
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
  
  int t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
  Serial.println("t");
  Serial.println(t);
  int d = t/6;
  return d;
}




void loop() {



  lcd.clear();
    int d=dismm();
    d=maximo-d;
    lcd.print("Distancia: ");
    print4digit(d);
  Serial.println(d);

    int nv = d*14/107;
  

    lcd.setCursor(0,1);
    lcd.print("Nivel:     ");
    print4digit(nv);

    

    delay(3000);
    lcd.clear();

    int ml=(d*100)/15;
    
      lcd.print("Mililitros: ");
    print4digit(ml);

     lcd.setCursor(0,1);
    lcd.print("Nivel BIN: ");
    Serial.print (" nv ");
    Serial.println(nv);
    lcd.print(String(nv, BIN));

  delay(3000);

  } 

