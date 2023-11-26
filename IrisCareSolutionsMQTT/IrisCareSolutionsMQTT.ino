#include <PubSubClient.h>
#include <WiFi.h>

const char *ssid = "SuaRedeWiFi";  // Coloque o nome da sua rede WiFi
const char *password = "SuaSenhaWiFi";  // Coloque a senha da sua rede WiFi
const char *mqtt_server = "broker.mqtt.com";  // Coloque o endereço do seu servidor MQTT

const char *topic = "sensor/ultrassom";

WiFiClient espClient;
PubSubClient client(espClient);

const int pinoBuzzer = 2; // PINO DIGITAL EM QUE O BUZZER ESTÁ CONECTADO
int inches = 0;
int cm = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup_wifi()
{
  delay(10);
  // Conectar-se a uma rede WiFi
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Mensagem recebida no tópico: ");
  Serial.println(topic);

  Serial.print("Mensagem:");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect()
{
  // Loop até que estejamos reconectados
  while (!client.connected())
  {
    Serial.print("Tentando se reconectar ao MQTT...");

    // Tente se reconectar
    if (client.connect("arduinoClient"))
    {
      Serial.println("Conectado!");
      // Assine o tópico
      client.subscribe(topic);
    }
    else
    {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" Tente novamente em 5 segundos");
      // Aguarde 5 segundos antes de tentar novamente
      delay(5000);
    }
  }
}

void setup()
{
  Serial.begin(9600);

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop()
{
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();

  // measure the ping time in cm
  cm = 0.01723 * readUltrasonicDistance(5, 7);
  // convert to inches by dividing by 2.54
  inches = (cm / 2.54);
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.println("cm");

  // Publica a leitura do sensor no tópico MQTT
  char msg[10];
  sprintf(msg, "%d", cm);
  client.publish(topic, msg);

  delay(1000); // Aguarde 1 segundo(s)

  if (cm <= 50)
  { // SE A DISTÂNCIA ENTRE O OBJETO E O SENSOR ULTRASSÔNICO FOR MENOR QUE 50CM, FAZ
    tone(pinoBuzzer, 1500); // ACIONA O BUZZER
  }
  else
  { //SENÃO, FAZ
    noTone(pinoBuzzer); //BUZZER PERMANECE DESLIGADO
  }
}
