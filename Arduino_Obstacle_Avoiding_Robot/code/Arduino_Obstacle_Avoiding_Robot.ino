//超音波センサー
const int trig = 12;
const int echo = 11;

//Motor 1
//スピードを変える線
const int enA = 9;
const int leftForward = 2;
const int leftBackward = 3;

//Motor 2
//スピードを変える線
const int enB = 8;
const int rightForward = 4;
const int rightBackward = 5;

//超音波を受け取るまでの時間と物までの距離
int duration = 0;
int distance = 0;

void setup() 
{
  pinMode(trig , OUTPUT);
  pinMode(echo , INPUT);
//上で追加したスピードを変える線の種類は？
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  
  pinMode(leftForward , OUTPUT);
  pinMode(leftBackward , OUTPUT);
  pinMode(rightForward , OUTPUT);
  pinMode(rightBackward , OUTPUT);

  //さいしょにモーターが動かないように
  digitalWrite(leftForward, LOW);
  digitalWrite(leftBackward, LOW);
  digitalWrite(rightForward, LOW);
  digitalWrite(rightBackward, LOW);

  Serial.begin(9600);

}

void loop()
{
  digitalWrite(trig , HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig , LOW);


  duration = pulseIn(echo , HIGH);
  distance = (duration/2) / 28.5 ;
  Serial.println(distance);

  
  if ( distance < 20 )
  {
    //スピードを下げて
    // Decelerate from maximum speed to zero　　スピード　を　255 から　0 に　すこしずつ　へらす
    for (int i = 255;i>=0;--i) {
      analogWrite(enA, i);
      analogWrite(enB, i);
      delay(20);
    }
    
    //右に曲がる
    left_right(HIGH,LOW,5000);
    
  }
  else
  {
    //スピードを上げて
    for (int i = 0;i<256;i++) {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
    }

    //前に進む
    front_back(HIGH,LOW,5000);
    
  }
 
}
//前後に進める関数
void front_back(int a1, int a2, int d){
  digitalWrite(leftForward , a1);
  digitalWrite(leftBackward , a2);
  
  digitalWrite(rightForward , a2);
  digitalWrite(rightBackward , a1);
  delay(d);
}

//左右に曲がる関数
void left_right(int b1, int b2, int d){
  digitalWrite(leftForward , b1);
  digitalWrite(leftBackward ,b2);
  digitalWrite(rightForward ,b1);
  digitalWrite(rightBackward,b2);
  delay(d);
}
