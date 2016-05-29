/*******************************************************************************
* File Name: Demos_Resources.h  
* Version 0.1 Alpha
*
* Description:
*  This file belongs to the PSoCEve library project.
*  Used for testing features of PSocEve library during development.
*  It contains some resources such as graphics and sounds.
*
* Note:
*
********************************************************************************
* Copyright (c) 2015 Jesús Rodríguez Cacabelos
* This library is dual licensed under the MIT and GPL licenses.
* http:
*******************************************************************************/

#if !defined(DEMOS_RESOURCES_H) /* Pins SPI_EVE_miso_s_H */
#define DEMOS_RESOURCES_H
    
#include <cytypes.h>    
    
#define SETFONT
//#define SETFONT_2
//#define SETFONT_NOTEXT
//#define SETFONT_2_NOTEXT    

/* Digits data taken from FTDI gauges example.  */
extern const uint8 font_setfont2[8413];
extern const uint8 font_setfont[8413];

#endif /* End DEMOS_RESOURCES_H */

/* [] END OF FILE */
