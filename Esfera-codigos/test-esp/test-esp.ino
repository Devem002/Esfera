#include <ESP8266WiFi.h> //ESP8266 Library
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h> //ESP8266 Library

#include <WiFiClient.h>

#include <ArduinoJson.h> //For phrasing JSON file download from https://github.com/bblanchon/ArduinoJson

 ESP8266WiFiMulti WiFiMulti;

const char* ssid = "Name"; //Enter your Wi-Fi SSID

const char* password = "Pass"; //Enter you Wi-Fi Password


String payload; //To store the JSON object as string


void setup () {

 

  Serial.begin(115200); //initialise serial monitor to send data to Arduino

   WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);

  //WiFi.begin(ssid, password); //connect to the network specified above


}

 

void loop() {

  if ((WiFiMulti.run() == WL_CONNECTED)) { //If Wi-Fi connected successfully 

    //Serial.println("wifi Connected");

    
    WiFiClient client;

    HTTPClient http;  //start a HTTPClinet as http 

    //####DO NOT USE THE SAME API as below

    http.begin(client,"http://192.168.1.39:80/movements");  //Enter your API 


    int httpCode = http.GET(); //pass a get request                                                                  

    //Serial.println(httpCode);

    if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) { //Check the returning code

 
      
      payload = http.getString();   // Store the value on varibale Payload for debugging

    //Serial.println(payload);   //Print the payload for debugging otherwise comment both lines
    
    const size_t bufferSize = JSON_OBJECT_SIZE(0) + JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2) + 2*JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(8) + JSON_OBJECT_SIZE(12) + JSON_OBJECT_SIZE(56) + 2160;

DynamicJsonDocument jsonBuffer(bufferSize);

deserializeJson(jsonBuffer, http.getString());
//JsonObject& root = jsonBuffer.parseObject(http.getString());

/*End of Phrasing Data*/


//Address the value sin to desired variables 

//JsonObject current_observation = jsonBuffer["Movements"]; //under current_observation


const char* current_Movements = jsonBuffer["Movements"]; // "ICHENNAI1" //get the location detials


Serial.print (current_Movements); //send the location details to Arduino

delay(100); //stability delay



    http.end();

/*Phrasing Data using the JSON librarey */ //Use https://arduinojson.org/assistant/ to get the phrasing values for your JSON string 


    }else{Serial.println("[HTTP] Unable to connect" );
   Serial.println(http.errorToString(httpCode).c_str());
   delay(100);

    http.end();   //Close http connection}

  

  }
  

  delay(10000);    //send values to Arduino every 10 sec.

}}
