// Definición de pines
const int trigPin = 5;  // Pin de Trigger
const int echoPin = 18; // Pin de Echo

const int leds[] = {15, 2, 4, 21, 22, 23}; // LEDs indicadores de distancia

// Variables para almacenar la distancia y el tiempo
long duration;
int distance;

void setup() {
  // Inicializar la comunicación serial
  Serial.begin(115200);

  // Configurar los pines como entrada/salida
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Configurar los pines de los LEDs como salidas
  for (int k = 0; k <= 5; k++) {
    pinMode(leds[k], OUTPUT);
  }
}

void loop() {
  // Limpiar el pin de Trigger
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Enviar un pulso de 10 microsegundos al pin de Trigger
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Leer el pin de Echo y calcular la duración del pulso
  duration = pulseIn(echoPin, HIGH);

  // Calcular la distancia en centímetros
  distance = duration * 0.034 / 2;

  // Mostrar la distancia en el monitor serial
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Llamar a la función para controlar los LEDs según la distancia
  medirNivelAgua();

  // Esperar un momento antes de la siguiente medición
  delay(1000);
}

void medirNivelAgua() {
  if (distance > 80) { // Distancia mayor a 80cm, se apagan todos los LEDs
    for (int k = 0; k <= 5; k++) {
      digitalWrite(leds[k], LOW);
    }
  } else if (distance <= 80 && distance > 60) { // Distancia entre 80cm y 60cm, se enciende el primer LED
    digitalWrite(leds[0], HIGH);
    for (int k = 1; k <= 5; k++) {
      digitalWrite(leds[k], LOW);
    }
  } else if (distance <= 60 && distance > 40) { // Distancia entre 60cm y 40cm, se encienden los primeros 2 LEDs
    for (int k = 0; k <= 1; k++) {
      digitalWrite(leds[k], HIGH);
    }
    for (int k = 2; k <= 5; k++) {
      digitalWrite(leds[k], LOW);
    }
  } else if (distance <= 40 && distance > 30) { // Distancia entre 40cm y 30cm, se encienden los primeros 3 LEDs
    for (int k = 0; k <= 2; k++) {
      digitalWrite(leds[k], HIGH);
    }
    for (int k = 3; k <= 5; k++) {
      digitalWrite(leds[k], LOW);
    }
  } else if (distance <= 30 && distance > 20) { // Distancia entre 30cm y 20cm, se encienden los primeros 4 LEDs
    for (int k = 0; k <= 3; k++) {
      digitalWrite(leds[k], HIGH);
    }
    for (int k = 4; k <= 5; k++) {
      digitalWrite(leds[k], LOW);
    }
  } else if (distance <= 20 && distance > 15) { // Distancia entre 20cm y 15cm, se encienden los primeros 5 LEDs
    for (int k = 0; k <= 4; k++) {
      digitalWrite(leds[k], HIGH);
    }
    digitalWrite(leds[5], LOW);
  } else if (distance <= 15) { // Distancia menor o igual a 15cm, se encienden todos los LEDs
    for (int k = 0; k <= 5; k++) {
      digitalWrite(leds[k], HIGH);
    }
  }
}