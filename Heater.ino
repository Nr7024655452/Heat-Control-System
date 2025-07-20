#include <OneWire.h>
#include <DallasTemperature.h>

// Pin setup
#define TEMP_SENSOR 2
#define HEATER 3
#define BUZZER 4

// Temperature thresholds
const float HEAT_ON = 30.0;
const float HEAT_OFF = 40.0;
const float OVERHEAT = 45.0;

OneWire oneWire(TEMP_SENSOR);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  sensors.begin();

  pinMode(HEATER, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(HEATER, LOW);
  digitalWrite(BUZZER, LOW);

  Serial.println("Heater system started");
}

void loop() {
  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" °C | ");

  if (temp > OVERHEAT) {
    digitalWrite(HEATER, LOW);    // Turn off heater
    digitalWrite(BUZZER, HIGH);   // Sound buzzer
    Serial.println("State: OVERHEAT");
  }
  else if (temp < HEAT_ON) {
    digitalWrite(HEATER, HIGH);   // Turn on heater
    digitalWrite(BUZZER, LOW);    // Buzzer off
    Serial.println("State: HEATING");
  }
  else if (temp >= HEAT_OFF) {
    digitalWrite(HEATER, LOW);    // Turn off heater
    digitalWrite(BUZZER, LOW);    // Buzzer off
    Serial.println("State: STABLE");
  }
  else {
    // Between 30–40°C (stabilizing)
    digitalWrite(HEATER, HIGH);
    digitalWrite(BUZZER, LOW);
    Serial.println("State: STABILIZING");
  }

  delay(1000);  // Wait for 1 second
}
