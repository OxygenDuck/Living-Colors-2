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
#define aoGreen 11
#define aiPotMeter A0

void setup() {
  // put your setup code here, to run once:
    InitSerial();
    InitCreator();
    InitGlobals();
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
  Serial.println("READY: globals initialized");
}

void InitDemo()
{
  Serial.println("INIT: Demo");
  //loop to handle three colors
  while(colorNr < 3)
  {
   while(colorValue < 256)
  {
    //loop to handle one color incrementing
    UpdateColor();
    colorValue--;
  }
  while(colorValue >= 0)
  {
    //loop to handle one color incrementing
    UpdateColor();
    colorValue++;
  }
  colorNr++;
  }
  
  //inside
  //loop to handle one color increment
  Serial.println("READY: Demo");
}

void UpdateColor()
{
  switch(colorNr)
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
  PrintLn("Colorvalue : " + (String)colorvalue + " > colorNr : " + (String)colorNr);
  delay(color_Delay);
}

void InitPins()
{
  Serial.println("INIT: Pins");
  Serial.println("READY: Pins");
}
void loop() {
  // put your main code here, to run repeatedly:

}
void PrintLn(String a_inputString)
{
  if(enableDebugLog == true)
  {
    Serial.println(a_inputString);
  }
}

