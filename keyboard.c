// #include "globals.h"
// #include <stdbool.h>

// void check_keypress() {
//     //unsigned char byte1 = 0;
// 	//unsigned char byte2 = 0;

// 	unsigned char make_code = 0;
//     int PS2_data, RVALID;
//     int q_pressed, w_pressed, o_pressed, p_pressed;
    
//     // initialze pointer to PS/2 base
//   	volatile int * PS2_ptr = (int *) PS2_BASE;

//     // read the Data register in the PS/2 port
//     PS2_data = *(PS2_ptr);	

//     // check RVALID for the data
//     RVALID = (PS2_data & 0x8000);	

//     if (RVALID != 0){
//         // byte1 = byte2;
//         // byte2 = byte3;

//         // extracts the make_code 
//         make_code = PS2_data & 0xFF;

//         // check if note keys are pressed
//         switch (make_code) {
//             case (0x15):
//                 q_pressed = true;
//                 break;
            
//             case (0x1D):
//                 w_pressed = true;
//                 break;
            
//             case (0x44):
//                 o_pressed = true;
//                 break;
            
//             case (0x4D):
//                 p_pressed = true;
//                 break;

//             default:
//                 break;
//         }
//     }	
// }
