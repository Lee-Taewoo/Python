#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22

#define MQ_PIN A0
#define RL_VALUE 10.0
#define R0 117.1   // ★ 보정된 값

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();  // DHT 센서 초기화
}

void loop() {
  int adc = analogRead(MQ_PIN);
  float rs = RL_VALUE * (1023.0 / adc - 1.0);
  float ratio = rs / R0;

  // DHT22 센서 읽기
  float t = dht.readTemperature();  // 섭씨
  float h = dht.readHumidity();

  // 센서 오류 처리
  if (isnan(t) || isnan(h)) {
    Serial.println("DHT read failed!");
  } else {
    Serial.print(ratio);  // MQ 센서 보정값
    Serial.print(",");
    Serial.print(t);
    Serial.print(",");
    Serial.println(h);
  }

  delay(1000);
}
