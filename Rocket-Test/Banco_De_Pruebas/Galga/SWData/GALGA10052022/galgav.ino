const int adc_Galga = 13;
float read_Adc = 0;
float voltaje = 0;
float peso = 0;
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  read_Adc = analogRead(adc_Galga);
  peso = map(read_Adc,0,4095,0,2000);
  voltaje = read_Adc*5/4095;
  Serial.print("bits = ");
  Serial.println(read_Adc);
  Serial.print("voltaje = ");
  Serial.println(voltaje);
  Serial.print("Peso = ");
  Serial.println(peso);
  Serial.println("----------------------------------------");

  delay(1000);
}
