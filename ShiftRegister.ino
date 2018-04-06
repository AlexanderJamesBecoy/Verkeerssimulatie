// Attributes
const int DS_PIN = 8;
const int STCP_PIN = 9;
const int SHCP_PIN = 10;
const int MAX_SHIFT_PINS = 8;

// Operations
void setupShiftRegister() {
  pinMode(DS_PIN, OUTPUT);
  pinMode(STCP_PIN, OUTPUT);
  pinMode(SHCP_PIN, OUTPUT);
}

void clearShiftRegister() {
  digitalWrite(STCP_PIN, LOW);
  for(int pinIndex = 0; pinIndex < MAX_SHIFT_PINS; pinIndex++) {
    digitalWrite(SHCP_PIN, LOW);
    digitalWrite(DS_PIN, LOW);
    digitalWrite(SHCP_PIN, HIGH);
  }
  digitalWrite(STCP_PIN, HIGH);
}

void allOnShiftRegister() {
  digitalWrite(STCP_PIN, LOW);
  for(int pinIndex = 0; pinIndex < MAX_SHIFT_PINS; pinIndex++) {
    digitalWrite(SHCP_PIN, LOW);
    digitalWrite(DS_PIN, HIGH);
    digitalWrite(SHCP_PIN, HIGH);
  }
  digitalWrite(STCP_PIN, HIGH);
}

void setShiftRegister(byte pattern) {
  digitalWrite(STCP_PIN, LOW);
  for(int pinIndex = 0; pinIndex < MAX_SHIFT_PINS; pinIndex++) {
    digitalWrite(SHCP_PIN, LOW);
    (isSet(pattern, pinIndex))? digitalWrite(DS_PIN, HIGH) : digitalWrite(DS_PIN, LOW);
    digitalWrite(SHCP_PIN, HIGH);
  }
  digitalWrite(STCP_PIN, HIGH);
}

boolean isSet(byte ledPattern, int bitNr) {
  byte bitPattern = B00000001 << bitNr;
  if (ledPattern & bitPattern)
    return true;
  else
    return false;
}

