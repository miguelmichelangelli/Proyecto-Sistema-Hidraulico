#include <WiFi.h>

const char* SSID = "NOMBRE_DE_LA_RED";
const char* PASSWORD = "CONTRASEÑA_DE_LA_RED";
int hidraulicSystemReference = 15;
WiFiServer Server(80);

String WEB = R"raw_string(
  <!DOCTYPE html>
  <html>
  <head>
      <meta charset='utf-8'>
      <meta name='viewport' content='width=device-width, initial-scale=1'>
      <title>Control Sistema Hidráulico</title>
      <style>
        * {
            box-sizing: border-box;
            padding: 0;
            margin: 0;
        }

        body {
            display: grid;
            grid-template-rows: auto 1fr auto;
            min-height: 100vh;
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            padding: 25px 10px;
            background-color: #f4f4f9;
            color: #333;
        }

        header {
            background-color: #283992;
            color: white;
            padding: 20px;
            text-align: center;
        }

        .titulo {
            margin: 0;
        }

        .universidad {
            margin: 10px 0 20px 0;
            font-size: 1.2em;
        }

        main {
            padding: 20px;
            text-align: center;
        }

        .proyecto {
            margin-bottom: 20px;
            font-size: 1.5em;
            color: #283992;
        }

        footer {
            background-color: #283992;
            color: white;
            padding: 10px 0;
            text-align: center;
        }

        ul {
            display: flex;
            list-style: none;
            justify-content: center;
            padding: 0;
        }

        li {
            border-left: 1px solid #ccc;
            border-right: 1px solid #ccc;
            padding: 0 10px;
        }

        li:first-child {
            border-left: none;
        }

        li:last-child {
            border-right: none;
        }

        form {
            display: flex;
            flex-direction: column;
            background-color: #283992;
            align-items: center;
            color: #f4f4f9;
            height: 350px;
            margin-top: 50px;
        }

        label {
            font-size: 2em;
            font-weight: 700;
            padding-top: 40px;
        }

        input {
            border-radius: 5px;
            width: 150px;
            height: 30px;
            margin: 50px;
        }

        button {
            width: 110px;
            height: 40px;
            cursor: pointer;
            font-weight: 700;
            border-radius: 5px;
        }
      </style>
  </head>
  <body>
      <header>
          <h1 class="titulo">PROYECTO SISTEMAS DE CONTROL I</h1>
          <h3 class="universidad">UNEXPO Vice-Rectorado "Luis Caballero Mejías"</h3>
      </header>
      <main>
          <h2 class="proyecto">Control de Sistema Hidráulico</h2>
          <form id="nivel-form">
              <label for="nivel">Nivel de agua deseado (cm):</label>
              <input type="number" name="reference" id="nivel" min="0" max="80" required>
              <button type="submit">ESTABLECER NIVEL</button>
          </form>
          <div id="mensaje"></div>
      </main>
      <footer>
          <ul class="integrantes">
              <li>Julio Guerrero</li>
              <li>Marlon La Rosa</li>
              <li>Miguel Michelangelli</li>
              <li>Kelvin Prada</li>
              <li>Cleyberth Villarroel</li>
          </ul>
      </footer>
  </body>
  </html>
)raw_string";

void setup() {
  Serial.begin(115200);
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a Red WiFi...");
  }
  Server.begin();
  Serial.print("Conectado. IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
    WiFiClient client = Server.available();
    if (client) {
        String currentLine = "";
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                Serial.write(c); // Depuración

                if (c == '\n') {
                    if (currentLine.length() == 0) {
                        // Respuesta HTTP
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println();
                        client.println(WEB);
                        if (hidraulicSystemReference != 15) {
                            client.print("<script>document.getElementById('mensaje').innerHTML = 'Llenando hasta ");
                            client.print(hidraulicSystemReference);
                            client.println("cm';</script>");
                        }
                        break;
                    } else {
                        // Procesar la línea actual (GET /?reference=...)
                        if (currentLine.startsWith("GET /?reference=")) {
                            int new_ref = currentLine.substring(
                                currentLine.indexOf('=') + 1,
                                currentLine.indexOf(' ')
                            ).toInt();
                            if (new_ref >= 0 && new_ref <= 80) {
                                hidraulicSystemReference = new_ref;
                                Serial.print("Referencia nueva: ");
                                Serial.println(hidraulicSystemReference);
                            }
                        }
                        currentLine = ""; // Reiniciar para la siguiente línea
                    }
                } else if (c != '\r') {
                    currentLine += c; // Acumular caracteres
                }
            }
        }
        client.stop();
    }
}
