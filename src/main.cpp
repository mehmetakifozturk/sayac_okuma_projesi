
#include <Arduino.h>// arduino kütüphanelerinden faydalanıldı
#include <electricmeter.h>//sayac hakkındaki tüm işlemlerin yapıldığı kütüphane dosyası
#include <ethernet.h>
#include <definations.h>
electricmeter counter; // sayaç için yeni sayac nesnesi tanımı
ethernet connection;


void functionsOfMain(void){
incoming_data=counter.readCounter();
Serial.print(incoming_data);
counter.vParseOsosProcess(incoming_data,&e_meter_data);
if(e_meter_data.current_values[0]>5||e_meter_data.current_values[1]>5||e_meter_data.current_values[2]>5){
      e_meter_data.faill_satatus=OVER_CURRENT;
}else{
     e_meter_data.faill_satatus=SYSTEM_NORMAL;
}
Serial.println();
Serial.println("TARiH SAAT:"+e_meter_data.date_time);
Serial.println("VOLTAJLAR:"+String(e_meter_data.voltage_values[0])+"/"+String(e_meter_data.voltage_values[1])+"/"+String(e_meter_data.voltage_values[2]));
Serial.println("AKIMLAR:"+String(e_meter_data.current_values[0])+"/"+String(e_meter_data.current_values[1])+"/"+String(e_meter_data.current_values[2]));
Serial.println("ANLIK GUC:"+String(e_meter_data.instant_consumption));
Serial.println("TOPLAM TUKETiM:"+String(e_meter_data.total_consumption));

//connection.method_post();// internete post edebilmek için bu fonksiyonları düzenleyin
delay(1000);
}

void setup() {
//connection.wifiBegin(&e_meter_data);// internete bağlanmak için bu fonksiyonları düzenleyin
Serial.begin(115200);
counter.begin();
delay(1000);
}

void loop() { 
functionsOfMain();    
//connection.checkTheWifi(&functionsOfMain); //internete bağlanmak için bu fonksiyonları düzenleyin
}
    
 
  


    
 
  



