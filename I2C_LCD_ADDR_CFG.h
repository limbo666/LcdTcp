#ifndef I2C_LCD_ADDR_CFG__
#define I2C_LCD_ADDR_CFG__

/* 1. I2C ADDRESS SETTING */
/* Please modify the address to match your hardware settings */
#define I2C_LCD_ADDR 0x27 // Common addresses: 0x27 or 0x3F

/* 2. SCREEN SIZE SELECTION */
/* Uncomment EXACTLY ONE of the lines below to select your screen */

// #define LCD_SIZE_1x16  // Split 8+8 layout
// #define LCD_SIZE_2x16  // Standard 2-line
// #define LCD_SIZE_4x20  // Standard 4-line
 #define LCD_SIZE_2x40  // Wide 2-line
//#define LCD_SIZE_4x40  // Huge 4-line (Dual Controller)

#endif