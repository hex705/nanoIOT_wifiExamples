/*
 *
 *  run this with receiveLEDControl on another board.
 *  config an instance on shiftr or use public credentails
 *
 *  this file sends 0, 1 via  shiftr broker
 *  this code is essentially a metronome or heart beat that controls blink rate of remote LED
 *  change interval time ot change remote lbink rate
 *  ie change this line below  --> const long interval = 500;
 *
 */

/*
  ArduinoMqttClient - WiFi Simple Sender

  This example connects to a MQTT broker and publishes a message to
  a topic once a second.

  The circuit:
  - Arduino MKR 1000, MKR 1010 or Uno WiFi Rev2 board

  This example code is in the public domain.
*/


#include <Arduino_JSON.h>

#include <ArduinoMqttClient.h>

#if defined(ARDUINO_SAMD_MKRWIFI1010) || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_AVR_UNO_WIFI_REV2)
  #include <WiFiNINA.h>
#elif defined(ARDUINO_SAMD_MKR1000)
  #include <WiFi101.h>
#elif defined(ARDUINO_ESP8266_ESP12)
  #include <ESP8266WiFi.h>
#endif

#include "arduino_secrets.h"
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;    // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)

// To connect with SSL/TLS:
// 1) Change WiFiClient to WiFiSSLClient.
// 2) Change port value from 1883 to 8883.
// 3) Change broker value to a server with a known SSL/TLS root certificate
//    flashed in the WiFi module.

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);


//https://www.shiftr.io/docs/manuals/arduino
const char broker[] = "public.cloud.shiftr.io"; // yes this url for SHFTR even with unique instance
int        port     = 1883;
const char topic[]  = "topic2";


const long interval = 2000; // this line control blink rate of remote led -- small = faster
unsigned long previousMillis = 0;

int count = 0;

// to get aprsable string from Mqtt
char mqttInBuffer[128]; // 128 char buffer -- keep message shorter than this

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // attempt to connect to WiFi network:
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }

  Serial.println("You're connected to the network");
  Serial.println();

  // You can provide a unique client ID, if not set the library uses Arduino-millis()
  // Each client must have a unique client ID

  mqttClient.setId(SHIFTR_ID); // any name works here -- be smart about it

  // You can provide a username and password for authentication
  mqttClient.setUsernamePassword(SHFTR_INSTANCE, SHFTR_TOKEN); // instance name, token secret -- if raw in quotes

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
    while (1);
  }

  // set the message receive callback
  mqttClient.onMessage(mqttMessageEvent);
  // subscribe to a topic
//  mqttClient.subscribe(topic);
  mqttClient.subscribe("topic1");


  Serial.println("You're connected to the MQTT broker!");
  Serial.println();
}

void loop() {
  // call poll() regularly to allow the library to send MQTT keep alives which
  // avoids being disconnected by the broker
  mqttClient.poll();

  // to avoid having delays in loop, we'll use the strategy from BlinkWithoutDelay
  // see: File -> Examples -> 02.Digital -> BlinkWithoutDelay for more info
  unsigned long currentMillis = millis();

  // send MQTT when timer expires
  if (currentMillis - previousMillis >= interval) {
    // save the last time a message was sent
    previousMillis = currentMillis;
    //sendMqtt();
  }

}

void sendMqtt(){

      count = 1 - count; // toggle 0,1

      // for debug
      Serial.print("Sending to topic: ");
      Serial.print(topic);
      Serial.print(" with payload :: ");
      Serial.println(count);

      // send message, the Print interface can be used to set the message contents
      mqttClient.beginMessage(topic);
      mqttClient.print(count);
      mqttClient.endMessage();
}

// receive messages here
void mqttMessageEvent(int messageSize) {
  // we received a message, print out the topic and contents
  Serial.print("Received a message with topic: '");
  Serial.print(mqttClient.messageTopic());
  Serial.print("', length ");
  Serial.print(messageSize);
  Serial.println(" bytes.");


  // use the Stream interface to get the contents and put in char array
  int count = 0;
  while (mqttClient.available()) {
    char c = mqttClient.read();
    mqttInBuffer[count] = c;
    count ++;
    //Serial.print(c);
  }

  mqttInBuffer[messageSize] = '\0'; // put null termniator at end of string
  printBuffer(messageSize); // debug

  //use JSON lib parse tools to get contents of message
  // id and val could be made global for use elsewhere
  JSONVar mqttJsonObject = JSON.parse(mqttInBuffer);
  // safe way
  if (mqttJsonObject.hasOwnProperty("idOrOther")) {
    int id = (int) mqttJsonObject["idOrOther"];
    Serial.print("mqttJsonObject[\"idOrOther\"] = ");
    Serial.println(id);
  }
  // less safe way
  int val = (int) mqttJsonObject["str"];
  Serial.print("val :: ");
  Serial.println(val);

}

void printBuffer(int messageSize){
  Serial.println("rec'd message in char array format :: ");
  for (int i = 0; i < messageSize; i++){
      Serial.print(mqttInBuffer[i]);
  }
  Serial.println();
}
