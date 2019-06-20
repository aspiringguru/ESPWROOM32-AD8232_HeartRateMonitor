
const int OutputPin = 34;
const int OutputPinLplus = 32;
const int OutputPinLminus = 35;
int Output = 0;
int Lplus = 0;
int Lminus = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println("started");
  delay(1000);
}


void loop()
{
  Output = analogRead(OutputPin);
  Lplus = analogRead(OutputPinLplus);
  Lminus = analogRead(OutputPinLminus);
  Serial.print("Output:");
  Serial.print(Output);  
  Serial.print("  Lplus :");
  Serial.print(Lplus );  
  Serial.print("  Lminus:");
  Serial.println(Lminus);  
  delay(500);
}
