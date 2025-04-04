int trig = 16;     //Transmisor
int eco = 19;      //Receptor
int duracion;     //Variable para duracion del pulso
int distancia;    //Variable para hallar la distancia

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(eco, INPUT);
  Serial.begin(9600);
}

void loop() {
  //Enviamos el pulso
  digitalWrite(trig, HIGH);
  delay(1);
  digitalWrite(trig, LOW);

  duracion = pulseIn(eco, HIGH);  //Recibe el puslo
  distancia = duracion / 58.2;    //Calculo para hallar la distancia en cm

  Serial.print(distancia);
  Serial.println(" cm");
  delay(500);
}