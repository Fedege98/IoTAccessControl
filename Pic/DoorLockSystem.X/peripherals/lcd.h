/* 
 * File:   lcd.h
 * Author: User
 *
 * Created on 2 maggio 2023, 20.21
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

    
void Lcd_Port(char a);

void Lcd_Cmd(char a);

void Lcd_Init();

void Lcd_Clear();

void Lcd_Set_Cursor(char riga, char colonna);

void Lcd_Write_Char(char a);

void Lcd_Write_String(char *a);

void Lcd_Shift_Right();

void Lcd_Shift_Left();

char* Lcd_Write_Int(int val);



#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

