
void ConfigDevice_init(void){
  
  // --------------------Получаем настройки влажности со страницы
  HTTP.on("/set", HTTP_GET, []() {
  jsonWrite(configSetup, "Sethum", HTTP.arg("Sethum"));
  jsonWrite(configSetup, "timewatering", HTTP.arg("timewatering"));
  jsonWrite(configSetup, "timeofzamerHum", HTTP.arg("timeofzamerHum"));
  jsonWrite(configSetup, "timeofzamerLight", HTTP.arg("timeofzamerLight"));
  jsonWrite(configSetup, "light", HTTP.arg("light"));                // Функция сохранения данных во Flash
  Data=1;
  NewData=true;
  jsonWrite(configSetup, "DataInf",(String)Data);
  saveConfig(); 
  HTTP.send(200, "text/plain", "OK"); // отправляем ответ о выполнении
  });
  // --------------------Разрешение отправки данных на сайт
  HTTP.on("/otpravka", HTTP_GET, []() {
  jsonWrite(configSetup, "otpravka", HTTP.arg("otpravka"));
  saveConfig();                 // Функция сохранения данных во Flash
  HTTP.send(200, "text/plain", "OK"); // отправляем ответ о выполнении
  });
  
  
  
  }
 void Soil_hum(long& timing5,int Normallevelofhum,bool& time1,long dlitelnostpoliva,byte& countofzamer){ //////////////// Управление датчиком влажности почвы

      digitalWrite(SoilSensorPower,HIGH);
      delay(100);
      int Levelofhum = map(analogRead(SoilSensorData),4096, 0, 0, 100);
      Serial.println((String)"Уровень влажности почвы:" + Levelofhum);
      digitalWrite(SoilSensorPower,LOW);
      jsonWrite(configSetup, "humS", Levelofhum);
      if (Levelofhum < Normallevelofhum)
      {      
        digitalWrite(motorpin, HIGH);
        delay(dlitelnostpoliva); 
        digitalWrite(motorpin, LOW);       
      }
      countofzamer--;
      
      if (countofzamer == 0) {
        countofzamer =2;
        timing5 = millis();
        time1 = false;
      }
  }
  void RoomHum_Tem(){ /////////////////////// Управление датчиком температуры и влажности помещения
   float h = dht.readHumidity();
   float t = dht.readTemperature();
    if (isnan(h) || isnan(t)) {
      Serial.println("Ошибка считывания");
    }
    else{
      jsonWrite(configSetup, "hum", h);
      jsonWrite(configSetup, "tem", t);
       Serial.println((String)"Влажность:" + h + " %\t" + "Температура: " + t + " *C ");
      } 
    
    }

  void Check_Light(long NormalLight){///////////////////////Управление датчиком освещ
   ledcWrite(ledChannel, 0);
   delay(1000);
   int last=map(analogRead(lightpin),0,4095,10,0);
   Serial.println((String)"LevelOfLight="+last);
   int i=map(analogRead(lightpin),0,4095,255,0);
   Serial.println((String)"i="+i);
   if(last<NormalLight)
  {
  while(last!=NormalLight)
  {
   if(i<256)
    {
  ledcWrite(ledChannel, i);
  i++;
  delay(100);
  last=map(analogRead(lightpin),0,4095,10,0);
  Serial.println((String)"LastAF="+last);
    }
    else i=0;
  }
 }   
  }
void PosthttpRequest(String idenfnum,String type)
{
if (client.connect(server, 80)) {
 Serial.println("Connection to server...");
 
  jsonString = "idenfnum=" +idenfnum+ "&type="+ type +"&temp=" + jsonRead(configSetup, "tem") + "&humroom=" + jsonRead(configSetup, "hum") +"&humsoil="+jsonRead(configSetup, "humS");
  PostHeader = "POST /connect.php/HTTP/1.1\r\n"; 
  PostHeader += "Host: ismartplant.ru:80\r\n";
  PostHeader += "User-Agent: ESP8266WiFi\r\n"; 
  PostHeader += "Accept: application/xml\r\n";
  PostHeader += "Content-Type: application/x-www-form-urlencoded\r\n"; 
  PostHeader += "X-Requested-With: XMLHttpRequest\r\n";  
  PostHeader += "Referer: http://ismartplant.ru\r\n";
  PostHeader += "Accept: application/xml\r\n";  
  PostHeader += "Connection: close\r\n";
  PostHeader += "Content-Length: " + String(jsonString.length()) + "\r\n";
  jsonString += "\r\n\r\n\r\n";
  
  client.println(PostHeader);
  client.println(jsonString);
 }
 else {
    Serial.println("Сonnection failed");
 }
   if (!client.connected()) {
    Serial.println();
    Serial.println("Disconnecting.");
    client.stop();
   }  
}
