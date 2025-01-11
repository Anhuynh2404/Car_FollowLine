#define IR_PIN 2
void setup() {
  pinMode(IR_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  int sesorRead = digitalRead(IR_PIN);
  if (sesorRead == HIGH){
    Serial.println("1");
  }else{
    Serial.println("0");
  }
  delay(500);
}
