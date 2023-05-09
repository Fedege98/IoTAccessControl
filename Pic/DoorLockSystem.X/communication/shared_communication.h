#ifndef SHARED_COMMUNICATION_H
#define	SHARED_COMMUNICATION_H
#include "../constants/constants.h"

#ifdef	__cplusplus
extern "C" {
#endif

    typedef enum 
    {
        PACKET_DEBUG = 1,
        PACKET_GENERATE         
    } packet_type_t;
    
    typedef struct 
    {
        uint8_t code;
    } shared_generate_command_t;
    
    
  
    
    typedef struct 
    {
        uint16_t length;
        char source_device [DEVICE_SERIAL_NUMBER_MAX_LENGHT];
        char target_device [DEVICE_SERIAL_NUMBER_MAX_LENGHT];
        packet_type_t packet_type;
        union
        {
            shared_generate_command_t generate_command;
        };
        
    } shared_packet_t;

#ifdef	__cplusplus
}
#endif

#endif	/* SHARED_COMMUNICATION_H */

