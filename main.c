#include <Arduino.h>
// hall sensor receive 8
// motor INA-9;    INB-10;
#define HALL_SENSOR 8
#define MOTOR_A 10
#define MOTOR_B 9
// #define WAITTING 800000

struct vars{
  long long waitting = 800000;
  long long counter = 0;
  // long long *pc;
};
vars ww;

bool ok = false;


void setup(){
  pinMode(HALL_SENSOR, INPUT_PULLUP);
  pinMode(MOTOR_A, OUTPUT);
  pinMode(MOTOR_B, OUTPUT);
  digitalWrite(MOTOR_A, LOW);
  digitalWrite(MOTOR_B, LOW);
  // ww.pc = &ww.counter;
}

void loop() {
  // 满足?条件使得 OK = true, 不满足?条件时 OK是否等于false,还是应该保持不变？
  // 如果霍尔返回值连续 waitting 次都是HIGH,则ok=true
  if(digitalRead(HALL_SENSOR) == HIGH) {
    // 棋子不在位
    ww.counter++;
    // *ww.pc++;
    if(ww.counter >= ww.waitting){
      ok = true;
      ww.counter = ww.waitting;
    }
  }else{
    // 棋子在位
    ok = false;
    ww.counter = 0;
  }

  if(ok){
    // 连续500次霍尔离开
    // if(digitalRead(HALL_SENSOR) == HIGH)
    // start motor
    digitalWrite(MOTOR_B, HIGH);
    _delay_us(9);
    digitalWrite(MOTOR_B, LOW);
    _delay_us(1);
  }else{
    // stop motor
    digitalWrite(MOTOR_B, LOW);
  }
}
