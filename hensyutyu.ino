/*
   光電ロータリーエンコーダを動かしてみる！
*/
#include <FlexiTimer2.h> 
#include <math.h>
//volatile unsigned int temp, counter = 0;
volatile int temp, counter = 0;
double val = 0;

#include <avr/io.h>


void flash() { //割込み処理
 // double val = 0;
  static boolean output = HIGH;  // プログラム起動前に１回だけHIGH(1)で初期化される
  double Target=-0.1;
  double p=-3500, h=0, i=0;
  static double sum=0;
  
  val = (counter*0.0000612)/0.05;//0.1225
   

  counter = 0;

  h = (Target-val);
//  Serial.println (round(x*p+sum*i));
  sum += h*0.05;
 Motor_set(round(h*p+sum*i));
 //Motor_set(-100);
 // output = !output;              // 現在のoutput内容を反転(HIGH→LOW/LOW→HIGH)させoutputにセットする
}

void setup() {
  Serial.begin (9600);

  pinMode(2, INPUT_PULLUP);

  pinMode(3, INPUT_PULLUP);
  //interuptをセットアップする
  //
  FlexiTimer2::set(50,flash);     // 50ms毎にflash( )割込み関数を呼び出す様に設定
  FlexiTimer2::start();      //割込みスタート
  
  attachInterrupt(0, ai0, RISING);
  //CHANGEで立ち上がり立下り両方取れる可能性があったがダメだった
  //
  attachInterrupt(1, ai1, RISING);


  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  //TCCR1B = (TCCR1B & 0b11111000) | 0x02;
  //OCR1A = 99;
}

void Motor_set(float out){
  
    if(out>=0){
    if(out>255) out = 255;
     analogWrite(11,out);
     analogWrite(12,LOW);
  
  }
 
  if(out<=0){
    out = -1*out;
    if(out>255) out = 255;
   
    analogWrite(11,LOW);
    analogWrite(12,out);
  }


  
}


void loop() {
  

 Serial.println (val);



 //delay(10);
 
}





void ai0() {
  if (digitalRead(3) == LOW) {
    counter++;
  } else {
    counter--;
  }
}

void ai1() {
  if (digitalRead(2) == LOW) {
    counter--;
  } else {
    counter++;
  }
}
