// Ultrasonic sensor pins
const int trigPin1 = 2;
const int echoPin1 = 3;
const int trigPin2 = 4;
const int echoPin2 = 5;
const int trigPin3 = 6;
const int echoPin3 = 7;

// Buzzer pin
const int buzzerPin = 8;

// Variables
long duration1, duration2, duration3;
long distance1, distance2, distance3;
long closestDistance;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Ultrasonic sensor pins as inputs and buzzer pin as output
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // Measure distance from the first ultrasonic sensor
  distance1 = measureDistance(trigPin1, echoPin1);

  // Measure distance from the second ultrasonic sensor
  distance2 = measureDistance(trigPin2, echoPin2);

  // Measure distance from the third ultrasonic sensor
  distance3 = measureDistance(trigPin3, echoPin3);

  // Determine the closest distance among the three sensors
  closestDistance = min(distance1, min(distance2, distance3));

  // Print the closest distance to the serial monitor
  Serial.print("Closest Distance: ");
  Serial.print(closestDistance);
  Serial.println(" cm");

  // Check if the closest distance is less than a threshold - Normal functionality
  if (closestDistance > 5 && closestDistance <= 30) {
    // Turn on the buzzer
    digitalWrite(buzzerPin, HIGH);
  } else {
    // Turn off the buzzer
    digitalWrite(buzzerPin, LOW);
  }

  // Delay before the next measurement
  delay(500);

  // Check if the closest distance is less than a threshold - Interference (nahagbong ang cane)
   if (closestDistance <= 5){
    for(int i=0; i<=5; i++){
      digitalWrite(buzzerPin, HIGH);
      delay(10);
    }
  }

}

int measureDistance(int trigPin, int echoPin) {
  // Send a pulse to the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the time it takes for the pulse to bounce back
  long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  long distance = duration * 0.034 / 2;

  return distance;
}
