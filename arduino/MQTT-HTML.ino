//---------- Librerías ----------
#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include "max6675.h"

//--------- Declaración de variables --------
WiFiClient esp32Client;
PubSubClient mqttClient(esp32Client);

const char *ssid = "Datco_usuarios";  // Nombre de la red WiFi
const char *password = "Datco_Chile"; // Contraseña de la red WiFi

char *server = "190.110.108.59"; // IP del servidor que funciona como broker
int port = 1883;                 // Puerto por defecto de un broker

float temperatura = 0;
int count = 0;
char msj[40];
#define CS 5
#define SO 19
#define SCK 18

MAX6675 myMAX6675(SCK, CS, SO);

//------------ Inicializar WiFi -------------
void wifiInit()
{
    Serial.print("Conectándose a ");
    Serial.println(ssid);

    WiFi.begin(ssid, password); // Comienza a conectarse al Wifi

    // Esto ocurre MIENTRAS se está conectando
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print("."); // Muestra un punto cada 0,5 segundos
        delay(500);
    }

    Serial.println("");
    Serial.println("Conectado a la red WiFi.");
    Serial.print("Dirección IP: ");
    Serial.println(WiFi.localIP());
}

//------------ Callback del MQTT -------------
void callback(char *topic, byte *payload, unsigned int length)
{
    String mensaje = "";

    Serial.print("Mensaje recibido desde [");
    Serial.print(topic);
    Serial.println("]");

    for (int i = 0; i < length; i++)
    {
        Serial.println("El mensaje es: " + mensaje);
        mensaje += (char)payload[i];
    }

    Serial.println("Mensaje -> " + mensaje);
}

//------------- Reconectarse al WiFi -------------
void reconnect()
{
    while (!mqttClient.connected())
    {
        Serial.println("Intentando conexión MQTT...");

        if (mqttClient.connect("arduinoClient"))
        {
            Serial.println("Conectado al broker.");
            //Chile
            //Chile - Oficina 1 - Temperatura
            if (mqttClient.subscribe("Datco/Chile/Oficina_1/Temperatura"))
            {
                Serial.println("Suscrito a Datco/Chile/Oficina_1/Temperatura.");
            }
            else
            {
                Serial.println("Fallo suscripción a Datco/Chile/Oficina_1/Temperatura.");
            }

            //Chile - Oficina 2 - Temperatura
            if (mqttClient.subscribe("Datco/Chile/Oficina_2/Temperatura"))
            {
                Serial.println("Suscrito a Datco/Chile/Oficina_2/Temperatura.");
            }
            else
            {
                Serial.println("Fallo suscripción a Datco/Chile/Oficina_2/Temperatura.");
            }

            //Chile - Oficina 3 - Temperatura
            if (mqttClient.subscribe("Datco/Chile/Oficina_3/Temperatura"))
            {
                Serial.println("Suscrito a Datco/Chile/Oficina_3/Temperatura.");
            }
            else
            {
                Serial.println("Fallo suscripción a Datco/Chile/Oficina_3/Temperatura.");
            }

<<<<<<< HEAD
            /*
=======
>>>>>>> 5410a7602edf18338c4ae542fa2d83f2d0b38200
            //Chile - Oficina 1 - Humedad
            if (mqttClient.subscribe("Datco/Chile/Oficina_1/Humedad"))
            {
                Serial.println("Suscrito a Datco/Chile/Oficina_1/Humedad");
            }
            else
            {
                Serial.println("Fallo suscripción a Datco/Chile/Oficina_1/Humedad");
            }

            //Chile - Oficina 2 - Humedad
            if (mqttClient.subscribe("Datco/Chile/Oficina_2/Humedad"))
            {
                Serial.println("Suscrito a Datco/Chile/Oficina_2/Humedad");
            }
            else
            {
                Serial.println("Fallo suscripción a Datco/Chile/Oficina_2/Humedad");
            }

            //Chile - Oficina 3 - Humedad
            if (mqttClient.subscribe("Datco/Chile/Oficina_3/Humedad"))
            {
                Serial.println("Suscrito a Datco/Chile/Oficina_3/Humedad");
            }
            else
            {
                Serial.println("Fallo suscripción a Datco/Chile/Oficina_3/Humedad");
            }
<<<<<<< HEAD
            */
=======
>>>>>>> 5410a7602edf18338c4ae542fa2d83f2d0b38200

            //Argentina
            //Argentina - Oficina 1 - Temperatura
            if (mqttClient.subscribe("Datco/Argentina/Oficina_1/Temperatura"))
            {
                Serial.println("Suscrito a Datco/Argentina/Oficina_1/Temperatura.");
            }
            else
            {
                Serial.println("Fallo suscripción a Datco/Argentina/Oficina_1/Temperatura.");
            }

            //Argentina - Oficina 2 - Temperatura
            if (mqttClient.subscribe("Datco/Argentina/Oficina_2/Temperatura"))
            {
                Serial.println("Suscrito a Datco/Argentina/Oficina_2/Temperatura.");
            }
            else
            {
                Serial.println("Fallo suscripción a Datco/Argentina/Oficina_2/Temperatura.");
            }

            //Argentina - Oficina 3 - Temperatura
            if (mqttClient.subscribe("Datco/Argentina/Oficina_3/Temperatura"))
            {
                Serial.println("Suscrito a Datco/Argentina/Oficina_3/Temperatura.");
            }
            else
            {
                Serial.println("Fallo suscripción a Datco/Argentina/Oficina_3/Temperatura.");
            }

<<<<<<< HEAD
            /*
=======
>>>>>>> 5410a7602edf18338c4ae542fa2d83f2d0b38200
            //Argentina - Oficina 1 - Humedad
            if (mqttClient.subscribe("Datco/Argentina/Oficina_1/Humedad"))
            {
                Serial.println("Suscrito a Datco/Argentina/Oficina_1/Humedad");
            }
            else
            {
                Serial.println("Fallo suscripción a Datco/Argentina/Oficina_1/Humedad");
            }

            //Argentina - Oficina 2 - Humedad
            if (mqttClient.subscribe("Datco/Argentina/Oficina_2/Humedad"))
            {
                Serial.println("Suscrito a Datco/Argentina/Oficina_2/Humedad");
            }
            else
            {
                Serial.println("Fallo suscripción a Datco/Argentina/Oficina_2/Humedad");
            }

            //Argentina - Oficina 3 - Humedad
            if (mqttClient.subscribe("Datco/Argentina/Oficina_3/Humedad"))
            {
                Serial.println("Suscrito a Datco/Argentina/Oficina_3/Humedad");
            }
            else
            {
                Serial.println("Fallo suscripción a Datco/Argentina/Oficina_3/Humedad");
            }
<<<<<<< HEAD
            */
=======
>>>>>>> 5410a7602edf18338c4ae542fa2d83f2d0b38200
        }
        else
        {
            Serial.print("Falló la conexión. Error -> ");
            Serial.println(mqttClient.state());
            Serial.println("Intentando de nuevo en 5 segundos...");
            delay(5000);
        }
    }
}

//--------- Setup del Arduino ----------
void setup()
{
    Serial.begin(115200);
    delay(10);
    wifiInit();
    mqttClient.setServer(server, port);
    mqttClient.setCallback(callback);
}

//---------- Función Loop del Arduino ----------
void loop()
{
    // Si no está conectado, se trata de conectar.
    if (!mqttClient.connected())
    {
        reconnect();
    }
    else
    {
        mqttClient.loop();

        temperatura = myMAX6675.readCelsius();

        String str = "Temperatura -> " + String(temperatura);
        str.toCharArray(msj, 40);

        Serial.print("Dato #");
        Serial.print(count);
        Serial.print(". La temperatura es: ");
        Serial.print(temperatura);
        Serial.println("°C.");
        count++;

        // Las siguientes 3 lineas sirven para publicar los datos en el topico Temp cada 5 segundos
        sprintf(msj, "Temperatura: %.2f °C", temperatura);
        mqttClient.publish("Temp", msj);
        delay(5000);
    }
}
