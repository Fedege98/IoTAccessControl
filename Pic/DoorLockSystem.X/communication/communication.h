/* 
 * File:   communication.h
 * Author: User
 *
 * Created on 29 aprile 2023, 19.53
 */

#ifndef COMMUNICATION_H
#define	COMMUNICATION_H

#ifdef	__cplusplus
extern "C" {
#endif

    void communication_init(long int baudrate);
    void communication_task();
    void UART_send_packet(shared_packet_t* packet_to_send);
    void UART_data_received();
    uint8_t received_queue_thereispending();
    void received_queue_get_packet(shared_packet_t* packet);


#ifdef	__cplusplus
}
#endif

#endif	/* COMMUNICATION_H */

