#include <WiFi.h>
#include <WebServer.h>

// Reemplaza con las credenciales de tu red WiFi
const char* ssid = "Cybersystech";
const char* password = "00000000";

// Crea una instancia del servidor web en el puerto 80
WebServer servidor(80);

// Define los pines GPIO para los LEDs
const int pinLed1 = 2; // LED interno
const int pinLed2 = 4; // Define el pin para el segundo LED
const int pinLed3 = 5; // Define el pin para el tercer LED

// Prototipos de funciones
void manejarRaiz();
void manejarLed1();
void manejarLed2();
void manejarLed3();

void setup() {
  Serial.begin(115200);
  pinMode(pinLed1, OUTPUT);
  pinMode(pinLed2, OUTPUT);
  pinMode(pinLed3, OUTPUT);
  digitalWrite(pinLed1, LOW);
  digitalWrite(pinLed2, LOW);
  digitalWrite(pinLed3, LOW);

  // Conexión a la red WiFi
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado.");
  Serial.println("Dirección IP: ");
  Serial.println(WiFi.localIP());
  servidor.begin();

  // Define las rutas del servidor web
  servidor.on("/", manejarRaiz);
  servidor.on("/led1", manejarLed1);
  servidor.on("/led2", manejarLed2);
  servidor.on("/led3", manejarLed3);
}

void loop() {
  servidor.handleClient();
}

void manejarRaiz() {
  String html = "<!DOCTYPE html><html>"
                "<head><title>Control de LEDs ESP32</title></head>"
                "<body>"
                "<h1>Control de LEDs ESP32</h1>"
                "<p><a href=\"/led1\"><button>LED 1</button></a></p>"
                "<p><a href=\"/led2\"><button>LED 2</button></a></p>"
                "<p><a href=\"/led3\"><button>LED 3</button></a></p>"
                "</body></html>";
  servidor.send(200, "text/html", html);
}

void manejarLed1() {
  digitalWrite(pinLed1, HIGH);
  delay(300);
  digitalWrite(pinLed1, LOW);
  servidor.sendHeader("Location", "/");
  servidor.send(303);
}

void manejarLed2() {
  digitalWrite(pinLed2, HIGH);
  delay(300);
  digitalWrite(pinLed2, LOW);
  servidor.sendHeader("Location", "/");
  servidor.send(303);
}

void manejarLed3() {
  digitalWrite(pinLed3, HIGH);
  delay(300);
  digitalWrite(pinLed3, LOW);
  servidor.sendHeader("Location", "/");
  servidor.send(303);
}
