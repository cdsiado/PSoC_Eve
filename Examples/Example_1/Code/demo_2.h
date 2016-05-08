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
#if !defined(DEMO_2_H)
#define DEMO_2_H
    
/* DEMO 2.
    Testing more primitives.
*/    
    
/* Possible events from this demo. Demo 0. */
typedef enum { D2_NONE, D2_BTN_EXIT = 202 } DEMO_2_EVENTS;

/* *** Function prototypes. ***************************************************
*/
void* Demo_2_Start(void (*touchcallback)(DEMO_2_EVENTS button), void (**closefunction)());
    
#endif /* End DEMO_2_H */    

/* [] END OF FILE */