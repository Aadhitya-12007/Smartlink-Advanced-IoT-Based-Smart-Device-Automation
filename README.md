# Smartlink: Advanced IoT-Based Smart Device Automation

![Platform](https://img.shields.io/badge/Platform-LPC2129%20%7C%20ESP8266mod-blue)
![Language](https://img.shields.io/badge/Language-Embedded%20C-orange)

## Project Overview
**Smartlink** is a robust, master-slave IoT automation framework that bridges cloud-based remote interfaces with deterministic, bare-metal hardware execution. 

Designed to overcome the limitations of single-SoC IoT setups, this architecture uses an **ESP8266mod** as a dedicated network coprocessor to handle Wi-Fi connectivity and MQTT brokering via the Arduino IoT Cloud. The network module translates remote dashboard interactions into asynchronous serial commands (UART). These commands are transmitted to an **LPC2129 (ARM7)** master controller running bare-metal C firmware. The LPC2129 ensures highly reliable, real-time hardware execution, driving a local LCD interface and safely actuating high-voltage AC loads via an opto-isolated relay manifold.

**Author:** Aadhitya G.

## Hardware Components Required
* **LPC2129 Development Board** (ARM7TDMI-S Master Controller)
* **ESP8266 NodeMCU** (Network Coprocessor / Wi-Fi Bridge)
* **HD44780 based 16x2 Alphanumeric LCD** (Local UI)
* **4-Channel Opto-isolated Relay Module** (Actuator)
* **4x Test LEDs & 330Ω Resistors** (For safe logic testing before the actual implementation)
* **Jumper Wires & Breadboard**
* **Standard 3.3V Power Supply (Vcc)**

## Software & Toolchain
* **Keil µVision** (For compiling the bare-metal C firmware for LPC2129)
* **Arduino IoT Cloud** (For the remote MQTT dashboard (virtual switches) and uploading the sketch to ESP8266mod)
* **Flash Magic** (Or equivalent programmer for LPC2129)

## System Architecture & Pin Mapping

### UART Communication (The Bridge)
Both microcontrollers operate on 3.3V logic, allowing for direct, level-shifter-free communication at 9600 Baud.
| ESP8266mod (Serial) | LPC2129 (Hardware UART0) | Function |
| :--- | :--- | :--- |
| D2 (GPIO 4) - TX | RXD0 (Port 0.0) | Transmits cloud commands ('A', 'a', etc.) |
| D1 (GPIO 5) - RX | TXD0 (Port 0.1) | Receives debug/status confirmations |
| GND | GND | **Common Ground (Crucial)** |

### LPC2129 GPIO Mapping
* **UART0 TxD and RxD** `P0.0` and `P0.1`
* **LCD Data/Control:** `P0.2` to `P0.11`
* **Relay/LED Outputs:** `P0.12` to `P0.15`

## Step-by-Step Initialization & Execution

### Step 1 - Configure the Arduino IoT Cloud
1. Navigate to the [Arduino IoT Cloud](https://cloud.arduino.cc/).
2. Create a new "Thing" and bind it to your ESP8266mod NodeMCU 1.0 (ESP-12E Module) device.
3. Add four Cloud Variables: `L1`, `L2`, `L3`, and `L4` (Type: Boolean/CloudLight, Permission: Read & Write).
4. Navigate to the "Dashboards" tab and create 4 switch widgets mapped to these variables.

### Step 2 - Flash the ESP8266mod Microcontroller
1. Open the auto-generated sketch in the Web Editor.
3. Map the state of `L1`-`L4` inside the auto-generated callback functions to transmit specific character bytes over `Serial` (e.g., `if (L1 == true) { Serial.print('A'); }`).
4. Upload the code to the ESP8266mod.

### Step 3 - Flash the LPC2129 Bare-Metal Firmware
1. Open the provided project files in Keil µVision.
2. Ensure the `UART0_Rx()` logic is set to **polling mode** (not interrupt-driven) to sequentially parse incoming commands.
3. Compile the `.c` files (`main.c`, `LCD_functions.c`, `UART_config.c`, etc.) to generate the `.hex` binary.
4. Flash the binary to the LPC2129 using Flash Magic.

### Step 4 - Hardware Assembly & Testing
1. Wire the common ground between the LPC2129, ESP8266mod, and your power supply.
2. Connect the TX/RX lines according to the pin mapping table.
3. *Phase 1 (Safe Testing):* Connect standard LEDs to pins `P0.12` - `P0.15` to verify the logic.
4. *Phase 2 (Deployment):* Replace the LEDs with the `IN1`-`IN4` pins of the relay module. Wire your AC loads through the Normally Open (NO) and Common (COM) terminals of the relays.

### Step 5: Getting the Output
1. Power up the master LPC2129 board first. The LCD will initialize and display the startup text: `"SmartLink-Smart Device Automatio"`.
2. Power the ESP8266. Wait 5-10 seconds for it to establish a Wi-Fi connection with the Arduino Cloud.
3. Open the Arduino IoT Cloud Dashboard on your mobile device or PC.
4. Toggle a switch. The command is routed over MQTT to the ESP8266mod, bridged via UART to the LPC2129, and physically executed by the relays within milliseconds.
