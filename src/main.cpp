#include <Arduino.h>

/*
     Ejemplo de conexión usando IP estática
     por Evandro Luis Copercini
     Dominio público - 2017
*/

#include <WiFi.h>

const char *ssid = "blanc";
const char *password = "tiempocompartido";
const char *host = "example.com";
const char *url = "/index.html";

IPAddress local_IP(192, 168, 100, 100);  // IP estática dentro del rango correcto
IPAddress gateway(192, 168, 100, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);    //opcional
IPAddress secondaryDNS(8, 8, 4, 4);  //opcional

void setup() {
  Serial.begin(115200);

  Serial.println("Configurando IP estática...");
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("Error al configurar la IP estática");
  } else {
    Serial.println("Configuración de IP estática exitosa");
  }

  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("¡WiFi conectado!");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("Dirección MAC del ESP: ");
  Serial.println(WiFi.macAddress());
  Serial.print("Máscara de subred: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("IP del gateway: ");
  Serial.println(WiFi.gatewayIP());
  Serial.print("DNS: ");
  Serial.println(WiFi.dnsIP());
}

void loop() {
  delay(5000);

  Serial.print("Conectando a ");
  Serial.println(host);

  // Usar la clase WiFiClient para crear conexiones TCP
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("Conexión fallida");
    return;
  }

  Serial.print("Solicitando URL: ");
  Serial.println(url);

  // Esto enviará la solicitud al servidor
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Tiempo de espera del cliente !");
      client.stop();
      return;
    }
  }

  // Leer todas las líneas de la respuesta del servidor y mostrarlas en el Serial Monitor
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("Cerrando conexión");
  //wee
  
}


