#include <ESP8266WiFi.h>
#include <IRremoteESP8266.h> //INCLUSÃO DE BIBLIOTECA

IRsend irsend(4); //FUNÇÃO RESPONSÁVEL PELO MÉTODO DE ENVIO DO SINAL IR / UTILIZA O GPIO4(D)
#ifndef STASSID
#define STASSID "VIVO-0A88"
#define STAPSK  "flamengo"
#endif

const char* ssid     = "RODRIGO OI FIBRA 2G";
const char* password = "flamengo";

const char* host = "192.168.1.95";
const uint16_t port = 2000;
int i=0;

int tamanho = 60; //TAMANHO DA LINHA RAW(68 BLOCOS) 
int frequencia = 38; //FREQUÊNCIA DO SINAL IR(32KHz)
unsigned int ligadesliga[60] = {3250,9950,550,1650,500,600,500,600,500,600,500,1650,500,600,450,650,500,600,500,600,500,600,500,600,500,650,500,600,450,600,450,650,450,650,450,1650,500,600,500,650,500,600,500,600,450,1650,500,600,500,600,500,1650,450,1650,500,600,450,650,500}; //COLE A LINHA RAW CORRESPONDENTE DENTRO DAS CHAVES
unsigned int aum_volume[60] = {3200,9950,500,1650,450,650,500,600,500,600,500,1650,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,1650,500,600,500,600,500,600,500,1650,500,600,500,1650,500,600,450,650,450,1700,450,650,500,600,450,600,500,1650,500,1650,500,600,500}; //COLE A LINHA RAW CORRESPONDENTE DENTRO DAS CHAVES
unsigned int dim_volume[60] = {3200,9950,500,1650,500,600,500,600,500,600,500,1650,500,600,450,600,500,600,500,600,450,650,500,600,500,600,500,1650,500,600,500,600,500,600,500,1650,500,600,500,600,500,600,450,650,500,1650,500,600,500,600,500,600,450,1650,500,600,500,600,500}; //COLE A LINHA RAW CORRESPONDENTE DENTRO DAS CHAVES

//unsigned int liga[100] = {3000,9100,500,600,500,1650,500,600,450,650,500,600,500,600,500,600,500,650,500,600,500,1600,500,650,450,650,500,1600,500,1650,450,650,500,1650,450,1600,500,1650,450,1650,450,1650,500,650,500,600,450,650,500,600,500,600,500,650,450,650,500,600,500,600,550,650,450,650,500,600,500,600,500,650,450,650,500,600,500,600,500,650,500,600,500,650,500,600,500,650,500,600,450,650,450,650,550,600,500,600,500,650,450}; //COLE A LINHA RAW CORRESPONDENTE DENTRO DAS CHAVES
//unsigned int liga1[100] ={3000,9150,400,1600,300,700,300,650,300,650,350,650,300,750,300,700,300,650,350,750,250,1650,350,700,300,700,300,1650,300,700,300,1650,400,1650,350,1700,300,1650,300,1700,300,1650,300,700,300,750,300,700,300,700,300,700,300,700,300,700,300,700,300,700,300,700,300,700,300,650,300,700,300,650,350,700,300,700,300,700,300,650,350,700,300,650,350,700,300,650,350,700,300,700,300,700,300,650,300,700,350,700,300};
//unsigned int liga2[100] ={3050,9000,400,1650,400,700,350,650,400,650,400,650,400,650,400,700,350,700,350,700,350,1650,400,650,400,700,350,650,350,1700,400,700,350,650,400,1650,400,1650,400,1600,400,1650,350,650,400,1650,400,650,400,1650,350,1700,350,700,350,700,350,650,350,700,350,650,400,600,400,700,300,700,350,650,400,700,350,700,350,650,400,1650,400,650,400,1650,400,1650,350,150,350,150,400,700,350,700,350,1650,350,700,350,700,300};

//unsigned int desliga[100] = {2950,9150,450,600,450,1650,500,600,500,600,500,650,500,600,500,650,500,600,450,650,450,1700,500,600,500,650,450,1650,450,650,450,650,500,1600,500,1650,500,1650,450,1650,500,1650,500,650,450,650,450,650,450,650,500,600,450,650,450,650,450,650,500,600,500,600,500,650,450,650,450,650,450,650,500,600,500,650,450,650,500,600,500,650,450,650,450,650,500,600,500,650,450,650,450,650,500,600,500,600,500,650,450};
//unsigned int aum_volume[100] = {3000,9100,500,600,550,1600,500,600,500,600,450,650,500,600,550,600,500,600,500,600,500,1650,500,600,450,650,500,1550,500,600,500,600,500,1600,450,1650,500,1600,500,1600,450,1700,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,450,650,500,600,500,600,500,600,450,650,550,600,500,600,500,600,450,650,500,600,500,600,500,600,450,750,450,600,500,600,500,600,500}; //COLE A LINHA RAW CORRESPONDENTE DENTRO DAS CHAVES
//unsigned int dim_volume[100] = {2900,9150,500,600,500,1600,500,600,500,600,450,650,450,650,500,600,500,600,500,600,450,1650,500,600,500,600,500,1600,500,600,500,600,500,1600,500,1600,500,1600,450,1650,500,1600,500,600,450,650,500,600,450,650,500,650,450,650,500,600,500,600,500,600,450,650,500,600,450,650,450,650,450,700,450,650,500,600,500,650,450,650,500,600,450,650,500,650,450,750,400,650,450,650,450,650,500,650,500,600,450,650,500}; //COLE A LINHA RAW CORRESPONDENTE DENTRO DAS CHAVES



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
    //Serial.println("connection failed");
    return;
  }

  // This will send a string to the server
  //Serial.println("sending data to server");
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
    Serial.print("ch: ");
    Serial.println(ch); 
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
