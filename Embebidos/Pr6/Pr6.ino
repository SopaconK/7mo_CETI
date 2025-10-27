#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 177); 
EthernetServer server(80);

const int RELE1_PIN = 7;
const int RELE2_PIN = 8;

boolean rele1_estado = false; 
boolean rele2_estado = false;

void setup() {
  Serial.begin(9600);

  pinMode(RELE1_PIN, OUTPUT);
  pinMode(RELE2_PIN, OUTPUT);

  digitalWrite(RELE1_PIN, HIGH);
  digitalWrite(RELE2_PIN, HIGH);

  Ethernet.begin(mac, ip);
  server.begin();
  
  Serial.print("Servidor iniciado en la IP: ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  EthernetClient client = server.available();
  if (client) {
    Serial.println("Nuevo cliente conectado.");
    boolean currentLineIsBlank = true;
    String request = ""; 
    
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        request += c; 
        
        if (c == '\n' && currentLineIsBlank) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close"); 
          client.println(); 

          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<head><title>Control de Relevadores</title>");
          client.println("<meta name='viewport' content='width=device-width, initial-scale=1'>");
          client.println("<style>");
          client.println("body { font-family: Arial, sans-serif; text-align: center; background-color: #282c34; color: white; }");
          client.println("h1 { color: #61dafb; }");
          client.println(".boton { display: block; width: 80%; padding: 20px; margin: 20px auto; font-size: 24px; border: none; border-radius: 10px; cursor: pointer; }");
          client.println(".on { background-color: #28a745; color: white; }");
          client.println(".off { background-color: #dc3545; color: white; }");
          client.println("</style></head>");
          client.println("<body>");
          client.println("<h1>Control de Dispositivos con Arduino</h1>");

          client.println("<h2>Foco Incandescente</h2>");
          if (rele1_estado) {
            client.println("<a href=\"/?rele1=off\"><button class='boton off'>APAGAR</button></a>");
          } else {
            client.println("<a href=\"/?rele1=on\"><button class='boton on'>ENCENDER</button></a>");
          }

          client.println("<h2>Ventilador</h2>");
          if (rele2_estado) {
            client.println("<a href=\"/?rele2=off\"><button class='boton off'>APAGAR</button></a>");
          } else {
            client.println("<a href=\"/?rele2=on\"><button class='boton on'>ENCENDER</button></a>");
          }
          
          client.println("</body></html>");
          break; 
        }
        if (c == '\n') {
          currentLineIsBlank = true;
        } else if (c != '\r') {
          currentLineIsBlank = false;
        }

        if(request.indexOf("GET /?rele1=on") != -1) {
          Serial.println("Peticion para encender Rele 1");
          digitalWrite(RELE1_PIN, LOW); 
          rele1_estado = true;
        }
        if(request.indexOf("GET /?rele1=off") != -1) {
          Serial.println("Peticion para apagar Rele 1");
          digitalWrite(RELE1_PIN, HIGH); 
          rele1_estado = false;
        }
        if(request.indexOf("GET /?rele2=on") != -1) {
          Serial.println("Peticion para encender Rele 2");
          digitalWrite(RELE2_PIN, LOW); 
          rele2_estado = true;
        }
        if(request.indexOf("GET /?rele2=off") != -1) {
          Serial.println("Peticion para apagar Rele 2");
          digitalWrite(RELE2_PIN, HIGH);
          rele2_estado = false;
        }
      }
    }
    
    delay(1);

    client.stop();
    Serial.println("Cliente desconectado.");
  }
}