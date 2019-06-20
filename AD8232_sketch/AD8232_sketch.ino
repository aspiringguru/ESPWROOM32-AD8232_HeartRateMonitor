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
#define DELTASIZE 140

unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 10;           // interval at which to blink (milliseconds)
int BPM;


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


  /*
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    hitung_HR(analogRead(OutputPin));
    //    Serial.println(analogRead(pin_sinyal));
  }
  Serial.println(BPM);
  */

}

unsigned long oldtime = 0;
unsigned long newtime = 0;
unsigned long beat_time = 0;
unsigned long cek_beat_time = 0;
int data_now, data_old, delta_data;
bool flag_detek = false;
float HR, HR_old;
void hitung_HR(int data_pulse)
{
  data_now = data_pulse;
  delta_data = data_now - data_old;
  //get absolute value of delta_data
  if (delta_data < 0)
    delta_data = delta_data * -1;
  data_old = data_now;

  //Serial.println(data_now);
  //Serial.println(delta_data);
  if (delta_data > DELTASIZE) // detek pertama
  {
    if (flag_detek == false)
    {
      flag_detek = true;
      newtime = millis();
    }
    else
    {
      beat_time = millis() - newtime;
      if (beat_time < 400)
      {
        newtime = millis();
//        beat_time = millis();
      }
      else
      {
        HR = 60 / (((float) beat_time) / 1000);
        HR = HR * 0.6 + HR_old * 0.4;
        if (abs(HR - HR_old) > 10)
        {
          HR = 60 / (((float) beat_time) / 1000);
          HR = HR * 0.1 + HR_old * 0.9;
        }
        //Serial.println(beat_time);
        flag_detek = false;
        HR_old = HR;
      }
    }

  }

  // cancel pertitungan
  // 150 BPM = 400 ms dan 40 BPM = 1500 ms
  cek_beat_time = millis() - newtime;
  if (cek_beat_time > 10000)
  {
    newtime = millis();
    HR = 0;
  }

  BPM = HR;


}
