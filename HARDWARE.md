# Hardware Configuration for ETC EOS OSC Wing

This project is designed for an **Olimex ESP32-POE** board.
Due to the large number of buttons (128 buttons in an 8x16 matrix) and the pins consumed by the Ethernet interface, the ESP32 does not have enough native GPIO pins to drive the matrix directly.

## Required Hardware

1.  **Olimex ESP32-POE** Board.
2.  **Two (2) MCP23017** I/O Expanders (I2C).
    *   **Chip 1**: Handles the 16 Columns (Inputs).
    *   **Chip 2**: Handles the 8 Rows (Outputs).
3.  **Keyboard Matrix**: 8 Rows x 16 Columns.

## Wiring Guide

### I2C Connection (ESP32 <-> MCP23017s)

Both MCP23017 chips share the I2C bus.
The Olimex ESP32-POE uses specific pins for I2C (available on the UEXT connector).

| ESP32 Pin | MCP23017 Pins | Description |
| :--- | :--- | :--- |
| GPIO 13 | 13 (SDA) | I2C Data (Connect to SDA on both chips) |
| GPIO 16 | 12 (SCL) | I2C Clock (Connect to SCL on both chips) |
| 3.3V | 9 (VDD) | Power |
| GND | 10 (VSS) | Ground |
| - | 18 (RESET) | Connect to 3.3V (Active Low) |

### Chip Configuration (Addresses)

You must set the address pins (A0, A1, A2) differently for each chip.

**Chip 1 (Columns) - Address 0x20**:
*   A0 (Pin 15) -> GND
*   A1 (Pin 16) -> GND
*   A2 (Pin 17) -> GND

**Chip 2 (Rows) - Address 0x21**:
*   A0 (Pin 15) -> 3.3V (HIGH)
*   A1 (Pin 16) -> GND
*   A2 (Pin 17) -> GND

### Matrix Connections

**Chip 1 (Columns) - Inputs with Pull-Ups**:
Connect Matrix Columns 9-24 to Chip 1.

| Matrix Column | Chip 1 Pin | Port/Bit |
| :--- | :--- | :--- |
| Col 9 | 21 | GPA0 |
| Col 10 | 22 | GPA1 |
| Col 11 | 23 | GPA2 |
| Col 12 | 24 | GPA3 |
| Col 13 | 25 | GPA4 |
| Col 14 | 26 | GPA5 |
| Col 15 | 27 | GPA6 |
| Col 16 | 28 | GPA7 |
| Col 17 | 1 | GPB0 |
| Col 18 | 2 | GPB1 |
| Col 19 | 3 | GPB2 |
| Col 20 | 4 | GPB3 |
| Col 21 | 5 | GPB4 |
| Col 22 | 6 | GPB5 |
| Col 23 | 7 | GPB6 |
| Col 24 | 8 | GPB7 |

**Chip 2 (Rows) - Outputs**:
Connect Matrix Rows 1-8 to Chip 2 (Port A).

| Matrix Row | Chip 2 Pin | Port/Bit |
| :--- | :--- | :--- |
| Row 1 | 21 | GPA0 |
| Row 2 | 22 | GPA1 |
| Row 3 | 23 | GPA2 |
| Row 4 | 24 | GPA3 |
| Row 5 | 25 | GPA4 |
| Row 6 | 26 | GPA5 |
| Row 7 | 27 | GPA6 |
| Row 8 | 28 | GPA7 |

## Software Dependencies

In Arduino IDE, you must install:
1.  **Adafruit MCP23017 Arduino Library** (by Adafruit)
2.  **OSC** (by Adrian Freed)
