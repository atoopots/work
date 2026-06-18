// ex03 ESP32 millis实现SOS灯光 无delay阻塞
// 规则：3短闪→3长闪→3短闪，整套结束停顿2000ms循环
const int ledPin = 2;
const unsigned long shortLight = 200;
const unsigned long longLight = 600;
const unsigned long gap = 200;
const unsigned long fullPause = 2000;

unsigned long prevTick = 0;
unsigned long lightStart = 0;
bool ledIsOn = false;
int runStage = 0;
int pulseCount = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  unsigned long now = millis();
  if(runStage == 99){
    digitalWrite(ledPin, LOW);
    if(now - prevTick >= fullPause){
      runStage = 0;
      pulseCount = 0;
      prevTick = now;
      Serial.println("新一轮SOS开始");
    }
    return;
  }
  if(!ledIsOn && now - prevTick >= gap){
    prevTick = now;
    if(pulseCount >= 3){
      pulseCount = 0;
      runStage++;
      if(runStage > 2){
        runStage = 99;
        return;
      }
    }else{
      pulseCount++;
      ledIsOn = true;
      lightStart = now;
      digitalWrite(ledPin, HIGH);
    }
  }
  unsigned long lightDuration = (runStage == 0 || runStage == 2) ? shortLight : longLight;
  if(ledIsOn && now - lightStart >= lightDuration){
    ledIsOn = false;
    digitalWrite(ledPin, LOW);
    prevTick = now;
  }
}