/*
USB Pinout (Left to Right, USB symbol up)
4: GND
3: Clk
2: Data
1: Vcc
*/

#include "PS2Mouse.h"

PS2Mouse mouse(6,5);

int pos = 0;

void avviaMotore(int pV, int pG){
  digitalWrite(pV,HIGH);
  digitalWrite(pG,LOW);
}
void arrestaMotore(int pV, int pG){
  digitalWrite(pV,LOW);
  digitalWrite(pG,LOW);
}

void setup(){
  Serial.begin(9600);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(16,OUTPUT);
  while(!Serial);
  Serial.print("Setup...");

  mouse.begin();
  Serial.println("complete!");
}

void curvadx(){
  uint8_t stat;
  int x,y;
  mouse.getPosition(stat,x,y);
  pos = 0;
  while(pos < 150){
    uint8_t stat;
    int x,y;
    mouse.getPosition(stat,x,y);
    Serial.print("\tx=");
    Serial.print(x, DEC);
    Serial.print("\ty=");
    Serial.println(y, DEC);
    avviaMotore(9,8);
    avviaMotore(10,16);
    pos += abs(y);
  }
  arrestaMotore(9,8);
  arrestaMotore(10,16);

}
void dritto(int dist){
  //avvi il primo motore
  //avvi il secondo motore
  //vai dritto finché non sei arrivato
  //spegni i motori
  pos = 0;
  while(pos < dist){
    uint8_t stat;
    int x,y;
    mouse.getPosition(stat,x,y);
    Serial.print("\tx=");
    Serial.print(x, DEC);
    Serial.print("\ty=");
    Serial.println(y, DEC);
    avviaMotore(8,9);
    avviaMotore(10,16);
    pos += abs(y);
  }
  arrestaMotore(8,9);
  arrestaMotore(10,16);

}

void quadrato(int lato){
  dritto(lato);
  delay(1000);
  curvadx();
  delay(1000);
  dritto(lato);
  delay(1000);
  curvadx();
  delay(1000);
  dritto(lato);
  delay(1000);
  curvadx();
  delay(1000);
  dritto(lato);
  delay(1000);
  curvadx();
  delay(1000);
}


void loop(){
  uint8_t stat;
  int x,y;
  mouse.getPosition(stat,x,y);

 
  Serial.print(stat, DEC);
  Serial.print("\tx=");
  Serial.print(x, DEC);
  Serial.print("\ty=");
  Serial.println(y, DEC);
  
  quadrato(500);
  delay(10000);
}

