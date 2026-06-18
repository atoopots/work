// lab02基础实验：1秒间隔LED闪烁 GPIO2
const int ledPin = 2; 

void setup() {
  // 初始化串口，波特率115200
  Serial.begin(115200);
  // 设置GPIO2为输出引脚，控制LED
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);  // 输出高电平，点亮LED
  Serial.println("LED ON");    // 串口打印状态
  delay(1000);                 // 阻塞延时1000ms=1秒

  digitalWrite(ledPin, LOW);   // 输出低电平，熄灭LED
  Serial.println("LED OFF");
  delay(1000);
}