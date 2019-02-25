//Created: Jeremey van Uden, 11feb2019, v0
//Version
//v0, 11feb2019: initial version

//globals
bool enableDebugLog = true;
int colorNr = 0;
int colorValue = 0;
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
  InitDemo();
}

void InitSerial()
{
  Serial.begin(115200);
  Serial.println("READY: serial initialized");
}

void InitCreator()
{
  Serial.println("Created: Jeremey van Uden, 11feb2019, v0");
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
      colorValue = colorValue + 5;
    }
    while (colorValue >= 0)
    {
      //loop to handle one color incrementing
      UpdateColor();
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
  delay(color_Delay);
}


void HandlePresets()
{
  if (digitalRead(diPresetCMY) == LOW)
  {
    PrintLn("CMY Preset");
    HandleCmy();
    delay(500);
  }
}

void HandleCmy()
{
  static int m_colorCmyNr = 0;
  colorNr = 0;
  colorValue = 0;
  PrintLn("CMY mode:" + (String)m_colorCmyNr);
  switch (m_colorCmyNr)
  {
    case 0:
      colorNr = 0;
      colorValue = 255;
      UpdateColor();

      colorNr = 1;
      UpdateColor();

      colorNr = 2;
      UpdateColor();

      PrintLn("Cyan");
      break;
    case 1:
      colorNr = 0;
      UpdateColor();

      colorNr = 1;
      colorValue = 255;
      UpdateColor();

      colorNr = 2;
      UpdateColor();
      PrintLn("Magenta");
      break;
    default:
      colorNr = 0;
      UpdateColor();

      colorNr = 1;
      UpdateColor();

      colorNr = 2;
      colorValue = 255;
      UpdateColor();
      PrintLn("Yellow");
      m_colorCmyNr = -1;
      break;
  }
  m_colorCmyNr++;
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

