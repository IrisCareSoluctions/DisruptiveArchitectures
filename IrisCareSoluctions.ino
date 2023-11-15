/* 
	=======================================
	IrisCareSoluctions
    
    Sensor Ultrassom HC-SR04 e Buzzer
	
	Demonstra o uso de sensor ultrassom
	simplificado HC-SR04 no Arduino. Ativa o
	Buzzer toda vez que sensor captar objeto
	a certa distância.
	
	=======================================    
*/

const int pinoBuzzer = 2; //PINO DIGITAL EM QUE O BUZZER ESTÁ CONECTADO

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

void setup()
{
  Serial.begin(9600);

}

void loop()
{
  // measure the ping time in cm
  cm = 0.01723 * readUltrasonicDistance(5, 7);
  // convert to inches by dividing by 2.54
  inches = (cm / 2.54);
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.println("cm");
  delay(100); // Wait for 100 millisecond(s)
  
  if(cm <= 50){// SE A DISTÂNCIA ENTRE O OBJETO E O SENSOR ULTRASONICO FOR MENOR QUE 50CM, FAZ
  tone(pinoBuzzer,1500);//ACIONA O BUZZER
  }else{//SENÃO, FAZ
   noTone(pinoBuzzer);//BUZZER PERMANECE DESLIGADO
  }
  
  
}