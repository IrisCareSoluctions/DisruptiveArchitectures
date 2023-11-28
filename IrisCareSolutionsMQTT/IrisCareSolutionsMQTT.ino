#include <PubSubClient.h>
#include <WiFi.h>

const char* ssid = "Vilma";
const char* password = "mamis6350";
const char* mqttServer = "SEU_BROKER_MQTT";
const int mqttPort = 1883;
const char* mqttUser = "SEU_USUARIO_MQTT";
const char* mqttPassword = "SUA_SENHA_MQTT";

#define PINO_LED9 9
#define SENSOR 10
#define DELAY 50
#define QUANT_MAX 6
#define TEMPO_PISCA 200

bool VALOR_SENSOR = LOW;
int CONTADOR = 0;
bool SETA_SENSOR = LOW;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  pinMode(PINO_LED9, OUTPUT);
  pinMode(SENSOR, INPUT);
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conectado ao WiFi");

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  VALOR_SENSOR = digitalRead(SENSOR);
  delay(DELAY);
  digitalWrite(PINO_LED9, !VALOR_SENSOR);

  if (VALOR_SENSOR == LOW) {
    SETA_SENSOR = HIGH;
  }
  if (VALOR_SENSOR == HIGH && SETA_SENSOR == HIGH) {
    CONTADOR = CONTADOR + 1;
    SETA_SENSOR = LOW;
    Serial.print("QUANTIDADE DE PEÇAS=");
    Serial.println(CONTADOR);

    // Publicar o valor do contador no tópico "contador"
    client.publish("contador", String(CONTADOR).c_str());
  }

  if (CONTADOR >= QUANT_MAX) {
    client.publish("status", "Quantidade máxima atingida");
    digitalWrite(PINO_LED9, HIGH);
    delay(TEMPO_PISCA);
    digitalWrite(PINO_LED9, LOW);
    delay(TEMPO_PISCA);
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensagem recebida no tópico: ");
  Serial.println(topic);

  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.print("Conteúdo da mensagem: ");
  Serial.println(message);

  // Lógica de controle remoto
  if (strcmp(topic, "controle") == 0) {
    if (message == "LIGAR_LED") {
      digitalWrite(PINO_LED9, HIGH);
      Serial.println("LED ligado");
    } else if (message == "DESLIGAR_LED") {
      digitalWrite(PINO_LED9, LOW);
      Serial.println("LED desligado");
    } else if (message == "ZERAR_CONTADOR") {
      CONTADOR = 0;
      Serial.println("Contador zerado");
    }
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Tentando se reconectar ao MQTT...");

    if (client.connect("ArduinoClient", mqttUser, mqttPassword)) {
      Serial.println("Conectado ao broker MQTT");
      // Assinar os tópicos relevantes aqui
      client.subscribe("controle");
    } else {
      Serial.print("Falha na conexão ao broker, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}
