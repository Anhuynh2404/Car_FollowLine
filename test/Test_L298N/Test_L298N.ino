#define INT1_PIN 9
#define INT2_PIN 10
#define ENA 5
void setup() {
  pinMode(INT1_PIN, OUTPUT);
  pinMode(INT2_PIN, OUTPUT);
  pinMode(ENA, OUTPUT);
}

void loop() {
  digitalWrite(INT1_PIN,HIGH);
  digitalWrite(INT2_PIN,HIGH);
  analogWrite(ENA, 200);
}
