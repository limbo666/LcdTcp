/*
 * LcdInterface.cpp
 * Universal Layout Manager for 1x16, 2x16, 4x20, 2x40, 4x40
 */

#include "LcdTcp.h"

// =================================================================================
//  CONSTRUCTOR SELECTION
// =================================================================================

#if defined(LCD_SIZE_1x16)
    // 1x16 is treated as 16x2 (8+8 split) by the controller
    LiquidCrystal_I2C lcd(I2C_LCD_ADDR, 16, 2, LCD_5x8DOTS);

#elif defined(LCD_SIZE_2x16)
    LiquidCrystal_I2C lcd(I2C_LCD_ADDR, 16, 2, LCD_5x8DOTS);

#elif defined(LCD_SIZE_4x20)
    LiquidCrystal_I2C lcd(I2C_LCD_ADDR, 20, 4, LCD_5x8DOTS);

#elif defined(LCD_SIZE_2x40)
    LiquidCrystal_I2C lcd(I2C_LCD_ADDR, 40, 2, LCD_5x8DOTS);

#elif defined(LCD_SIZE_4x40)
    // 40,4 triggers the Dual-Chip logic in the modified library
    LiquidCrystal_I2C lcd(I2C_LCD_ADDR, 40, 4, LCD_5x8DOTS);

#else
    #error "Please select a screen size in I2C_LCD_ADDR_CFG.h"
#endif

// =================================================================================
//  COMMON INIT
// =================================================================================
void LcdInit(void)
{
    lcd.begin();
    lcd.clear();
}

// =================================================================================
//  SCREEN LAYOUTS
// =================================================================================

// ---------------------------------------------------------
// LAYOUT: 1x16 (Special 8+8 Split)
// ---------------------------------------------------------
#if defined(LCD_SIZE_1x16)

void LcdShowFetchIP(void)
{
    lcd.clear();
    lcd.setCursor(0, 0); lcd.print("Waiting"); // Left Half
    lcd.setCursor(0, 1); lcd.print(" IP...");  // Right Half
}

void LcdShowStandby(void)
{
    lcd.clear();
    String ipStr = WiFi.localIP().toString();
    
    // Split IP across the chemical split (0-7 Left, 8-15 Right)
    lcd.setCursor(0, 0);
    lcd.print(ipStr.substring(0, 8));

    if (ipStr.length() > 8) {
        lcd.setCursor(0, 1);
        lcd.print(ipStr.substring(8));
    }
}

// ---------------------------------------------------------
// LAYOUT: 2x16 (Standard Compact)
// ---------------------------------------------------------
#elif defined(LCD_SIZE_2x16)

void LcdShowFetchIP(void)
{
    lcd.clear();
    lcd.setCursor(0, 0); lcd.print("LCD Smartie TCP");
    lcd.setCursor(0, 1); lcd.print("Waiting IP...");
}

void LcdShowStandby(void)
{
    lcd.clear();
    lcd.setCursor(0, 0); lcd.print("IP Address:");
    lcd.setCursor(0, 1); lcd.print(WiFi.localIP());
}

// ---------------------------------------------------------
// LAYOUT: 4x20 (Standard Spacious)
// ---------------------------------------------------------
#elif defined(LCD_SIZE_4x20)

void LcdShowFetchIP(void)
{
    lcd.clear();
    lcd.setCursor(2, 0); lcd.print("LCD Smartie TCP");
    lcd.setCursor(0, 1); lcd.print("--------------------");
    lcd.setCursor(0, 2); lcd.print("Status: Connecting");
    lcd.setCursor(0, 3); lcd.print("Waiting for IP...");
}

void LcdShowStandby(void)
{
    lcd.clear();
    lcd.setCursor(2, 0); lcd.print("LCD Smartie TCP");
    lcd.setCursor(0, 1); lcd.print("--------------------");
    lcd.setCursor(0, 2); lcd.print("Connected! IP:");
    lcd.setCursor(0, 3); lcd.print(WiFi.localIP());
}

// ---------------------------------------------------------
// LAYOUT: 2x40 (Wide Single Controller)
// ---------------------------------------------------------
#elif defined(LCD_SIZE_2x40)

void LcdShowFetchIP(void)
{
    lcd.clear();
    lcd.setCursor(0, 0); lcd.print("LCD Smartie TCP Client - Booting...");
    lcd.setCursor(0, 1); lcd.print("Status: Waiting for DHCP Address...");
}

void LcdShowStandby(void)
{
    lcd.clear();
    lcd.setCursor(0, 0); lcd.print("LCD Smartie TCP Client - Connected");
    lcd.setCursor(0, 1); 
    lcd.print("IP Address: ");
    lcd.print(WiFi.localIP());
}

// ---------------------------------------------------------
// LAYOUT: 4x40 (Huge Dual Controller)
// ---------------------------------------------------------
#elif defined(LCD_SIZE_4x40)

void LcdShowFetchIP(void)
{
    lcd.clear();
    lcd.setCursor(9, 0); lcd.print("LCD Smartie TCP Client");
    lcd.setCursor(0, 1); lcd.print("----------------------------------------");
    lcd.setCursor(0, 2); lcd.print("Status: Connecting to WiFi...");
    lcd.setCursor(0, 3); lcd.print("        Please wait for DHCP...");
}

void LcdShowStandby(void)
{
    lcd.clear();
    String ssid = WiFi.SSID();
    
    lcd.setCursor(9, 0); lcd.print("LCD Smartie TCP Client");
    lcd.setCursor(0, 1); lcd.print("----------------------------------------");
    lcd.setCursor(0, 2); 
    lcd.print("Network: "); lcd.print(ssid);
    
    lcd.setCursor(0, 3); 
    lcd.print("IP Addr: "); lcd.print(WiFi.localIP());
}

#endif