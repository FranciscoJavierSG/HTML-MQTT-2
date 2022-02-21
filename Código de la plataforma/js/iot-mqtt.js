// Declaración del id del cliente
var clientId = "ws" + Math.random(); //Dirección aleatoria

// Declaración de las variables
Temperatura1 = 0;
Temperatura2 = 0;
Temperatura3 = 0;
Temperatura4 = 0;
Temperatura5 = 0;
Temperatura6 = 0;

// Creación de la instancia del cliente
var client = new Paho.MQTT.Client("190.110.108.59", 8083, clientId);

// Se establece el control de Callbacks
client.onConnectionLost = onConnectionLost;
client.onMessageArrived = onMessageArrived;

// Conexión con el cliente
client.connect({ onSuccess: onConnect });

// Función que se llama cuando el cliente se conecta (y se suscribe a los tópicos)
function onConnect() {
  console.log("Conectado MQTT-WebSocket");
  client.subscribe("Datco/Chile/Oficina_1/Temperatura");
  client.subscribe("Datco/Chile/Oficina_2/Temperatura");
  client.subscribe("Datco/Chile/Oficina_3/Temperatura");
  client.subscribe("Datco/Argentina/Oficina_1/Temperatura");
  client.subscribe("Datco/Argentina/Oficina_2/Temperatura");
  client.subscribe("Datco/Argentina/Oficina_3/Temperatura");
  client.subscribe("Datco/Chile/Oficina_1/Rele/1");
  client.subscribe("Datco/Chile/Oficina_2/Rele/1");
  client.subscribe("Datco/Chile/Oficina_2/Rele/2");
  client.subscribe("Datco/Chile/Oficina_3/Rele/1");
  client.subscribe("Datco/Argentina/Oficina_1/Rele/1");
  client.subscribe("Datco/Argentina/Oficina_1/Rele/2");
  client.subscribe("Datco/Argentina/Oficina_1/Rele/3");
  client.subscribe("Datco/Argentina/Oficina_2/Rele/1");
  client.subscribe("Datco/Argentina/Oficina_3/Rele/1");
}

// Función que se llama cuando el cliente pierde la conexión
function onConnectionLost(responseObject) {
  if (responseObject.errorCode !== 0) {
    console.log("Conexión con el broker perdida. Error:" + responseObject.errorMessage);
  }
}

// Función que se llama cuando llega un mensaje
function onMessageArrived(message) {
  console.log(message.destinationName + ": " + message.payloadString);
  if (message.destinationName == 'Datco/Chile/Oficina_1/Temperatura') {
    document.getElementById("CH_OF1_T").textContent = message.payloadString;
    Temperatura1 = parseFloat(message.payloadString);
  }
  if (message.destinationName == 'Datco/Chile/Oficina_2/Temperatura') {
    document.getElementById("CH_OF2_T").textContent = message.payloadString;
    Temperatura2 = parseFloat(message.payloadString);
  }
  if (message.destinationName == 'Datco/Chile/Oficina_3/Temperatura') {
    document.getElementById("CH_OF3_T").textContent = message.payloadString;
    Temperatura3 = parseFloat(message.payloadString);
  }
  if (message.destinationName == 'Datco/Argentina/Oficina_1/Temperatura') {
    document.getElementById("ARG_OF1_T").textContent = message.payloadString;
    Temperatura4 = parseFloat(message.payloadString);
  }
  if (message.destinationName == 'Datco/Argentina/Oficina_2/Temperatura') {
    document.getElementById("ARG_OF2_T").textContent = message.payloadString;
    Temperatura5 = parseFloat(message.payloadString);
  }
  if (message.destinationName == 'Datco/Argentina/Oficina_3/Temperatura') {
    document.getElementById("ARG_OF3_T").textContent = message.payloadString;
    Temperatura6 = parseFloat(message.payloadString);
  }
  if (message.destinationName == 'Datco/Chile/Oficina_1/Rele/1') {
    document.getElementById("CH_OF1_RELE_1").textContent = message.payloadString;
  }
  if (message.destinationName == 'Datco/Chile/Oficina_2/Rele/1') {
    document.getElementById("CH_OF2_RELE_1").textContent = message.payloadString;
  }
  if (message.destinationName == 'Datco/Chile/Oficina_2/Rele/2') {
    document.getElementById("CH_OF2_RELE_2").textContent = message.payloadString;
  }
  if (message.destinationName == 'Datco/Chile/Oficina_3/Rele/1') {
    document.getElementById("CH_OF3_RELE_1").textContent = message.payloadString;
  }
  if (message.destinationName == 'Datco/Argentina/Oficina_1/Rele/1') {
    document.getElementById("ARG_OF1_RELE_1").textContent = message.payloadString;
  }
  if (message.destinationName == 'Datco/Argentina/Oficina_1/Rele/2') {
    document.getElementById("ARG_OF1_RELE_2").textContent = message.payloadString;
  }
  if (message.destinationName == 'Datco/Argentina/Oficina_1/Rele/3') {
    document.getElementById("ARG_OF1_RELE_3").textContent = message.payloadString;
  }
  if (message.destinationName == 'Datco/Argentina/Oficina_2/Rele/1') {
    document.getElementById("ARG_OF2_RELE_1").textContent = message.payloadString;
  }
  if (message.destinationName == 'Datco/Argentina/Oficina_3/Rele/1') {
    document.getElementById("ARG_OF3_RELE_1").textContent = message.payloadString;
  }
}