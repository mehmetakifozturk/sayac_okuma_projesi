#ifndef ELECTRICMETER_H
#define ELECTRICMETER_H
#include <variables.h>
#define RXD2 16 //port pin tanımlamaları
#define TXD2 17
class electricmeter{
private:

public:
String readDatetime(char *p);// sayaçtan gelen veri içersindeki zaman verisini parçalayıp alır
double readValuesFromCounter(char *p);// sayaç verilerinden numerik değer çekiyoruz
void vParseOsosProcess(String buffer,meter_data* e_counter);// sayaç üzerineki veriyi parçalıyoruz
String readCounter(void);// sayaçtan tüm veriyi çekiyoruz
void begin(void); // sayaç iletişimini başlatıyoruz

};





#endif