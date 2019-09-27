#define TCP_MSS whatever
#define LWIP_IPV6 whatever
#define LWIP_FEATURES whatever
#define LWIP_OPEN_SRC whatever
#define BLYNK_PRINT Serial
#define FAN D5
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;
int flag=0;
int flag1=0;
float temp;
int fanSpeed = 0;
// It should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "6cb5b285043d482a9a3779f642b18f5a";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "codebreakers";
char pass[] = "abcd1234efgh";

void myTimerEvent()
{
  float sensorData = analogRead(A0);
  sensorData = (sensorData *3.3*100.0)/1024.0;
  Blynk.virtualWrite(V5, sensorData);
  fanSpeed = map(sensorData, 20, 70, 32, 255);
  analogWrite(FAN, fanSpeed);

  int temp = digitalRead(D2);
  if (temp == LOW && flag1==0) {
    Blynk.notify("Alert : Danger! Gas Detected");
    flag1=1;
  }
  else
  {
    flag1=0;
  }
  int isButtonPressed = digitalRead(D3);
  if (isButtonPressed==1 && flag==0) {
    Serial.println("Someone Opened the door");
    Blynk.notify("Alert : Someone Opened the door");
    flag=1;
  }
  else if (isButtonPressed==0)
  {
    flag=0;
  }
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(D3,INPUT_PULLUP);
  pinMode(D2,INPUT_PULLUP);
  pinMode(FAN, OUTPUT);
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();
  //temp = analogRead(A0);
  //temp = (temp *5.0*100.0)/1024.0;
  //fanSpeed = map(temp, 20, 70, 32, 255);
  //analogWrite(FAN, fanSpeed);
}
