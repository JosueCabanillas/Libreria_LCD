#define DATA_LCD PORTF //Estoy usando el puerto F porque si uso el puerto D //
//los pines RD0 y RD1 tienen tambien multiplexado los pines OC1 y OC2
#define TRIS_DATA_LCD TRISF

#define RW_PIN LATBbits.LATB10     /* PORT for RW */
#define TRIS_RW  TRISBbits.TRISB10    /* TRIS for RW */
#define RS_PIN   LATBbits.LATB9   /* PORT for RS */
#define TRIS_RS  TRISBbits.TRISB9    /* TRIS for RS */
#define E_PIN    LATBbits.LATB11   /* PORT for E  */
#define TRIS_E   TRISBbits.TRISB11    /* TRIS for E  */

void LCD_XY(int x,int y);
void LCD_Caracter(unsigned char data);
void LCD_Comando(unsigned char cmd);
void LCD_Init(void);
void LCD_String(char *dat);
