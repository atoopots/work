// lab02拓展 SOS摩尔斯灯光 阻塞delay版本
const int ledPin = 2;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // S：3次短闪 亮200ms
  for(int i = 0; i < 3; i++){
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
    delay(200);
  }
  delay(500); // S与O间隔

  // O：3次长闪 亮600ms
  for(int i = 0; i < 3; i++){
    digitalWrite(ledPin, HIGH);
    delay(600);
    digitalWrite(ledPin, LOW);
    delay(200);
  }
  delay(500); // O与S间隔

  // S：3次短闪
  for(int i = 0; i < 3; i++){
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
    delay(200);
  }
  delay(2000); // 整套SOS结束长停顿
}