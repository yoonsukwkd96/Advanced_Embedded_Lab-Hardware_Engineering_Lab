const int buzzer = 9;

//float val, voltage, temp;
String ssid     = "Simulator Wifi";  // SSID to connect to
String password = ""; //virtual wifi has no password 
String host     = "api.thingspeak.com"; // Open Weather Map API
const int httpPort   = 80;
String url     = "/channels/1635426/fields/1/last.json?api_key=EOZJII76M7HPBB05";
//Replace XXXXXXXXXXXXXXXX by your ThingSpeak Channel API Key

int setupESP8266(void) {
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
  
  return 0;
}

int BuzzerESP8266(void) {
  
 // Construct our HTTP call
  String httpPacket = "GET " + url + " HTTP/1.1\r\nHost: " + host + "\r\n\r\n";
  //String httpPacket = "GET https://api.thingspeak.com/channels/1635450/fields/1.json?api_key=MWXFEWZ2REP36I4H&results=20";
  int length = httpPacket.length();
  
  // Send our message length
  Serial.print("AT+CIPSEND=");
  Serial.println(length);
  delay(10); // Wait a little for the ESP to respond if (!Serial.find(">")) return -1;

  // Send our http request
  Serial.print(httpPacket);
  delay(10); // Wait a little for the ESP to respond
  
  while(!Serial.available()) delay(5);	
  String saida = "";
  
  if (Serial.find("\r\n\r\n")){	
    	delay(5);
    
    	unsigned int i = 0; 
    	
  		while (!Serial.find("\"field1\":")){} 
    
  		while (i<60000) { 
            if(Serial.available()) {
                  int c = Serial.read(); 
                  if (c == '.') 
                      break; 
                  if (isDigit(c)) {
                    saida += (char)c; 
                  }   
            }
      		i++;
        }
    }
  if (Serial.find("SEND OK\r\n")){
    	Serial.println("ESP8266 sends data to the server\n");
  		Serial.println("..........\n");
  }
  
    return saida.toFloat();
  
  
}


void setup() {
  pinMode(buzzer, OUTPUT);
  setupESP8266();
               
}

void loop() {
  
  int buzz = BuzzerESP8266();
  Serial.print(buzz);
  if (buzz < 50){
    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(1000);        // ...for 1 sec
  }
  else{
    noTone(buzzer);     // Stop sound...
    delay(1000);        // ...for 1sec
  }
  
  delay(1000);
}
