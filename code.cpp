#define BLYNK_TEMPLATE_ID "TMPL2HZHup8Ct"
#define BLYNK_TEMPLATE_NAME "mq2mq5"
#define BLYNK_AUTH_TOKEN "s9nXas8eZEUfaglgRAW9lHZ0b6iDSmc0"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h> // For ESP32

// WiFi credentials
char ssid[] = "Galaxy F22D60D";
char pass[] = "11211121";

// === Pin definitions ===
#define BUZZER_PIN 14
#define MQ5_PIN    36
#define MQ2_PIN    34
#define LED_PIN    23

void setup() {
  Serial.begin(9600);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(MQ5_PIN, INPUT);
  pinMode(MQ2_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  // Connect to WiFi and Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run(); // Required for Blynk

  // Read gas sensor values
  int mq5value = analogRead(MQ5_PIN);
  int mq2value = analogRead(MQ2_PIN);

  // Display raw values
  Serial.print("mq5value: ");
  Serial.println(mq5value);
  Serial.print("mq2value: ");
  Serial.println(mq2value);

  // Convert ADC values to percentages
  int percentage5 = map(mq5value, 0, 4095, 0, 100);
  int percentage2 = map(mq2value, 0, 4095, 0, 100);

  // Display percentages
  Serial.print("MQ-5 : ");
  Serial.print(percentage5);
  Serial.println("%");
  Serial.print("MQ-2 : ");
  Serial.print(percentage2);
  Serial.println("%");

  // Send to Blynk
  Blynk.virtualWrite(V36, percentage5); // MQ-5
  Blynk.virtualWrite(V34, percentage2); // MQ-2

  // Trigger buzzer and LED if threshold exceeded
  if (percentage5 > 40 || percentage2 > 40) {
    tone(BUZZER_PIN, 2000); // Buzzer ON
    digitalWrite(LED_PIN, HIGH); // LED ON
  } else {
    noTone(BUZZER_PIN); // Buzzer OFF
    digitalWrite(LED_PIN, LOW); // LED OFF
  }

  delay(2000); // Wait 2 seconds
}
