#include <WiFi.h>
#include <WebServer.h>

const char* ssid     = "esp32";
const char* password = "12345678";

WebServer server(80);
const int adcPin = 36;  // 代替A0

const char* htmlPage = R"HTML(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<style>
body{text-align:center;margin-top:140px;}
#num{font-size:90px;color:red;}
</style>
</head>
<body>
  <h2>实时传感器仪表盘</h2>
  <div id="num">0</div>
  <script>
    function getData(){
      fetch("/data")
      .then(res=>res.text())
      .then(v=>document.getElementById("num").innerText=v)
    }
    setInterval(getData, 120);
  </script>
</body>
</html>
)HTML";

void handleRoot() {
  server.send(200, "text/html", htmlPage);
}

void handleData() {
  int val = analogRead(adcPin);
  server.send(200, "text/plain", String(val));
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(400);
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/data", handleData);
  server.begin();
}

void loop() {
  server.handleClient();
}