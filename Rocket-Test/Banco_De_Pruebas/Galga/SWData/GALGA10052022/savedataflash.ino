#include "SPIFFS.h"

const int adc_Galga = 13;

float read_Adc = 0;
float voltaje = 0;
float peso = 0;

void setup() {
 
   Serial.begin(115200);
   pinMode(25, INPUT);
   pinMode(32, INPUT);
   pinMode(33, INPUT);
   //pinMode(34, INPUT);
 
   if(!SPIFFS.begin(true)){
        Serial.println("Error montando SPIFFS");
        return;
   }
//  else if(digitalRead(34) == 1){
//    //--------- Escribir en el archivo
//    File fileToWrite = SPIFFS.open("/test2.txt", FILE_WRITE);
// 
//    if(!fileToWrite){
//        Serial.println("Error abriendo el archivo para escribir");
//        return;
//    }
// 
//    fileToWrite.println("Galga");
//    fileToWrite.close();
// }
    //--------- Agregar contenido al archivo
  else if(digitalRead(32) == 1){
   for (int i = 0; i <= 9; i++) { 
    read_Adc = analogRead(adc_Galga);
    peso = map(read_Adc,0,4095,0,2000);
    voltaje = read_Adc*5/4095;
    
    File fileToAppend = SPIFFS.open("/test2.txt", FILE_APPEND);
 
    if(!fileToAppend){
        Serial.println("Error abriendo el archivo para agregar contenido");
        return;
    }
    
    Serial.println(peso);
    fileToAppend.println(peso); 
    
    fileToAppend.close();

    delay(50);
   }
  }
    //---------- Leer archivo
   else if(digitalRead(33) == 1){
    File fileToRead = SPIFFS.open("/test2.txt");
 
    if(!fileToRead){
        Serial.println("Fallo abriendo el archivo para leer");
        return;
    }
 
    Serial.println("contenido:");
 
    while(fileToRead.available()){
 
        Serial.write(fileToRead.read());
    }
 
    fileToRead.close();
   }
    //---------- borrar archivo   
   else if(digitalRead(25) == 1){
   SPIFFS.remove("/test2.txt");
   }
}
void loop() {}
