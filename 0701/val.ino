/*
   光電ロータリーエンコーダを動かしてみる！
*/
#include <FlexiTimer2.h> 
int temp, counter = 0;
float val = 0;


void flash() { //割込み処理
  static boolean output = HIGH;  // プログラム起動前に１回だけHIGH(1)で初期化される
   val = (counter*0.1225)/50;
    Serial.println (counter);
  counter = 0;
  output = !output;              // 現在のoutput内容を反転(HIGH→LOW/LOW→HIGH)させoutputにセットする
}

void setup() {
  Serial.begin (9600);

  pinMode(2, INPUT_PULLUP);

  pinMode(3, INPUT_PULLUP);
  //interuptをセットアップする
  //
  FlexiTimer2::set(50,1.0/1000,flash);     // 50ms毎にflash( )割込み関数を呼び出す様に設定
  FlexiTimer2::start();      //割込みスタート
  
  attachInterrupt(0, ai0, RISING);

  //
  attachInterrupt(1, ai1, RISING);
}


void loop() {
  
  // カウンターの値を出力する
//  if ( counter != temp ) {
//    Serial.println (counter);
//    temp = counter;
//  }
  Serial.println (counter);
  delay(100);
 
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
