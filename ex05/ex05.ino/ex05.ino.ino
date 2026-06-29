#define TOUCH_PIN T0
#define LED_PIN 2

int gear = 1;
int brightness = 0;
int fadeStep = 1;

int lastTouchVal = 40;
const int touchThreshold = 40;
unsigned long debounceTime = 0;
const unsigned long debounceDelay = 80;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // 触摸检测放在最前面，优先执行
  int touchVal = touchRead(TOUCH_PIN);
  unsigned long now = millis();

  // 严格上升沿：之前没触摸，现在触摸
  if ((touchVal < touchThreshold) && (lastTouchVal >= touchThreshold))
  {
    if (now - debounceTime > debounceDelay)
    {
      gear = gear + 1;
      if (gear > 3)
      {
        gear = 1;
      }
      debounceTime = now;
    }
  }
  lastTouchVal = touchVal;

  // 档位对应速度
  if (gear == 1)
  {
    fadeStep = 1;
  }
  else if (gear == 2)
  {
    fadeStep = 4;
  }
  else if (gear == 3)
  {
    fadeStep = 8;
  }

  // 呼吸灯逻辑
  analogWrite(LED_PIN, brightness);
  brightness = brightness + fadeStep;

  if (brightness >= 255 || brightness <= 0)
  {
    fadeStep = -fadeStep;
  }

  // 缩短延时，避免卡死触摸检测
  delay(5);
}