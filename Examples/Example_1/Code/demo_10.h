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
#if !defined(DEMO_10_H)
#define DEMO_10_H
    
/* DEMO 10.
    Rotating screen.
*/    
    
/* Possible events from this demo. Demo 10. */
typedef enum { D10_NONE, D10_BTN_EXIT = 210 } DEMO_10_EVENTS;

/* *** Function prototypes. ***************************************************
*/
void* Demo_10_Start(void (*touchcallback)(DEMO_10_EVENTS button), void (**closefunction)());
    
#endif /* End DEMO_10_H */    

/* [] END OF FILE */