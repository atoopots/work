#define TOUCH_PIN T0
#define LED_PIN 2

int gear = 1;
int brightness = 0;
int fadeStep = 1;

int lastTouchVal = 0;
const int touchThreshold = 35;
unsigned long debounceTime = 0;
const unsigned long debounceDelay = 50;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  int touchVal = touchRead(TOUCH_PIN);
  unsigned long now = millis();
  if (touchVal < touchThreshold && lastTouchVal >= touchThreshold && now - debounceTime > debounceDelay)
  {
    gear++;
    if(gear > 3) gear = 1;
    debounceTime = now;
  }
  lastTouchVal = touchVal;

  switch(gear){
    case 1: fadeStep = 1; break;
    case 2: fadeStep = 3; break;
    case 3: fadeStep = 6; break;
  }

  analogWrite(LED_PIN, brightness);
  brightness += fadeStep;
  if (brightness <= 0 || brightness >= 255) {
    fadeStep = -fadeStep;
  }
  delay(10);
}