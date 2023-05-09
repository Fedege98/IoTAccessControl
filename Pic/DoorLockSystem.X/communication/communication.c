
#include <xc.h>
#include <string.h>
#include"shared_communication.h"
#include "communication.h"

#define MAX_QUEUE_LENGHT 3

static uint8_t is_line_busy;


static shared_packet_t receive_queue [MAX_QUEUE_LENGHT];
static uint8_t receive_queue_elements; 

static void UART_TxByte(char byte);

void UART_send_packet(shared_packet_t* packet_to_send)
{       
    packet_to_send->length = sizeof(shared_packet_t);
    strncpy(packet_to_send->source_device, DEVICE_SERIAL_NUMBER, DEVICE_SERIAL_NUMBER_MAX_LENGHT);

    unsigned char buffer[sizeof(shared_packet_t)];

    memcpy(buffer, packet_to_send, sizeof(shared_packet_t));
    for (int i = 0; i < sizeof(shared_packet_t); i++) {

        UART_TxByte(buffer[i]);
    }
   
}

void communication_init(long int baudrate)
{
    //UART INIT
    TXSTA |= 0x24;
    RCSTA = 0x90;
    SPBRG = (char) (_XTAL_FREQ / (long) (64UL * baudrate)) - 1;
    INTCON |= 0x80;
    INTCON |= 0x40;
    PIE1 |= 0x20;
}

void communication_task()
{
  
}

void UART_data_received()
{
    static char buffer[sizeof(shared_packet_t)];
    static int index;
  
    char data = RCREG; // Read received data from UART receive buffer
        if (index < sizeof(shared_packet_t)) {
            buffer[index++] = data;
            
            if (index >= sizeof(shared_packet_t)) {
                if(receive_queue_elements < MAX_QUEUE_LENGHT)
                {
                    memcpy(&receive_queue[++receive_queue_elements], buffer, sizeof(shared_packet_t));
                }
                else
                {
                    //TODO manage full queue
                }
                index = 0;
            }
        }
}

uint8_t received_queue_thereispending()
{
    return receive_queue_elements;
}

void received_queue_get_packet(shared_packet_t* packet)
{
    memcpy(packet, &receive_queue[--receive_queue_elements], sizeof(shared_packet_t));
}


static void UART_TxByte(char byte){
    TRISC &= ~0x40;
    TRISC |= 0x80;
    while (!(PIR1 & 0x10));
    PIR1 &= ~0x10;
    TXREG = byte;

}