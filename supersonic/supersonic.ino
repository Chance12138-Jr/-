const int TrigPin = 2; //发送超声波
const int EchoPin = 3; //接收超声波
float cm;
void setup()
{
Serial.begin(115200);
pinMode(TrigPin, OUTPUT);
pinMode(EchoPin, INPUT);
}
void loop()
{
// 产生一个10us的高电平脉冲去触发TrigPin
digitalWrite(TrigPin, LOW);
delayMicroseconds(2);
digitalWrite(TrigPin, HIGH);
delayMicroseconds(10);
digitalWrite(TrigPin, LOW);

// 检测脉冲宽度，并计算出距离
cm = pulseIn(EchoPin, HIGH) / 58.0;
//通过串口监视器输出
Serial.print ("Distance:");
Serial.println(cm);
delay(1000);
}
