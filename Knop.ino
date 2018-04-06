// Attributes
const int autoKnopLinks = A3;
const int autoKnopRechts = A5;
const int voetgangersKnop = A4;

int laatsteKnopStand;
int buttonState = LOW;

// Operations
void knopSetup()
{
  pinMode(autoKnopLinks, INPUT);
  pinMode(autoKnopRechts, INPUT);
  pinMode(voetgangersKnop, INPUT);
}

boolean autoKnopLinks_Pressed()
{
  return (digitalRead(autoKnopLinks) == HIGH);
}

boolean autoKnopRechts_Pressed()
{
  return (digitalRead(autoKnopRechts) == HIGH);
}

boolean voetgangersKnop_Pressed()
{
  return (digitalRead(voetgangersKnop) == HIGH);
}

void setLaatsteKnop()
{
  if(autoKnopLinks_Pressed()) {
    laatsteKnopStand = autoKnopLinks;
  } else if(autoKnopRechts_Pressed()) {
    laatsteKnopStand = autoKnopRechts;
  } else {
    laatsteKnopStand = voetgangersKnop;
  }
}

boolean heeftGedrukt() {
  return (autoKnopLinks_Pressed() || autoKnopRechts_Pressed() || voetgangersKnop_Pressed());
}

// Getters
int getautoKnopLinks()
{
  return autoKnopLinks;
}

int getautoKnopRechts()
{
  return autoKnopRechts;
}

int getvoetgangersKnop()
{
  return voetgangersKnop;
}

int getLaatsteKnopStand()
{
  return laatsteKnopStand;
}

///////////////////////////////////////////////
//       Check If Button Clicked
///////////////////////////////////////////////
void checkButton()
{
  if(getCurrentState() != getSTATE_VERKEER_NACHTMODUS() && getCurrentState() != getSTATE_DODE_TIJD() && heeftGedrukt() && buttonState == LOW)
  {
    if(getAutoIsAanwezig())
    {
      switchState(getSTATE_DODE_TIJD());
    }
    else
    {
      if(autoKnopLinks_Pressed())
      {
        switchState(getSTATE_SLAGBOOM_SLUITEN());
      }
      else if(autoKnopRechts_Pressed())
      {
        switchState(getSTATE_SLAGBOOM_SLUITEN());
      }
      else
      {
        switchState(getSTATE_SLAGBOOM_OPENEN());
      }
    }
    setLaatsteKnop();
    setAutoIsAanwezig();
    buttonState = HIGH;
  }
  else if(!heeftGedrukt())
  {
    buttonState = LOW;
  }
}
