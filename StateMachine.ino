// Attributes
const int STATE_VERKEER_IDLE          = 0;
const int STATE_SLAGBOOM_SLUITEN      = 1;
const int STATE_AUTO_LINKS_PASSEREN   = 2;
const int STATE_AUTO_RECHTS_PASSEREN  = 3;
const int STATE_DODE_TIJD             = 4;
const int STATE_SLAGBOOM_OPENEN       = 5;
const int STATE_VOETGANGERS_PASSEREN  = 6;
const int STATE_VERKEER_NACHTMODUS     = 7;

const int ROOD = 0;
const int GEEL = 1;
const int GROEN = 2;
const int STOP = B01010101;

int currentState;
boolean stateSwitched = false;


// Operations
void stateMachine_Setup() {
  verkeersLichtSetup();
  serialInput_Setup();
  servoSetup();
  knopSetup();
  LDR_Setup();
  currentState = STATE_VERKEER_IDLE;
  State_Verkeer_Idle_Entry();
}

void stateMachine_Loop() {
  switch(currentState) {
    case STATE_VERKEER_IDLE:
      if(stateSwitched) {
        State_Verkeer_Idle_Entry();
        stateSwitched = false;
      } else {
        State_Verkeer_Idle_Do();
      }
      break;
    case STATE_SLAGBOOM_SLUITEN:
      if(stateSwitched) {
        State_Slagboom_Sluiten_Entry();
        stateSwitched = false;
      } else {
        State_Slagboom_Sluiten_Do();
      }
      break;
    case STATE_AUTO_LINKS_PASSEREN:
      if(stateSwitched) {
        State_Auto_Links_Passeren_Entry();
        stateSwitched = false;
      } else {
        State_Auto_Links_Passeren_Do();
      }
      break;
    case STATE_AUTO_RECHTS_PASSEREN:
      if(stateSwitched) {
        State_Auto_Rechts_Passeren_Entry();
        stateSwitched = false;
      } else {
        State_Auto_Rechts_Passeren_Do();
      }
      break;
    case STATE_DODE_TIJD:
      if(stateSwitched) {
        State_Dode_Tijd_Entry();
        stateSwitched = false;
      } else {
        State_Dode_Tijd_Do();
      }
      break;
    case STATE_SLAGBOOM_OPENEN:
      if(stateSwitched) {
        State_Slagboom_Openen_Entry();
        stateSwitched = false;
      } else {
        State_Slagboom_Openen_Do();
      }
      break;
    case STATE_VOETGANGERS_PASSEREN:
      if(stateSwitched) {
        State_Voetgangers_Passeren_Entry();
        stateSwitched = false;
      } else {
        State_Voetgangers_Passeren_Do();
      }
      break;
    case STATE_VERKEER_NACHTMODUS:
      if(stateSwitched) {
        State_Verkeer_Nachtmodus_Entry();
        stateSwitched = false;
      } else {
        State_Verkeer_Nachtmodus_Do();
      }
      break;
  }
}

void switchState(int switchStateTo) {
  switch(currentState) {
    case STATE_VERKEER_IDLE:
      State_Verkeer_Idle_Exit();
      break;
    case STATE_SLAGBOOM_SLUITEN:
      State_Slagboom_Sluiten_Exit();
      break;
    case STATE_AUTO_LINKS_PASSEREN:
      State_Auto_Links_Passeren_Exit();
      break;
    case STATE_AUTO_RECHTS_PASSEREN:
      State_Auto_Rechts_Passeren_Exit();
      break;
    case STATE_DODE_TIJD:
      State_Dode_Tijd_Exit();
      break;
    case STATE_SLAGBOOM_OPENEN:
      State_Slagboom_Openen_Exit();
      break;
    case STATE_VOETGANGERS_PASSEREN:
      State_Voetgangers_Passeren_Exit();
      break;
    case STATE_VERKEER_NACHTMODUS:
      State_Verkeer_Nachtmodus_Exit();
      break;
  }
  currentState = switchStateTo;
  stateSwitched = true;
}

////////////////////////////////////
//        Verkeer_Idle
////////////////////////////////////

void State_Verkeer_Idle_Entry() {
  for(int verkeerslichtIndex = 0; verkeerslichtIndex < getMAX_VERKEERSLICHTEN(); verkeerslichtIndex++) {
    verkeersLicht(verkeerslichtIndex, ROOD);
  }
  setShiftRegister(STOP);
  setAutoIsAfwezig();
}

void State_Verkeer_Idle_Do() {
  if (isNacht()) {
    switchState(STATE_VERKEER_NACHTMODUS);
  }
}


void State_Verkeer_Idle_Exit() {
  // <nothing>
}

////////////////////////////////////
//        Slagboom_Sluiten
////////////////////////////////////

void State_Slagboom_Sluiten_Entry() {
  servoDownwards();
}

void State_Slagboom_Sluiten_Do() {
  if(servoIsMin()) {
    if(getLaatsteKnopStand() == getautoKnopRechts()) {
      switchState(STATE_AUTO_RECHTS_PASSEREN);
    } else {
      switchState(STATE_AUTO_LINKS_PASSEREN);
    }
  }
}


void State_Slagboom_Sluiten_Exit() {
  // <nothing>
}

////////////////////////////////////
//        Auto_Links_Passeren
////////////////////////////////////

void State_Auto_Links_Passeren_Entry() {
  verkeersLicht(getLINKER_VERKEERSLICHT(), GROEN);
}

void State_Auto_Links_Passeren_Do() {
  // <nothing>
}


void State_Auto_Links_Passeren_Exit() {
  verkeersLicht(getLINKER_VERKEERSLICHT(), GEEL);
}

////////////////////////////////////
//        Auto_Rechts_Passeren
////////////////////////////////////

void State_Auto_Rechts_Passeren_Entry() {
  verkeersLicht(getRECHTER_VERKEERSLICHT(), GROEN);
}

void State_Auto_Rechts_Passeren_Do() {
  // <nothing>
}


void State_Auto_Rechts_Passeren_Exit() {
  verkeersLicht(getRECHTER_VERKEERSLICHT(), GEEL);
}

////////////////////////////////////
//        Dode_Tijd
////////////////////////////////////

void State_Dode_Tijd_Entry() {
  setDodeTijdTimer();
  int laatsteKnop = getLaatsteKnopStand();
}

void State_Dode_Tijd_Do() {
  if(dodeTijdTimer_IsKlaar()) {
    int laatsteKnop = getLaatsteKnopStand();
    if(laatsteKnop == getautoKnopLinks()) {
      switchState(STATE_AUTO_LINKS_PASSEREN);
    } else if(laatsteKnop == getautoKnopRechts()) {
      switchState(STATE_AUTO_RECHTS_PASSEREN);
    } else {
      switchState(STATE_SLAGBOOM_OPENEN);
    }
  }
}


void State_Dode_Tijd_Exit() {
  for(int verkeerslichtIndex = 0; verkeerslichtIndex < getMAX_VERKEERSLICHTEN(); verkeerslichtIndex++) {
    verkeersLicht(verkeerslichtIndex, ROOD);
  }
}

////////////////////////////////////
//        Slagboom_Openen
////////////////////////////////////

void State_Slagboom_Openen_Entry() {
  servoUpwards();
}

void State_Slagboom_Openen_Do() {
  if(servoIsMax()) {
    switchState(STATE_VOETGANGERS_PASSEREN);
  }
}


void State_Slagboom_Openen_Exit() {
  // <nothing>
}

////////////////////////////////////
//        Voetgangers_Passeren
////////////////////////////////////

void State_Voetgangers_Passeren_Entry() {
  resetVoetgangers_CurrentDigit();
}

void State_Voetgangers_Passeren_Do() {
  voetgangersAftellen();
}


void State_Voetgangers_Passeren_Exit() {
  // <nothing>
}

////////////////////////////////////
//        Verkeer_Nachtmodus
////////////////////////////////////

void State_Verkeer_Nachtmodus_Entry() {
  for(int verkeerslichtIndex = 0; verkeerslichtIndex < getMAX_VERKEERSLICHTEN(); verkeerslichtIndex++) {
    verkeersLicht(verkeerslichtIndex, GEEL);
  }
  clearShiftRegister();
}

void State_Verkeer_Nachtmodus_Do() {
  if(!isNacht()) {
    switchState(STATE_VERKEER_IDLE);
  }
}


void State_Verkeer_Nachtmodus_Exit() {
  // <nothing>
}

///////////////////////////////////
//      Get States
///////////////////////////////////
int getCurrentState() {
  return currentState;
}

int getSTATE_VERKEER_IDLE() {
  return STATE_VERKEER_IDLE;
}
int getSTATE_SLAGBOOM_SLUITEN() {
  return STATE_SLAGBOOM_SLUITEN;
}
int getSTATE_AUTO_LINKS_PASSEREN() {
  return STATE_AUTO_LINKS_PASSEREN;
}
int getSTATE_AUTO_RECHTS_PASSEREN() {
  return STATE_AUTO_RECHTS_PASSEREN;
}
int getSTATE_DODE_TIJD() {
  return STATE_DODE_TIJD;
}
int getSTATE_SLAGBOOM_OPENEN() {
  return STATE_SLAGBOOM_OPENEN;
}
int getSTATE_VOETGANGERS_PASSEREN() {
  return STATE_VOETGANGERS_PASSEREN;
}
int getSTATE_VERKEER_NACHTMODUS() {
  return STATE_VERKEER_NACHTMODUS;
}
