#include <ESP8266WiFi.h> // ESP 8266 와이파이 라이브러리
#include <ArduinoJson.h>

String cpy= "";
int Relaypin = D0;
int count =0;
//MAC주소
uint8_t MAC_array[6];
char MAC_char[18];
//수분 센서의 핀번호를 설정한다.
int Sensor_pin = A0;    // 토양수분센서 핀을 A1으로 설정

char ssid[] = "bssm_guest";
char pass[] = "bssm_guest";
int status = WL_IDLE_STATUS;
int compare = -1;

WiFiClient client;
String line;

void from(String p, int start, char f) {
  cpy = "";
  for(int i=start; p[i]!=f; i++) {
    cpy += p[i];
  }
  return ;
}

void str(String p, String check, int s, char f) {
  int u, i, cnt=0;
  for(u=0; check[u]!='\0'; u++) ;
  int index = 0;
  for(i=0; p[i]!='\0'; i++) {
    if(p[i] == check[index]) {
      index++;
    } else if(index != u){
      index=0;
    }
    if(index == u) {
      from(p, i+s, f);
      return ;
    }
  }
}

void setup() {
  Serial.begin(115200);
  //MAC주소
  WiFi.macAddress(MAC_array);
  for (int i = 0; i < sizeof(MAC_array); ++i) {
    sprintf(MAC_char, "%s%02x:", MAC_char, MAC_array[i]);
  }
  delay(1000);
  Serial.println(analogRead(Sensor_pin));    // 센서값을 시리얼모니터로 전송
  WiFi.begin("bssm_guest", "bssm_guest"); // 공유기 이름과 비밀번호

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) // 와이파이 접속하는 동안 "." 출력
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP()); // 접속된 와이파이 주소 출력
  pinMode(Relaypin, OUTPUT);        // 릴레이를 출력으로 설정
}


void loop() {
  String li = "";
  int nsoil = analogRead(Sensor_pin);
  int value =  map(nsoil, 170, 1023, 100, 0); // 센서 값을 %로 변경
  String jsondata = ""; //문자열 형태로 전송하기위해 문자열을 선언한다
  Serial.println(compare);
  
  if (compare>value)    // 
  {
    while(value<=compare) {
      digitalWrite(Relaypin, HIGH);    // 1채널 릴레이 ON
      nsoil = analogRead(Sensor_pin);
      value =  map(nsoil, 170, 1023, 100, 0);
      Serial.println("물주는중");
    }
    digitalWrite(Relaypin, LOW);
  }
  else                               // 스위치를 누르지 않으면
  {
    digitalWrite(Relaypin, LOW);     // 1채널 릴레이 OFF
  }

  StaticJsonBuffer<200> jsonBuffer; //JSON변환에 필요한 StaticJsonBuffer을 선언정하고 용량을 설정한다.
  JsonObject& root = jsonBuffer.createObject(); //JsonObject를 선언하여 JSON형식을 만들어 낼 수 있언는 객체를 선언
  String ppl = "ppl";
  root["macadress"] = MAC_char;
  root["huminity"] = value; //[]표기법으로 Key값을 설정하고, 이꼴 이후에 값을 지정한다

  root.printTo(jsondata); //JSON으로 포멧된 데이터를 String변수로~

  Serial.println(jsondata); //jsondata를 String으로 출력


  int re = client.connect("211.216.92.115", 5000);
  if (re) {
    client.println("POST /GB/machineValue HTTP/1.1");
    client.println("Host: 211.216.92.115:5000");
    client.println("Cache-Control: no-cache");
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.println(jsondata.length());
    client.println();
    client.println(jsondata);
    li = client.readString();
   Serial.println(li);
  str(li, "isadded", 3, ',');
  str(li, "plant", 3, '}');
  str(cpy, "humid", 3, ',');
  Serial.println(cpy);
  compare = cpy.toInt();
  count = 0;
  }
  delay(10000);
}