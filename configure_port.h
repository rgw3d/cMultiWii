#ifndef CONFIGURE_PORT_MULITWII
#define CONFIGURE_PORT_MULTIWII

#include <libserialport.h>


struct serial_port_config{ //Config data
    char port_name[13];
    int baudrate;
    int bits;
    //enum sp_flowcontrol flow;
    enum sp_parity parity;
    int stopbits;       
    int xonxoff;
    int rtscts;
    int dsrdtr;
};


int init_port(struct sp_port ** multiwii);
int close_port(struct sp_port * multiwii);

int init_configs(struct sp_port_config ** mconfig);

void list_ports();

#endif
