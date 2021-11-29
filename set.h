#include <WiFi.h>
#include <WebServer.h>
#include "DHT.h"
#include <ArduinoJson.h>
#include "SPIFFS.h"

#define SoilSensorData 13
#define SoilSensorPower 23
#define dhtSensor 33
#define lamppin 16
#define lightpin 32
#define motorpin 22


// Web интерфейс для устройства
WebServer HTTP;

WiFiClient client;
String jsonString; // данные
String PostHeader; // заголовок

//dht датчик
DHT dht(dhtSensor, DHT11);

// Для файловой системы
File fsUploadFile;

char server[] = "ismartplant.ru";
String idenfnum = "tPmAT5Ab3j7F9";
String type = "nachinaika";


String configSetup = "{}";
String configJson = "{}";
int port = 80;

// задаём свойства ШИМ-сигнала
const int freq = 20000;
const int ledChannel = 0;
const int resolution = 8;


 long timing = 0;
 long timing2 = 0;
 long timing3 = 0; // время отправки данных
 long timing4 = 0; //для замера влажности почвы
 long timing5 = 0;
 long timing6 = 0; //включение/выключение насоса



bool time1 = false;
byte countofzamer = 2; //кол-во замеров
int timerofminizamer = 600000; //Время между мини замерами(в мин.)
int Data;
bool NewData=false;
bool firstStart=true;

byte NormalLight;
int humsoil = 0;
long NormalTime=0;
long dlitelnostpoliva=0;//Длительность полива(в сек.)
long timerofzamer=0; //Время между замерами(в часах)
byte Normallevelofhum=0;
bool _otpravka=0;
