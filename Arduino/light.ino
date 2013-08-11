//номер порта = номер адреса + 2, т.к. 0 и 1 порт 
//использовать для вывода нельзя
//
//1000 ячейка для включения/отключения автоматического включения 
//света


#include <EEPROM.h>

int light_val;

void setup(){
  EEPROM.write(1000,1);
  pinMode(2, OUTPUT);    //table
  pinMode(3, OUTPUT);    //lamp 1
  pinMode(4, OUTPUT);    //lamp 3
  Serial.begin(9600);
}
void loop(){
  memory_read();
  
  data_read();
  
  illuminate();
}


void data_read(){
  if (Serial.available() > 0) {
    EEPROM.write(1000,0);
    int message = Serial.parseInt();
    int address = message/10;
    int val = message-address*10;
    Serial.println(address);
    Serial.println(val);
    Serial.println("-----------");
    memory_write(address,val);
  }
}


int illuminate(){
  light_val=analogRead(0);
  Serial.println(light_val);
  if(light_val>270){            //выключение света утром
    if(EEPROM.read(1000)==2){
      EEPROM.write(1000,1);
    }
  }
  if(light_val<240){
    if(EEPROM.read(1000)==1){
      memory_write(111,1);
    }
    EEPROM.write(1000,2);
  }
  else{
    if(EEPROM.read(1000)==1){
      memory_write(111,0);
    }
  }
}



void memory_write(int address, int val){
  if(address==111){    //all on/off
    EEPROM.write(0,val);
    EEPROM.write(1,val);
    EEPROM.write(2,val);
  }
  else if(address==11){      //lamps on/off
    EEPROM.write(1,val);
    EEPROM.write(2,val);
  }
  else{
    EEPROM.write(address, val);
  }
}

void memory_read(){
  for(int adr=0; adr<3; adr++){
    if(EEPROM.read(adr)==1){
      digitalWrite(adr+2,HIGH);    //см. шапку программы
    } 
    else{
      digitalWrite(adr+2,LOW);
    }
  }
}


