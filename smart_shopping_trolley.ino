// Define ultrasonic sensor pins
#define trigPin1 9
#define echoPin1 10
#define trigPin2 11
#define echoPin2 12

// Define motor driver pins
#define IN1 5
#define IN2 6
#define IN3 7
#define IN4 8
#define ENA 3
#define ENB 9

// Define motor speeds
int motorSpeed = 150; // Adjust speed as needed (0-255)

void setup() {
  // Initialize ultrasonic sensors
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  // Initialize motor driver pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Start serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Measure distances from both sensors
  long distance1 = getDistance(trigPin1, echoPin1);
  long distance2 = getDistance(trigPin2, echoPin2);

  // Debugging: Print distances to serial monitor
  Serial.print("Distance 1: ");
  Serial.print(distance1);
  Serial.print(" cm | Distance 2: ");
  Serial.println(distance2);

  // Logic to follow the customer
  if (distance1 > 50 && distance2 > 50) {
    // No customer detected: Stop
    stopMotors();
  } else if (distance1 < 30 && distance2 < 30) {
    // Customer is in front: Move forward
    moveForward();
  } else if (distance1 < 30 && distance2 > 30) {
    // Customer is on the left: Turn left
    turnLeft();
  } else if (distance1 > 30 && distance2 < 30) {
    // Customer is on the right: Turn right
    turnRight();
  } else {
    // Default: Stop
    stopMotors();
  }
}

// Function to measure distance using ultrasonic sensor
long getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2; // Convert to cm
  return distance;
}

// Function to move forward
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
}

// Function to turn left
void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
}

// Function to turn right
void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
}

// Function to stop motors
void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

/*Components Required:
Arduino Uno (or any compatible board).

Ultrasonic Sensors (HC-SR04) – To detect the customer's position.

Motor Driver (L298N) – To control the DC motors.

DC Motors (2 or 4) – For the trolley's wheels.

Chassis – To mount the motors, sensors, and Arduino.

Power Supply – Battery pack or external power source.

Wheels – For the trolley's movement.

/*Wiring:
Ultrasonic Sensors:

Trig → Arduino Digital Pin (e.g., 9, 11).

Echo → Arduino Digital Pin (e.g., 10, 12).

VCC → 5V.

GND → GND.

Motor Driver (L298N):

IN1, IN2 → Arduino Digital Pins (e.g., 5, 6) – Controls Motor A.

IN3, IN4 → Arduino Digital Pins (e.g., 7, 8) – Controls Motor B.

ENA, ENB → Arduino PWM Pins (e.g., 3, 9) – Controls motor speed.

VCC → External power supply (e.g., 9V battery).

GND → Common ground with Arduino.

DC Motors:

Connect Motor A and Motor B to the motor driver outputs.