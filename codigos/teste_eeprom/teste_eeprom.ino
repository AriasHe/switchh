#include <EEPROM.h>   
int ligar = B0;
int rele_ligar = B0;
int dados = B1;
int desligar = B1;
int switchh, switch1=B000000,switch2=B000000;
int cmd,bobina;
int liga_antiga = 0;
int d_bobina_antiga_2,d_bobina_antiga_1,n_bobina_antiga_1,n_bobina_antiga_2;



void setup() {
   //primeira vez na utilização desse código descomentar essas linhas
   //EEPROM.write(0, 2);
   //EEPROM.write(1, 2);
   //EEPROM.write(2, 2);
   //EEPROM.write(3, 2);
  
 Serial.begin(9600);  
  DDRD = B11111100;
  DDRB = B111111; 
  DDRC = B111111;
  //switch1 = EEPROM.read(0);
  //switch2 = EEPROM.read(1);

}

void loop() {
  
  if (Serial.available() > 0) {

     cmd = Serial.read();
     switchh = cmd/10;
     bobina = cmd%10;
     aberto();
     delay(1000);
     desligar_bobina();
     delay(1000);
     aberto();
     delay(1000);
     escolher_bobina(bobina);
     ligar_bobina();
     delay(1000);
     aterrado();
     delay(1000);
    
    
   }

}

void escolher_bobina(int valor){
  
   switch (valor) {
   case 1:  
    dados = B111100;
    break;
   case 2:
    dados = B111001;
    break;
   case 3:
    dados = B110011;
    break;
   case 4:
    dados = B100111;
    break;
   case 5:
    dados = B001111;
    break;
   case 6:
    dados = B011110; 
  default:
    // Se nenhuma das condições for satisfeita
    break;
  }
  
}


void ligar_bobina(){
   if(bobina%2==0){
      PORTD = B10<<6;
     }else{
      PORTD = B01<<6;
     }
     
     delay(10);
     switchhh(dados);
 

}

void desligar_bobina(){
  
   if(switchh==1){
       if(EEPROM.read(1)%2==0){
        PORTD = B01<<6;
       }else{
       PORTD = B10<<6;
       } 
       PORTB =  EEPROM.read(0);
       PORTC = B111111;
    

       
     }else{
      if(EEPROM.read(3)%2==0){
      PORTD = B01<<6;
     }else{
      PORTD = B10<<6;
     } 
      PORTB = B111111;
      PORTC = EEPROM.read(2);
     }
     delay(10);
}



void switchhh(int valor){
  if(switchh==1){
       PORTB = valor;
       PORTC = B111111;
       d_bobina_antiga_1 = dados;
       n_bobina_antiga_1 = bobina;
       EEPROM.update(0, d_bobina_antiga_1);
       EEPROM.update(1, n_bobina_antiga_1);
       

     }else{
       PORTB = B111111;
       PORTC = valor;
       d_bobina_antiga_2 = dados;   
       n_bobina_antiga_2 = bobina;  
       EEPROM.update(2, d_bobina_antiga_2);
       EEPROM.update(3, n_bobina_antiga_2); 
     }
}

void aberto(){
  PORTC = B1111111;
  PORTB = B1111111;
  PORTD = B0000011;
}

void aterrado(){
  PORTD = B00<<6;
  delay(10);
  PORTC = B000000;
  PORTB = B000000;
  
} 
