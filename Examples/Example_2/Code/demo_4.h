/*******************************************************************************
* Description:
*  This file belongs to the PSoCEve library project.
*  Used for testing features of PSocEve library during development.
*
* Note:
*
********************************************************************************
* Copyright (c) 2015, 2016 Jesús Rodríguez Cacabelos
* This library is dual licensed under the MIT and GPL licenses.
* http:
*******************************************************************************/
#if !defined(DEMO_4_H)
#define DEMO_4_H
    
/* DEMO 4.
    
    First, the demo plays the FTDI logo.
    Then shows the screen saver with a moving bitmap.
    To exit, you have to touch the moving bitmap. 
    Then, the screen is cleared, and the spinner is shown during 5 seconds before to return 
    to main menu.
        ¡¡¡ Catch the bitmap !!!
*/    
    
/* Possible events from this demo. Demo 0. */
typedef enum { D4_NONE, D4_EXIT = 204 } DEMO_4_EVENTS;

/* *** Function prototypes. ***************************************************
*/
void* Demo_4_Start(void (*touchcallback)(DEMO_4_EVENTS event), void (**closefunction)());
    
#endif /* End DEMO_4_H */    

/* [] END OF FILE */