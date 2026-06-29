#define LED_A 2
#define LED_B 4

int val = 0;
int step = 2;

void setup() {
  pinMode(LED_A, OUTPUT);
  pinMode(LED_B, OUTPUT);
}

void loop() {
  analogWrite(LED_A, val);
  analogWrite(LED_B, 255 - val);
  val += step;
  if (val <= 0 || val >= 255)
    step = -step;
  delay(10);
}