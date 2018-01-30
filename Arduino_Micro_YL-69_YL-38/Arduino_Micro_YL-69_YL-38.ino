byte humidity_sensor_pin = A0;
byte output_alarm = 12;

void setup() {
  pinMode(12, OUTPUT);
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

  int res = map(val, 383, 1022, 100, 0);

  if (res >= 40)
  {
    digitalWrite(12, HIGH);       // Not necesary esp:pullup resistor??
  }
  else
  {
    digitalWrite(12, LOW); //feed the plants!!!
  }

  Serial.print("Humidity Level (0-1023): ");
  Serial.print(res);
  Serial.println("%");

  delay(10000);
}
