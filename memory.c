#include <LPC17xx.H>                    /* NXP LPC17xx definitions            */
#include "string.h"
#include "GLCD.h"
#include "LED.h"
#include "KBD.h"
#include <stdlib.h>
#include <stdio.h>

#include "four_of_hearts.c"
#include "three_of_spades.c"
#include "two_of_diamonds.c"
#include "ace_of_spades.c"
#include "eight_of_spades.c"
#include "five_of_hearts.c"
#include "jack_of_hearts.c"
#include "king_of_clubs.c"
#include "nine_of_hearts.c"
#include "queen_of_diamonds.c"
#include "seven_of_clubs.c"
#include "six_of_diamonds.c"
#include "ten_of_spades.c"
#include "backCard.c"
#include "redBackCard.c"

#define __FI        1                     /* Font index 16x24               */
#define __USE_LCD   0

#define TOTAL_CARDS 13
#define SELECTED_CARDS 8
#define MATRIX_CARDS (SELECTED_CARDS * 2)
#define CARD_WIDTH 40
#define CARD_HEIGHT 58
#define X_MARGIN 1
#define Y_MARGIN 1
#define X_SPACING 2
#define Y_SPACING 2
#define CARD_BACK 0  // Representing face-down card
#define CARD_FACE 1  // Representing face-up card

int cardStates[MATRIX_CARDS];  // Array to track each card's state
unsigned char* images[] = {(unsigned char *)&ACESPADE_pixel_data, (unsigned char *)&EIGHTSPADE_pixel_data, (unsigned char *)&FIVEHEART_pixel_data, (unsigned char *)&FOURHEART_pixel_data, (unsigned char *)&JACKHEART_pixel_data, 
(unsigned char *)&KINGCLUB_pixel_data, (unsigned char *)&NINEHEART_pixel_data, (unsigned char *)&QUEENDIAMOND_pixel_data, (unsigned char *)&SEVENCLUB_pixel_data, (unsigned char *)&SIXDIAMONDS_pixel_data, 
(unsigned char *)&TENSPADE_pixel_data, (unsigned char *)&THREESPADE_pixel_data, (unsigned char *)&TWODIAMOND_pixel_data};
unsigned char* distributedIndices[MATRIX_CARDS]; // Filled by your shuffle function

typedef struct {
	char value[3];
	char suit;
} Card;

typedef struct {
    int x;
    int y;
} Cursor;

void memorydelay(int milliseconds) {
  int i;  
	for(i = 0; i < milliseconds; i++) {
	}
}


Cursor cursor;

void updateCursorPosition(int buttonPress) {
    switch (buttonPress) {
        case KBD_UP:    // Replace with the actual value for up
            cursor.y = (cursor.y - 1 > 0) ? cursor.y - 1 : 0;
            break;
        case KBD_DOWN:  // Replace with the actual value for down
            cursor.y = (cursor.y + 1 < 3) ? cursor.y + 1 : 3;
            break;
        case KBD_LEFT:  // Replace with the actual value for left
            cursor.x = (cursor.x - 1 > 0) ? cursor.x - 1 : 0;
            break;
        case KBD_RIGHT: // Replace with the actual value for right
            cursor.x = (cursor.x + 1 < 3) ? cursor.x + 1 : 3;
            break;
    }
}


void shuffleArrayAndDistributeImages(int n, unsigned char* distributedIndices[], int size) {
    int i, j;
    unsigned char* temp;

    // Shuffle the entire images array
    for (i = n - 1; i > 0; i--) {
        j = rand() % (i + 1);
        temp = images[i];
        images[i] = images[j];
        images[j] = temp;
    }

    // Randomly pick 8 unique cards from the shuffled images
    for (i = 0; i < SELECTED_CARDS; i++) {
        distributedIndices[i] = images[i];
        distributedIndices[i + SELECTED_CARDS] = images[i];
    }

    // Shuffle the distributedIndices array
    for (i = size - 1; i > 0; i--) {
        j = rand() % (i + 1);
        temp = distributedIndices[i];
        distributedIndices[i] = distributedIndices[j];
        distributedIndices[j] = temp;
    }
}


void display_cards() {
    int x, y, row, col, index;
    int selectedCardIndex = cursor.y * 4 + cursor.x; // Index of the card selected by the cursor

    for (row = 0; row < 4; row++) {
        for (col = 0; col < 4; col++) {
            x = X_MARGIN + col * (CARD_WIDTH + X_SPACING);
            y = Y_MARGIN + row * (CARD_HEIGHT + Y_SPACING);
            index = row * 4 + col;

            if (cardStates[index] == CARD_BACK) {
                if (index == selectedCardIndex) {
                    // Display red back of the card for the selected one
                    GLCD_Bitmap(x, y, CARD_WIDTH, CARD_HEIGHT, (unsigned char *)&REDBACKCARD_pixel_data);
                } else {
                    // Display regular back of the card for others
                    GLCD_Bitmap(x, y, CARD_WIDTH, CARD_HEIGHT, (unsigned char *)&BACKCARD_pixel_data);
                }
            } else {
                // Display face of the card
                GLCD_Bitmap(x, y, CARD_WIDTH, CARD_HEIGHT, distributedIndices[index]);
            }
        }
    }
}

int memory(void) {
		int KBD_But;
	  int isNewGame = 1; 
		int selectedCardIndex;
		int flippedCardIndices[2];  // Array to store indices of the flipped cards
		int flippedCardCount = 0;   // Count of currently flipped cards
		int allCardsMatched;
		int i;

		cursor.x = 0;  // Starting at the top-left of the matrix
		cursor.y = 0;
    KBD_Init();
		
    LED_Init();
    GLCD_Init();
		KBD_But = get_button(); 
        for (;;) { // Outer loop for each new game
					allCardsMatched = 1;
        if (isNewGame) {
            // Initialize all card states to CARD_BACK
          int i;  
					for ( i = 0; i < MATRIX_CARDS; i++) {
                cardStates[i] = CARD_BACK;
            }

            shuffleArrayAndDistributeImages(TOTAL_CARDS, distributedIndices, MATRIX_CARDS);
            display_cards();
            isNewGame = 0;
						flippedCardCount = 0;
        }

        KBD_But = get_button();

				if (KBD_But == KBD_SELECT) {
						selectedCardIndex = cursor.y * 4 + cursor.x;
						if (cardStates[selectedCardIndex] == CARD_BACK && flippedCardCount < 2) {
								cardStates[selectedCardIndex] = CARD_FACE;
								flippedCardIndices[flippedCardCount++] = selectedCardIndex;

								display_cards(); // Update display to show the flipped card

								if (flippedCardCount == 2) {
										// Introduce a memorydelay to allow players to see both cards
										memorydelay(15000000); // Adjust the duration as needed

										// Check if the two flipped cards match
										if (distributedIndices[flippedCardIndices[0]] != distributedIndices[flippedCardIndices[1]]) {
												// Cards do not match, flip them back over
												cardStates[flippedCardIndices[0]] = CARD_BACK;
												cardStates[flippedCardIndices[1]] = CARD_BACK;
												display_cards(); // Update display again to show cards flipped back
										}
										flippedCardCount = 0; // Reset flipped card count
								}
						}
				} else {
						updateCursorPosition(KBD_But);
				}

        display_cards(); // Update the display to reflect any changes
				
				for (i = 0; i < MATRIX_CARDS; i++) {
								if (cardStates[i] == CARD_BACK) {
										allCardsMatched = 0;
										break;
								}
						}

				if (allCardsMatched) {
					KBD_But = get_button();
					GLCD_Clear(White);
					GLCD_DisplayString(3, 0, 1, " Use Joystick UP to   ");
					GLCD_DisplayString(4, 0, 1, "   play again, or    ");
					GLCD_DisplayString(5, 0, 1, " SELECT to go back   ");
					GLCD_DisplayString(6, 0, 1, "   to the menu.      ");
					
					while(1) {
                KBD_But = get_button();
                if(KBD_But == KBD_UP) {
                    isNewGame = 1; 
                    break; 
                } else if(KBD_But == KBD_SELECT){
                    return 0;                    
                } 
            }
					GLCD_Clear(White);
				}
    }
}



