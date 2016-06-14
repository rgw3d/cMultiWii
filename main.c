#include "msp.h"

int main(){
    struct sp_port * multiwii;
    struct sp_port_config * mconfig;

    //initialization
    int config_return = init_configs(&mconfig);
    if(config_return>0){
        printf("Error during configuration");
        printf("Error code: %d", config_return);
        printf("Exiting now");
        return config_return;
    }

    int init_return = init_port(&multiwii, mconfig);
    if(init_return>0){
        printf("Error during port configuration");
        printf("Error code: %d", init_return);
        printf("Exiting now");
        return init_return;
    }

    uint16_t * rc_data;
    rc_data = ( uint16_t *)(malloc(sizeof(uint16_t)*8));
    rc_data[0] = 1500;
    rc_data[1] = 1000;
    rc_data[2] = 1300;
    rc_data[3] = 1200;
    rc_data[4] = 1100;
    rc_data[5] = 1900;
    rc_data[6] = 1800;
    rc_data[7] = 1700;
    int i = 0;
    for(;i<1000; i++){
        send_RAW_RC(multiwii,rc_data);
        send_request(multiwii,105);
        read_response(multiwii);
        rc_data[1]=i+1000;
    }
    free(rc_data);
    //Program logic

    
    //Cleanup
    close_port(multiwii);
    sp_free_config(mconfig);
    return 0;
}
