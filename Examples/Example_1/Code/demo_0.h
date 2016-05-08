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
#if !defined(DEMO_0_H)
#define DEMO_0_H
    
/* DEMO 0.
    This is the access point to several other demo screens.
    Here, we show several buttons and messages to access to other demo screens.
    
    - Demo_0_Start function initializes de display and send to the main program a 
                   pointer to the loop function.
                   This demo don´t have a close function, so; for close function
                   sends a 0 pointer to the main program.
    - Demo_0_Loop is continually called by the main program loop. 
                  In loop function, the only thing we do is to check if  
                  a button was pressed and then we call the callback function
                  in main program with the value of the pressed button.
                   
    
    Every button in the screen will have its own event.
*/    
    
/* Possible events from this demo. Demo 0. */
typedef enum { D0_NONE, D0_BTN_DEMO_1 = 1, D0_BTN_DEMO_2 = 2, D0_BTN_DEMO_3 = 3,
    D0_BTN_DEMO_4 = 4 } DEMO_0_EVENTS;

/* *** Function prototypes. ***************************************************
*/
void* Demo_0_Start(void (*touchcallback)(DEMO_0_EVENTS button), void (**closefunction)());
    
#endif /* End DEMO_0_H */    

/* [] END OF FILE */

