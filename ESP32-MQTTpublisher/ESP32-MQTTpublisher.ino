
//#include "DHT.h"
#include "PubSubClient.h"
#include "WiFi.h"

//#define DHTPIN 4 
//#define DHTTYPE DHT11 
//DHT dht(DHTPIN, DHTTYPE);


// WiFi
const char* ssid = "Test";    //Brukernavnet til WLAN            
const char* wifi_password = "********";//Fyll inn passordet til det trådløse internettet

// MQTT
const char* mqtt_server = "192.168.**.***"; //Fyll inn resten av IP
const char* ultrasound_topic = "ultrasound";
const char* dopplerradar_topic = "doppler-radar";
const char* potmeter_topic = "potmeter";
const char* mqtt_username = "Gruppe3"; // MQTT username
const char* mqtt_password = "**************"; // MQTT password
const char* clientID = "Weather_Reporter"; // MQTT client ID

// Initialise the WiFi and MQTT Client objects
WiFiClient wifiClient;

// 1883 is the listener port for the Broker
PubSubClient client(mqtt_server, 1883, wifiClient);

 

// Custom function to connect to the MQTT broker via WiFi
void connect_MQTT(){
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Connect to the WiFi
  WiFi.begin(ssid, wifi_password);

  // Wait until the connection is confirmed
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Debugging – Output the IP Address of the ESP8266
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Connect to MQTT Broker
  if (client.connect(clientID, mqtt_username, mqtt_password)) {
    Serial.println("Connected to MQTT Broker!");
  }
  else {
    Serial.println("Connection to MQTT Broker failed…");
  }
}

//_____

int detectPin = 13;         // Detects doppler-radar-sensor (RCWL-0516) output signal
bool detect = false;        // Keeps track of 

const int trigPin = 32;     // GPIO 32 = trigger pin
const int echoPin = 33;     // GPIO 33 = echo pin

const int potPin = 34;      // potentiometer is connected to GPIO 34 (Analog ADC1_CH6)
int potValue = 0;           // creating variable for storing the potentiometer value.

void setup() {

  Serial.begin(115200); // Establishing serial output at 115200 baud.
  //dht.begin();    
  pinMode(trigPin, OUTPUT); // Configuring trigger pin to output.
  pinMode(echoPin, INPUT);  // Configuring echo pin to input.
  pinMode(potPin, INPUT);
  pinMode (detectPin, INPUT);
}

void loop() {
  connect_MQTT();
  Serial.setTimeout(5000);
  
  // Reading potentiometer value.
  potValue = analogRead(potPin);

  // Reading microwave doppler sensor value.
  detect = digitalRead(detectPin);

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

  // PUBLISH to the MQTT Broker (topic = potmeter)
  if (client.publish(potmeter_topic, String(potValue).c_str())) {  
    Serial.println("Potmeter value sent!");
  }
  else {
    Serial.println("Potmeter value failed to send. Reconnecting to MQTT Broker and trying again");
    client.connect(clientID, mqtt_username, mqtt_password);
    delay(2); // This delay ensures that client.publish doesn't clash with the client.connect call
    client.publish(potmeter_topic, String(potValue).c_str());
  }

  if (client.publish(dopplerradar_topic, String(detect).c_str())) {  
    Serial.println("Detect value sent");
  }
  else {
    Serial.println("Detect value failed to send. Reconnecting to MQTT Broker and trying again");
    client.connect(clientID, mqtt_username, mqtt_password);
    delay(2); // This delay ensures that client.publish doesn't clash with the client.connect call
    client.publish(dopplerradar_topic, String(detect).c_str());
  }

  if (client.publish(ultrasound_topic, String(distance).c_str())) {
    Serial.println("Ultrasound-data sent!");
  }
  else {
    Serial.println("Ultrasound-data failed to send. Reconnecting to MQTT Broker and trying again");
    client.connect(clientID, mqtt_username, mqtt_password);
    delay(2); // This delay ensures that client.publish doesn't clash with the client.connect call
    client.publish(ultrasound_topic, String(distance).c_str());
  }

  client.disconnect();  // disconnect from the MQTT broker
  delay(1000*1);       // print new values after 1 Minute
  detect = digitalRead(detectPin); // Detecting movement with doppler effect
  
  

  

  // Writing microwave doppler sensor value to serial monitor.
  if(detect == true) {Serial.println("Toilett occupied");} // Movement detected
  else {Serial.println("Toilett not occupied");} // Movement not detected

  // Writing potentiometer value to serial monitor.
  Serial.print("Potentiometer value: "); Serial.println(potValue);
  
  // Writing ultrasound distance-sensor values to serial monitor
  if (distance > 400) {Serial.println("Out of range (too far)");}
  else if (distance < 2) {Serial.println("Out of range (too close)");}
  else {Serial.print("Distance: "); Serial.print(distance); Serial.println(" cm");}
  delay(500);
}
