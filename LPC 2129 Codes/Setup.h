//Code by Aadhitya G
//Setup header file containing the function declarations

#ifndef setup
#define setup

void delay_ms(unsigned int);
void LCD_INIT(void);
void LCD_command(unsigned char);
void LCD_data(unsigned char);
void LCD_PRINTSTR(unsigned char*);
void UART0_Init(void);
void UART0_str_tx(unsigned char *);
void UART0_Tx(unsigned char);
unsigned char UART0_Rx(void);
void UART0_ISR_Config(void);

#endif
