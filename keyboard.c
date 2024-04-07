#include "globals.h"
#include <stdbool.h>

// read the Data register in the PS/2 port
void check_keypress() {
  PS2_data = *(keyboardp);

  // check RVALID for the data
  RVALID = (PS2_data & 0x8000);

  if (RVALID != 0) {
    /* always save the last three bytes received */
    byte1 = byte2;
    byte2 = byte3;
    byte3 = PS2_data & 0xFF;
  }
  // printf("Break_Code: %u\n", byte2);
  // printf("Make_Code: %u\n", byte3);
  if (byte2 != 0xF0) {
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
  } else {
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