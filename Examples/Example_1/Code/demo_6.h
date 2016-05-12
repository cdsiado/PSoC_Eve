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
#if !defined(DEMO_6_H)
#define DEMO_6_H
    
/* DEMO 6.
    
    Showing some widgets.
    Without touch.
*/    
    
/* Possible events from this demo. Demo 6. */
typedef enum { D6_NONE, D6_BTN_EXIT = 216 } DEMO_6_EVENTS;

/* *** Function prototypes. ***************************************************
*/
void* Demo_6_Start(void (*touchcallback)(DEMO_6_EVENTS event), void (**closefunction)());
    
#endif /* End DEMO_6_H */    

/* [] END OF FILE */