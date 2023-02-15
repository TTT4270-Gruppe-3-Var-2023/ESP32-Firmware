#define led 2 //Gir pin 2 navnet led.

void setup() {
  // Koden her blir kjørt en gang i begynnelsen av programmet:
  pinMode(led,OUTPUT);
}

void loop() {
  // koden her blir kjørt igjen og igjen helt til ESP32 blir skrudd av:
  digitalWrite(led,HIGH); //sender ut signalet "høy" til pin 2 (led), LED-lyset vil da lyse.
  delay(500); //Venter 500ms.
  digitalWrite(led,LOW); //sender ut signalet "lav" til pin 2 (led), LED-lyset blir skrudd av.
  delay(500); //Venter 500ms.
}
