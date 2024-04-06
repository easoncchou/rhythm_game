#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "globals.h"
#include "functions.h"

// update location of keys (rectangles) based on the song
void graphics_controller() {
	draw_background();
    // go through list and update location of each tile
    for (int i = 0; i < 4; i++) {
        NoteTile* prev = NULL;
        NoteTile* curr = NULL;
		bool tileHit = false;
        switch (i) {
        case 0:
            curr = q_head;
			tileHit = q_pressed;
            break;
        case 1:
            curr = w_head;
			tileHit = w_pressed;
            break;
        case 2:
            curr = o_head;
			tileHit = o_pressed;
            break;
        case 3:
            curr = p_head;
			tileHit = p_pressed;
            break;
        }
        while (curr != NULL) {
            // update the y_location of the NoteTile
            curr->y += curr->dy * 7;
            // draw line to represent updated position
            draw_tile(curr->x, curr->y, curr->color);
			// timing comparator
			if (curr->scored == false && curr->y > GREAT_UPPER && curr->y < GREAT_LOWER) {
				if (tileHit) {
					// printf("great\n");
					score += GREAT;
					curr->scored = true;
				}
			}
			// printf("%d, %d\n", curr->x, curr->y);
            // if a tile is past the screen's bottom edge, remove from the list then free the memory
            if (curr->y > 240 - TILE_HEIGHT) { // no longer visible
                // Store a pointer to the next node before freeing the current node
				NoteTile* temp = curr->next;
				// If the current node is the head of the list
				if (prev == NULL) {
					// Update the head pointer to the next node
					switch (i) {
						case 0:
							q_head = temp;
							break;
						case 1:
							w_head = temp;
							break;
						case 2:
							o_head = temp;
							break;
						case 3:
							p_head = temp;
							break;
					}
				} else {
					// Update the next pointer of the previous node to skip over the current node
					prev->next = temp;
				}
				// Free the memory allocated for the current node
				free(curr);
				// printf("tile deleted\n");
				// Move to the next node
				curr = temp;
				// No need to update prev since the node has been removed
				continue; // Skip the update of prev and curr at the end of the loop
			}
            // update prev and curr
            prev = curr;
            curr = curr->next;
        }
    }
}