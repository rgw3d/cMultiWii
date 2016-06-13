#include "configure_port.h"

struct serial_port_config sp_config= { //initilizing config data
    .port_name = "/dev/ttyUSB0",
    //if you change the length of the string, change the length o the char array in the defining struct
    .baudrate = 115200,
    .bits = 8,
    //.flow = SP_FLOWCONTROL_NONE,
    .parity = SP_PARITY_NONE,
    .stopbits = 1,
    .xonxoff = 0,
    .rtscts = 0,
    .dsrdtr = 0
    
};

int init_port(struct sp_port ** multiwii, struct sp_port_config * mconfig){    

    //access multiwii port
    enum sp_return port_status = sp_get_port_by_name(sp_config.port_name, multiwii);   
    if(port_status != 0){
        printf("UNABLE TO ACCESS PORT OR PORT ERROR. HALTING"); 
        return 1;
    }
    
    //open multwii port
    port_status = sp_open(*multiwii, SP_MODE_READ_WRITE);//open
    if(port_status != 0){
        printf("UNABLE TO OPEN PORT. HALTING"); 
        return 2;
    }
    
    //set configuration to port
    port_status = sp_set_config(*multiwii, mconfig);
    if(port_status != 0){
        printf("ERROR sp_set_config. HALTING \n");  
        printf("ERROR: %d", port_status);
        return 3;
    }

    //No errors!
    return 0;
}

int close_port(struct sp_port * multiwii){
    int close_return = sp_close(multiwii);
    if(close_return!=0){
        printf("error duing sp_close");
        printf("error code: %d",close_return);
        return 1;
    }
    sp_free_port(multiwii);
    return 0;
}

int init_configs(struct sp_port_config ** mconfig){

    enum sp_return config_status = sp_new_config(mconfig);

    if(config_status != 0){
        printf("ERROR CREATING sp_new_config. HALTING");
        return 1;
    }
    config_status = sp_set_config_baudrate(*mconfig, sp_config.baudrate);
    if(config_status != 0){
        printf("ERROR SETTING sp_config_set_baudrate. HALTING");
        return 1;
    }
    config_status = sp_set_config_bits(*mconfig, sp_config.bits);
    if(config_status != 0){
        printf("ERROR SETTING sp_config_set_bits. HALTING");
        return 1;
    }
//  config_status = sp_set_config_flowcontrol(*mconfig, sp_config.flow);
//  if(config_status != 0){
//      printf("ERROR SETTING sp_config_set_flowcontrol. HALTING");
//      return 1;
//  }

    config_status = sp_set_config_parity(*mconfig, sp_config.parity);
    if(config_status != 0){
        printf("ERROR SETTING sp_config_set_parity. HALTING");
        return 1;
    }

    config_status = sp_set_config_stopbits(*mconfig, sp_config.stopbits);
    if(config_status != 0){
        printf("ERROR SETTING sp_config_set_stopbits. HALTING");
        return 1;
    }

    config_status = sp_set_config_xon_xoff(*mconfig, sp_config.xonxoff);
    if(config_status != 0){
        printf("ERROR SETTING sp_config_set_xon_xoff. HALTING");
        return 1;
    }
    config_status = sp_set_config_rts(*mconfig, sp_config.rtscts);
    if(config_status != 0){
        printf("ERROR SETTING sp_config_set_rts. HALTING");
        return 1;
    }
    config_status = sp_set_config_cts(*mconfig, sp_config.rtscts);
    if(config_status != 0){
        printf("ERROR SETTING sp_config_set_cts. HALTING");
        return 1;
    }
    config_status = sp_set_config_dtr(*mconfig, sp_config.dsrdtr);
    if(config_status != 0){
        printf("ERROR SETTING sp_config_set_dsr. HALTING");
        return 1;
    }
    config_status = sp_set_config_dsr(*mconfig, sp_config.dsrdtr);
    if(config_status != 0){
        printf("ERROR SETTING sp_config_set_dtr. HALTING");
        return 1;
    }
    return 0;
}


void list_ports(){
    struct sp_port ** ports;
    sp_list_ports(&ports);
    int i;
    for(i = 0; ports[i]; i++){
        printf("Availiable port: %s \n",sp_get_port_name(ports[i]));
    }
    sp_free_port_list(ports);
}







