#include <WiFi.h>
#include <WebServer.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// Reemplaza con las credenciales de tu red WiFi
const char* ssid = "Cybersystech";
const char* password = "00000000";

// Crea una instancia del servidor web en el puerto 80
WebServer servidor(80);

// Define el pin GPIO donde está conectado el LED
const int pinLed = 2;

// Variable para almacenar el estado actual del LED (encendido/apagado)
volatile bool estadoLed = false;

// Prototipos de funciones para las tareas de FreeRTOS
void tareaServidorWeb(void *pvParameters);
void tareaControlLed(void *pvParameters);
void manejarRaiz();
void manejarToggleLed();
void manejarEstadoLed();

void setup() {
  Serial.begin(115200); // Inicia la comunicación serial a 115200 baudios.
  pinMode(pinLed, OUTPUT); // Configura el pin del LED como salida.
  digitalWrite(pinLed, LOW); // Asegura que el LED esté apagado al iniciar.

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
  servidor.begin(); // Inicia el servidor web.

  // Define las rutas del servidor web
  servidor.on("/", manejarRaiz);
  servidor.on("/toggle", manejarToggleLed);
  servidor.on("/estado", manejarEstadoLed);

  // Crea tareas en diferentes núcleos para el servidor web y el control del LED
  xTaskCreatePinnedToCore(tareaServidorWeb, "TareaServidorWeb", 10000, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(tareaControlLed, "TareaControlLed", 10000, NULL, 1, NULL, 1);
}

void loop() {
  // El loop principal está vacío ya que estamos utilizando tareas de FreeRTOS.
}

void tareaServidorWeb(void *pvParameters) {
  for (;;) {
    servidor.handleClient(); // Maneja los clientes del servidor web.
    delay(1); // Pequeña pausa para permitir el cambio de contexto entre tareas.
  }
}

void tareaControlLed(void *pvParameters) {
  for (;;) {
    // Aquí se podría agregar código para controlar el LED basado en alguna condición.
    delay(1000); // Un delay para simular trabajo en la tarea.
  }
}

void manejarRaiz() {
  String estado = estadoLed ? "ENCENDIDO" : "APAGADO";
  String html = "<!DOCTYPE html><html>"
                "<head><title>Control de LED ESP32</title>"
                "<script>"
                "setInterval(function() {"
                "fetch('/estado').then(response => response.text()).then(data => {"
                "document.getElementById('estadoLed').innerText = data;"
                "});"
                "}, 1000);"
                "</script>"
                "</head>"
                "<body>"
                "<h1>Control de LED ESP32</h1>"
                "<p>Estado del LED: <strong>" + estado + "</strong></p>"
                "<p><a href=\"/toggle\"><button style='height:100px;width:200px;font-size:30px;'>Cambiar Estado del LED</button></a></p>"
                "</body></html>";
  servidor.send(200, "text/html", html);
}

void manejarToggleLed() {
  estadoLed = !estadoLed;
  digitalWrite(pinLed, estadoLed ? HIGH : LOW);
  servidor.sendHeader("Location", "/");
  servidor.send(303);
}

void manejarEstadoLed() {
  servidor.send(200, "text/plain", (estadoLed ? "ENCENDIDO" : "APAGADO"));
}
