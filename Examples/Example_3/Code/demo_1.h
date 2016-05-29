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
#if !defined(DEMO_1_H)
#define DEMO_1_H
    
/* DEMO 1.
    Testing loading of images.
    LOADIMAGE doesn´t work on FT800
*/    
    
/* Possible events from this demo. Demo 0. */
typedef enum { D1_NONE, D1_BTN_EXIT = 201, D1_BTN_NEXT = 202 } DEMO_1_EVENTS;

/* *** Function prototypes. ***************************************************
*/
void* Demo_1_Start(void (*touchcallback)(DEMO_1_EVENTS button), void (**closefunction)());
    
#endif /* End DEMO_1_H */    

/* [] END OF FILE */