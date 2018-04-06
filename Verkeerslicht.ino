// Attributes
const int MAX_LED_PATTERNS = 10;
const int VOETGANGERSLICHT_LED_PATTERN[MAX_LED_PATTERNS] = { //-ABCDEFG(DP)
                                                               B11111100, //0
                                                               B01100000, //1
                                                               B11011010, //2
                                                               B11110010, //3
                                                               B01100110, //4
                                                               B10110110, //5
                                                               B10111110, //6
                                                               B11100000, //7
                                                               B11111110, //8
                                                               B11110110  //9
                                                           };
const int MAX_VERKEERSLICHTEN = 2;
const int MAX_KLEUREN = 3;
const int LINKER_VERKEERSLICHT = 0;
const int RECHTER_VERKEERSLICHT = 1;
const int MAX_TIMER = 9;
const int LED_PINS[MAX_VERKEERSLICHTEN][MAX_KLEUREN] = {  {5, 6, 7}, {2, 3, 4} };
const long TIME_INTERVAL = 1000;

unsigned long previousMillis_Verkeerslicht;
int voetgangers_CurrentDigit;
boolean autoIsAanwezig;

// Operations
void verkeersLichtSetup() {
  setupShiftRegister();
  clearShiftRegister();
  buzzerSetup();
  voetgangers_CurrentDigit = -1;
  ledControlSetup(LED_PINS[LINKER_VERKEERSLICHT]);
  ledControlSetup(LED_PINS[RECHTER_VERKEERSLICHT]);
}

void voetgangersAftellen() {
  if(voetgangers_CurrentDigit >= 0) {
    buzzerTrillen(voetgangers_CurrentDigit);
    if(millis() - previousMillis_Verkeerslicht >= TIME_INTERVAL) {
      setShiftRegister(VOETGANGERSLICHT_LED_PATTERN[voetgangers_CurrentDigit]);
      voetgangers_CurrentDigit = voetgangers_CurrentDigit - 1;
      previousMillis_Verkeerslicht = millis();
    }
  } else {
    buzzerStoppen();
    switchState(getSTATE_VERKEER_IDLE());
  }
}

void verkeersLicht(int verkeerslicht, int kleur) {
  for(int led = 0; led < MAX_KLEUREN; led++) {
    if(led == kleur) {
      ledControlSetLedOn(LED_PINS[verkeerslicht][led]);
    } else {
      ledControlSetLedOff(LED_PINS[verkeerslicht][led]);
    }
  }
}

void resetVoetgangers_CurrentDigit() {
  voetgangers_CurrentDigit = MAX_TIMER;
  setShiftRegister(VOETGANGERSLICHT_LED_PATTERN[voetgangers_CurrentDigit]);
  previousMillis_Verkeerslicht = millis();
}

// Getters
int getLINKER_VERKEERSLICHT() {
  return LINKER_VERKEERSLICHT;
}

int getRECHTER_VERKEERSLICHT() {
  return RECHTER_VERKEERSLICHT;
}

int getMAX_VERKEERSLICHTEN() {
  return MAX_VERKEERSLICHTEN;
}

boolean getAutoIsAanwezig() {
  return autoIsAanwezig;
}

void setAutoIsAanwezig() {
  autoIsAanwezig = true;
}

void setAutoIsAfwezig() {
  autoIsAanwezig = false;
}
