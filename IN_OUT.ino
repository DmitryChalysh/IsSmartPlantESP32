  // поместим данные для web страницы в json строку configJson
  // Будем вызывать эту функцию каждый раз при запросе /config.live.json
  // jsonWrite(строка, "ключ", значение_число); Так можно дабавить или обнавить json значение ключа в строке
  // jsonWrite(строка, "ключ", "значение_текст"); 
void outData(){

   
   double _temRoom=atoi(jsonRead(configSetup, "otpravka").c_str());
   int _humRoom= atoi(jsonRead(configSetup, "tem").c_str());
   bool _otpravka=atoi(jsonRead(configSetup, "otpravka").c_str()); 
   
    jsonWrite(configJson, "Sethum", jsonRead(configSetup, "Sethum"));
    jsonWrite(configJson, "SoilHum", jsonRead(configSetup, "humS")); 
    jsonWrite(configJson, "TempRoom", jsonRead(configSetup, "tem"));
    jsonWrite(configJson, "HumRoom", jsonRead(configSetup, "hum"));
    jsonWrite(configJson, "configotpravka", _otpravka);
  }
