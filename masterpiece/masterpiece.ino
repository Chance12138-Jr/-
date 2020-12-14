#include <ESP8266.h>


#if defined (__AVR_ATmega168__) || defined (__AVR_ATmega328__) || defined (__AVR_ATmega328P__)
#include <SoftwareSerial.h>
SoftwareSerial mySerial1(2,3); /* RX:D2, TX:D3 */
int state; 
#define EspSerial mySerial1
#define UARTSPEED  9600
#endif


#define SSID        F("*********")//WiFi热点名称
#define PASSWORD    F("*********")//热点密码
#define HOST_NAME   F("api.heclouds.com")
#define HOST_PORT   (80)//端口
#define DEVICEID    "****************" //OneNet上的设备ID
String apiKey = "**************************";
String jsonToSend;
String postString;
String P;

char shijian1[23] = {'0'}, shijian2[23] = {'0'};


//电机反转
 
void clockwise(int num)       //正向旋转
{
  for (int count = 0; count < num; count++)
  {
    for (int i = 2; i < 6; i++)
    {
      digitalWrite(i, HIGH);
      delay(2);
      digitalWrite(i, LOW);
    }
  }
}

void anticlockwise(int num)   //反向旋转
{
  for (int count = 0; count < num; count++)
  {
    for (int i = 5; i > 1; i--)
    {
      digitalWrite(i, HIGH);
      delay(2);
      digitalWrite(i, LOW);
    }
  }
}

void A() 
{
  for (int i = 1; i < 6; i++) {
    pinMode(i, OUTPUT);
  }
  clockwise(256);
  delay(6);
 }

void B() 
{
  for (int i = 2; i < 6; i++) {
    pinMode(i, OUTPUT);
  }
  anticlockwise(256);
  delay(6);
  }




static const byte  GETDATA[]  PROGMEM = {
  "GET https://api.heclouds.com/devices/**********/datapoints?datastream_id=abc HTTP/1.1\r\nHost:api.heclouds.com\r\napi-key:*******************\r\nConnection: close\r\n\r\n"
};//数字的地方改成设备id   api的地方换成自己的api

ESP8266 wifi(&EspSerial);

#define servoPin  8

void setup(void)

{
   
    Serial.begin(115200);
    
  
    int state; 


  while (!Serial); // wait for Leonardo enumeration, others continue immediately//WiFi连接部分,勿动
  
  Serial.print(F("setup begin\r\n"));
  delay(100);




  WifiInit(EspSerial, UARTSPEED);

  Serial.print(F("FW Version:"));
  Serial.println(wifi.getVersion().c_str());

  if (wifi.setOprToStationSoftAP()) {
    Serial.print(F("to station + softap ok\r\n"));
  } else {
    Serial.print(F("to station + softap err\r\n"));
  }

  if (wifi.joinAP(SSID, PASSWORD)) {
    Serial.print(F("Join AP success\r\n"));

    Serial.print(F("IP:"));
    Serial.println( wifi.getLocalIP().c_str());
  } else {
    Serial.print(F("Join AP failure\r\n"));
  }

  if (wifi.disableMUX()) {
    Serial.print(F("single ok\r\n"));
  } else {
    Serial.print(F("single err\r\n"));
  }

  Serial.print(F("setup end\r\n"));
}




void loop(void)

{
  //从onenet读取服务器数值
  if (wifi.createTCP(HOST_NAME, HOST_PORT)) {
    Serial.print(F("create tcp ok\r\n"));
  } else {
    Serial.print(F("create tcp err\r\n"));
  }



  wifi.sendFromFlash(GETDATA, sizeof(GETDATA)); //从Flash读取发送内容，节约内存


  char a = '0';

  
  uint8_t buffer[512] = {0};
  uint32_t len = wifi.recv(buffer, sizeof(buffer), 20000);
  if (len > 0) {
    Serial.print(F("Received:["));
    for (uint32_t i = 0; i < len; i++) {
      Serial.print((char)buffer[i]);
    }
    Serial.print(F("]\r\n"));

    for (uint32_t i = 0; i < len - 12; i++) {
      if ((char)buffer[i] == 'v' && (char)buffer[i + 1] == 'a' && (char)buffer[i + 2] == 'l' && (char)buffer[i + 3] == 'u' && (char)buffer[i + 4] == 'e')
      {

        a= buffer[i + 8];
      }
    }
  }

  
  if(a=='1')
   {
    A();
   }
 else if(a=='2')
   {
    B();
   }
}
