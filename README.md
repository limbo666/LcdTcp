# Wifi2LCD - Enhanced Version Stable

This project is a high-performance WiFi-based Text LCD interface for ESP8266, designed to work seamlessly with **LCD Smartie** and other compatible software.

### Remarks
This version of firmware requires the latest driver to be used on LCD Smartie. 
Drive is available on the following repo release pages:  https://github.com/limbo666/LcdTcpDll

### Credits

This project is a fork of the original work by  [**eeyrw**](https://github.com/eeyrw). Many thanks to him for providing the excellent foundation for this TCP-to-I2C bridge.

----------

## LCD Smartie driver
A fully compatible LCD Smartie display driver for this hardware can be found on https://github.com/limbo666/LcdTcpDll

----------

## Key Enhancements in this Version

-   **Expanded Hardware Support:** Added native support for **4x40** (Dual Controller) displays, alongside 1x16, 2x16, 4x20, and 2x40.        
-   **Integrated I/O System:** Support for **4 physical buttons** (sending keys to PC) and **2 Outputs** (GPO and PWM Fan control)    
-   **Stability Fixes:** Optimized TCP handling to prevent ESP8266 crashes during high-traffic updates.    
-   **Dynamic Boot Screens:** Professional startup layouts tailored to the detected screen size.  

----------

## Build & Setup (Arduino IDE)

### 1. Prerequisites

-   **Arduino IDE** installed.
    
-   **ESP8266 Core** installed (via Boards Manager).
    
-   **Libraries:**
    
    -   `WiFiManager` (Install via Library Manager).
        
    -   `LiquidCrystal_I2C` (The modified version included in this repository is required for 4x40 support)
        

### 2. Configuration (Mandatory)

Before uploading, you **must** configure your hardware in `I2C_LCD_ADDR_CFG.h`
1.  **I2C Address:** Set `#define I2C_LCD_ADDR` to your backpack address (usually `0x27` or `0x3F`).    
2.  **Screen Size:** Uncomment exactly **one** line that matches your screen (e.g., `#define LCD_SIZE_4x40`).
    

### 3. Uploading

1.  Open `LcdTcp.ino`    
2.  Select your board (e.g., **Wemos D1 Mini** or **NodeMCU 1.0**)    
3.  Click **Upload**.
    

----------

## Hardware Pinout (Wemos D1 Mini)

|Component|Pin|Function|
|--|--|--|
|I2C LCD  | D1 (SCL) / D2 (SDA)  |Standard Screen Connection   |
| Button 1-4 |D5, D6, D7, D3  |Connect between Pin and GND  |
| GPO Out |D0  |Connect between Pin and GND  |Digital On/Off|
| Fan Out |D8  |PWM Speed/0-255 Control |
|--|--|--|

Note: Avoid holding the button on D3 during power-up as it may enter Flash Mode14.

----------

## Usage

1.  **WiFi Setup:** On first boot, the ESP will create an AP named **"LCD TCP WIFI CONFIG"**. Connect with your phone to set your home WiFi credentials.    
2.  **Display:** Once connected, the screen will display the **Local IP Address**    
3.  **PC Connection:** Use the matching `LcdTcpDll.dll` in your **LCD Smartie** "displays" folder. Configure the DLL with the IP address shown on the LCD.    

### License

This project is released under the **MIT License**, following the licensing applied by the original author.
