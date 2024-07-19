#include <WiFi.h>
#include <WebServer.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

const char* ssid = "Internet_Services_1418";
const char* password = "meia242113";

// Configuración de IP estática
IPAddress local_IP(192, 168, 100, 100);
IPAddress gateway(192, 168, 100, 1);
IPAddress subnet(255, 255, 255, 0);

WebServer server(80);

int lightPin = 2;  // Pin donde está conectada la luz (LED)

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

String targetTime = "22:05";  // Variable para almacenar la hora establecida

void handleRoot() {
  server.send(200, "text/html", "<form action=\"/set-time\" method=\"POST\"><input type=\"time\" name=\"time\"><input type=\"submit\" value=\"Set Time\"></form>");
}

void handleSetTime() {
  if (server.hasArg("time")) {
    targetTime = server.arg("time");
    server.send(200, "text/plain", "Time set to: " + targetTime);
  } else {
    server.send(400, "text/plain", "Time parameter missing");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(lightPin, OUTPUT);
  digitalWrite(lightPin, LOW);

  // Configuración de IP estática
  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/set-time", HTTP_POST, handleSetTime);

  server.begin();

  // Configurar NTPClient
  timeClient.begin();
  timeClient.setTimeOffset(-14400);  // Ajusta según tu zona horaria
}

void loop() {
  server.handleClient();
  timeClient.update();

  String currentTime = timeClient.getFormattedTime().substring(0, 5);

  if (targetTime != "" && currentTime == targetTime) {
    digitalWrite(lightPin, HIGH);
  } else {
    digitalWrite(lightPin, LOW);
  }
}
