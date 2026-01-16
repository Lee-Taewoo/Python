#include <DHT.h>

#define RXD2 16
#define TXD2 17

#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#define MQ135_CALIB_FACTOR 1.0

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  dht.begin();
  Serial.println("PPM,TEMP,HUMIDITY"); // CSV 헤더
}

void loop() {
  if (Serial2.available()) {
    String data = Serial2.readStringUntil('\n');
    data.trim();

    float ratio, temp, humi;
    if (sscanf(data.c_str(), "%f,%f,%f", &ratio, &temp, &humi) == 3) {
      float ppm = 116.602 * pow(ratio, -2.769) * MQ135_CALIB_FACTOR;
      Serial.print(ppm, 1);
      Serial.print(",");
      Serial.print(temp, 1);
      Serial.print(",");
      Serial.println(humi, 0);
    }
  }
  delay(1000);
}




