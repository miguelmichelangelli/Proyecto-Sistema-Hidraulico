#include <WiFi.h>

// Variables globales de la pagina

const char* ssid = 'NOMBRE_DE_LA_RED'; // credencial de la red wifi
const char* password = 'CONTRASEÑA_DE_LA_RED'; // credencial de la red wifi
int hidraulicSystemReference = 15; // referencia del sistema hidraulico
WifiServer server(80); // servidor web en el puerto 80, por convención

// Parametros que solo se ejecutan al iniciar el programa
void setup() {
    Serial.begin(11520);
    WiFi.begin(ssid, password); // se intentará conectar a la red indicada con la clave indicada

    while (WiFi.status() != WL_CONNECTED) { // entra en el bucle hasta que logre conectarse a la red wifi
        delay(1000);
        Serial.println('Conectando a red WiFi...');
    }
    Serial.println('Conectado a WiFi'); // mensaje a imprimir una vez se haya conectado a la red wifi

    server.begin(); // incializando servidor
    Serial.println('Servidor iniciado');
    Serial.println(WiFi.localIP()); // imprime en el monitor serial la IP a la cual nos conectaremos para ver la pagina
}


// Parametros que se estarán ejecutand constantemente en un bucle para captar cambios
void loop() {
    WiFiClient client = server.available(); // revisa si hay usuarios intentando conectarse al servidor

    if(client) { // manejo del cliente
        int 
    }
}
