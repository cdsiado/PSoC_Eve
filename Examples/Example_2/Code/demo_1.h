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
    Testing some primitives.
    
    Here we use DLVertexFormat wich change the way DLVertex2F uses the numeric data.
    Remember!!! By default, when FT chip is turned on, format of DLVertex2F is 1/16 of a pixel.
    In this demo, we use DLVertexFormat to change this. Here, format of DLVertes2F is 1/1 of pixel.
    
    DLVertexFormat is a native command only for FT810. But it is implemented as software in 
    PSoC_Eve_Library, so it can be used with FT800 chip.
*/    
    
/* Possible events from this demo. Demo 0. */
typedef enum { D1_NONE, D1_BTN_EXIT = 201 } DEMO_1_EVENTS;

/* *** Function prototypes. ***************************************************
*/
void* Demo_1_Start(void (*touchcallback)(DEMO_1_EVENTS button), void (**closefunction)());
    
#endif /* End DEMO_1_H */    

/* [] END OF FILE */