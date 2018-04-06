// Attributes

// Operations
void ledControlSetup(int pins[]) {
  int MAX_LEDS = 3;
  for(int led = 0; led < MAX_LEDS; led++) {
    pinMode(pins[led], OUTPUT);
  }
}

void ledControlSetLedOn(int pin) {
  digitalWrite(pin, HIGH);
}

void ledControlSetLedOff(int pin) {
  digitalWrite(pin, LOW);
}

