#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h"

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "192.168.59.196";
int        port     = 1883;
const char topic[]  = "light_sensor";
const char topic2[]  = "light_sensor_command";
//const char topic3[]  = "temperature_sensor";
//const char topic4[] = "temperature_sensor_command";

//set interval for sending messages (milliseconds)
const long interval = 8000;
unsigned long previousMillis = 0;

int count = 0;
int sensorPin = A5; // Declare the input pin here
/* int tempPin = A0; // Declaring Input Pin for Temp
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07; */

// Serial output in 9600 baud
void setup()
{
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }

  Serial.println("You're connected to the network");
  Serial.println();

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();

  // setup for the subscriber part
  // set the message receive callback
  mqttClient.onMessage(onMqttMessage);

  Serial.print("Subscribing to topic: ");
  Serial.println(topic2);
  Serial.println();

  //  Serial.print("Subscribing to topic: ");
  //  Serial.println(topic4);
  //  Serial.println();

  // subscribe to a topic
  mqttClient.subscribe(topic2);
  //mqttClient.subscribe(topic4);

  // topics can be unsubscribed using:
  // mqttClient.unsubscribe(topic);

  Serial.print("Topic: ");
  Serial.println(topic2);
  //  Serial.print("Topic: ");
  //  Serial.println(topic4);

}

// The program measures the current voltage value at the sensor,
// calculates from this and the known series resistance the current
// resistance value of the sensor and outputs the results to the serial output

void loop()
{
  // call poll() regularly to allow the library to send MQTT keep alive which
  // avoids being disconnected by the broker
  mqttClient.poll();

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time a message was sent
    previousMillis = currentMillis;


    //-------------Light sensor-----------------
    //    //record random value from A5
    //    int Rvalue = analogRead(A5);

    // Current voltage value is measured...
    int rawValue = analogRead(sensorPin);
    float voltage = rawValue * (5.0 / 1023) * 1000;

    float resistance = 10000 * ( voltage / ( 5000.0 - voltage) );

    //  if(resistance >= 2000){
    //    resistance = 1000;
    //  }
    //  else{
    //    resistance = 500;
    //  }

    Serial.print("Sending message to topic: ");
    Serial.println(topic);
    Serial.println(resistance);

    // send message, the Print interface can be used to set the message contents
    mqttClient.beginMessage(topic);
    mqttClient.print(resistance);
    mqttClient.endMessage();

    //--------End light sensor-----------------

    //------------Temperature sensor-----------
    //
 /*
  Vo = analogRead(tempPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  Tc = T - 273.15;
  

  Serial.print("Temperature: "); 
  Serial.print(Tc);
  Serial.println(" C");   
  */



    // Serial.print("Sending message to topic: ");
    // Serial.println(topic3);
    // Serial.println(temperature);

    // send message, the Print interface can be used to set the message contents
    //    mqttClient.beginMessage(topic3);
    //    mqttClient.print(temperature);
    //    mqttClient.endMessage();

    //--------End temperature sensor-----------

    Serial.println();

    // ... and here output to the serial interface
    Serial.print("Voltage value:"); Serial.print(voltage); Serial.print("mV");
    Serial.print(", resistance value:"); Serial.print(resistance); Serial.println("Ohm");
    Serial.println("---------------------------------------");

    // ... and here output to the serial interface
    //    Serial.print("Voltage value:"); Serial.print(voltage); Serial.print("mV");
    //    Serial.print(", temperature value:"); Serial.print(temperature); Serial.println("Celcius degree");
    //    Serial.println("---------------------------------------");

    delay(500);
  }
}

void onMqttMessage(int messageSize) {
  // we received a message, print out the topic and contents
  Serial.println("Received a message with topic '");
  Serial.print(mqttClient.messageTopic());
  Serial.print("', length ");
  Serial.print(messageSize);
  Serial.println(" bytes:");

  String led = "";
  // use the Stream interface to print the contents
  while (mqttClient.available()) {
    char msg = (char)mqttClient.read();
    Serial.print(msg);
    led += msg;
  }
  Serial.print(led);
  if (mqttClient.messageTopic() == "light_sensor_command") {
    if (led == "on") {
      digitalWrite(LED_BUILTIN, HIGH);
    }
    if (led == "off") {
      digitalWrite(LED_BUILTIN, LOW);
    }
    //  } else if (mqttClient.messageTopic() == "temperature_sensor_command") {
    //    if (led == "on") {
    //      digitalWrite(LED_BUILTIN, HIGH);
    //    }
    //    if (led == "off") {
    //      digitalWrite(LED_BUILTIN, LOW);
    //    }
    //  }

  }

  Serial.println();
  Serial.println();
}
