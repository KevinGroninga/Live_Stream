#define pirSensor 8
#define playerpin 7

int reading;

void setup() {

  pinMode(pirSensor, INPUT);
  pinMode(playerpin, OUTPUT);

  Serial.begin(9600);

  digitalWrite(playerpin, HIGH);
}

void loop() {

  reading = digitalRead(pirSensor);

  if (reading == HIGH) {
    Serial.println("Motion");
    digitalWrite(playerpin, LOW);
    delay(100);
    digitalWrite(playerpin, HIGH);
    delay(5000);
  } else {
    Serial.println("0");
    digitalWrite(playerpin, HIGH);
  }

}
