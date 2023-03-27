// set pin numbers
const int pirPin = 4;  // the number of the pir-sensor pin

// variable for storing the pushbutton status 
int pirState = 0;

bool pirState1 = false;
bool pirState2 = false;
bool pirState3 = false;
bool pirState4 = false;
bool pirState5 = false;

bool pirValue = false;

void setup() {
  // Begin serial monitor at 115200 baud
  Serial.begin(115200);  
  // initialize the pir sensor pin as an input
  pinMode(pirPin, INPUT);
  
}

void loop() {
  // read the state of the pir-sensor value
  pirState = analogRead(pirPin);

  delay(1000);
  
  pirState5 = pirState4;
  pirState4 = pirState3;
  pirState3 = pirState2;
  pirState2 = pirState1;

  if (pirState > 1900 || pirState < 1800) { //
    pirState1 = true;
    Serial.println("Movement detected");
  } else {
    pirState1 = false;
    Serial.println("Movement is not detected");
  }

  if (pirState1 == pirState2 == pirState3 == pirState4 == pirState5 == false) {
    pirValue = false;
  }  else {
    pirValue = true;
  }
  Serial.print("PirValue: ");
  Serial.println(pirValue);

}
