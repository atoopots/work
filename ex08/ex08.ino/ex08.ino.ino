#include <WiFi.h>
#include <WebServer.h>

const char* ssid     = "esp32";
const char* password = "12345678";

WebServer server(80);
const int touchPin = T0;
const int ledPin = 2;

bool isArm = false;
bool isAlarmLock = false;

const char* htmlPage = R"HTML(
<!DOCTYPE html>
<html>
<body style="text-align:center;margin-top:100px;">
  <h2>安防报警主机</h2>
  <br>
  <button style="font-size:22px;padding:10px 30px;margin:10px;" onclick="fetch('/arm')">布防 Arm</button>
  <br>
  <button style="font-size:22px;padding:10px 30px;margin:10px;" onclick="fetch('/disarm')">撤防 Disarm</button>
</body>
</html>
)HTML";

void handleRoot() {
  server.send(200, "text/html", htmlPage);
}

void handleArm() {
  isArm = true;
  isAlarmLock = false;
  digitalWrite(ledPin, LOW);
  server.send(200, "text/plain", "已布防");
}

void handleDisarm() {
  isArm = false;
  isAlarmLock = false;
  digitalWrite(ledPin, LOW);
  server.send(200, "text/plain", "已撤防");
}

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(115200);

  Serial.println("正在连接热点...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n联网成功");
  Serial.print("IP：");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/arm", handleArm);
  server.on("/disarm", handleDisarm);
  server.begin();
}

void loop() {
  server.handleClient();

  if(isArm && !isAlarmLock){
    int touchVal = touchRead(touchPin);
    if(touchVal < 35){
      isAlarmLock = true;
    }
  }

  if(isAlarmLock){
    digitalWrite(ledPin, HIGH);
    delay(70);
    digitalWrite(ledPin, LOW);
    delay(70);
  }
}