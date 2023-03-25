#include <ESP8266WiFi.h> //ESP8266 Library
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h> //ESP8266 Library

#include <WiFiClient.h>

#include <ArduinoJson.h> //For phrasing JSON file download from https://github.com/bblanchon/ArduinoJson

 ESP8266WiFiMulti WiFiMulti;

const char* ssid = "name"; //Enter your Wi-Fi SSID

const char* password = "pass"; //Enter you Wi-Fi Password


String payload; //To store the JSON object as string


void setup () {

 

  Serial.begin(9600); //initialise serial monitor to send data to Arduino

   WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);

  //WiFi.begin(ssid, password); //connect to the network specified above


}

 

void loop() {

  if ((WiFiMulti.run() == WL_CONNECTED)) { //If Wi-Fi connected successfully 

    Serial.println("wifi Connected");

    
    WiFiClientSecure client;

    HTTPClient http;  //start a HTTPClinet as http 

    //####DO NOT USE THE SAME API as below

    http.begin(client,"https://catfact.ninja/fact");  //Enter your API 
    

  

    int httpCode = http.GET(); //pass a get request                                                                  

    Serial.println(httpCode);

    if (httpCode > 0) { //Check the returning code

 
      Serial.println("httpcode accepted");
      payload = http.getString();   // Store the value on varibale Payload for debugging

    Serial.println(payload);   //Print the payload for debugging otherwise comment both lines



/*Phrasing Data using the JSON librarey */ //Use https://arduinojson.org/assistant/ to get the phrasing values for your JSON string 

const size_t bufferSize = JSON_OBJECT_SIZE(0) + JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2) + 2*JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(8) + JSON_OBJECT_SIZE(12) + JSON_OBJECT_SIZE(56) + 2160;

DynamicJsonDocument jsonBuffer(bufferSize);

deserializeJson(jsonBuffer, http.getString());

/*End of Phrasing Data*/


//Address the value sin to desired variables 

JsonObject current_observation = jsonBuffer["current_observation"]; //under current_observation

JsonObject current_observation_observation_location = current_observation["observation_location"]; //under observation_location

const char* current_observation_station_id = current_observation["fact"]; // "ICHENNAI1" //get the location detials

const char* current_observation_local_time_rfc822 = current_observation["length"]; //Local time //get the local time

//const char* current_observation_temperature_string = current_observation["temperature_string"]; // "90.7 F (32.6 C)" //get the temperature value

//const char* current_observation_relative_humidity = current_observation["relative_humidity"]; // "73%" //get the humidity value


//Print the variables thorugh serial monitor

Serial.print (current_observation_station_id); //send the location details to Arduino

delay(100); //stability delay

Serial.print (current_observation_local_time_rfc822); //send the local time details to Arduino

delay(100); //stability delay

//Serial.print (current_observation_temperature_string); //send the temperature details to Arduino

//delay(100); //stability delay

//Serial.print (current_observation_relative_humidity); //send the humidity details to Arduino

//delay(100); //stability delay


    }

  Serial.println("[HTTP] Unable to connect" );
   Serial.println(http.errorToString(httpCode).c_str());

    http.end();   //Close http connection

  }
  else
  {
     Serial.println("[HTTP] Unable to connect");
    }

  delay(10000);    //send values to Arduino every 30 sec.

}
