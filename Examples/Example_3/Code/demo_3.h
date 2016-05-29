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
#if !defined(DEMO_3_H)
#define DEMO_3_H
    
/* DEMO 3.
    Play sounds.
    Ref: FTDI AN-276 FT800 Audio File Conversion
*/    
    
/* Possible events from this demo. Demo 0. */
typedef enum { D3_NONE, D3_BTN_EXIT = 203 } DEMO_3_EVENTS;

/* *** Function prototypes. ***************************************************
*/
void* Demo_3_Start(void (*touchcallback)(DEMO_3_EVENTS button), void (**closefunction)());
    
#endif /* End DEMO_3_H */    

/* [] END OF FILE */