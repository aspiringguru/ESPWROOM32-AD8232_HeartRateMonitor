
const int OutputPin = 34;
int Output = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println("started");
  delay(1000);
}


void loop()
{
  Output = analogRead(OutputPin);
  Serial.print("Output:");
  Serial.println(Output);  
  delay(500);
}
