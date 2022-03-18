const int magnet_switch = 5;     // Magnet switch
const int ledPin =  2;      // LED pin

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(magnet_switch, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(magnet_switch) == LOW) {
    digitalWrite(ledPin, HIGH);
  }else {
    digitalWrite(ledPin, LOW);
  }
}
