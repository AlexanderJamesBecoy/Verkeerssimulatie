// Attributes
const int BAUD = 9600;

// Operations
void serialInput_Setup() {
  Serial.begin(BAUD);
}

boolean serialInput_Received() {
  int value = Serial.read();
  return (value > -1);
}

