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
#if !defined(DEMO_12_H)
#define DEMO_12_H
    
/* DEMO 12.
    
    Testing macro & append.
*/    
    
/* Possible events from this demo. Demo 12. */
typedef enum { D12_NONE, D12_EXIT = 212 } DEMO_12_EVENTS;

/* *** Function prototypes. ***************************************************
*/
void* Demo_12_Start(void (*touchcallback)(DEMO_12_EVENTS event), void (**closefunction)());
    
#endif /* End DEMO_4_H */    

/* [] END OF FILE */