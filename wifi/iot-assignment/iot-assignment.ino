#include<ESP8266WiFi.h> 

const char* ssid = "Winnie"; //your WiFi Name
const char* password = "DavidGHS24";  //Your Wifi Password
WiFiServer server(88);
void setup() {
  Serial.begin(9600);
  delay(10); 
  Serial.println();
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
  server.begin();
  Serial.println("Server started");
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/"); 
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  } 
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush(); 
  int value = LOW;
  if (request.indexOf("/LED=ON") != -1)  {
    value = HIGH;
    Serial.println("HIGH");    
  }
  if (request.indexOf("/LED=OFF") != -1)  {
     value = LOW;
    Serial.println("LOW");  
  }
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); 
  client.println("");
  client.println("");
  client.print("Led is : "); 
  if(value == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }  client.println("");  
client.println(" On ");
   client.println(" Off ");  
  client.println(" ");
     delay(1);
   Serial.println("Client disonnected");
  Serial.println("");   
}
//code copied from link