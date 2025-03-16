const int trigPin = 5;  // Pin Trig conectado a GPIO 5
const int echoPin = 18; // Pin Echo conectado a GPIO 18

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Enviamos un pulso de 10 microsegundos al pin Trig
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Medimos el tiempo que tarda en llegar el eco
  long duration = pulseIn(echoPin, HIGH, 30000); // Timeout de 30 ms

  // Si no se detecta eco, duration será 0
  if (duration == 0) {
    Serial.println("Error: No se detectó eco. Verifica las conexiones.");
  } else {
    // Calculamos la distancia en centímetros
    float distance = duration * 0.0343 / 2;

    // Mostramos la distancia en el monitor serie
    Serial.print("Distancia: ");
    Serial.print(distance);
    Serial.println(" cm");
  }

  // Esperamos un momento antes de la siguiente medición
  delay(1000);
}
