
#pragma config FOSC = HS       // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF      // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = ON        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF       // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF       // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF        // Flash Program Memory Code Protection bit (Code protection off)


#include <xc.h>
#include <string.h>
#include "communication/shared_communication.h"
#include "communication/communication.h"
#include "constants/constants.h"
#include "peripherals/lcd.h"
#include "peripherals/numpad.h"

void main(void) {
    Lcd_Init();
    communication_init(115200);
    Lcd_Write_String("ab ");
    TRISD = 0x00;
    PORTD = 0x00;

    
    uint16_t received_count;

    while (1) {
        communication_task();
        
        shared_packet_t send_packet;
        memset(&send_packet,0x00,sizeof(shared_packet_t));
        send_packet.packet_type = PACKET_GENERATE;

        strncpy(send_packet.target_device, "raspi", DEVICE_SERIAL_NUMBER_MAX_LENGHT);
        send_packet.generate_command.code = 12;
        UART_send_packet(&send_packet);
     
       
        if(received_queue_thereispending() > 0)
        {
            shared_packet_t packet;
            received_queue_get_packet(&packet);
            Lcd_Clear();
            Lcd_Write_Int(++received_count);
        }
    }
}

void __interrupt()ISR() {
    if (RCIF) {
        UART_data_received();
        RCIF = 0;
    }
}