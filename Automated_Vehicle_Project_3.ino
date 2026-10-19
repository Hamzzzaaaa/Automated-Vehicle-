// IoT & Robotics Minor Project - Automated Vehicle
// Arduino Uno + L293D + 2 DC motors + HC-SR04 + PIR + 2 push buttons
//
// 5 directions : Forward, Backward, Stop, Right, Left
// Priority     : 1) PIR motion  -> stop, then go BACKWARD
//                2) Button pressed -> RIGHT (D11) or LEFT (D12)
//                3) Ultrasonic distance -> FORWARD with 5 gears, or STOP
//
// Gears (analogWrite on the L293D enable pins, 0..255 mapped to 0..5):
//   distance > 300 cm       -> Gear 5 (255)
//   250 < distance <= 300   -> Gear 4 (204)
//   200 < distance <= 250   -> Gear 3 (153)
//   150 < distance <= 200   -> Gear 2 (102)
//   100 <= distance <= 150  -> Gear 1 (51)
//   distance < 100 cm       -> STOP

// ----- L293D pins -----
int EN_LEFT  = 5;    // L293D pin 1  (Left motor speed)
int IN1      = 7;    // L293D pin 2
int IN2      = 8;    // L293D pin 7
int EN_RIGHT = 6;    // L293D pin 9  (Right motor speed)
int IN3      = 9;    // L293D pin 10
int IN4      = 10;   // L293D pin 15

// ----- Other pins -----
int BTN_RIGHT = 11;  // Push button 1 -> RIGHT
int BTN_LEFT  = 12;  // Push button 2 -> LEFT
int PIR_PIN   = 4;
int TRIG_PIN  = 3;
int ECHO_PIN  = 2;

// ----- Settings -----
int TURN_SPEED = 153;   // speed while turning (0-255)
int BACK_SPEED = 153;   // speed while reversing (0-255)

String lastState = "";
unsigned long lastPrint = 0;

void setup()
{
  pinMode(EN_LEFT, OUTPUT);
  pinMode(EN_RIGHT, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(BTN_RIGHT, INPUT_PULLUP);
  pinMode(BTN_LEFT, INPUT_PULLUP);
  pinMode(PIR_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  stopMotors();
  Serial.begin(9600);
  Serial.println("Automated vehicle ready");
}

void loop()
{
  long distance = readDistanceCm();
  String state;

  if (digitalRead(PIR_PIN) == HIGH) {
    // 1) Motion in front: immediately stop and go backward
    state = "BACKWARD (PIR motion detected)";
    moveBackward(BACK_SPEED);
  }
  else if (digitalRead(BTN_RIGHT) == LOW) {
    // 2a) Right button held
    state = "RIGHT (button pressed)";
    turnRight(TURN_SPEED);
  }
  else if (digitalRead(BTN_LEFT) == LOW) {
    // 2b) Left button held
    state = "LEFT (button pressed)";
    turnLeft(TURN_SPEED);
  }
  else {
    // 3) Ultrasonic decides forward speed (gear) or stop
    int gear = getGear(distance);
    if (gear == 0) {
      state = "STOP (obstacle < 100 cm)";
      stopMotors();
    }
    else {
      state = "FORWARD gear " + String(gear);
      moveForward(gear * 51);       // 255 / 5 = 51 per gear
    }
  }

  // Print when state changes, and distance every 500 ms
  if (state != lastState) {
    Serial.println(state);
    lastState = state;
  }
  if (millis() - lastPrint > 500) {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    lastPrint = millis();
  }

  delay(30);
}

// ---------- Gear selection ----------
int getGear(long d)
{
  if (d > 300) return 5;
  if (d > 250) return 4;
  if (d > 200) return 3;
  if (d > 150) return 2;
  if (d >= 100) return 1;
  return 0;   // less than 100 cm -> stop
}

// ---------- Ultrasonic ----------
long readDistanceCm()
{
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) return 999;      // no echo = nothing ahead
  return duration / 58;               // microseconds -> cm
}

// ---------- Motors (both motors always move in sync) ----------
void moveForward(int speedVal)          // clockwise
{
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(EN_LEFT, speedVal);
  analogWrite(EN_RIGHT, speedVal);
}

void moveBackward(int speedVal)         // anticlockwise
{
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
  analogWrite(EN_LEFT, speedVal);
  analogWrite(EN_RIGHT, speedVal);
}

void turnRight(int speedVal)            // left motor forward, right motor backward
{
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
  analogWrite(EN_LEFT, speedVal);
  analogWrite(EN_RIGHT, speedVal);
}

void turnLeft(int speedVal)             // left motor backward, right motor forward
{
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(EN_LEFT, speedVal);
  analogWrite(EN_RIGHT, speedVal);
}

void stopMotors()
{
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(EN_LEFT, 0);
  analogWrite(EN_RIGHT, 0);
}
