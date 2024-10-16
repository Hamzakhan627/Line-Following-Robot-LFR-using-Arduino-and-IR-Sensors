// Pin Assignments
const int IR1 = 2;   // Leftmost sensor
const int IR2 = 3;   // Left sensor
const int IR3 = 4;   // Center sensor
const int IR4 = 5;   // Right sensor
const int IR5 = 6;   // Rightmost sensor

// Motor Pin Assignments
const int ENA = 9;   // Speed control for Left Motor
const int IN1 = 10;  // Direction control for Left Motor
const int IN2 = 11;  // Direction control for Left Motor

const int ENB = 8;   // Speed control for Right Motor
const int IN3 = 12;  // Direction control for Right Motor
const int IN4 = 13;  // Direction control for Right Motor

// Motor Speeds
const int MOTOR_SPEED = 180; // Adjust for motor speed control

void setup() {
  // Initialize IR sensors as inputs
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(IR5, INPUT);

  // Initialize Motor Pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Initialize motor speed
  analogWrite(ENA, MOTOR_SPEED); // Left Motor Speed
  analogWrite(ENB, MOTOR_SPEED); // Right Motor Speed

  Serial.begin(9600); // Debugging purpose
}

void loop() {
  // Read IR sensor values
  int leftmost = digitalRead(IR1);
  int left = digitalRead(IR2);
  int center = digitalRead(IR3);
  int right = digitalRead(IR4);
  int rightmost = digitalRead(IR5);

  // Debugging IR sensor values
  Serial.print(leftmost);
  Serial.print("\t");
  Serial.print(left);
  Serial.print("\t");
  Serial.print(center);
  Serial.print("\t");
  Serial.print(right);
  Serial.print("\t");
  Serial.println(rightmost);

  // Line following logic based on sensor input

  // Forward - if center sensor is on the line
  if (center == LOW) {
    moveForward();
  }
  // Slight left - if left sensor detects the line
  else if (left == LOW) {
    turnSlightLeft();
  }
  // Slight right - if right sensor detects the line
  else if (right == LOW) {
    turnSlightRight();
  }
  // Hard left - if leftmost sensor detects the line
  else if (leftmost == LOW) {
    turnHardLeft();
  }
  // Hard right - if rightmost sensor detects the line
  else if (rightmost == LOW) {
    turnHardRight();
  }
  // Stop - if no sensor detects the line
  else {
    stopMotors();
  }

  delay(50); // Delay to avoid too rapid motor changes
}

// Motor Control Functions
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);   // Left motor forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);   // Right motor forward
}

void turnSlightLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);  // Left motor stops or goes slightly backward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);   // Right motor forward
}

void turnSlightRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);   // Left motor forward
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);  // Right motor stops or goes slightly backward
}

void turnHardLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);  // Left motor backward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);   // Right motor forward
}

void turnHardRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);   // Left motor forward
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);  // Right motor backward
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);   // Left motor stop
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);   // Right motor stop
}
