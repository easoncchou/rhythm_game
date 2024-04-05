#include "globals.h"
#include <stdbool.h>


void check_keypress() {
    unsigned char byte1 = 0;
	unsigned char byte2 = 0;
	unsigned char byte3 = 0;

    int PS2_data, RVALID;
    q_pressed= w_pressed= o_pressed= p_pressed= false;
    
    // initialze pointer to PS/2 base
  	volatile unsigned int * PS2_ptr = (unsigned int *) PS2_BASE;
    volatile unsigned int * LED_ptr = (unsigned int *) LED_BASE;

    // read the Data register in the PS/2 port
    PS2_data = *(PS2_ptr);	

    // check RVALID for the data
    RVALID = (PS2_data & 0x8000);	

    if (RVALID != 0){
        /* always save the last three bytes received */
        byte1 = byte2;
        byte2 = byte3;
        byte3 = PS2_data & 0xFF;
    }

    if (byte2 != 0xF0){
        // check if note keys are pressed
        switch (byte3) {
            case (0x15):
                q_pressed = true;
                *LED_ptr = (*LED_ptr) | 0x8;
                break;

            case (0x1D):
                w_pressed = true;
                *LED_ptr = (*LED_ptr) | 0x4;
                break;

            case (0x44):
                o_pressed = true;
                *LED_ptr = (*LED_ptr) | 0x2;
                break;

            case (0x4D):
                p_pressed = true;
                *LED_ptr = (*LED_ptr) | 0x1;
                break;

            default:
                break;
        }
    } else{
        switch (byte3) {
            case (0x15):
            q_pressed = false;
            *LED_ptr = (*LED_ptr) & 0x7;
            break;

            case (0x1D):
            w_pressed = false;
            *LED_ptr = (*LED_ptr) & 0xA;
            break;

            case (0x44):
            o_pressed = false;
            *LED_ptr = (*LED_ptr) & 0xD;
            break;

            case (0x4D):
            p_pressed = false;
            *LED_ptr = (*LED_ptr) & 0xE;
            break;

            default:
            break;
        }
    }
}	

