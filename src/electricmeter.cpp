#include <electricmeter.h>
void electricmeter::begin(void){
pinMode(RS_DR_PIN,OUTPUT);
Serial2.begin(300, SERIAL_7E1, RXD2, TXD2);
}
String electricmeter::readDatetime(char *p){
   char buf[20];
      int i = 0;
 if(p)
  {
    
    p = strstr(p, "(");
    
    if(p)
    {
     
      
      while(*p++ != ')')
      {
        buf[i] = *p;
        i++;
      }
      
      buf[i-1] = '\0';
     
      
    }
  }

return buf;

}
double electricmeter::readValuesFromCounter(char *p){
   char buf[20];
      int i = 0;
 if(p)
  {
    
    p = strstr(p, "(");
    
    if(p)
    {
     
      
      while(*p++ != '*')
      {
        buf[i] = *p;
        i++;
      }
      
      buf[i-1] = '\0';
    
    }
  }

return atof(buf);

}

void electricmeter::vParseOsosProcess(String buffer,meter_data* e_counter)
{
  const String DateObisCode="0.9.2", timeObisCode="0.9.1";
  const String totalkwObiscode="1.8.0",L1totalkwObiscode="1.8.1",L2totalkwObiscode="1.8.2",L3totalkwObiscode="1.8.3";
  const String average_consumObiscode="1.7.0",L1average_consumObiscode="21.7.0",L2average_consumObiscode="41.7.0",L3average_consumObiscode="61.7.0";
  const String L1CurrentObiscode="31.7.0",L2CurrentObiscode="51.7.0",L3CurrentObiscode="71.7.0";
  const String L1VoltageObiscode="32.7.0",L2VoltageObiscode="52.7.0",L3VoltageObiscode="72.7.0";
  char ObisCode[2644];
  char *p =  NULL;
  
  buffer.toCharArray(ObisCode, sizeof(ObisCode));
p = strstr(ObisCode, "0.9.1");
   e_counter->date_time= readDatetime(p)+"/";
   e_counter->time=readDatetime(p);
  p = strstr(ObisCode, "0.9.2");
   e_counter->date_time+= readDatetime(p);
   e_counter->date=readDatetime(p); 
  p = strstr(ObisCode, "1.8.0");
    e_counter->total_consumption= readValuesFromCounter(p);
     p = strstr(ObisCode,"\n1.7.0");
    e_counter->instant_consumption= readValuesFromCounter(p);
     p = strstr(ObisCode, "31.7.0");
    e_counter->current_values[0]= readValuesFromCounter(p);
      p = strstr(ObisCode, "51.7.0");
    e_counter->current_values[1]= readValuesFromCounter(p);
      p = strstr(ObisCode, "71.7.0");
    e_counter->current_values[2]= readValuesFromCounter(p);
      p = strstr(ObisCode, "32.7.0");
    e_counter->voltage_values[0]= readValuesFromCounter(p);
      p = strstr(ObisCode, "52.7.0");
    e_counter->voltage_values[1]= readValuesFromCounter(p);
    p = strstr(ObisCode, "72.7.0");
    e_counter->voltage_values[2]= readValuesFromCounter(p);

}  

String electricmeter::readCounter(){
  char sayacGonder[] = { 0X2F, 0X3F, 0X21, 0X0D, 0X0A };// /?!\r\n
char baunrateGecis[]={0X06,0X30,0X35,0X30,0X0D,0X0A};// 220 MS 
bool izin=true;
char gelenchar;
bool oku=true;
  char data[2644];
  int datasize=0;
  Serial2.begin(300, SERIAL_7E1, RXD2, TXD2);
  digitalWrite(RS_DR_PIN,1);
  delay(50);
    int i=0;
    while(i<5){
         Serial2.write(sayacGonder[i]);
         i++;
    }
    delay(200);
    digitalWrite(RS_DR_PIN,0);
    unsigned long timeout=millis();
    while((millis()-timeout<=10000)&&oku){
 while (Serial2.available()&&izin) {

    if(Serial2.read()==10){
      digitalWrite(RS_DR_PIN,1);
      delay(100);
       int i=0;
      while(i<6){
         Serial2.write(baunrateGecis[i]);
         i++;
    }
    izin=false;
    delay(500);
    Serial2.updateBaudRate(9600);
    digitalWrite(RS_DR_PIN,0);
    }
    
  }
 if(!izin){
     
while(Serial2.available()){
  //Serial.print(char(Serial2.read()));
  gelenchar=char(Serial2.read());
  if(gelenchar==3||gelenchar==2)
  break;
  if(gelenchar=='!'){
   oku=false;
   data[datasize]='\0';
  }
 
  if(oku){
    data[datasize]=gelenchar;
    datasize++;

  }
    
}

    }
     

 }
   Serial2.end();
   if(datasize>=2643){
   Serial.println("data size="+String(datasize));
    return(data);
    
   }else{
    return"0";
   }

}
