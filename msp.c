#include "msp.h"

void read_response(struct sp_port * multiwii){
    msp_header head = {.pre1 ='x', .pre2 = 'x', .pre3 = 'x'};
    read_header(multiwii, &head);
    
    if(head.pre1 == 'x')//if nothing was read
        return;

    if(head.code == 100){//IDENT
        read_IDENT(multiwii, &head);
    }
    else if(head.code == 101){//STATUS
        read_STATUS(multiwii, &head);
    }
    else if(head.code == 105){//RAW_RC
        read_RAW_RC(multiwii, &head);
    }
    
    

}

void read_header(struct sp_port * multiwii, struct msp_header * msp_head){
    sp_blocking_read(multiwii, &(head->pre1),1,10);
    sp_blocking_read(multiwii, &(head->pre2),1,10);
    sp_blocking_read(multiwii, &(head->pre3),1,10);
    sp_blocking_read(multiwii, &(head->length),1,10);
    sp_blocking_read(multiwii, &(head->code),1,10);
}

void read_IDENT(struct sp_port * multiwii, struct msp_header * msp_head){

}
void read_STATUS(struct sp_port * multiwii, struct msp_header * msp_head){

}
void read_RAW_RC(struct sp_port * multiwii, struct msp_header * msp_head){

}

void send_request(struct sp_port * multiwii, uint8_t code_in){
    uint8_t size = 0;
    uint8_t command = command_in;
    uint8_t crc = command_in;// == (crc=0) ^=command_in

    int a = sp_blocking_write(multiwii,(char *)"$",1,0);
    int b = sp_blocking_write(multiwii,(char *)"M",1,0);
    int c = sp_blocking_write(multiwii,(char *)"<",1,0);
    int d = sp_blocking_write(multiwii, &size, 1,0);
    int e = sp_blocking_write(multiwii, &command, 1,0);
    int f = sp_blocking_write(multiwii, &crc, 1,0);
    if(a<0 || b<0 || c<0 ||d<0 ||e<0||f<0){
        printf("writing error");
    }
    printf("SEND:\t$M<, size %d, command %d, crc %d\n", size, command, crc);
    //sp_drain(multiwii);//wait for data to be sent
}

void send_RAW_RC(struct sp_port * multiwii, uint16_t * data){
    uint8_t size = 16;
    uint8_t command = 200;
    uint8_t crc = 0;
    crc ^= size;
    crc ^= command;
    int i = 0;
    for(; i<8;i++){
        crc ^= (data[i]>>8);
        crc ^= (data[i] & 0x0f);
    }

    int a = sp_blocking_write(multiwii,(char *)"$",1,0);
    int b = sp_blocking_write(multiwii,(char *)"M",1,0);
    int c = sp_blocking_write(multiwii,(char *)"<",1,0);
    int d = sp_blocking_write(multiwii, &size, 1,0);
    int e = sp_blocking_write(multiwii, &command, 1,0);
    int f = 0;
    for(i = 0; i< 8; i++){
        f = sp_blocking_write(multiwii,&data[i],2,0);
        if (f<0)
            break;
    }

    int g = sp_blocking_write(multiwii, &crc, 1,0);

    if(a<0 || b<0 || c<0 ||d<0 ||e<0||f<0 || g <0){
        printf("Writing Error");
    }
    
    printf("SEND:\t$M<, size %d, command %d, crc %d\n", size, command, crc);
    sp_drain(multiwii);//wait for data to be sent
}
