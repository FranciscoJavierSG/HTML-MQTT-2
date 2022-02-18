//---------- Librerías ----------
#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include "max6675.h"

//--------- Declaración de variables --------
WiFiClient esp32Client;
PubSubClient mqttClient(esp32Client);

const char* ssid = "Datco_usuarios"; //Nombre de la red WiFi
const char* password = "Datco_Chile"; //Contraseña de la red WiFi

char *server = "190.110.108.59"; //IP del servidor que funciona como broker
int port = 1883; //Puerto por defecto de un broker

const int relay = 26;
float temperatura = 0;
int count = 0;
char msj[40];
#define CS 5
#define SO 19
#define SCK 18

MAX6675 myMAX6675(SCK, CS, SO);

//------------ Inicializar WiFi -------------
void wifiInit() {
  Serial.print("Conectándose a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password); //Comienza a conectarse al Wifi

  //Esto ocurre MIENTRAS se está conectando
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("."); //Muestra un punto cada 0,5 segundos
    delay(500);
  }

  Serial.println("");
  Serial.println("Conectado a la red WiFi.");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());
}

//------------ Callback del MQTT -------------
void callback(char* topic, byte* payload, unsigned int length) {
  String mensaje = "";

  Serial.print("Mensaje recibido desde [");
  Serial.print(topic);
  Serial.println("]");

  for (int i = 0; i < length; i++) {
    //Serial.println("El mensaje es: " + mensaje);
    mensaje += (char)payload[i];
  }

  Serial.println("Mensaje -> " + mensaje);

  String str = String(mensaje);
  str.toCharArray(msj, 40);

  Serial.print("Nuevo mensaje -> '");
  Serial.print(msj);
  Serial.println("'");

  //Si es 1, el relé se enciende. Si es 0, se apaga.
  if ((int)strtol(msj, NULL, 10) == 1) {
    digitalWrite(relay, LOW);
    Serial.println("Corriente fluyendo. Led prendido.");
    Serial.print("Mensaje como número -> '");
    Serial.print(msj);
    Serial.println("'");
  } else {
    digitalWrite(relay, HIGH);
    Serial.println("La corriente no fluye. Led apagado.");
    Serial.print("Mensaje como número -> '");
    Serial.print(msj);
    Serial.println("'");
  }
}

//------------- Reconectarse al WiFi -------------
void reconnect() {
  while (!mqttClient.connected()) {
    Serial.println("Intentando conexión MQTT...");

    if (mqttClient.connect("arduinoClient")) {
      Serial.println("Conectado al broker.");
      // Datco/Rele/1
      if (mqttClient.subscribe("Datco/Rele")) {
        Serial.println("Suscrito a Datco/Rele/1");
      } else {
        Serial.println("Fallo en la suscripción a Datco/Rele/1");
      }
    } else {
      Serial.print("Falló la conexión. Error -> ");
      Serial.println(mqttClient.state());
      Serial.println("Intentando de nuevo en 5 segundos...");
      delay(5000);
    }
  }
}

//--------- Setup del Arduino ----------
void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(relay, OUTPUT);
  wifiInit();
  mqttClient.setServer(server, port);
  mqttClient.setCallback(callback);
}

//---------- Función Loop del Arduino ----------
void loop() {
  //Si no está conectado, se trata de conectar.
  if (!mqttClient.connected()) {
    reconnect();
  } else {
    mqttClient.loop();

    temperatura = myMAX6675.readCelsius();

    String str = String(temperatura);
    str.toCharArray(msj, 40);

    Serial.print("Dato #");
    Serial.print(count);
    Serial.print(". La temperatura es: ");
    Serial.print(temperatura);
    Serial.println("°C.");
    count++;

    //Las siguientes 3 lineas sirven para publicar los datos en el topico Datco/Chile/Oficina_1/Temperatura cada 5 segundos
    sprintf(msj, "%.2f", temperatura);
    mqttClient.publish("Datco/Argentina/Oficina_1/Temperatura", msj);
    delay(5000);
  }
}
