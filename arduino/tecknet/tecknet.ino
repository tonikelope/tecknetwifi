#include <ESP8266WiFi.h>

#define sensorPin A0

const char * WIFI_SSID = ""; 
const char * WIFI_PASSWORD = "";

IPAddress ip(192,168,1,2);   
IPAddress gateway(192,168,1,1);   
IPAddress subnet(255,255,255,0);   

const int LOOP_DELAY = 100;
const int DING_DONG_DELAY = 3000;

const int SENSOR_TRIGGER_THRESHOLD = 100;

const char * host = "192.168.1.5"; //Your PC, Laptop, RaspberryPI, etc running HTTP SERVER for receive notification
const int httpPort = 7123;
const char * url = "/";

int sensorValue = 0;

void setup() {
    pinMode(sensorPin, INPUT);
    
    Serial.begin(115200);

    // wait until serial port opens for native USB devices
    while (!Serial) {
        yield();
    }

    Serial.println();

    Serial.println("*********************************");
    Serial.println("DING-O-MATIC by tonikelope LOADED");
    Serial.println("*******************************\n");

    int wifi_error;

    do{

        wifi_error=0;
        
        Serial.println("Initialising Wifi...\n");
        WiFi.mode(WIFI_STA);
        WiFi.config(ip, gateway, subnet);
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        WiFi.persistent(true);
        WiFi.setAutoConnect(true);
        WiFi.setAutoReconnect(true);
    
        if (WiFi.waitForConnectResult() != WL_CONNECTED) {
          
          Serial.println("Connection Failed!");
    
          wifi_error = 1;
          
        }else{
          
          Serial.println("WiFi connected");
          
          Serial.println(WiFi.SSID());
          
          Serial.println(WiFi.localIP());
    
        }
    
    }while(wifi_error);

    Serial.println("\nWaiting for DOOR EVENT(s)...");

}

void loop() {
  sensorValue = analogRead(sensorPin);

  Serial.println(sensorValue);
  
  if(sensorValue >= SENSOR_TRIGGER_THRESHOLD){
      dingDong();
      delay(DING_DONG_DELAY);
  }
  
  delay(LOOP_DELAY);
}

void dingDong() {
  
    WiFiClient client;
    
    if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
    }

    client.print(String("GET ") + url + "?ext=1" + "&int=0" + "&door=0 HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");

    while (!client.available()){
        yield();
    }

    while (client.available()) {
        client.read();
    }
}
