int detectPin = 13;
bool detect = false;

const int trigPin = 32;     // GPIO 32 = trigger pin
const int echoPin = 33;     // GPIO 33 = echo pin

const int potPin = 34;      // potentiometer is connected to GPIO 34 (Analog ADC1_CH6)
int potValue = 0;           // creating variable for storing the potentiometer value.

void setup() {
  Serial.begin(115200);     // Establishing serial output at 115200 baud.
  pinMode(trigPin, OUTPUT); // Configuring trigger pin to output.
  pinMode(echoPin, INPUT);  // Configuring echo pin to input.

  pinMode (detectPin, INPUT);
}

void loop() {
  // Reading microwave doppler sensor value.
  detect = digitalRead(detectPin); // Detecting movement with doppler effect
  
  // Reading potentiometer value.
  potValue = analogRead(potPin);

  // Reading distance sensor value
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Calculating distance
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) /29.1;

  // Writing microwave doppler sensor value to serial monitor.
  if(detect == true) {Serial.println("Toilett occupied");} // Movement detected
  else {Serial.println("Toilett not occupied");} // Movement not detected

  // Writing potentiometer value to serial monitor.
  Serial.print("Potentiometer value: "); Serial.println(potValue);
  
  // Writing to serial monitor
  if (distance > 400) {Serial.println("Out of range (too far)");}
  else if (distance < 2) {Serial.println("Out of range (too close)");}
  else {Serial.print("Distance: "); Serial.print(distance); Serial.println(" cm");}
  delay(500);
}
