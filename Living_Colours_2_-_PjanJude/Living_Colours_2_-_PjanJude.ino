//Created: Jeremey van Uden, 11feb2019, v0
//Version
//v0, 11feb2019: initial version

//globals
bool enableDebugLog = true;
int colorNr = 0;
int colorValue = 0;
int rgbRedValue = 0;
int rgbGreenValue = 0;
int rgbBlueValue = 0;

int buttonState = 0;
int lastButtonState = 0;
#define color_Delay 100
//io
#define doLedTest 6
#define diPresetRGB 7
#define diPresetCMY 8
#define aoRed 9
#define aoGreen 10
#define aoBlue 11
#define aiPotMeter A0

void setup() {
  // put your setup code here, to run once:
  InitSerial();
  InitCreator();
  InitGlobals();
  InitPins();
}

void InitSerial()
{
  Serial.begin(115200);
  Serial.println("READY: serial initialized");
}

void InitCreator()
{
  Serial.println("Created: Jeremey van Uden, Peter Janssen, 11feb2019, v0");
}

void InitGlobals()
{
  Serial.println("INIT: globals");
  enableDebugLog = true;
  colorNr = 0;
  colorValue = 0;
  Serial.println("READY: globals initialized");
}

void InitPins()
{
  Serial.println("INIT: Pins");
  pinMode(diPresetRGB, INPUT_PULLUP);
  pinMode(diPresetCMY, INPUT_PULLUP);
  Serial.println("READY: Pins initialized");
}
void InitDemo()
{
  Serial.println("INIT: Demo");
  //loop to handle three colors
  while (colorNr < 3)
  {
    while (colorValue < 256)
    {
      //loop to handle one color incrementing
      UpdateColor();
      delay(color_Delay);
      colorValue = colorValue + 5;
    }
    while (colorValue >= 0)
    {
      //loop to handle one color incrementing
      UpdateColor();
      delay(color_Delay);
      colorValue = colorValue - 5;
    }
    colorNr++;
  }

  //inside
  //loop to handle one color increment
  Serial.println("READY: Demo");
}

void UpdateColor()
{
  switch (colorNr)
  {
    case 0:
      analogWrite(aoRed, colorValue);
      break;
    case 1:
      analogWrite(aoGreen, colorValue);
      break;
    case 2:
      analogWrite(aoBlue, colorValue);
      break;
  }
  PrintLn("Colorvalue : " + (String)colorValue + " > colorNr : " + (String)colorNr);
}


void HandlePresets()
{
  if (digitalRead(diPresetCMY) == LOW)
  {
    PrintLn("CMY Preset");
    HandleCmy();
    delay(500);
  }
  else if (digitalRead(diPresetRGB) == LOW)
  {
    PrintLn("RGB Preset");
    HandleRgb();
    delay(500);
  }
}

void HandleCmy()
{
  static int m_colorCmyNr = 0;
  colorNr = 0;
  colorValue = 255;
  UpdateColor();

  colorNr = 1;
  UpdateColor();

  colorNr = 2;
  UpdateColor();

  colorNr = m_colorCmyNr;
  colorValue = 0;
  UpdateColor();
  PrintLn("CMY mode:" + (String)m_colorCmyNr);
  switch (m_colorCmyNr)
  {
    case 0:
      PrintLn("Cyan");
      break;
    case 1:
      PrintLn("Magenta");
      break;
    default:
      PrintLn("Yellow");
      m_colorCmyNr = -1;
      break;
  }
  m_colorCmyNr++;
}

void HandleRgb()
{
  resetLightValues();
  int m_rgbCounter = 0;
  int m_potMeterValue = 0;
  while (m_rgbCounter < 3)
  {
    if (digitalRead(diPresetCMY) == LOW)
    {
      buttonState = 0;
      lastButtonState = 0;
      resetLightValues();
      m_rgbCounter = 0;
      m_potMeterValue = 0;
      HandleCmy();
      break;
    }
    m_potMeterValue = map(analogRead(aiPotMeter), 0, 1019, 0, 255);
    switch (m_rgbCounter)
    {
      case 0:
        analogWrite(aoRed, m_potMeterValue);

        break;
      case 1:
        analogWrite(aoGreen, m_potMeterValue);
        break;
      case 2:
        analogWrite(aoBlue, m_potMeterValue);
        break;
    }
    m_rgbCounter = CheckButtonPress(m_rgbCounter);
  }
}

int CheckButtonPress(int a_rgbCounter)
{
  buttonState = digitalRead(diPresetRGB);
  if (buttonState != lastButtonState) {
    if (buttonState == LOW) {
      a_rgbCounter++;
    }
    delay(50);
  }
  lastButtonState = buttonState;
  return a_rgbCounter;
}
void resetLightValues()
{
  colorValue = 0;
  analogWrite(aoRed, colorValue);
  analogWrite(aoGreen, colorValue);
  analogWrite(aoBlue, colorValue);
}
void loop() {
  HandlePresets();
}
void PrintLn(String a_inputString)
{
  if (enableDebugLog == true)
  {
    Serial.println(a_inputString);
  }
}

