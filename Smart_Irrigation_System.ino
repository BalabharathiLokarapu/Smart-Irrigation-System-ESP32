/*
  Smart Agriculture Monitoring and Irrigation System using ESP32

  Reconstructed from the source-code appendix of the academic project report.
  Project: Smart Agriculture Monitoring and Irrigation System using ESP32 and Blynk IoT

  Hardware used in the appendix:
  - ESP32
  - DHT11
  - Digital soil-moisture sensor
  - Relay module / water pump
  - 16x2 I2C LCD

  IMPORTANT:
  The report title mentions Blynk IoT, but the appendix code provided in the
  report implements an ESP32 SoftAP + WebServer interface rather than Blynk.
  This file follows the appendix implementation.

  The original report also contains a stray text line in the code:
      (adjust depending on your sensor)
  That text was removed because it is not valid C++ syntax.
*/

#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// DHT11 configuration
#define DHTPIN 14
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Sensor and relay pins from the report appendix
int soilSensor = 27;
int relay = 26;

// ESP32 creates its own Wi-Fi access point
const char* ssid = "agri-sys";
const char* password = "agri-sys";

WebServer server(80);

const char MAIN_page[] PROGMEM = R"=====(
<!doctype html>
<html>
<head>
<title>Smart Agriculture and Irrigation System</title>

<h2 style="text-align:center;">
SMART AGRI AND IRRIGATION SYSTEM OVER IoT PLATFORM
</h2>

<style>
#dataTable {
  font-family: Arial, sans-serif;
  border-collapse: collapse;
  width: 100%;
  text-align: center;
}

#dataTable td, #dataTable th {
  border: 1px solid #ddd;
  padding: 8px;
}

#dataTable tr:nth-child(even) {
  background-color: #f2f2f2;
}

#dataTable tr:hover {
  background-color: #ddd;
}

#dataTable th {
  padding: 12px;
  background-color: #4CAF50;
  color: white;
}

.center {
  text-align: center;
}

button {
  padding: 10px 20px;
  margin: 10px;
  font-size: 16px;
  background-color: #4CAF50;
  color: white;
  border: none;
  cursor: pointer;
}

button:hover {
  background-color: #45a049;
}
</style>
</head>

<body>

<h3 class="center">Control Irrigation Pump</h3>

<div class="center">
  <button onclick="controlPump('on')">Turn On Pump</button>
  <button onclick="controlPump('off')">Turn Off Pump</button>
</div>

<br><br>

<table id="dataTable" class="center">
  <tr>
    <th>Time</th>
    <th>Temperature</th>
    <th>Humidity</th>
    <th>Soil Moisture</th>
    <th>Relay</th>
  </tr>
</table>

<br>

<script>
setInterval(function() {
  getData();
}, 3000);

function getData() {
  var xhttp = new XMLHttpRequest();

  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      var response = JSON.parse(this.responseText);
      var date = new Date();

      var table = document.getElementById("dataTable");
      var row = table.insertRow(1);

      row.insertCell(0).innerHTML = date.toLocaleTimeString();
      row.insertCell(1).innerHTML = response.Temperature + " °C";
      row.insertCell(2).innerHTML = response.Humidity + " %";
      row.insertCell(3).innerHTML = response.Soil;
      row.insertCell(4).innerHTML = response.Relay;
    }
  };

  xhttp.open("GET", "readData", true);
  xhttp.send();
}

function controlPump(action) {
  var xhttp = new XMLHttpRequest();
  xhttp.open("GET", "controlPump?action=" + action, true);
  xhttp.send();
}
</script>

</body>
</html>
)=====";

// Display the web page
void handleRoot() {
  server.send(200, "text/html", MAIN_page);
}

// Read sensors and return JSON data
void readData() {
  // Read DHT11 sensor
  int temp = dht.readTemperature();
  int humidity = dht.readHumidity();

  // Read digital soil-moisture sensor
  int soilValue = digitalRead(soilSensor);

  // For the sensor used in the report:
  // HIGH = Dry, LOW = Wet
  String soilStatus = (soilValue == HIGH) ? "Dry" : "Wet";

  // Read current relay state
  // Relay is active LOW in the report:
  // LOW  = Pump ON
  // HIGH = Pump OFF
  String relayState = digitalRead(relay) ? "OFF" : "ON";

  // Prepare JSON response
  String json = "{\"Temperature\":\"" + String(temp) + "\",";
  json += "\"Humidity\":\"" + String(humidity) + "\",";
  json += "\"Soil\":\"" + soilStatus + "\",";
  json += "\"Relay\":\"" + relayState + "\"}";

  server.send(200, "application/json", json);

  // Display sensor data on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:" + String(temp));
  lcd.print(",H:" + String(humidity));

  lcd.setCursor(0, 1);
  lcd.print("S:" + soilStatus);

  delay(2000);
}

// Control pump from the web page
void controlPump() {
  String action = server.arg("action");

  if (action == "on") {
    // Active-LOW relay: LOW turns pump ON
    digitalWrite(relay, LOW);
  }
  else if (action == "off") {
    // Active-LOW relay: HIGH turns pump OFF
    digitalWrite(relay, HIGH);
  }

  server.send(200, "text/plain", "Pump control updated");
}

void setup() {
  Serial.begin(115200);

  pinMode(relay, OUTPUT);
  pinMode(soilSensor, INPUT);

  // Pump OFF at startup (active-LOW relay)
  digitalWrite(relay, HIGH);

  dht.begin();

  // Initialize LCD
  lcd.init();
  lcd.backlight();

  // Welcome message
  lcd.setCursor(0, 0);
  lcd.print(" WELCOME TO THE");
  lcd.setCursor(0, 1);
  lcd.print(" PROJECT ");
  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SMART FARMING");
  lcd.setCursor(0, 1);
  lcd.print(" USING IOT ");
  delay(2000);

  // Display AP credentials
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SSID:");
  lcd.setCursor(0, 1);
  lcd.print(ssid);
  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PSWD:");
  lcd.setCursor(0, 1);
  lcd.print(password);
  delay(2000);

  lcd.clear();

  // Create ESP32 Wi-Fi Access Point
  WiFi.softAP(ssid, password);

  Serial.print("ESP32 Access Point IP: ");
  Serial.println(WiFi.softAPIP());

  // Register web-server routes
  server.on("/", handleRoot);
  server.on("/readData", readData);
  server.on("/controlPump", controlPump);

  server.begin();

  lcd.print("HTTP Server Ready");
  delay(1000);
  lcd.clear();
}

void loop() {
  server.handleClient();
}
