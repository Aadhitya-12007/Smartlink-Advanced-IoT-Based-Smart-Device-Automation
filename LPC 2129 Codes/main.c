#include <lpc21xx.h>
#include "setup.h"

#define LED1 (1 << 12)
#define LED2 (1 << 13)
#define LED3 (1 << 14)
#define LED4 (1 << 15)

unsigned char rxbyte;

int main() {
    LCD_INIT();
    UART0_Init();
    IODIR0 |= (LED1 | LED2 | LED3 | LED4);
    IOSET0 = (LED1 | LED2 | LED3 | LED4);
    LCD_command(0x01); 
    delay_ms(2);
    LCD_command(0x80); 
    LCD_PRINTSTR("SmartLink-Smart");
    LCD_command(0xc0); 
    LCD_PRINTSTR("DeviceAutomation"); 
    UART0_str_tx("\n====================================================\n");
    UART0_str_tx("Project: Smartlink\n");
    UART0_str_tx("Advanced IoT-Based Smart Device Automation\n");
    UART0_str_tx("with cloud-Enabled Embedded Intelligence\n");
    UART0_str_tx("====================================================\n");
    UART0_str_tx("Commands:\n");
    UART0_str_tx("  'A' -> LED 1 ON  | 'a' -> LED 1 OFF\n");
    UART0_str_tx("  'B' -> LED 2 ON  | 'b' -> LED 2 OFF\n");
    UART0_str_tx("  'C' -> LED 3 ON  | 'c' -> LED 3 OFF\n");
    UART0_str_tx("  'D' -> LED 4 ON  | 'd' -> LED 4 OFF\n");
    UART0_str_tx("====================================================\n");
    UART0_str_tx("System Ready\n");

    while (1) {
        rxbyte = UART0_Rx();
        
        switch (rxbyte) {
            case 'A': 
                IOCLR0 = LED1; 
                UART0_str_tx("LED 1 is ON\n");
                break; 
            case 'a': 
                IOSET0 = LED1; 
                UART0_str_tx("LED 1 is OFF\n");
                break; 
            case 'B': 
                IOCLR0 = LED2; 
                UART0_str_tx("LED 2 is ON\n");
                break; 
            case 'b': 
                IOSET0 = LED2; 
                UART0_str_tx("LED 2 is OFF\n");
                break; 
            case 'C': 
                IOCLR0 = LED3; 
                UART0_str_tx("LED 3 is ON\n");
                break; 
            case 'c': 
                IOSET0 = LED3; 
                UART0_str_tx("lED 3 is OFF\n");
                break; 
            case 'D': 
                IOCLR0 = LED4; 
                UART0_str_tx("LED 4 is ON\n");
                break; 
            case 'd': 
                IOSET0 = LED4; 
                UART0_str_tx("LED 4 is OFF\n");
                break; 
            default:
                UART0_str_tx("Error\n"); 
                break; 
        }       
    }
}
