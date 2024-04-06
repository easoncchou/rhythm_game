#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "globals.h"
#include "functions.h"

// update location of keys (rectangles) based on the song
void graphics_controller() {
    // go through list and update location of each tile
    for (int i = 0; i < 4; i++) {
        NoteTile* prev = NULL;
        NoteTile* curr = NULL;
        switch (i) {
        case 0:
            curr = q_head;
            break;
        case 1:
            curr = w_head;
            break;
        case 2:
            curr = o_head;
            break;
        case 3:
            curr = p_head;
            break;
        }
        while (curr != NULL) {
            // draw over the tile's prev y-line with white
            draw_line(curr->x, curr->y, 0xFFFF); 
            // update the y_location of the NoteTile
            curr->y += curr->dy;
            // draw line to represent updated position
            draw_line(curr->x, curr->y + TILE_HEIGHT, curr->color);
            // if a tile is past the screen's bottom edge, remove from the list then free the memory
            if (curr->y > 240) { // no longer visible
                prev->next = curr->next;
                curr->next = NULL;
                free(curr);
            }
            // update prev and curr
            prev = curr;
            curr = curr->next;
        }
    }
}