// Attributes
const int MIN_VALUE = 0;
const int MAX_VALUE_ANALOG = 1023;
const int MAX_VALUE_RANGE = 10;

const int LDR_PIN = A2;
const int MINIMUM_NIGHT_VALUE = 6;

// Operations
void LDR_Setup() {
  pinMode(LDR_PIN, INPUT);
}

int getLDR_Value() {
  int value = map(analogRead(LDR_PIN), MIN_VALUE, MAX_VALUE_ANALOG, MIN_VALUE, MAX_VALUE_RANGE);
  return value;
}

boolean isNacht() {
  int LDR_Value = getLDR_Value();
  return (LDR_Value <= MINIMUM_NIGHT_VALUE);
}

