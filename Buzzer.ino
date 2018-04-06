// Attributes
const int BUZZER_PIN = 13;
unsigned long previousMillis_Buzzer;
const long BUZZER_INTERVAL_FAST = 50;
const long BUZZER_INTERVAL_SLOW = 150;

void buzzerSetup() {
  pinMode(BUZZER_PIN, OUTPUT);
  previousMillis_Buzzer = millis();
}

// Operations
void buzzerTrillen(int stand) {
  if(stand >= 0) {
    int DODE_TIJD = 1;
    int interval;
    (stand <= DODE_TIJD)? interval = BUZZER_INTERVAL_SLOW : interval = BUZZER_INTERVAL_FAST;
    if(millis() - previousMillis_Buzzer >= interval) {
      (pinIsActive(BUZZER_PIN))? digitalWrite(BUZZER_PIN, LOW) : digitalWrite(BUZZER_PIN, HIGH);
      previousMillis_Buzzer = millis();
    }
  }
}

void buzzerStoppen() {
  digitalWrite(BUZZER_PIN, LOW);
}

boolean pinIsActive(int pin) {
  return (digitalRead(pin));
}
