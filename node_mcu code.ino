#include<ESP8266WiFi.h>
#include "ThingSpeak.h"
#include<WiFiClient.h>
#include<ESP8266WebServer.h>
#include <ArduinoJson.h>
const char* ssid = "chpr";
const char* password = "prudhvi9915";
unsigned long Channel_ID = 1227471;
const char * myWriteAPIKey = "QG19VBWPUEQRO1AW";
ESP8266WebServer server(80);
String page = "";
float data1, data2, data3;
int data4=0, data5=0, data6=0;
const int Field_Number_1 = 1;
const int Field_Number_2 = 2;
const int Field_Number_3 = 3;
const int Field_Number_4 = 4;
const int Field_Number_5 = 5;
const int Field_Number_6 = 6;

WiFiClient  client;

void setup()
{
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  ThingSpeak.begin(client);

while (WiFi.status() != WL_CONNECTED)
  {
  delay(500);
  Serial.print(".");
  }
  Serial.println(WiFi.localIP());
  server.on("/", []()
  {
    page = "<html><head><title>Embedded System project</title></head><style type=\"text/css\">";
    page += "table{border-collapse: collapse;}th {background-color:  green ;color: white;}table,td {border: 4px solid black;font-size: x-large;";
    page += "text-align:center;border-style: groove;border-color: rgb(255,0,0);}</style><body><center>";
    page += "<h1>Smart Watering and Distribution System</h1><br><br><table style=\"width: 1200px;height: 450px;\"><tr>";
    page += "<th>Parameters</th><th>Value</th><th>Units</th></tr><tr><td>Temperature</td><td>"+String(data1)+"</td><td>Centigrade</td></tr>";
    page += "<tr><td>Turbidity</td><td>"+String(data2)+"</td><td>NTU</td></tr><tr><td>Water Level</td><td>"+String(data3)+"</td><td>m</td>";
    page += "<meta http-equiv=\"refresh\" content=\"3\">";
    server.send(200, "text/html", page);
  });
  server.begin();
}
void loop()
{
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(Serial);
  if (root == JsonObject::invalid())
  {
    return;
    Serial.println("invalid");
  }
  data1 = root["a1"];
  data2 = root["a2"];
  data3 = root["a3"];
  if(data1<27)
      {
        if(data2<250)
          {
            data4 = 1;
          }
        else if(data2>250)
          {
            data5 = 1;
          }
      }
    if(data1>27)
      {
        data6 = 1;
      }
      
 
  Serial.println(data1);
  Serial.println(data2);
  Serial.println(data3);
  Serial.println(data4);
  Serial.println(data5);
  Serial.println(data6);

  upload();

  server.handleClient();
}
void upload()
{
  ThingSpeak.setField(1,(float)data1);
  ThingSpeak.setField(2,(float)data2);
  ThingSpeak.setField(3,(float)data3);
  ThingSpeak.setField(4,data4);
  ThingSpeak.setField(5,data5);
  ThingSpeak.setField(6,data6);


  ThingSpeak.writeFields(Channel_ID, myWriteAPIKey);
  delay(20000);
}
