/*
 * 
 * 
 * 
 */


const int OutputPin = 34;
const int OutputPinLplus = 32;
const int OutputPinLminus = 35;
uint32_t Output;
uint32_t millistimer = millis();

#define DEVICE_TYPE "ESPWROOM32" //
String clientId = DEVICE_TYPE ;
#define WARMUPTIME 10000 // 10sec

void setup()
{
  Serial.begin(115200);
  Serial.println("started");
  
  uint64_t chipid;
  chipid = ESP.getEfuseMac();
  clientId += "-";
  clientId += String((uint32_t)chipid, HEX);
  Serial.println("clientId :" + clientId);

  //pinMode(OutputPin, INPUT); // Setup for leads off detection 
  pinMode(OutputPinLplus, INPUT); // Setup for leads off detection LO +
  pinMode(OutputPinLminus, INPUT); // Setup for leads off detection LO -

  while (millis() < WARMUPTIME) {
    delay(1);
  }
  Serial.println("warmup time completed.");

  //delay(1000);
}


void loop()
{
  /*
  Serial.print("analogRead(OutputPin):");
  Serial.print(analogRead(OutputPin));
  Serial.print("  analogRead(OutputPinLplus):");
  Serial.print(analogRead(OutputPinLplus));
  Serial.print("  analogRead(OutputPinLminus):");
  Serial.println(analogRead(OutputPinLminus));
  */
  if ( (analogRead(OutputPinLplus)!=0) || (analogRead(OutputPinLminus)!=0) ) {
    Serial.print("!");
  }
  else {
    Serial.println(analogRead(OutputPin));
  }
  delay(1);//small delay to prevent saturation of serial port
}
