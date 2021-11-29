#include "set.h"

void setup() {
  Serial.begin(9600);
  pinMode(SoilSensorData, INPUT);
  pinMode(dhtSensor, INPUT_PULLUP);
  pinMode(SoilSensorPower, OUTPUT);
  pinMode(motorpin, OUTPUT);
  digitalWrite(motorpin,LOW);
  pinMode(lamppin, OUTPUT);
  digitalWrite(lamppin,LOW);
  pinMode(lightpin, INPUT_PULLUP);
  digitalWrite(SoilSensorPower, LOW);
  dht.begin();
  WebServer HTTP (port);
  delay(5);
  ledcSetup(ledChannel, freq, resolution);  
  // привязываем канал к портам светодиодов
  ledcAttachPin(lamppin, ledChannel);
  //Запускаем файловую систему  
  FS_init();
  configSetup = readFile("config.json", 4096);
  //Запускаем WIFI
  WIFIinit();
  NormalTime =(atoi(jsonRead(configSetup, "timeofzamerLight").c_str()))*1000*60; //время между проверками //миним. 1 минута по умолч 10 мин
  //Настраиваем и запускаем HTTP интерфейс
  HTTP_init();

  Serial.println("Start");
  Data=atoi(jsonRead(configSetup, "DataInf").c_str());
  Serial.println(jsonRead(configSetup, "DataInf"));

  //Проверяем и отправляем настройки устройства
  ConfigDevice_init();
  
}

void loop() {
  HTTP.handleClient();
  if(Data==true){
    if(NewData==true)
    {
  NewData=false;
  dlitelnostpoliva =(atoi(jsonRead(configSetup, "timewatering").c_str()))*1000;//Длительность полива(в сек.)
  timerofzamer =(atoi(jsonRead(configSetup, "timeofzamerHum").c_str()))*1000*60*60; //Время между замерами(в часах)
  Normallevelofhum = atoi(jsonRead(configSetup, "Sethum").c_str());
  _otpravka=atoi(jsonRead(configSetup, "otpravka").c_str());
  NormalTime =(atoi(jsonRead(configSetup, "timeofzamerLight").c_str()))*1000*60; //время между проверками //миним. 1 минута по умолч 10 мин
  Serial.println(NormalTime);
  NormalLight=(atoi(jsonRead(configSetup, "light").c_str()));
  if(firstStart==true)
  {
  firstStart==false;
  timing= -60000;
  timing2= -NormalTime;
  timing5 =timerofzamer*(-1); 
  timing3 = -1800000; 
  timing4= timerofminizamer*(-1);
  }
    }
    if (millis() - timing > 60000) 
    {
     timing = millis();
     RoomHum_Tem();
    }
    if (millis() - timing2>NormalTime) 
     {
      timing2 = millis();
      Check_Light(NormalLight);
     }
    if (millis() - timing5 > timerofzamer) time1 = true; 
  if (time1 == true) 
  {
    if (millis() - timing4 > (timerofminizamer)) 
    {
      timing4 = millis();
    Soil_hum(timing5,Normallevelofhum,time1,dlitelnostpoliva,countofzamer); 
    }
  }  
    if(_otpravka==true){
      if(millis()-timing3>1800000){
        timing3=millis();
      PosthttpRequest( idenfnum, type);
      }
      } 
}

}
