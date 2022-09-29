#include <SPI.h>
#include <WiFiNINA.h>
#include <Arduino_LSM6DSOX.h>

float atualX, atualY, atualZ;
float posiX, posiY, posiZ;

unsigned long lastMillis;

void zeraLeds();
void mostraZ(float Zvalue);

void setup() {
  pinMode(LEDR, OUTPUT); 
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  Serial.begin(9600); 
  IMU.begin();
  delay(500);
  IMU.readAcceleration(posiX, posiY, posiZ);
}

void loop() {
    IMU.readAcceleration(atualX, atualY, atualZ);
    if (atualZ < posiZ-0.5) {
      mostraZ(atualZ);
      digitalWrite(LEDR, HIGH);
      //lastMillis = millis();
    } else if (atualZ < posiZ-0.2) {
      mostraZ(atualZ);
      digitalWrite(LEDR, HIGH);
      digitalWrite(LEDG, HIGH);
      //lastMillis = millis();
    } else if (atualZ < posiZ-0.1 || atualZ > posiZ+0.1) {
      mostraZ(atualZ);
      zeraLeds();
      digitalWrite(LEDG, HIGH);
    }
}

void zeraLeds() {
  digitalWrite(LEDR, LOW); 
  digitalWrite(LEDG, LOW); 
  digitalWrite(LEDB, LOW); 
}

void mostraZ(float Zvalue) {
  Serial.print("Z = "); 
  Serial.print(Zvalue);
  Serial.println();
  zeraLeds();
}
