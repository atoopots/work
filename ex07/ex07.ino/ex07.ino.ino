#include <WiFi.h>
#include <WebServer.h>

const char* ssid     = "esp32";
const char* password = "12345678";

WebServer server(80);
const int ledPin = 2;
int brightness = 0;

const char* htmlPage = R"HTML(
<!DOCTYPE html>
<html>
<body>
  <h2>LED无极调光</h2>
  <input type="range" min="0" max="255" id="slider" value="0">
  <p>当前亮度：<span id="val">0</span></p>

  <script>
    let slider = document.getElementById("slider");
    let showVal = document.getElementById("val");
    slider.oninput = function(){
      let num = this.value;
      showVal.innerText = num;
      fetch("/set?br="+num);
    }
  </script>
</body>
</html>
)HTML";

void handleRoot() {
  server.send(200, "text/html", htmlPage);
}

void handleSet() {
  if (server.hasArg("br")) {
    brightness = server.arg("br").toInt();
    analogWrite(ledPin, brightness);
  }
  server.send(200, "text/plain", "ok");
}

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println(WiFi.localIP());
  server.on("/", handleRoot);
  server.on("/set", handleSet);
  server.begin();
}

void loop() {
  server.handleClient();
}