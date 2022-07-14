#include <WiFi.h> 
#include <WiFiClient.h> 
#include <HTTPClient.h>

#define relay1 13
#define relay2 12     
#define relay3 14 
#define relay4 26

//SSID and Password of your WiFi router 
const char* ssid = "wifiname"; 
const char* password = "12345678"; 

//IP Address Server yang terpasang XAMPP
const char *host = "192.168.216.166";

String url; 

void setup(void){ 
  Serial.begin(115200); 
   
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
 
  //Onboard LED port Direction output 
  pinMode(relay1, OUTPUT); 
  pinMode(relay2, OUTPUT); 
  pinMode(relay3, OUTPUT); 
  pinMode(relay4, OUTPUT);
  //Power on LED state off 
  digitalWrite(relay1, LOW); 
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW); 
   
  // Wait for connection 
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500); 
    Serial.print("."); 
  } 
 
  //If connection successful show IP address in serial monitor 
  Serial.println(""); 
  Serial.print("Connected to "); 
  Serial.println(ssid); 
  Serial.print("IP address: "); 
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP 
}

void loop() {
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  // Mengirimkan ke alamat host dengan port 80 -----------------------------------
  //Relay1
  String LinkRelay;
  HTTPClient httpRelay;             
  LinkRelay = ("http://" +String(host)+"/coba-PA/bcrelay1.php");
  httpRelay.begin(LinkRelay);
  httpRelay.GET();
  //Baca respon
  String responseRelay = httpRelay.getString();
  Serial.print(responseRelay);
  httpRelay.end();
  digitalWrite(relay1, responseRelay.toInt());

  //Relay2
  String LinkRelay2;
  HTTPClient httpRelay2;             
  LinkRelay2 = ("http://" +String(host)+"/coba-PA/bcrelay2.php");
  httpRelay2.begin(LinkRelay2);
  httpRelay2.GET();
  //Baca respon
  String responseRelay2 = httpRelay2.getString();
  Serial.print(responseRelay2);
  httpRelay2.end();
  digitalWrite(relay2, responseRelay2.toInt());

  //Relay3
  String LinkRelay3;
  HTTPClient httpRelay3;             
  LinkRelay3 = ("http://" +String(host)+"/coba-PA/bcrelay3.php");
  httpRelay3.begin(LinkRelay3);
  httpRelay3.GET();
  //Baca respon
  String responseRelay3 = httpRelay3.getString();
  Serial.print(responseRelay3);
  httpRelay3.end();
  digitalWrite(relay3, responseRelay3.toInt());

  //Relay4
  String LinkRelay4;
  HTTPClient httpRelay4;             
  LinkRelay4 = ("http://" +String(host)+"/coba-PA/bcrelay4.php");
  httpRelay4.begin(LinkRelay4);
  httpRelay4.GET();
  //Baca respon
  String responseRelay4 = httpRelay4.getString();
  Serial.print(responseRelay4);
  httpRelay4.end();
  digitalWrite(relay4, responseRelay4.toInt());

// Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  Serial.println();
  Serial.println("closing connection");
  }
}
