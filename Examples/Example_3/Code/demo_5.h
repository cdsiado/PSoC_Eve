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
#if !defined(DEMO_5_H)
#define DEMO_5_H
    
/* DEMO 5.
    
    Sketch Demo.
    Similar demo to FTDI sketch demo.
*/    
    
/* Possible events from this demo. Demo 0. */
typedef enum { D5_NONE, D5_EXIT = 205 } DEMO_5_EVENTS;

/* *** Function prototypes. ***************************************************
*/
void* Demo_5_Start(void (*touchcallback)(DEMO_5_EVENTS event), void (**closefunction)());
    
#endif /* End DEMO_5_H */    

/* [] END OF FILE */