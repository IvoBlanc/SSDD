
#include <Arduino.h>

const int ledPin = 2;  // Pin donde está conectado el LED
const int interval = 1000;  // Intervalo de tiempo en milisegundos para el parpadeo

void setup() {
  pinMode(ledPin, OUTPUT);  // Configurar el pin como salida
}

void loop() {
  digitalWrite(ledPin, HIGH);  // Encender el LED
  delay(interval);  // Esperar
  digitalWrite(ledPin, LOW);  // Apagar el LED
  delay(interval);  // Esperar

  printf ("sssss");
  delay(1);
}
