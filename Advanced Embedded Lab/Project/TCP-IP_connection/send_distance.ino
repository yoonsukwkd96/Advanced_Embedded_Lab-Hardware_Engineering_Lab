int distanceThreshold = 0;
int cm = 0;
int inches = 0;
float val, temp;
String ssid     = "Simulator Wifi";  // SSID to connect to
String password = ""; //virtual wifi has no password 
String host     = "api.thingspeak.com"; // Open Weather Map API
const int httpPort   = 80;
String url     = "/update?api_key=R76DHK39L7ID3BDJ&field1=";
//Replace XXXXXXXXXXXXXXXX by your ThingSpeak Channel API Key


void setupESP8266(void) {
  
  // Start our ESP8266 Serial Communication
  Serial.begin(115200);   // Serial connection over USB to computer
  Serial.println("AT");   // Serial connection on Tx / Rx port to ESP8266
  delay(10);        // Wait a little for the ESP to respond
  if (Serial.find("OK"))
    Serial.println("ESP8266 OK!!!");
    
  // Connect to Simulator Wifi
  Serial.println("AT+CWJAP=\"" + ssid + "\",\"" + password + "\"");
  delay(10);        // Wait a little for the ESP to respond
  if (Serial.find("OK"))
    Serial.println("Connected to WiFi!!!");
  
  // Open TCP connection to the host:
  //ESP8266 connects to the server as a TCP client. 

  Serial.println("AT+CIPSTART=\"TCP\",\"" + host + "\"," + httpPort);
  delay(50);        // Wait a little for the ESP to respond
  if (Serial.find("OK")) 
   Serial.println("ESP8266 Connected to server!!!") ;
 
}



long UltrasoundDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT); //Clear Trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  //Triger Pin -> HIGH for 10 ms
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  //Read EchoPin & Return SoundWave Travel Time
  long pulse=pulseIn(echoPin, HIGH);
  Serial.print(pulse);
  Serial.println(" Microseconds");
  return pulse;
}


void anydata(void) 
{
  
  //LED Activation
  distanceThreshold = 350;
  //Measure Ping Time in cm
  cm = 0.01715 * UltrasoundDistance(5, 4);
  //Convert cm to inches (cm%2.54)
  inches = (cm / 2.54);
   
  // Construct our HTTP call
  String httpPacket = "GET " + url + String(inches) + " HTTP/1.1\r\nHost: " + host + "\r\n\r\n";
  int length = httpPacket.length();
  
  // Send our message length
  Serial.print("AT+CIPSEND=");
  Serial.println(length);
  delay(10); // Wait a little for the ESP to respond if (!Serial.find(">")) return -1;

  // Send our http request
  Serial.print(httpPacket);
  delay(10); // Wait a little for the ESP to respond
  if (Serial.find("SEND OK\r\n"))
    Serial.println("ESP8266 sends data to the server"); 
}

void setup() {
  pinMode(A0, INPUT);
  setupESP8266();
               
}

void loop() {
  
 anydata();
  
  delay(10000);
}
