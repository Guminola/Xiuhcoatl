#include "SPIFFS.h"

const int adc_Galga = 13;

float read_Adc = 0;
float voltaje =  0;
float peso =     0;
float save_peso= 0;

bool flag = false;

TaskHandle_t lectura_adc;


void setup()
{
  Serial.begin(115200);
  pinMode(25, INPUT);
  pinMode(32, INPUT);
  pinMode(33, INPUT);

  if(!SPIFFS.begin(true)){
        Serial.println("Error montando SPIFFS");
        delay(10);
        return;
  }
  
  xTaskCreatePinnedToCore(
      lectura, /* Funcion de la tarea1 */
      "lectura_adc", /* Nombre de la tarea */
      10000,  /* Tamaño de la pila */
      NULL,  /* Parametros de entrada */
      0,  /* Prioridad de la tarea */
      &lectura_adc,  /* objeto TaskHandle_t. */
      0); /* Nucleo donde se correra */

    //--------- Agregar contenido al archivo
  if(digitalRead(32) == 1){
   
   for (int i = 0, t = 0 ; i <= 1000; i++, t+=15) {     
    File fileToAppend = SPIFFS.open("/test.txt", FILE_APPEND);
    if(!fileToAppend){
        Serial.println("Error abriendo el archivo para agregar contenido");
        return;
    }
      if(flag == true){
        Serial.println(peso,0);
        fileToAppend.print(t);
        fileToAppend.print("\t");
        fileToAppend.println(save_peso,0); 
        fileToAppend.close();
        //delay(100);
           flag = false;
     }
   }delay(1);
  }

    //---------- Leer archivo
   else if(digitalRead(33) == 1){
    File fileToRead = SPIFFS.open("/test.txt");
 
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
   SPIFFS.remove("/test.txt");
   SPIFFS.remove("/test2.txt");
   }
}

void loop(){}

////////////Leer ADC
void lectura(void * pvParameters)
{  
for(;;){  
  read_Adc = analogRead(adc_Galga);
  voltaje = read_Adc*5/4095;
  peso = map(read_Adc,0,4095,0,2000);
  save_peso = peso;
  flag = true;
}
 vTaskDelay(5);
}
