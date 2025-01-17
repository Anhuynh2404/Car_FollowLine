#include <Arduino.h>

// Các chân cảm biến IR
#define SENSOR_LEFT 2
#define SENSOR_MID 3
#define SENSOR_RIGHT 4

// Các chân điều khiển động cơ
#define ENA 5
#define IN1 6
#define IN2 7
#define ENB 9
#define IN3 10
#define IN4 11

// Tham số PID
float Kp = 2.0; // Hệ số tỉ lệ
float Ki = 0.0; // Hệ số tích phân
float Kd = 1.0; // Hệ số vi phân

int baseSpeed = 100; // Tốc độ cơ bản của động cơ
float previousError = 0;
float integral = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(SENSOR_LEFT, INPUT);
  pinMode(SENSOR_MID, INPUT);
  pinMode(SENSOR_RIGHT, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  // Đọc giá trị cảm biến
  int left = digitalRead(SENSOR_LEFT);
  int mid = digitalRead(SENSOR_MID);
  int right = digitalRead(SENSOR_RIGHT);

  if (left == LOW && mid == LOW && right == LOW) {
    stopMotors(); // Dừng xe
    while (true); // Giữ xe dừng lại
  }

  // Xác định lỗi
  float error = 0;
  if (left) error = -1; // Xe lệch trái
  if (right) error = 1; // Xe lệch phải
  if (mid) error = 0;   // Xe ở giữa

  // Tính toán PID
  integral += error;
  float derivative = error - previousError;
  float correction = Kp * error + Ki * integral + Kd * derivative;

  // Tính tốc độ động cơ
  int speedLeft = baseSpeed - correction;
  int speedRight = baseSpeed + correction;

  // Giới hạn tốc độ
  speedLeft = constrain(speedLeft, 0, 255);
  speedRight = constrain(speedRight, 0, 255);

  // Điều khiển động cơ
  moveMotors(speedLeft, speedRight);

  previousError = error;
}

void moveMotors(int speedLeft, int speedRight) {
  // Động cơ trái
  if (speedLeft > 0) {
    analogWrite(ENA, speedLeft);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  } else {
    analogWrite(ENA, -speedLeft);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  }

  // Động cơ phải
  if (speedRight > 0) {
    analogWrite(ENB, speedRight);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  } else {
    analogWrite(ENB, -speedRight);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
}

void stopMotors() {
  analogWrite(ENA, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  analogWrite(ENB, 0);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
