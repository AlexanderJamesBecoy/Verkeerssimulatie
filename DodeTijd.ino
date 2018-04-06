// Attributes
const long TIME_INTERVAL_DODE_TIJD = 2000;
unsigned long previousMillis_Dode_Tijd;

// Operations
void setDodeTijdTimer() {
  previousMillis_Dode_Tijd = millis();
}

boolean dodeTijdTimer_IsKlaar() {
  return (millis() - previousMillis_Dode_Tijd >= TIME_INTERVAL_DODE_TIJD);
}

