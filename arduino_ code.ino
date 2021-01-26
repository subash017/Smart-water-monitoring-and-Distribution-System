#include <OneWire.h>
#include <DallasTemperature.h>
#include <ArduinoJson.h>
OneWire oneWire(4);
int motor1 = 8;
int motor2 = 9;
int motor3 = 10;
DallasTemperature temp_sensor(&oneWire);
void setup()
{
  Serial.begin(9600);
  temp_sensor.begin();
}
StaticJsonBuffer<1000> jsonBuffer;
JsonObject& root = jsonBuffer.createObject();
void loop() {
  
  int turbidity_analog=analogRead(A1);
  int water_level_analog = analogRead(A2);
  delay(2000);
  temp_sensor.requestTemperatures();
  Serial.print("Temperature: ");
  Serial.print(temp_sensor.getTempCByIndex(0));
  Serial.print("C  |  ");
  
  Serial.print("Turbiditty: ");
  Serial.print(turbidity_analog);
  Serial.print("NTU  |  ");
  
  Serial.print("Water level: ");
  Serial.print(water_level_analog);
  Serial.print("m");

  
  root["a1"] = temp_sensor.getTempCByIndex(0);
  root["a2"] = turbidity_analog;
  root["a3"] = water_level_analog;
  root.printTo(Serial);
  


  while(water_level_analog>20)
  {
    if(temp_sensor.getTempCByIndex(0)<27)
      {
        if(turbidity_analog<250)
          {
           Serial.println("Motor 1 ON    ");
           Serial.println("Drinking water");
            digitalWrite(motor1, HIGH);
          }
        else if(turbidity_analog>250)
          {
            Serial.println("Motor 1 ON    ");
            Serial.println("Water for irrigation");
            digitalWrite(motor2, HIGH);
          }
      }
    if(temp_sensor.getTempCByIndex(0)>27)
      {
        Serial.println("Motor 3 ON    ");
        Serial.println("Water for washing");
        digitalWrite(motor3, HIGH);
      }
  }
     Serial.println("");
     digitalWrite(motor1, LOW);
     digitalWrite(motor2, LOW);
     digitalWrite(motor3, LOW);

}
