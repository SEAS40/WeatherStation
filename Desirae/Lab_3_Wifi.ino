 #include <ESP8266WiFi.h>

const char* ssid= "SEAS40"; // Wifi network for connection
const char* password= "12345678"; // Wifi network password

// Connection information for host
const char* host="postman-echo.com";
WiFiClient client;
const int httpPort=80;

void setup () {
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.println();
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid,password);
  while (WiFi.status()!= WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println(" ");
  Serial.println("WiFi connected");
  Serial.println("IP adress:");
  Serial.println(WiFi.localIP());
}

void loop() {
  delay (5000);
  Serial.print("connecting to ");
  Serial.println(host);

  // A connection is established
  if (!client.connect(host,httpPort)) {
    Serial.println("connection failed");
    return;
  }
  // Indicate specific URL and send request
  String url="/get";
  Serial.print("Requesting URL: ");
  Serial.println(url);
  client.print(String("GET  ")+url+" HTTP/1.1\r\n"+"Host: "+host+"\r\n"+"Connection: close\r\n\r\n");

 // Allow 5 second delay for server response
  unsigned long timeout=millis();
  while (client.available()==0) {
    if (millis()-timeout>5000) {
      Serial.println(">>>> Client Timeout!");
      client.stop();
      return;
    }
  }

  while (client.available()) {
    String line = client.readStringUntil('\n');
    Serial.print (line);
  }

  Serial.println();
  Serial.println("closing connection");
}
