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
#if !defined(DEMO_9_H)
#define DEMO_9_H
    
/* DEMO 9.
    Bitmaps transformations.
*/    
    
/* Possible events from this demo. Demo 0. */
typedef enum { D9_NONE, D9_BTN_EXIT = 219 } DEMO_9_EVENTS;

/* *** Function prototypes. ***************************************************
*/
void* Demo_9_Start(void (*touchcallback)(DEMO_9_EVENTS button), void (**closefunction)());
    
#endif /* End DEMO_9_H */    

/* [] END OF FILE */