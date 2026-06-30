#define TOUCH_PIN T0
#define LED_PIN 2

bool ledState = false;
int lastTouchVal = 0;
const int touchThreshold = 35;
unsigned long debounceTime = 0;
const unsigned long debounceDelay = 50;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  int touchVal = touchRead(TOUCH_PIN);
  unsigned long now = millis();

  if (touchVal < touchThreshold && lastTouchVal >= touchThreshold && now - debounceTime > debounceDelay)
  {
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
    debounceTime = now;
  }

  lastTouchVal = touchVal;
}