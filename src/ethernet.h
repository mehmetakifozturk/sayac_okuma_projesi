#ifndef ETHERNET_H
#define ETHERNET_H
#include <variables.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
class ethernet
{
private:
int16_t previusErrorCode=0; //onceki hata kodu
const unsigned int wifiCheckTime=4000;//wifi kontrol zaman aralığı ms
unsigned long wifiCheckPreviusTime=0;//wifi zaman tutucu
 unsigned long postingTimeRange=5000;//post zaman aralığı
 unsigned long postingPreviusTime=0;// post zaman tutucu
const String apiAddress="server ip addres";
const String Content_Type="application/x-www-form-urlencoded";// uygulama tipi
const String key="yourkey";  // server anahtarı
meter_data *e_meter; // verilerin tutulduğu yapı adresi
public:
const char* ssid = "yourssid"; //modem ismi
const char* password = "yourpasword"; //modem şifresi
// fonksiyon tanımlamaları
boolean wifiBegin(meter_data *ac_meter);
void method_post(void);
boolean wifiRun(const boolean Check_Or_Try);
void checkTheWifi(void (*pointer) (void));

    



};
#endif