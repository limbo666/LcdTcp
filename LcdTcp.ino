/*
 * LcdTcp.ino - Version 1.0 Stable
 * Supports multi-size LCDs and Hardware I/O
 */

#include "LcdTcp.h"

// --- PIN DEFINITIONS ---
// Buttons connect Pin to GND
#define PIN_BTN_1   D5  // GPIO 14
#define PIN_BTN_2   D6  // GPIO 12
#define PIN_BTN_3   D7  // GPIO 13
#define PIN_BTN_4   D3  // GPIO 0 (Warning: Do NOT hold at boot!)

// Outputs
#define PIN_OUT_GPO D0  // GPIO 16 (Digital On/Off)
#define PIN_OUT_FAN D8  // GPIO 15 (PWM Speed Control)

void setup()
{
  Serial.begin(230400);

  // --- I/O SETUP ---
  pinMode(PIN_BTN_1, INPUT_PULLUP);
  pinMode(PIN_BTN_2, INPUT_PULLUP);
  pinMode(PIN_BTN_3, INPUT_PULLUP);
  pinMode(PIN_BTN_4, INPUT_PULLUP);
  
  pinMode(PIN_OUT_GPO, OUTPUT);
  pinMode(PIN_OUT_FAN, OUTPUT);
  
  // Ensure outputs start in OFF state
  digitalWrite(PIN_OUT_GPO, LOW);
  analogWrite(PIN_OUT_FAN, 0);   

  // Initialize LCD based on size defined in I2C_LCD_ADDR_CFG.h
  LcdInit();
  
  // Connect to WiFi and show status on LCD
  WifiConnectionInit();

  // Setup mDNS for easy discovery
  if (!MDNS.begin("WIFI_LCD_STA"))
  {
    Serial.println("Error setting up MDNS responder!");
  }
  Serial.println("mDNS responder started");
  MDNS.addService("lcd", "tcp", 2400);
  
  // Start the TCP Server on port 2400
  TcpServerInit();
}

// Helper to read buttons with debounce and edge detection
void CheckButtons() {
  static unsigned long lastDebounceTime = 0;
  static int lastBtnState[4] = {HIGH, HIGH, HIGH, HIGH}; // HIGH = Released
  
  // Map our pins to arrays for iteration
  int btnPins[4] = {PIN_BTN_1, PIN_BTN_2, PIN_BTN_3, PIN_BTN_4};
  char btnChars[4] = {'1', '2', '3', '4'}; // Characters sent to LCD Smartie

  // Scan buttons every 50ms (Non-blocking)
  if (millis() - lastDebounceTime > 50) {
    lastDebounceTime = millis();
    
    for(int i = 0; i < 4; i++) {
      int reading = digitalRead(btnPins[i]);
      
      // If state changed from HIGH (Released) to LOW (Pressed)
      if (lastBtnState[i] == HIGH && reading == LOW) {
        BroadcastKeyToHost(btnChars[i]); // Notify the DLL/PC
      }
      lastBtnState[i] = reading;
    }
  }
}

void loop()
{
  TcpServerProc(); // Handle incoming network data
  CheckButtons();  // Handle physical button inputs
}