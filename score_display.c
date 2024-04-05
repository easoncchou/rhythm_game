#include "global.h"

unsigned int hex_display(int number){
    //depending on the number, return its corresponding HEX display in hexidecimal
    switch (number){
        case(0):
            return 0x3F;
        case(1):
            return 0x06;
        case(2):
            return 0x5B;
        case(3):
            return 0x4F;
        case(4):
            return 0x66;
        case(5):
            return 0x6D;
        case(6):
            return 0x7D;
        case(7):
            return 0x07;
        case(8):
            return 0x7F;
        case(9):
            return 0x67;       
    }
}

void score_display (int score){

    // initialize HEX pointer
    volatile unsigned int * HEX_ptr = (unsigned int *) HEX_BASE;

    // get the digits of the score in hexidecimal for HEX display
    unsigned int first_digit = hex_display(score % 10);

    int temp = (score-(score % 10))/10;
    unsigned int second_digit = hex_display(temp% 10);

    temp = (temp-(temp%10))/10;
    unsigned int third_digit = hex_display(temp%10);

    // shift and display the score on the HEX
    unsigned int display_num = third_digit;
    display_num = display_num << 8;
    display_num = display_num | second_digit;
    display_num = display_num << 8;
    display_num = display_num | first_digit;

    *HEX_ptr = display_num;
}