int detectPin = 13;
bool detect = false;

void setup() {
  Serial.begin(115200);
  pinMode (detectPin, INPUT);
}

void loop() {
  detect = digitalRead(detectPin);
  if(detect == true) {Serial.println("Movement detected");} 
  else {Serial.println("Movement not detected");}
  delay(1000);
}
