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

#define __FI        1                      /* Font index 16x24               */
#define __USE_LCD   0


/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
 
int mainFunctionality(void) {
	 int KBD_but, disp_val = 0;
	KBD_Init();
	GLCD_Init();
	GLCD_Clear(White);
	
	for(;;){
		switch(disp_val){
			case 0:
				GLCD_SetBackColor(Blue);
				GLCD_SetTextColor(White);
				GLCD_DisplayString(0, 0, __FI, "   COE718 Project   ");
				GLCD_DisplayString(1, 0, __FI, "    Simrat Gill     ");
				GLCD_DisplayString(2, 0, __FI, "    Media Center    ");
				GLCD_SetBackColor(White);
				GLCD_SetTextColor(Black);
				GLCD_DisplayString(5, 0, __FI, "Photo Gallery       ");
				GLCD_DisplayString(6, 0, __FI, "MP3 Player          ");
				GLCD_DisplayString(7, 0, __FI, "Memory              ");
			  GLCD_DisplayString(8, 0, __FI, "Snake               ");
			break;
			case 1:
				GLCD_SetBackColor(Blue);
				GLCD_SetTextColor(White);
				GLCD_DisplayString(0, 0, __FI, "   COE718 Project   ");
				GLCD_DisplayString(1, 0, __FI, "    Simrat Gill     ");
				GLCD_DisplayString(2, 0, __FI, "    Media Center    ");
				GLCD_SetBackColor(DarkGrey);
				GLCD_SetTextColor(White);
				GLCD_DisplayString(5, 0, __FI, "Photo Gallery       ");
				GLCD_SetBackColor(White);
				GLCD_SetTextColor(Black);
				GLCD_DisplayString(6, 0, __FI, "MP3 Player          ");
				GLCD_DisplayString(7, 0, __FI, "Memory              ");
				GLCD_DisplayString(8, 0, __FI, "Snake               ");
			break;
			case 2:
				GLCD_SetBackColor(Blue);
				GLCD_SetTextColor(White);
				GLCD_DisplayString(0, 0, __FI, "   COE718 Project   ");
				GLCD_DisplayString(1, 0, __FI, "    Simrat Gill     ");
				GLCD_DisplayString(2, 0, __FI, "    Media Center    ");
				GLCD_SetBackColor(White);
				GLCD_SetTextColor(Black);
				GLCD_DisplayString(5, 0, __FI, "Photo Gallery       ");
				GLCD_SetBackColor(DarkGrey);
				GLCD_SetTextColor(White);
				GLCD_DisplayString(6, 0, __FI, "MP3 Player          ");
				GLCD_SetBackColor(White);
				GLCD_SetTextColor(Black);
				GLCD_DisplayString(7, 0, __FI, "Memory              ");
				GLCD_DisplayString(8, 0, __FI, "Snake               ");
			break;
			case 3:
				GLCD_SetBackColor(Blue);
				GLCD_SetTextColor(White);
				GLCD_DisplayString(0, 0, __FI, "   COE718 Project   ");
				GLCD_DisplayString(1, 0, __FI, "    Simrat Gill     ");
				GLCD_DisplayString(2, 0, __FI, "    Media Center    ");
				GLCD_SetBackColor(White);
				GLCD_SetTextColor(Black);
				GLCD_DisplayString(5, 0, __FI, "Photo Gallery       ");
				GLCD_DisplayString(6, 0, __FI, "MP3 Player          ");
				GLCD_SetBackColor(DarkGrey);
				GLCD_SetTextColor(White);
				GLCD_DisplayString(7, 0, __FI, "Memory              ");
				GLCD_SetBackColor(White);
				GLCD_SetTextColor(Black);
				GLCD_DisplayString(8, 0, __FI, "Snake               ");			  
			break;
			case 4:
				GLCD_SetBackColor(Blue);
				GLCD_SetTextColor(White);
				GLCD_DisplayString(0, 0, __FI, "   COE718 Project   ");
				GLCD_DisplayString(1, 0, __FI, "    Simrat Gill     ");
				GLCD_DisplayString(2, 0, __FI, "    Media Center    ");
				GLCD_SetBackColor(White);
				GLCD_SetTextColor(Black);
				GLCD_DisplayString(5, 0, __FI, "Photo Gallery       ");
				GLCD_DisplayString(6, 0, __FI, "MP3 Player          ");
				GLCD_DisplayString(7, 0, __FI, "Memory              ");
				GLCD_SetBackColor(DarkGrey);
				GLCD_SetTextColor(White);
				GLCD_DisplayString(8, 0, __FI, "Snake               ");
			break;
		}
		
		KBD_but = get_button ();
		switch(KBD_but){
			case KBD_SELECT:
				GLCD_Clear(White);
				switch (disp_val){
					case 1:
						photo();
					break;
					case 2:
						MP3();
					break;
					case 3:
						memory();
					case 4:
						snakegame();
					break;
				}
			break;
			case KBD_UP:
				if(disp_val > 1) {
					disp_val--;
				} else{
					disp_val = 4;
				}
			break;
			case KBD_DOWN:
				if(disp_val < 4) {
					disp_val++;
				} else {
					disp_val = 1;
				}
			break;
		}
	}
}
int main (void) {                       /* Main Program                       */
  mainFunctionality();
}
