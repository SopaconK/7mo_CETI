/*
  Control de LED RGB con ESP32 y Servidor Web
  - Código actualizado para ser compatible con la versión 3.x del Core de ESP32 para Arduino.
  - Autor de la actualización: Gemini
  - Fecha: 2024-10-17
*/

#include <WiFi.h>
#include <esp_http_server.h> // Librería actualizada para el servidor web

// --- CONFIGURACIÓN WIFI ---
const char* ssid = "Emiliano";       // Reemplaza con el nombre de tu red
const char* password = "Eldiablaso1234567";  // Reemplaza con tu contraseña

// --- PINES GPIO PARA EL LED RGB ---
const int pinRojo = 23;
const int pinVerde = 22;
const int pinAzul = 21;

// --- CONFIGURACIÓN PWM (LEDC) ---
const int frecuenciaPWM = 5000;
const int resolucionPWM = 8; // Rango de 0 a 255

// --- VARIABLES PARA GUARDAR LOS COLORES ---
int valorRojo = 0;
int valorVerde = 0;
int valorAzul = 0;

// --- CÓDIGO HTML DE LA PÁGINA WEB ---
String generarPaginaWeb() {
  String ptr = "<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width, initial-scale=1'><title>Control LED RGB</title>";

  ptr += "</head><body><h1>Control de LED RGB</h1>";
  ptr += "<p>Mueve las perillas para cambiar el color del LED.</p>";

  // Slider Rojo
  ptr += "<p>Rojo: <span id='valorR'>" + String(valorRojo) + "</span></p>";
  ptr += "<input type='range' min='0' max='255' class='slider' id='r' value='" + String(valorRojo) + "' oninput='enviarColor(\"r\", this.value)'>";

  // Slider Verde
  ptr += "<p>Verde: <span id='valorG'>" + String(valorVerde) + "</span></p>";
  ptr += "<input type='range' min='0' max='255' class='slider' id='g' value='" + String(valorVerde) + "' oninput='enviarColor(\"g\", this.value)'>";

  // Slider Azul
  ptr += "<p>Azul: <span id='valorB'>" + String(valorAzul) + "</span></p>";
  ptr += "<input type='range' min='0' max='255' class='slider' id='b' value='" + String(valorAzul) + "' oninput='enviarColor(\"b\", this.value)'>";

  ptr += "<div id='colorBox' style='background-color:rgb(" + String(valorRojo) + "," + String(valorVerde) + "," + String(valorAzul) + ");'></div>";

  ptr += "<script>";
  ptr += "function enviarColor(color, valor) {";
  ptr += " var xhr = new XMLHttpRequest();";
  ptr += " xhr.open('GET', '/slider?color=' + color + '&valor=' + valor, true);";
  ptr += " xhr.send();";
  ptr += " document.getElementById('valor' + color.toUpperCase()).innerText = valor;";
  ptr += " var r = document.getElementById('r').value;";
  ptr += " var g = document.getElementById('g').value;";
  ptr += " var b = document.getElementById('b').value;";
  ptr += " document.getElementById('colorBox').style.backgroundColor = 'rgb(' + r + ',' + g + ',' + b + ')';";
  ptr += "}";
  ptr += "</script></body></html>";
  return ptr;
}

esp_err_t root_handler(httpd_req_t *req) {
    String html = generarPaginaWeb();
    httpd_resp_set_type(req, "text/html");
    return httpd_resp_send(req, html.c_str(), html.length());
}

esp_err_t slider_handler(httpd_req_t *req) {
    char* buf;
    size_t buf_len;

    buf_len = httpd_req_get_url_query_len(req) + 1;
    if (buf_len > 1) {
        buf = (char*)malloc(buf_len);
        if (httpd_req_get_url_query_str(req, buf, buf_len) == ESP_OK) {
            char color_param[8];
            char valor_param[8];

            if (httpd_query_key_value(buf, "color", color_param, sizeof(color_param)) == ESP_OK &&
                httpd_query_key_value(buf, "valor", valor_param, sizeof(valor_param)) == ESP_OK) {

                int valor = atoi(valor_param);
                String color = String(color_param);

                if (color == "r") {
                    valorRojo = valor;
                    // AHORA USAMOS EL PIN EN LUGAR DEL CANAL
                    ledcWrite(pinRojo, 255 - valorRojo);
                    Serial.println("Rojo actualizado: " + String(valorRojo));
                } else if (color == "g") {
                    valorVerde = valor;
                    ledcWrite(pinVerde, 255 - valorVerde);
                    Serial.println("Verde actualizado: " + String(valorVerde));
                } else if (color == "b") {
                    valorAzul = valor;
                    ledcWrite(pinAzul, 255 - valorAzul);
                    Serial.println("Azul actualizado: " + String(valorAzul));
                }
            }
        }
        free(buf);
    }
    
    httpd_resp_set_status(req, "204 No Content");
    return httpd_resp_send(req, NULL, 0);
}

// --- FUNCIÓN PARA INICIAR EL SERVIDOR WEB ---
void start_webserver() {
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.lru_purge_enable = true;

    Serial.println("Iniciando servidor...");
    if (httpd_start(&server, &config) == ESP_OK) {
        const httpd_uri_t root_uri = {
            .uri       = "/",
            .method    = HTTP_GET,
            .handler   = root_handler,
            .user_ctx  = NULL
        };
        httpd_register_uri_handler(server, &root_uri);

        const httpd_uri_t slider_uri = {
            .uri       = "/slider",
            .method    = HTTP_GET,
            .handler   = slider_handler,
            .user_ctx  = NULL
        };
        httpd_register_uri_handler(server, &slider_uri);
    } else {
        Serial.println("Error al iniciar el servidor!");
    }
}

void setup() {
    Serial.begin(9600);
    ledcAttach(pinRojo, frecuenciaPWM, resolucionPWM);
    ledcAttach(pinVerde, frecuenciaPWM, resolucionPWM);
    ledcAttach(pinAzul, frecuenciaPWM, resolucionPWM);

    // --- CONEXIÓN WIFI ---
    WiFi.begin(ssid, password);
    Serial.print("Conectando a WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConectado!");
    Serial.print("Direccion IP: ");
    Serial.println(WiFi.localIP());

    // --- INICIAR SERVIDOR WEB ---
    start_webserver();
    Serial.println("Servidor HTTP iniciado.");
}

void loop() {
    delay(1000);
}