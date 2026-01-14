#include <ETH.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include "keymap.h"

// --- Configuration ---

// EOS Console IP Address (CHANGE THIS TO YOUR CONSOLE'S IP)
IPAddress outIp(10, 101, 1, 1);
const unsigned int outPort = 8000; // EOS listens on 8000
const unsigned int localPort = 8001; // We listen on 8001 (optional)

// Matrix Dimensions
const int ROWS = 8;
const int COLS = 16;

// I2C Pins for Olimex ESP32-POE
#define I2C_SDA 13
#define I2C_SCL 16

// MCP23017 Instances
Adafruit_MCP23017 mcpCols; // Address 0x20 (Inputs)
Adafruit_MCP23017 mcpRows; // Address 0x21 (Outputs)

// State Tracking
bool keyState[ROWS][COLS]; // Current state (true = pressed)
bool lastKeyState[ROWS][COLS]; // Previous state for edge detection

WiFiUDP Udp;
bool ethConnected = false;

// --- Ethernet Event Handler ---
void WiFiEvent(WiFiEvent_t event) {
  switch (event) {
    case ARDUINO_EVENT_ETH_START:
      Serial.println("ETH Started");
      // The ETH hostname can be set here
      ETH.setHostname("esp32-eos-wing");
      break;
    case ARDUINO_EVENT_ETH_CONNECTED:
      Serial.println("ETH Connected");
      break;
    case ARDUINO_EVENT_ETH_GOT_IP:
      Serial.print("ETH MAC: ");
      Serial.print(ETH.macAddress());
      Serial.print(", IPv4: ");
      Serial.println(ETH.localIP());
      ethConnected = true;
      break;
    case ARDUINO_EVENT_ETH_DISCONNECTED:
      Serial.println("ETH Disconnected");
      ethConnected = false;
      break;
    case ARDUINO_EVENT_ETH_STOP:
      Serial.println("ETH Stopped");
      ethConnected = false;
      break;
    default:
      break;
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting EOS OSC Wing...");

  // Initialize I2C
  Wire.begin(I2C_SDA, I2C_SCL);

  // Initialize MCP23017 chips
  Serial.println("Initializing MCP23017s...");

  // Chip 1: Columns (Inputs with Pullups) - Address 0 (0x20)
  mcpCols.begin(0);
  for (int i = 0; i < 16; i++) {
    mcpCols.pinMode(i, INPUT);
    mcpCols.pullUp(i, HIGH); // Enable internal pull-up
  }

  // Chip 2: Rows (Outputs) - Address 1 (0x21)
  // We only use Port A (GPA0-7) for 8 rows.
  mcpRows.begin(1);
  for (int i = 0; i < 8; i++) {
    mcpRows.pinMode(i, OUTPUT);
    mcpRows.digitalWrite(i, HIGH); // Default HIGH (Inactive)
  }

  // Initialize Key State
  for (int r = 0; r < ROWS; r++) {
    for (int c = 0; c < COLS; c++) {
      keyState[r][c] = false;
      lastKeyState[r][c] = false;
    }
  }

  // Initialize Ethernet
  // Olimex ESP32-POE uses LAN8710 (use LAN8720 driver), Addr 0, Power Pin 12, MDC 23, MDIO 18, Clock Mode GPIO17_OUT
  WiFi.onEvent(WiFiEvent);
  ETH.begin(0, 12, 23, 18, ETH_PHY_LAN8720, ETH_CLOCK_GPIO17_OUT);

  Serial.println("Setup Complete.");
}

void sendOSC(const char* address, float value) {
  if (!ethConnected) return;

  OSCMessage msg(address);
  // Add arguments if needed. For keys, existing code sent analog value or just the path.
  // Standard EOS: Path with argument 1.0 (Down) or 0.0 (Up).
  // If argument is omitted, EOS simulates a full press-release cycle.
  // Since we detect edges, we should send 1.0 on Press, 0.0 on Release.

  if (value > 0.5) {
      msg.add(1.0f); // Press
  } else {
      msg.add(0.0f); // Release
  }

  Udp.beginPacket(outIp, outPort);
  msg.send(Udp);
  Udp.endPacket();
  msg.empty();

  Serial.print("Sent OSC: ");
  Serial.print(address);
  Serial.print(" ");
  Serial.println(value);
}

void loop() {
  // Matrix Scanning
  for (int r = 0; r < ROWS; r++) {
    // 1. Activate Row (Drive LOW)
    // We use Chip 2, Port A (Pins 0-7)
    mcpRows.digitalWrite(r, LOW);

    // Short delay for signal to settle?
    // I2C is slow enough (approx 100-400kHz), so physical electrical settling is likely instant relative to I2C transactions.
    // But good practice to not read immediately if possible, though strict I2C protocol inserts delay.

    // 2. Read Columns (Inputs)
    // We read all 16 pins from Chip 1.
    // readGPIOAB() reads 16 bits.
    uint16_t cols = mcpCols.readGPIOAB();

    // 3. Deactivate Row (Drive HIGH)
    mcpRows.digitalWrite(r, HIGH);

    // 4. Process Column Bits
    for (int c = 0; c < COLS; c++) {
      // Bit c in 'cols' corresponds to Column c.
      // If bit is 0, Button is PRESSED (Active Low).
      bool isPressed = !((cols >> c) & 1);

      // Store state
      keyState[r][c] = isPressed;

      // Check for Change
      if (keyState[r][c] != lastKeyState[r][c]) {
        // Debounce: A simple delay here would slow down scanning.
        // For a better debounce, we could require N stable reads.
        // However, with I2C scanning speed (~50Hz?), reading once per loop is already "debounced" by the loop time.
        // Let's implement simple edge handling.

        const char* oscPath = KEYMAP[r][c];
        if (oscPath != NULL) {
            if (isPressed) {
                sendOSC(oscPath, 1.0f);
            } else {
                sendOSC(oscPath, 0.0f);
            }
        }

        lastKeyState[r][c] = isPressed;
      }
    }
  }

  // Optional: Delay to control scan rate
  delay(10);
}
