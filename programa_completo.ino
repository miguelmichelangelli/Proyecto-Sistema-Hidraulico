// Definición de pines
const int trigPin = 5;  // Pin de Trigger
const int echoPin = 18; // Pin de Echo

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
  }
  pinMode(15, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(21, OUTPUT);
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(16,OUTPUT);
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
  ActivarBomba();

  // Esperar un momento antes de la siguiente medición
  delay(500);
}

void medirNivelAgua() {
  if (distance > 30) { // Distancia mayor a 80cm, se apagan todos los LEDs
    digitalWrite(15, LOW);
    digitalWrite(2, LOW);
    digitalWrite(4, LOW);
    digitalWrite(21, LOW);
    digitalWrite(22, LOW);
    digitalWrite(23, LOW);

  } else if (distance <= 30 && distance > 25) { // Distancia entre 80cm y 60cm, se enciende el primer LED
    digitalWrite(15, HIGH);

    digitalWrite(2, LOW);
    digitalWrite(4, LOW);
    digitalWrite(21, LOW);
    digitalWrite(22, LOW);
    digitalWrite(23, LOW);
    
  } else if (distance <= 25 && distance > 20) { // Distancia entre 60cm y 40cm, se encienden los primeros 2 LEDs
    digitalWrite(15, HIGH);
    digitalWrite(2, HIGH);

    digitalWrite(4, LOW);
    digitalWrite(21, LOW);
    digitalWrite(22, LOW);
    digitalWrite(23, LOW);
  } else if (distance <= 20 && distance > 15) { // Distancia entre 40cm y 30cm, se encienden los primeros 3 LEDs
    digitalWrite(15, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(4, HIGH);

    digitalWrite(21, LOW);
    digitalWrite(22, LOW);
    digitalWrite(23, LOW);
  } else if (distance <= 15 && distance > 10) { // Distancia entre 30cm y 20cm, se encienden los primeros 4 LEDs
    digitalWrite(15, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(21, HIGH);

    digitalWrite(22, LOW);
    digitalWrite(23, LOW);
  } else if (distance <= 10 && distance > 5) { // Distancia entre 20cm y 15cm, se encienden los primeros 5 LEDs
    digitalWrite(15, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(21, HIGH);
    digitalWrite(22, HIGH);

    digitalWrite(23, LOW);
  } else if (distance <= 5) { // Distancia menor o igual a 15cm, se encienden todos los LEDs
    digitalWrite(15, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(21, HIGH);
    digitalWrite(22, HIGH);
    digitalWrite(23, HIGH);

  }
  
}
void ActivarBomba() {
  if(distance > 5 && distance <= 15) {
    digitalWrite(16, HIGH);
  }
  else if(distance > 15 || distance <5){
    digitalWrite(16, LOW);
  }
}