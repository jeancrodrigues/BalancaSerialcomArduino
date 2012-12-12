#include <Wire.h>

void setup() {
  // inicializando a porta serial e o I2C
  Wire.begin();
  Serial.begin(9600);
  
  //Mudando paridade e stop bit da serial do arduíno
  UCSR0C = UCSR0C | B00100000;//Even par
  UCSR0C = UCSR0C | B00000000;//2stopbits   
}

void loop() {
  
  char byt[30];
  int pes[30],peso[10];
  long soma;
  int i=0;
  soma=0;
  long multi = 100000;
  
  if (Serial.available()) {
    for(i=0;i<5;i++){
      Serial.readBytes(byt,30);     //lendo da balança
    }
  }

  for(i=0;i<30;i++)Serial.print(byt[i]);	
  
  Serial.println();
  
  for(i=5;i<11;i++){    
    Serial.print(byt[i]);
    
    soma += (byt[i]-48)* multi;
    
    multi/=10;    
  }
  
  Wire.beginTransmission(2);
    
  if(byt[13]-48==1){      
    Serial.print("Peso : ");
    Serial.println(soma +soma);
    Wire.write(byt); //enviando dados para o outro arduino
  }else{
    Serial.println("Peso instavel");    
  }  
  Wire.endTransmission();
  
  delay(33);
}

