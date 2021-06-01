#include <ESP8266WiFi.h>


#include <SoftwareSerial.h>
SoftwareSerial NodeSerial(D3, D4);
//SoftwareSerial NodeSerial3(D3, D4);// RX | TX
SoftwareSerial NodeSerial2(D5, D6); // RX | TX
  // ขา Out ของ Sensor ต่อเข้าขา D4 ของ Esp8266

//เลือกชนิดของ Sensor

const char* ssid     = "aprl_supab";    // SSID Wifi
const char* password = "aprl2017supab";   // Password Wifi

const char* host = "api.thingspeak.com";    // Host ของ thingspeak ไม่ต้องแก้ไข
const char* api   = "0FC05RYEHBJWQRZG";  //API Key ที่เราจำไว้ ในขั้นต้นเมื่อกี้

void setup() {
   pinMode(D5, INPUT);
  pinMode(D6, OUTPUT);
  Serial.begin(9600);
  NodeSerial.begin(57600);
  NodeSerial2.begin(57600);
  //NodeSerial3.begin(38400);
  Serial.println();
  Serial.println("NodeMCU/ESP8266 Run");
  Serial.begin(9600);
  delay(10);
  // We start by connecting to a WiFi network

  Serial.println();
 
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("DHTxx test!");




}

int value = 0;

void loop() {
  
if(NodeSerial2.available()){
  delay(10000);
  ++value;
     int highbp = NodeSerial2.parseInt();
    int lowbp = NodeSerial2.parseInt();
   int bgl = NodeSerial2.parseInt();
 int spo2 = NodeSerial2.parseInt();
     //int BGLdelta = NodeSerial2.parseInt();
    int tem = NodeSerial.parseInt();
    int hr = NodeSerial.parseInt();

 // if(NodeSerial2.available()&& NodeSerial.available() ){
//  if (NodeSerial2.read() == '\n')
//    {
//      Serial.print("NodeMCU or ESP8266 1111");
//      Serial.print(" : ");
//      Serial.print(hr); 
//      Serial.print(" : ");
//      Serial.println(tem);
//   
//    }
//  if (NodeSerial.read() == '\n')
//    {
//      Serial.print("NodeMCU or ESP8266 2222");
//       Serial.print(" : ");
//      Serial.print(highbp); 
//      Serial.print(" : ");
//      Serial.println(lowbp);
//      Serial.print(" : ");
//      Serial.println(BGLdelta);
//     
//    }
 //}
    

  Serial.print("connecting to ");
  Serial.println(host);
   
  

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request
  String url = "/update?api_key=";
  url += api;
  url += "&field1=";
  url += highbp;
  url += "&field2=";  
  url += lowbp;
   url += "&field3=";  
  url += hr;
   url += "&field4=";  
  url += tem;
    url += "&field5=";  
  url += spo2;
   url += "&field6=";  
 url += bgl;
// เราจะส่งข้อมูล https://api.thingspeak.com/update?api_key=RRHS37ETW76RFAWB&field1=(อุณหภูมิ)&field2=(ความชื่น)

  Serial.print("Requesting URL: ");
  Serial.println(url);
 if(highbp>0 &&hr>0&&lowbp>0&&tem>0) {
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(10);

  // Read all the lines of the reply from server and print them to Serial
 
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  }
  Serial.println();
  Serial.println("closing connection");
}
}
