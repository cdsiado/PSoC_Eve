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
#if !defined(DEMO_8_H)
#define DEMO_8_H
    
/* DEMO 8.
    Testing bitmaps.
*/    
    
/* Possible events from this demo. Demo 8. */
typedef enum { D8_NONE, D8_BTN_EXIT = 218 } DEMO_8_EVENTS;

/* *** Function prototypes. ***************************************************
*/
void* Demo_8_Start(void (*touchcallback)(DEMO_8_EVENTS event), void (**closefunction)());
    
#endif /* End DEMO_8_H */    

/* [] END OF FILE */