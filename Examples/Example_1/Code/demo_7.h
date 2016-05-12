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
#if !defined(DEMO_7_H)
#define DEMO_7_H
    
/* DEMO 7.
    
*/    
    
/* Possible events from this demo. Demo 6. */
typedef enum { D7_NONE, D7_BTN_EXIT = 217 } DEMO_7_EVENTS;

/* *** Function prototypes. ***************************************************
*/
void* Demo_7_Start(void (*touchcallback)(DEMO_7_EVENTS event), void (**closefunction)());
    
#endif /* End DEMO_7_H */    

/* [] END OF FILE */