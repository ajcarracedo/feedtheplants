byte humidity_sensor_pin = A0;
byte output_alarm = A0;

void setup() {
  Serial.begin(9600);
}

int read_humidity_sensor() {
  int value = analogRead(humidity_sensor_pin);
  return value;
}

void loop() {
  int minValue = 383;
  int maxValue = 1022;
  int val = read_humidity_sensor();
  
  if (val <= minValue) {
    val = minValue;
  }
  
  if (val >= 1022) {
    val = 1022;
  }
  Serial.print("Humidity Level (0-1023): ");
  Serial.print(map(val, 383, 1022, 100, 0));
  Serial.println("%");
  
  delay(1000);
}
