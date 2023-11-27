#define BLYNK_TEMPLATE_ID "TMPL3Zo-zbqTU"
#define BLYNK_TEMPLATE_NAME "SMART IRRIGATION"
#define BLYNK_AUTH_TOKEN "LKkdweIPdsWzDK2g00ZDmUlY9W60yGKt"
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "AndroidAPFE2C";
char pass[] = "12345678";

// Pin connected to the solenoid control relay
const int solenoidPin = 5;

// DHT sensor
#define DHTPIN 13          // DHT11 data pin is connected to GPIO 2
#define DHTTYPE DHT11     // DHT11 sensor type
DHT dht(DHTPIN, DHTTYPE);

BLYNK_WRITE(V1) {
  int pinValue = param.asInt();
  // Control solenoid based on button state
  digitalWrite(solenoidPin, pinValue);
}

void setup() {
  Serial.begin(9600);
  delay(1000);
  pinMode(solenoidPin, OUTPUT);

  // Attempt to connect to WiFi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Not connected");
  }

  Serial.println("Connected");

  // Initialize Blynk
  Blynk.begin(auth, ssid, pass);

  // Initialize the DHT sensor
  dht.begin();
}

void loop() {
  Blynk.run();

  // Read and display temperature and humidity
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  
  int soilMoisture = analogRead(A0);

  // Send sensor readings to Blynk
  Blynk.virtualWrite(V2, temperature);
  Blynk.virtualWrite(V3, humidity);
  Blynk.virtualWrite(V4, soilMoisture);

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C\t");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Soil Moisture: ");
  Serial.println(soilMoisture);

  delay(1000); 
}