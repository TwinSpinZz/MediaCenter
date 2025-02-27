/*----------------------------------------------------------------------------
 * Name:    Blinky.c
 * Purpose: LED Flasher and Graphic Demo
 * Note(s): 
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2008-2011 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/
                  
#include <LPC17xx.H>                    /* NXP LPC17xx definitions            */
#include "string.h"
#include "GLCD.h"
#include "LED.h"
#include "KBD.h"
#include "CNTower.c"
#include "cloy.c"
#include "ENGBuilding.c"
#include "LoL.c"
#include "natsu.c"

#define __FI        1                      /* Font index 16x24               */
#define __USE_LCD   0

/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int photo (void) {                      
  int currentButtonState = 0;
  int lastButtonState = -1;    
  int pic     =  0;
	int KBD_but;
	unsigned char* images[] = {(unsigned char *)&CNTOWER_pixel_data, (unsigned char *)&NATSU_pixel_data, (unsigned char *)&LOL_pixel_data, (unsigned char *)&ENG_pixel_data, (unsigned char *)&CLOY_pixel_data};
	int totalImages = sizeof(images) / sizeof(images[0]); 

	KBD_Init();
  LED_Init ();
  GLCD_Init();

  GLCD_Clear  (White);
    for (;;) {
				GLCD_SetBackColor(Blue);
				GLCD_SetTextColor(White);
				GLCD_DisplayString(0, 0, __FI, "   COE718 Project   ");
				GLCD_DisplayString(1, 0, __FI, "   Photo Gallery    ");
        currentButtonState = get_button(); 

        // Check if the button state has changed since the last loop iteration
        if (currentButtonState != lastButtonState) {
            switch (currentButtonState) {
                case KBD_UP:
                    pic = (pic + 1) % totalImages;  // right, wrap around if necessary
                    break;
                case KBD_DOWN:
                    pic = (pic - 1 + totalImages) % totalImages;  // left, wrap around if necessary
                    break;
								case KBD_SELECT:
										GLCD_Clear (White);
										return 0;
										break;
            }

						if(currentButtonState == KBD_LEFT | currentButtonState == KBD_RIGHT){
						} else {
							GLCD_Clear(White);
							GLCD_Bitmap(50, 40, 200, 200, images[pic]);
						}
						
            lastButtonState = currentButtonState; 
        }
    }
}
