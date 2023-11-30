#include <ethernet.h>


boolean ethernet::wifiRun(const boolean Check_Or_Try){

    if(Check_Or_Try){
      WiFi.disconnect();
      delay(500);
      WiFi.enableSTA(true);
      
      WiFi.begin(ssid, password);
      delay(5000); //pyton kod yorumu için beklemek zorundayız
     }
      if(WiFi.status()!= WL_CONNECTED){
      return false;
     }else{
        return true;
     }
     }
     /////////////////////////////////////////////////////////////////
     boolean ethernet::wifiBegin(meter_data* ac_meter){
            e_meter=ac_meter;
            delay(1000);
            Serial.println("WiFi bekleniyor......");
            delay(1000);
             Serial.println("WiFi bekleniyor......");
              Serial.println("WiFi bekleniyor......");
               Serial.println("WiFi bekleniyor......");
            if(wifiRun(true)){
              Serial.println("Wifi tamam...");
              return true;
            }else{
              Serial.println("Wifi a baglanilamadi offline moda gecildi...");
              return false;
            }
          
}
//////////////////////////////////////////////////////////////////////////////
void ethernet::checkTheWifi(void (*functionsOfmain) (void)){
     A:
 
   if((millis()-wifiCheckPreviusTime>=wifiCheckTime)||wifiRun(false)==false){
     wifiCheckPreviusTime=millis();
   if((wifiRun(false))==false){
       wifiRun(true);
        
   }
  
    while((wifiRun(false))==false){
 
    functionsOfmain();
      if(millis()-wifiCheckPreviusTime>=180000) {goto A;}
    
    functionsOfmain();
    }
    
   
   wifiCheckPreviusTime=millis();
   }
}

///////////////////////////////////////////////////////////////////////////////////////////////
void ethernet::method_post(/*void (*functionsOfmain) (void)*/ void){
 
     String postData="key=" + key;
        postData+="&serial_number=";
        postData+=e_meter->serial_number;
        postData+="&device_status=";
        postData+=String(e_meter->faill_satatus);
        postData+="&id"+String(133)+"=";
        postData+=String(e_meter->instant_consumption);
        postData+="&id"+String(134)+"=";
        postData+=String(e_meter->total_consumption);
        postData+="&id"+String(135)+"=";
        postData+=String(e_meter->voltage_values[0]);
        postData+="&id"+String(136)+"=";
        postData+=String(e_meter->voltage_values[1]);
        postData+="&id"+String(137)+"=";
        postData+=String(e_meter->voltage_values[2]);
        postData+="&id"+String(138)+"=";
        postData+=String(e_meter->current_values[0]);
        postData+="&id"+String(139)+"=";
        postData+=String(e_meter->current_values[1]);
        postData+="&id"+String(140)+"=";
        postData+=String(e_meter->current_values[2]);
        Serial.println(postData);
        if(wifiRun(false)==true){
        if(millis()-postingPreviusTime>=postingTimeRange){
                 postingPreviusTime=millis();
                  
    

 
          
    ///////////////////////////////////////////////////////////////////////////////////
         if(wifiRun(false)==true){
        HTTPClient http;
        http.begin(apiAddress);// SUNUCU  URL Sİ
        http.addHeader("Content-Type", Content_Type);
        int httpResponseCode=http.POST(postData); //+ "&VTBP->ConVariables.NetVariables.sensorids=" + VTBP->ConVariables.NetVariables.sensorids 
        Serial.println();
        Serial.println("HTTP CEVABI=" +String(httpResponseCode));
        if(httpResponseCode>=200 && httpResponseCode<=226){
          String response =http.getString();
          int response_int=response.toInt();
          Serial.println("VERiLER BASARI iLE iLETiLDi");
   }
     http.end(); 
    
 }
}
        }
}