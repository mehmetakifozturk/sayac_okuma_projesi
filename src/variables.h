#ifndef VARIABLES_H
#define VARIABLES_H
#include <Arduino.h>
#define RS_DR_PIN 14


struct meter_data {
  String serial_number;
  String time;// şarj başlama zaman ve saati
  String date;
  String date_time;// şarj başlama zaman ve saati
  double total_consumption;//şarja başlamadan önceki kwh değeri
  double instant_consumption; // anlık ortalama tüketim değeri kw 
  float current_values[3];// L1,L2,L3
  float voltage_values[3];//L1,L2,L3
  int faill_satatus;
};





#endif