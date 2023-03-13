int trigPin = 32; // trigger pin
int echoPin = 33; // echo pin

void setup(){
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
void loop(){
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) /29.1;
  
  if (distance > 400) {Serial.println("Out of range (too far)");}
  else if (distance < 2) {Serial.println("Out of range (too close)");}
  else {Serial.print("Distance: "); Serial.print(distance, 1); Serial.println(" cm");}
  delay(2000);
}
