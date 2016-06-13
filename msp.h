#ifndef MSP_MULTIWII
#define MSP_MULTIWII

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "configure_port.h"

struct msp_header{
    char pre1;
    char pre2;
    char pre3;
    uint8_t length;
    uint8_t code;
};


void read_response(struct sp_port * multiwii);
void read_header(struct sp_port * multiwii, struct msp_header * msp_head);
void read_IDENT(struct sp_port * multiwii, struct msp_header * msp_head);
void read_STATUS(struct sp_port * multiwii, struct msp_header * msp_head);
void read_RAW_RC(struct sp_port * multiwii, struct msp_header * msp_head);

void send_request(struct sp_port * multiwii, uint8_t code_in);
void send_RAW_RC(struct sp_port * multiwii, uint16_t * data);

void display_header(struct msp_header * msp_head);

#endif
