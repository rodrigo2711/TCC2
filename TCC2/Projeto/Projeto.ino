#include <ESP8266WiFi.h>
#include <IRremoteESP8266.h> //INCLUSÃO DE BIBLIOTECA

IRsend irsend(4); //FUNÇÃO RESPONSÁVEL PELO MÉTODO DE ENVIO DO SINAL IR / UTILIZA O GPIO4(D)
#ifndef STASSID
#define STASSID "Natalia"
#define STAPSK  "flamengo"
#endif

const char* ssid     = "Natalia";
const char* password = "flamengo";

const char* host = "192.168.15.111";
const uint16_t port = 2000;
int i=0;

int tamanho = 68; //TAMANHO DA LINHA RAW(68 BLOCOS)
int frequencia = 32; //FREQUÊNCIA DO SINAL IR(32KHz)
unsigned int ligadesliga[68] = {9000,4550,500,650,550,650,550,1750,500,700,500,650,500,650,500,650,600,600,500,1800,500,1800,550,650,500,1800,500,1800,500,1800,500,1800,550,1800,500,650,500,650,500,650,500,1800,500,700,500,650,500,650,500,650,550,1750,500,1800,550,1750,500,650,550,1750,500,1800,500,1800,550,1750,500}; //COLE A LINHA RAW CORRESPONDENTE DENTRO DAS CHAVES
unsigned int aum_volume[68] = {9000,4600,500,650,500,650,500,1800,500,650,500,650,500,650,500,650,500,650,500,1800,500,1800,500,650,550,1750,500,1800,500,1800,500,1800,500,1800,500,650,500,1800,500,650,500,650,500,650,500,650,500,650,500,650,500,1800,500,650,500,1800,500,1800,500,1800,500,1800,500,1800,500,1800,500}; //COLE A LINHA RAW CORRESPONDENTE DENTRO DAS CHAVES
unsigned int dim_volume[68] = {}; //COLE A LINHA RAW CORRESPONDENTE DENTRO DAS CHAVES


void setup() {
  irsend.begin(); //INICIALIZA A FUNÇÃO
  Serial.begin(115200);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  static bool wait = false;

  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    return;
  }

  // This will send a string to the server
  Serial.println("sending data to server");
  if (client.connected()) {
    client.println("hello from ESP8266");
  }

  // wait for data to be available
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      delay(60000);
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  Serial.println("receiving from remote server");
  // not testing 'client.connected()' since we do not need to send data here
  while (client.available()) {
    
    char ch = (client.read());
    Serial.print(ch); 
    i=i+1;
    if(i==4){
        Serial.println();
        if(ch =='1'){
            Serial.println("Liga/Desliga");
            irsend.sendRaw(ligadesliga,tamanho,frequencia);  // PARÂMETROS NECESSÁRIOS PARA ENVIO DO SINAL IR
           delay(50); // TEMPO(EM MILISEGUNDOS) DE INTERVALO ENTRE UM COMANDO E OUTRO
        }
        else if(ch =='2'){
            Serial.print("Aumentar Temperatura");
            irsend.sendRaw(aum_volume,tamanho,frequencia); // PARÂMETROS NECESSÁRIOS PARA ENVIO DO SINAL IR
            delay(50); // TEMPO(EM MILISEGUNDOS) DE INTERVALO ENTRE UM COMANDO E OUTRO
        }  
        else if(ch =='3'){
            Serial.print("Diminuir Temperatura");
            irsend.sendRaw(dim_volume,tamanho,frequencia); // PARÂMETROS NECESSÁRIOS PARA ENVIO DO SINAL IR
            delay(50); // TEMPO(EM MILISEGUNDOS) DE INTERVALO ENTRE UM COMANDO E OUTRO
        } 
        i=0; 
        }
    
    }
      
  // Close the connection
  Serial.println();
  Serial.println("closing connection");
  client.stop();

 /* if (wait) {
    Serial.println("Esperando");
    delay(300000); // execute once every 5 minutes, don't flood remote service
  }
  wait = true;*/
}
