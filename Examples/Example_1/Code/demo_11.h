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
#if !defined(DEMO_11_H)
#define DEMO_11_H
    
/* DEMO 11.
    Testing several features.
*/    
    
/* Possible events from this demo. Demo 11. */
typedef enum { D11_NONE, D11_BTN_EXIT = 211 } DEMO_11_EVENTS;

/* *** Function prototypes. ***************************************************
*/
void* Demo_11_Start(void (*touchcallback)(DEMO_11_EVENTS button), void (**closefunction)());
    
#endif /* End DEMO_11_H */    

/* [] END OF FILE */